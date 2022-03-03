#include <iostream>
#include <vector>
#include <map>
#include <httplib.h>
#include <json.hpp>
#include <sqlite3.h>
#include "schemas.h"
#include <iterator>
#include <algorithm>

typedef std::vector<std::vector<std::string>> table_type;
typedef std::map<std::string, table_type> map_table_type;

static int select_data(const char *s, std::string &sql, table_type *table);

table_type getList(map_table_type *l, const std::string& c)
{
    return (*l)[c];
}

std::vector<std::string> getSelectStatements(const char *db, const string &param)
{
    std::vector<std::string> selectStatements = getSqlSelectStatementsByParam(param);
    if (selectStatements.empty()) throw std::runtime_error("There is no data.");

    return selectStatements;
}

std::vector<std::string> parseRow(std::string s)
{
    std::vector<std::string> fields {""};
    std::string f;
    size_t i = 0;

    for(char c: s)
    {
        switch (c) {
            case '\r':
                i++;
                break;
            case ';':
                fields.emplace_back("");
                i++;
                break;
            default:
                fields[i].push_back(c);
        }
    }
    return fields;
}

table_type readCsv(const std::string& filename)
{
    std::fstream ifs;
    ifs.open("csv/" + filename);
    if (!ifs)
        throw std::runtime_error("couldn't open file");

    table_type data;
    std::string s;
    int i = 0;

    while(std::getline(ifs, s))
    {
        i++;
        if (i <= 1) continue;
        auto fields = parseRow(s);
        data.push_back(fields);
    }

    ifs.close();

    return data;
}
// retrieve contents of database used by selectData()
/* argc: holds the number of results, azColName: holds each column returned in array, argv: holds each value in array */
static int callback(void *ptr, int argc, char **argv, char **azColName)
{
    int i;
    table_type *table = static_cast<table_type*>(ptr);
    std::vector<std::string> row;

    for (i = 0; i < argc; i++)
    {
        row.emplace_back(argv[i] ? argv[i] : "NULL");
        std::cout << azColName[i] << " = " << (argv[i] ? argv[i] : "NULL") << std::endl;
    }
    std::cout << "\n";
    table->emplace_back(row);

    return 0;
}

static int create_db(const char *s)
{
    sqlite3 *db;
    int rc = sqlite3_open(s, &db);

    if (rc)
        std::cout << "Can't open database: " << sqlite3_errmsg(db) << std::endl;
    else
        std::cout << "Opened database successfully!" << std::endl;

    sqlite3_close(db);

    return 0;
}

static int create_table(const char *s, std::vector<std::string> &tables)
{
    sqlite3 *db;
    int rc = sqlite3_open(s, &db);
    char *zErrMsg;

    for(const std::string& t: tables)
    {
        rc = sqlite3_exec(db, t.c_str(), callback, nullptr, &zErrMsg);

        if (rc != SQLITE_OK) {
            std::cerr << "SQL Error: " << zErrMsg << std::endl;
            sqlite3_free(zErrMsg);
        } else {
            std::cout << "Table created successfully!" << std::endl;
        }
    }

    return 0;
}

static int insert_data(const char *s, std::string &sql)
{
    sqlite3 *db;
    int rc = sqlite3_open(s, &db);
    char *zErrMsg;

    rc = sqlite3_exec(db, sql.c_str(), callback, nullptr, &zErrMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL Error: " << zErrMsg << ": " << sql << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Records created successfully!" << std::endl;
    }

    return 0;
}

static int select_data(const char *s, std::string &sql, table_type *table)
{
    sqlite3 *db;
    int rc = sqlite3_open(s, &db);
    char *zErrMsg;

    rc = sqlite3_exec(db, sql.c_str(), callback, table, &zErrMsg);

    if (rc != SQLITE_OK) {
        std::cerr << "SQL Error: " << zErrMsg << ": " << sql << std::endl;
        sqlite3_free(zErrMsg);
    } else {
        std::cout << "Operation done successfully!" << std::endl;
    }

    return 0;
}

void prepareDataAndInsertToDb(const char *db, std::vector<std::string> &categories, map_table_type *list)
{
    for(const std::string& s: categories)
    {
        table_type c = getList(list, s);
        string sql_statement;

        for(std::vector<std::string>row: c)
        {
            std::ostringstream oss;
            sql_statement = getSqlInsertStatement(s);
            sql_statement += " VALUES (";

            for(std::string &row_s: row) {
                if (row_s.empty()) row_s = "NULL";
                else row_s = "\"" + row_s.append("\"");
            }

            std::copy(row.begin(), row.end()-1, std::ostream_iterator<std::string>(oss, ","));

            oss << row.back();
            sql_statement += oss.str();
            sql_statement += ");";
            insert_data(db, sql_statement);
            std::cout << sql_statement << endl;
        }
    }
}

int main(int argc, char *argv[]) {
    httplib::Server svr;
    const char *db_name = "geostats.db";

    create_db(db_name);

    std::vector<std::string> tables = getCreateTableQuery();
    create_table(db_name, tables);

    table_type
    data;
    map_table_type list;

    std::vector<std::string> categories = getCategories();
    for(const std::string& category: categories)
    {
        std::string filename = category + ".csv";

        try {
            data = readCsv(filename);
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }

        list.insert({ category, data });
    }

    prepareDataAndInsertToDb(db_name, categories, &list);

    svr.Get(R"(/(\w+))", [&](const httplib::Request& req, httplib::Response& res) {
        std::string param = req.matches[1];
        std::vector<std::string> queryGroups = getSelectStatements(db_name, param);

        map_table_type selectList {};

        for(const std::string &s: queryGroups) {
            table_type table;
            std::string query = getSqlSelectStatement(s);
            select_data(db_name, query, &table);
            selectList.insert({ s, table });
        }

        nlohmann::json from_map(selectList);
//        nlohmann::json from_array(table);

        if (selectList.empty())
            res.set_content("404 Not found", "text/plain");
        else
            res.set_content(from_map.dump(), "application/json");
    });

    svr.listen("0.0.0.0", 8080);
//    return 0;
}

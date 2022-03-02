#include <iostream>
#include <vector>
#include <map>
#include <httplib.h>
#include <json.hpp>
#include <sqlite3.h>
#include "schemas.h"
#include <iterator>
#include <algorithm>

std::vector<std::vector<std::string>> getList(std::map<std::string, std::vector<std::vector<std::string>>> l, const std::string& c)
{
    return l[c];
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

std::vector<std::vector<std::string>> readCsv(const std::string& filename)
{
    std::fstream ifs;
    ifs.open("csv/" + filename);
    if (!ifs)
        throw std::runtime_error("couldn't open file");

    std::vector<std::vector<std::string>> data;
    std::string s;
    int i = 0;
//    std::istringstream ss;

    while(std::getline(ifs, s))
    {
//        std::cout << "Tohle je s: " << s << std::endl;
        i++;
        if (i <= 1) continue;
        auto fields = parseRow(s);
//        for(std::string s: fields)
//            std::cout << s << " - " << std::endl;
        data.push_back(fields);
    }

    ifs.close();

    return data;
}

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
    int i;
    for (i = 0; i < argc; i++)
    {
        std::cout << azColName[i] << " = " << argv[i] ? argv[i] : "NULL";
    }
    std::cout << "\n";

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

int main(int argc, char *argv[]) {
    httplib::Server svr;
    sqlite3 *db;
    char *zErrMsg;
    int rc;
    const char *db_name = "geostats.db";

    vector<string> categories = getCategories();
    vector<string> tables = getCreateTableQuery();

    create_db(db_name);
    create_table(db_name, tables);

    if (argc < 2)
        throw std::runtime_error("no filename entered");

    int i = 1;
    std::string filename;
    std::string category;
    std::vector<std::vector<std::string>> data;
    std::map<std::string, std::vector<std::vector<std::string>>> list;

    while(argv[i])
    {
        filename = argv[i];
        category = filename.substr(0, filename.find('.'));

        try {
            data = readCsv(filename);
        }
        catch(std::exception &e)
        {
            std::cout << e.what() << std::endl;
        }

        list.insert({ category, data });
        i++;
    }

    // insert data
    for(const std::string& s: categories)
    {
        std::vector<std::vector<std::string>> c = getList(list, s);
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
            insert_data(db_name, sql_statement);
            std::cout << sql_statement << endl;
        }
    }

    svr.Get(R"(/(\w+))", [&](const httplib::Request& req, httplib::Response& res) {
        category = req.matches[1];
        std::vector<std::vector<std::string>> result = getList(list, category);
        nlohmann::json from_map(list);
        nlohmann::json from_array(result);

        if (result.empty())
            res.set_content("404 Not found", "text/plain");
        else
            res.set_content(from_array.dump(), "application/json");
    });

    svr.listen("0.0.0.0", 8080);
//    return 0;
}

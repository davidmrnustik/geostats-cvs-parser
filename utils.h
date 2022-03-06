//
// Created by David Mrnustik on 6/3/22.
//

#ifndef GEOSTATS_CVS_PARSER_UTILS_H
#define GEOSTATS_CVS_PARSER_UTILS_H

#include <vector>
#include <string>
#include <map>

typedef std::vector<std::vector<std::string>> table_type;
typedef std::map<std::string, table_type> map_table_type;

table_type getList(map_table_type *l, const std::string& c);

#endif //GEOSTATS_CVS_PARSER_UTILS_H

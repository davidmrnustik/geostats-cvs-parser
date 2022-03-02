//
// Created by David Mrnustik on 1/3/22.
//

#ifndef GEOSTATS_CVS_PARSER_SCHEMAS_H
#define GEOSTATS_CVS_PARSER_SCHEMAS_H

#include <string>
#include <vector>
#include <map>

using namespace std;

string getSqlInsertStatement(const string& s) {
    map<string, string> list {
        {"capitals", "INSERT INTO capitals (city,country,continent,population,latitude,elevation)"},
        {"cities",   "INSERT INTO cities (city,district,country,continent,population_year,population,urban_area_year,urban_area_name,urban_area,density)"},
        {"coal",   "INSERT INTO coal (country,continent,production)"},
        {"continents",   "INSERT INTO continents (continent,total_land_area,land_area,earth_total_surface,shoreline,population,population_p,density,countries)"},
        {"countries",   "INSERT INTO countries (country,continent,area,eu)"},
        {"currents",   "INSERT INTO currents (current,ocean,volume,current_width,speed)"},
        {"gulfs",   "INSERT INTO gulfs (gulf,ocean,area)"},
        {"mountains",   "INSERT INTO mountains (mountain,country,continent,height)"},
        {"oceans",   "INSERT INTO oceans (ocean,total_area,volume,average_depth,deepest_point_name,deepest_point_location,deepest_point_depth)"},
        {"oil",   "INSERT INTO oil (country,continent,barrels)"},
        {"straits",   "INSERT INTO straits (strait,ocean,length,width)"},
        {"weather",   "INSERT INTO weather (place,country,continent,temperature,temperature_date,precipitation)"}
    };
    return list[s];
}

vector<string> getCategories() {
    return {
        "capitals",
        "cities",
        "weather",
        "straits",
        "mountains",
        "oceans",
        "oil",
        "currents",
        "gulfs",
        "continents",
        "countries",
        "coal"
    };
}

vector<string> getCreateTableQuery() {
    return {
        "CREATE TABLE capitals("\
        "id integer primary key autoincrement," \
        "city string," \
        "country string," \
        "continent string," \
        "population string," \
        "latitude string," \
        "elevation string);",
        "CREATE TABLE cities("\
        "id integer primary key autoincrement," \
        "city string," \
        "district string," \
        "country string," \
        "continent string," \
        "population_year string," \
        "population string," \
        "urban_area_year string," \
        "urban_area_name string," \
        "urban_area string," \
        "density string);",
        "CREATE TABLE coal("\
        "id integer primary key autoincrement," \
        "country string," \
        "continent string," \
        "production string);",
        "CREATE TABLE continents("\
        "id integer primary key autoincrement," \
        "continent string," \
        "total_land_area string," \
        "land_area string," \
        "earth_total_surface string," \
        "shoreline string," \
        "population string," \
        "population_p string," \
        "density string," \
        "countries string);",
        "CREATE TABLE countries("\
        "id integer primary key autoincrement," \
        "country string," \
        "continent string," \
        "area string," \
        "eu string);",
        "CREATE TABLE currents("\
        "id integer primary key autoincrement," \
        "current string," \
        "ocean string," \
        "volume string," \
        "current_width string," \
        "speed string);",
        "CREATE TABLE gulfs("\
        "id integer primary key autoincrement," \
        "gulf string," \
        "ocean string," \
        "area string);",
        "CREATE TABLE mountains("\
        "id integer primary key autoincrement," \
        "mountain string," \
        "country string," \
        "continent string," \
        "height string);",
        "CREATE TABLE oceans("\
        "id integer primary key autoincrement," \
        "ocean string," \
        "total_area string," \
        "volume string," \
        "average_depth string," \
        "deepest_point_name string," \
        "deepest_point_location string," \
        "deepest_point_depth string);",
        "CREATE TABLE oil("\
        "id integer primary key autoincrement," \
        "country string," \
        "continent string," \
        "barrels string);",
        "CREATE TABLE straits("\
        "id integer primary key autoincrement," \
        "strait string," \
        "ocean string," \
        "length string," \
        "width string);",
        "CREATE TABLE weather("\
        "id integer primary key autoincrement," \
        "place string," \
        "country string," \
        "continent string," \
        "temperature string," \
        "temperature_date string," \
        "precipitation string);"
    };
}

#endif //GEOSTATS_CVS_PARSER_SCHEMAS_H

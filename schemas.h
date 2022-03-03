//
// Created by David Mrnustik on 1/3/22.
//

#ifndef GEOSTATS_CVS_PARSER_SCHEMAS_H
#define GEOSTATS_CVS_PARSER_SCHEMAS_H

#include <string>
#include <vector>
#include <map>

using namespace std;

vector<string> getSqlSelectStatementsByParam(const string &c) {
    map<string, vector<string>> list {
        {
            "europe", {
                "largest_countries_europe",
                "highest_mountains_europe_kuma",
                "highest_mountains_europe",
                "precipitation_europe",
                "largest_eu_countries_europe",
                "lowest_point_europe",
                "temperature_europe",
                "largest_cities_europe",
                "capitals_europe",
                "largest_urban_areas_europe",
                "continent_europe"
            }
        },
        {
            "asia", {
                "precipitation_asia",
                "largest_countries_asia",
                "temperature_asia",
                "highest_mountains_asia",
                "lowest_point_asia",
                "continent_asia",
                "capitals_asia",
                "largest_cities_asia",
                "largest_urban_areas_asia"
            }
        },
        {
            "africa", {
                "highest_mountains_africa",
                "largest_countries_africa",
                "temperature_africa",
                "precipitation_africa",
                "lowest_point_africa",
                "largest_cities_africa",
                "largest_urban_areas_africa",
                "continent_africa",
                "capitals_africa"
            }
        },
        {
            "north_america", {
                "continent_namerica",
                "largest_urban_areas_namerica",
                "capitals_namerica",
                "largest_cities_namerica",
                "precipitation_namerica",
                "temperature_namerica",
                "largest_countries_namerica",
                "highest_mountains_namerica",
                "lowest_point_namerica"
            }
        },
        {
            "south_america", {
                "temperature_samerica",
                "precipitation_samerica",
                "lowest_point_samerica",
                "highest_mountains_samerica",
                "largest_countries_samerica",
                "largest_urban_areas_samerica",
                "continent_samerica",
                "capitals_samerica",
                "largest_cities_samerica"
            }
        },
        {
            "oceania", {
                "temperature_oceania",
                "highest_mountains_oceania",
                "largest_countries_oceania",
                "highest_mountains_oceania_aus",
                "precipitation_oceania",
                "lowest_point_oceania",
                "capitals_oceania",
                "largest_cities_oceania",
                "largest_urban_areas_oceania",
                "continent_oceania"
            }
        },
        {
            "antarctica", {
                "precipitation_antarctica",
                "lowest_point_antarctica",
                "temperature_antarctica",
                "highest_mountains_antarctica",
                "continent_antarctica"
            }
        },
        {
            "indian_ocean", {
                "currents_indian",
                "straits_indian",
                "gulfs_indian",
                "ocean_indian"
            }
        },
        {
            "atlantic_ocean", {
                "currents_atlantic",
                "straits_atlantic",
                "ocean_atlantic",
                "gulfs_atlantic"
            }
        },
        {
            "arctic_ocean", {
                "straits_arctic",
                "currents_arctic",
                "gulfs_arctic",
                "ocean_arctic"
            }
        },
        {
            "pacific_ocean", {
                "straits_pacific",
                "currents_pacific",
                "ocean_pacific",
                "gulfs_pacific"
            }
        },
        {
            "southern_ocean", {
                "ocean_southern"
            }
        },
        {
            "physical_geography", {
                "highest_mountains"
            }
        },
        {
            "political_urban_geography", {
                "largest_countries"
            }
        },
        {
            "economic_geography", {
                "total_primary_coal_production",
                "total_oil_supply"
            }
        },
        {
            "indicators", {
                "largest_countries",
                "highest_mountains",
                "total_primary_coal_production",
                "total_oil_supply"
            }
        }
    };
    return list[c];
}

string getSqlSelectStatement(const string &s) {
    map<string, string> list {
        { "largest_countries_europe", "select country, area from countries where continent = 'Europe' ORDER BY area DESC LIMIT 10" },
        { "highest_mountains_europe_kuma", "select mountain, height from mountains where continent = 'Europe' AND height <= 4810 ORDER BY height DESC LIMIT 5" },
        { "highest_mountains_europe", "select mountain, height from mountains where continent = 'Europe' ORDER BY height DESC LIMIT 5" },
        { "precipitation_europe", "select place, country, precipitation from weather where (continent = 'Europe' and temperature is null) order by precipitation desc" },
        { "largest_eu_countries_europe", "select country, area from countries where continent = 'Europe' AND eu = 1 ORDER BY area DESC LIMIT 10" },
        { "lowest_point_europe", "select mountain, height from mountains where continent = 'Europe' ORDER BY height ASC LIMIT 1" },
        { "temperature_europe", "select place, country, temperature, temperature_date from weather where (continent = 'Europe' and precipitation is null) order by temperature desc" },
        { "largest_cities_europe", "select city, population_year, population from cities where continent = 'Europe' ORDER BY population DESC LIMIT 10" },
        { "capitals_europe", "select city, population, latitude, elevation from capitals where continent = 'Europe'" },
        { "largest_urban_areas_europe", "select city, urban_area_name, urban_area_year, urban_area, density from cities where continent = 'Europe' ORDER BY urban_area DESC LIMIT 10" },
        { "continent_europe", "select total_land_area, land_area, earth_total_surface, shoreline from continents where continent = 'Europe'" },
        { "precipitation_asia", "select place, country, precipitation from weather where (continent = 'Asia' and temperature is null) order by precipitation desc" },
        { "largest_countries_asia", "select country, area from countries where continent = 'Asia' ORDER BY area DESC" },
        { "temperature_asia", "select place, country, temperature, temperature_date from weather where (continent = 'Asia' and precipitation is null) order by temperature desc" },
        { "highest_mountains_asia", "select mountain, height from mountains where continent = 'Asia' ORDER BY height DESC LIMIT 5" },
        { "lowest_point_asia", "select mountain, height from mountains where continent = 'Asia' ORDER BY height ASC LIMIT 1" },
        { "continent_asia", "select total_land_area, land_area, earth_total_surface, shoreline from continents where continent = 'Asia'" },
        { "capitals_asia", "select city, population, latitude, elevation from capitals where continent = 'Asia'" },
        { "largest_cities_asia", "select city, population_year, population from cities where continent = 'Asia' ORDER BY population DESC LIMIT 10" },
        { "largest_urban_areas_asia", "select city, urban_area_name, urban_area_year, urban_area, density from cities where continent = 'Asia' ORDER BY urban_area DESC LIMIT 10" },
        { "highest_mountains_africa", "select mountain, height from mountains where continent = 'Africa' ORDER BY height DESC LIMIT 5" },
        { "largest_countries_africa", "select country, area from countries where continent = 'Africa' ORDER BY area DESC" },
        { "temperature_africa", "select place, country, temperature, temperature_date from weather where (continent = 'Africa' and precipitation is null) order by temperature desc" },
        { "precipitation_africa", "select place, country, precipitation from weather where (continent = 'Africa' and temperature is null) order by precipitation desc" },
        { "lowest_point_africa", "select mountain, height from mountains where continent = 'Africa' ORDER BY height ASC LIMIT 1" },
        { "largest_cities_africa", "select city, population_year, population from cities where continent = 'Africa' ORDER BY population DESC LIMIT 10" },
        { "largest_urban_areas_africa", "select city, urban_area_name, urban_area_year, urban_area, density from cities where continent = 'Africa' ORDER BY urban_area DESC LIMIT 10" },
        { "continent_africa", "select total_land_area, land_area, earth_total_surface, shoreline from continents where continent = 'Africa'" },
        { "capitals_africa", "select city, population, latitude, elevation from capitals where continent = 'Africa'" },
        { "continent_namerica", "select total_land_area, land_area, earth_total_surface, shoreline from continents where continent = 'North America'" },
        { "largest_urban_areas_namerica", "select city, urban_area_name, urban_area_year, urban_area, density from cities where continent = 'North America' ORDER BY urban_area DESC LIMIT 10" },
        { "capitals_namerica", "select city, population, latitude, elevation from capitals where continent = 'North America'" },
        { "largest_cities_namerica", "select city, population_year, population from cities where continent = 'North America' ORDER BY population DESC LIMIT 10" },
        { "precipitation_namerica", "select place, country, precipitation from weather where (continent = 'North America' and temperature is null) order by precipitation desc" },
        { "temperature_namerica", "select place, country, temperature, temperature_date from weather where (continent = 'North America' and precipitation is null) order by temperature desc" },
        { "largest_countries_namerica", "select country, area from countries where continent = 'North America' ORDER BY area DESC" },
        { "highest_mountains_namerica", "select mountain, height from mountains where continent = 'North America' ORDER BY height DESC LIMIT 5" },
        { "lowest_point_namerica", "select mountain, height from mountains where continent = 'North America' ORDER BY height ASC LIMIT 1" },
        { "temperature_samerica", "select place, country, temperature, temperature_date from weather where (continent = 'South America' and precipitation is null) order by temperature desc" },
        { "precipitation_samerica", "select place, country, precipitation from weather where (continent = 'South America' and temperature is null) order by precipitation desc" },
        { "lowest_point_samerica", "select mountain, height from mountains where continent = 'South America' ORDER BY height ASC LIMIT 1" },
        { "highest_mountains_samerica", "select mountain, height from mountains where continent = 'South America' ORDER BY height DESC LIMIT 5" },
        { "largest_countries_samerica", "select country, area from countries where continent = 'South America' ORDER BY area DESC" },
        { "largest_urban_areas_samerica", "select city, urban_area_name, urban_area_year, urban_area, density from cities where continent = 'South America' ORDER BY urban_area DESC LIMIT 10" },
        { "continent_samerica", "select total_land_area, land_area, earth_total_surface, shoreline from continents where continent = 'South America'" },
        { "capitals_samerica", "select city, population, latitude, elevation from capitals where continent = 'South America'" },
        { "largest_cities_samerica", "select city, population_year, population from cities where continent = 'South America' ORDER BY population DESC LIMIT 10" },
        { "temperature_oceania", "select place, country, temperature, temperature_date from weather where (continent = 'Oceania' and precipitation is null) order by temperature desc" },
        { "highest_mountains_oceania", "select mountain, height from mountains where continent = 'Oceania' ORDER BY height DESC LIMIT 5" },
        { "largest_countries_oceania", "select country, area from countries where continent = 'Oceania' ORDER BY area DESC" },
        { "highest_mountains_oceania_aus", "select mountain, height from mountains where continent = 'Oceania' AND country = 'Australia' ORDER BY height DESC LIMIT 5" },
        { "precipitation_oceania", "select place, country, precipitation from weather where (continent = 'Oceania' and temperature is null) order by precipitation desc" },
        { "lowest_point_oceania", "select mountain, height from mountains where continent = 'Oceania' ORDER BY height ASC LIMIT 1" },
        { "capitals_oceania", "select city, population, latitude, elevation from capitals where continent = 'Oceania' ORDER BY population DESC, latitude DESC" },
        { "largest_cities_oceania", "select city, district, population_year, population from cities where continent = 'Oceania' ORDER BY population DESC LIMIT 10" },
        { "largest_urban_areas_oceania", "select city, urban_area_name, urban_area_year, urban_area, density from cities where continent = 'Oceania' ORDER BY urban_area DESC LIMIT 10" },
        { "continent_oceania", "select total_land_area, land_area, earth_total_surface, shoreline from continents where continent = 'Oceania'" },
        { "precipitation_antarctica", "select place, country, precipitation from weather where (continent = 'Antarctica' and temperature is null) order by precipitation desc" },
        { "lowest_point_antarctica", "select mountain, height from mountains where continent = 'Antarctica' ORDER BY height ASC LIMIT 1" },
        { "temperature_antarctica", "select place, country, temperature, temperature_date from weather where (continent = 'Antarctica' and precipitation is null) order by temperature desc" },
        { "highest_mountains_antarctica", "select mountain, height from mountains where continent = 'Antarctica' ORDER BY height DESC LIMIT 5" },
        { "continent_antarctica", "select total_land_area, land_area, earth_total_surface, shoreline from continents where continent = 'Antarctica'" },
        { "currents_indian", "select current, volume, current_width, speed from currents where ocean = 'Indian Ocean'" },
        { "straits_indian", "select strait, length, width from straits where ocean = 'Indian Ocean'" },
        { "gulfs_indian", "select gulf, area from gulfs where ocean = 'Indian Ocean'" },
        { "ocean_indian", "select total_area, volume, average_depth, deepest_point_name, deepest_point_location, deepest_point_depth from oceans where ocean = 'Indian Ocean'" },
        { "currents_atlantic", "select current, volume, current_width, speed from currents where ocean = 'Atlantic Ocean'" },
        { "straits_atlantic", "select strait, length, width from straits where ocean = 'Atlantic Ocean'" },
        { "ocean_atlantic", "select total_area, volume, average_depth, deepest_point_name, deepest_point_location, deepest_point_depth from oceans where ocean = 'Atlantic Ocean'" },
        { "gulfs_atlantic", "select gulf, area from gulfs where ocean = 'Atlantic Ocean'" },
        { "straits_arctic", "select strait, length, width from straits where ocean = 'Arctic Ocean'" },
        { "currents_arctic", "select current, volume, current_width, speed from currents where ocean = 'Arctic Ocean'" },
        { "gulfs_arctic", "select gulf, area from gulfs where ocean = 'Arctic Ocean'" },
        { "ocean_arctic", "select total_area, volume, average_depth, deepest_point_name, deepest_point_location, deepest_point_depth from oceans where ocean = 'Arctic Ocean'" },
        { "straits_pacific", "select strait, length, width from straits where ocean = 'Pacific Ocean'" },
        { "currents_pacific", "select total_area, volume, average_depth, deepest_point_name, deepest_point_location, deepest_point_depth from oceans where ocean = 'Pacific Ocean'" },
        { "ocean_pacific", "select total_area, volume, average_depth, deepest_point_name, deepest_point_location, deepest_point_depth from oceans where ocean = 'Pacific Ocean'" },
        { "gulfs_pacific", "select gulf, area from gulfs where ocean = 'Pacific Ocean'" },
        { "ocean_southern", "select total_area, volume, average_depth, deepest_point_name, deepest_point_location, deepest_point_depth from oceans where ocean = 'Southern Ocean'" },
        { "highest_mountains", "select mountain, height from mountains ORDER BY height DESC LIMIT 20" },
        { "largest_countries", "select distinct country, area from countries ORDER BY area DESC LIMIT 20" },
        { "total_primary_coal_production", "select country, production from coal where production > 0 ORDER BY production DESC" },
        { "total_oil_supply", "select country, barrels from oil where barrels IS NOT null ORDER BY barrels DESC" }
    };
    return list[s];
}

string getSqlInsertStatement(const string &s) {
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

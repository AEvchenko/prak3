#pragma once
#include <string>
#include <map>

struct Valids {
    const int year[2] = { 1800, 2024 };
    const int month[2] = { 1, 12 };
    const int day[2] = { 1 , 31 };
    const int temperature[2] = { -60, 40 };
    std::multimap<char, std::string> cities = { {'M', "Moskva"}, {'S', "Sankt-Peterburg"},
    {'N', "Novosibirsk"}, {'E', "Ekaterinburg"}, {'K', "Kazan"}, {'N', "Nijniy Novgorod"},
    {'C', "Chelyabinsk"}, {'S', "Samara"}, {'U', "Ufa"}, {'R', "Rostov-na-Donu"}, {'K', "Krasnodar"},
    {'O', "Omsk"}, {'V', "Voronej"}, {'P', "Perm"}, {'V', "Volgograd"}, {'K', "Krasnoyarsk"} };
};
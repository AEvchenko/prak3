#pragma once
#include <string>
#include <vector>

struct Valids {
    const int year[2] = { 1800, 2024 };
    const int month[2] = { 1, 12 };
    const int day[2] = { 1 , 31 };
    const int temperature[2] = { -60, 40 };
    vector<string> cities = { "Moskva", "Sankt-Peterburg",
    "Novosibirsk", "Ekaterinburg", "Kazan", "Nijniy Novgorod",
    "Chelyabinsk", "Samara", "Ufa", "Rostov-na-Donu", "Krasnodar",
    "Omsk", "Voronej", "Perm", "Volgograd", "Krasnoyarsk"};
};
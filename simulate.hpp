#ifndef SIMULATE_H
#define SIMULATE_H

#include <string>
#include <vector>

struct vehicle_type {
    char c;
    int l;
    int w;
    int ms;
    int pa;
    int na;
    std::string t;
};

struct vehicle {
    bool s;
    int x;
    int y;
    int u;
    std::string c;
    vehicle_type t;
};

struct command {
    std::string t;
    std::string v;
};

struct color {
    std::string c;
    float r;
    float g;
    float b;
};

extern int t, id, length, width, signalX, speedLimit;
extern std::string signal;
extern std::vector<color> colors;
extern std::vector<vehicle_type> vehicle_types;
extern std::vector<vehicle> vehicles;
extern std::vector<command> commands;
extern std::vector<std::vector<char>> r;

void simulate();

#endif

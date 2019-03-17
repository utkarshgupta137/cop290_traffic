#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "simulate.hpp"

using namespace std;

bool readLine(istream& f, vector<string>& l) {
    if (!f) {
        return false;
    }
    l.clear();

    string w;
    getline(f, w);
    stringstream ls(w);
    while (getline(ls, w, ' ')) {
        l.push_back(w);
    }

    int i = 0;
    for (auto w : l) {
        if (w != "") {
            if (w.back() == ':') {
                w.resize(w.size() - 1);
            }
            l[i++] = w;
        }
    }
    l.resize(i);
    return true;
}

void parseFile(string p) {
    ifstream f(p);
    if (!f) {
        cout << "Cannot open input file: " << p << "\n";
        exit(EXIT_FAILURE);
    }

    bool c = false;
    bool v = false;
    bool o = false;
    int ms, pa, na;
    vector<string> l;
    while (readLine(f, l)) {
        if (l.size() == 0) {
            continue;
        } else if (l[0] == "Colors") {
            c = true;
            v = false;
            o = false;
        } else if (l[0] == "Vehicles") {
            c = false;
            v = true;
            o = false;
        } else if (l[0] == "Commands") {
            c = false;
            v = false;
            o = true;
        } else if (c) {
            if (l[0] == "-") {
                l.erase(l.begin());
                colors.push_back(color());
            }

            colors.back().c = l[0];
            colors.back().r = stof(l[1]);
            colors.back().g = stof(l[2]);
            colors.back().b = stof(l[3]);
        } else if (v) {
            if (l[0] == "-") {
                l.erase(l.begin());
                vehicle_types.push_back(vehicle_type());
                vehicle_types.back().ms = ms;
                vehicle_types.back().pa = pa;
                vehicle_types.back().na = na;
            }

            if (l[0] == "Name") {
                vehicle_types.back().c = l[1][0];
            } else if (l[0] == "Type") {
                vehicle_types.back().t = l[1];
            } else if (l[0] == "Length") {
                vehicle_types.back().l = stoi(l[1]);
            } else if (l[0] == "Width") {
                vehicle_types.back().w = stoi(l[1]);
            } else if (l[0] == "MaxSpeed") {
                vehicle_types.back().ms = stoi(l[1]);
            } else if (l[0] == "Acceleration") {
                vehicle_types.back().pa = stoi(l[1]);
            } else if (l[0] == "Deceleration") {
                vehicle_types.back().na = stoi(l[1]);
            }
        } else if (o) {
            if (l[0] == "-") {
                l.erase(l.begin());
                commands.push_back(command());
            }

            commands.back().t = l[0];
            commands.back().v = l[1];
        } else if (l[0] == "Road_Id") {
            id = stoi(l[1]);
        } else if (l[0] == "Road_Length") {
            length = stoi(l[1]);
        } else if (l[0] == "Road_Width") {
            width = stoi(l[1]);
        } else if (l[0] == "Road_Signal") {
            signalX = stoi(l[1]);
        } else if (l[0] == "Road_SpeedLimit") {
            speedLimit = stoi(l[1]);
        } else if (l[0] == "Default_MaxSpeed") {
            ms = stoi(l[1]);
        } else if (l[0] == "Default_Acceleration") {
            pa = stoi(l[1]);
        } else if (l[0] == "Default_Deceleration") {
            na = stoi(l[1]);
        }
    }
}

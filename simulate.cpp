#include <algorithm>
#include <iostream>
#include <string>
#include <vector>

#include "simulate.hpp"

using namespace std;

int t, id, length, width, signalX, speedLimit;
string signal;
vector<color> colors;
vector<vehicle_type> vehicle_types;
vector<vehicle> vehicles;
vector<command> commands;
vector<vector<char>> r;

bool compare(vehicle a, vehicle b) {
    if (a.x != b.x) {
        return a.x > b.x;
    } else {
        return a.y > b.y;
    }
}

bool canMoveX(int x, int y, int w, int u) {
    if (u > length - x) {
        u = length - x;
    }
    for (int i = y - w; i < y; i++) {
        for (int j = x; j < x + u; j++) {
            if (r[i][j] != ' ') {
                return false;
            }
        }
    }
    return true;
}

bool canMoveY(int x, int y1, int y2, int l) {
    if (l > x) {
        l = x;
    }
    for (int i = min(y1, y2); i < max(y1, y2); i++) {
        for (int j = x - l; j < x; j++) {
            if (r[i][j] != ' ') {
                return false;
            }
        }
    }
    return true;
}

void simulate() {
    if (signal == "Red") {
        for (int i = 0; i < width; i++) {
            if (r[i][signalX] == ' ') {
                r[i][signalX] = '|';
            } else if (r[i][signalX] != '|' ) {
                cout << r[i][signalX] << " has jumped red light\n";
                for (int j = i; j < width; j++) {
                    if (r[j + 1][signalX] != r[i][signalX]) {
                        i = j;
                        break;
                    }
                }
            }
        }
    } else if (signal == "Green") {
        for (int i = 0; i < width; i++) {
            if (r[i][signalX] == '|' ) {
                r[i][signalX] = ' ';
            }
        }
    }

    char c;
    int l, w, x, y, u;
    vehicle_type vt;
    sort(vehicles.begin(), vehicles.end(), compare);
    for (auto v = vehicles.begin(); v != vehicles.end(); v++) {
        vt = v->t;
        c = vt.c;
        l = vt.l;
        w = vt.w;
        x = v->x;
        y = v->y;
        u = min(vt.ms, speedLimit);

        y = w;
        while (!canMoveX(x, y, w, u) || !canMoveY(x, y, v->y, l)) {
            y++;
            if (y > width) {
                y = w;
                u--;
            }
        }

        if (canMoveX(x, v->y, w, u) || u <= v->u) {
            y = v->y;
            while (!canMoveX(x, y, w, u)) {
                u--;
            }
        } else if (y < v->y) {
            if (x > 0 && v->y - y > 2) {
                y = v->y - 2;
                while (!canMoveX(x, y, w, u)) {
                    u--;
                }
            }
            for (int i = y - w; i < y; i++) {
                for (int j = x - l; j < x; j++) {
                    r[i][j] = c;
                }
            }
            for (int i = y; i < v->y; i++) {
                for (int j = x - l; j < x; j++) {
                    r[i][j] = ' ';
                }
            }
        } else if (y > v->y) {
            if (x > 0 && y - v->y > 2) {
                y = v->y + 2;
                while (!canMoveX(x, y, w, u)) {
                    u--;
                }
            }
            for (int i = v->y - w; i < y - w; i++) {
                for (int j = x - l; j < x; j++) {
                    r[i][j] = ' ';
                }
            }
            for (int i = y - w; i < y; i++) {
                for (int j = x - l; j < x; j++) {
                    r[i][j] = c;
                }
            }
        }
        v->y = y;

        while (!canMoveX(x, y, w, 2*u - vt.na)) {
            u--;
        }
        if (u == 0) {
            v->s = true;
        } else if (v->s) {
            v->s = false;
            continue;
        } else if (u > (v->u + vt.pa)) {
            u = v->u + vt.pa;
        }
        v->u = u;

        for (int i = y - w; i < y; i++) {
            for (int j = x; j < x + u; j++) {
                r[i][j] = c;
                if (j - l == signalX && signal == "Red") {
                    r[i][j - l] = '|';
                } else {
                    r[i][j - l] = ' ';
                }
            }
        }
        v->x += u;

        if (v->x - l >= length) {
            vehicles.erase(v);
            v--;
        }
    }

    t++;
    cout << "\nTime: " << t << "\n";
    for (int i = 0; i < length; i++) {
        cout << "-";
    }
    cout << "\n";
    for (auto l : r) {
        for (auto p : l) {
            cout << p;
        }
        cout << "\n";
    }
    for (int i = 0; i < length; i++) {
        cout << "-";
    }
    cout << "\n";
    for (int i = 0; i < signalX; i++) {
        cout << " ";
    }
    cout << signal[0] << "\n";
}

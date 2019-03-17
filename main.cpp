#include <iostream>
#include <vector>

#include <GL/glut.h>

#include "parser.hpp"
#include "simulate.hpp"

using namespace std;

void setColor(string c) {
    int i = 0;
    while (colors[i].c != c) {
        i++;
    }
    glColor3f(colors[i].r, colors[i].g, colors[i].b);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    glTranslatef(-1.0f, 1.0f, 0.0f);
    glScalef(2.0f, 2.0f, 0.0f);

    glPushMatrix();
    glBegin(GL_QUADS);
        setColor(signal);
        glVertex2f((float) signalX/length, -1.0f);
        glVertex2f((float) signalX/length, 0.0f);
        glVertex2f((float) (signalX+1)/length, 0.0f);
        glVertex2f((float) (signalX+1)/length, -1.0f);
    glEnd();
    int x, y, l, w;
    for (vehicle v : vehicles) {
        x = v.x;
        y = v.y;
        l = v.t.l;
        w = v.t.w;
        glBegin(GL_QUADS);
            setColor(v.c);
            glVertex2f((float) (x-l)/length, (float) (w-y)/width);
            glVertex2f((float) (x-l)/length, (float) -y/width);
            glVertex2f((float) x/length, (float) -y/width);
            glVertex2f((float) x/length, (float) (w-y)/width);
        glEnd();
    }
    glPopMatrix();

    glutSwapBuffers();
}

void update(int value) {
    command* c = &commands.front();
    if (c->t == "Signal") {
        signal = c->v;
        commands.erase(commands.begin());
    } else if (c->t == "Pass") {
        simulate();
        if (stoi(c->v) == 0) {
            commands.erase(commands.begin());
        } else {
            c->v = to_string(stoi(c->v) - 1);
        }
    } else if (c->t == "Continue") {
        simulate();
        if (vehicles.size() == 0) {
            commands.erase(commands.begin());
        }
    } else {
        vehicle v = vehicle();
        v.s = false;
        for (auto vt : vehicle_types) {
            if (vt.t == c->t) {
                v.t = vt;
                break;
            }
        }
        v.x = 0;
        v.y = v.t.w;
        v.u = 0;
        v.c = c->v;
        vehicles.push_back(v);

        simulate();
        commands.erase(commands.begin());
    }

    glutPostRedisplay();
    if (commands.empty()) {
        cout << "Simulation Id = " << id << " | Simulation Time = " << t;
        cout << " | Number of vehicles remaining = " << vehicles.size() << "\n";
        glutDestroyWindow(glutGetWindow());
    }
    glutTimerFunc(500, update, 0);
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    if (argc == 1) {
        cout << "Please provide input file\n";
        exit(EXIT_FAILURE);
    }
    parseFile(argv[1]);

    glutInitDisplayMode(GLUT_DOUBLE);
    glutInitWindowPosition(0, 0);
    glutInitWindowSize(1600, 1600*width/length);
    glutCreateWindow("Simulation");
    glutDisplayFunc(display);
    glClearColor(1.0f/6, 1.0f/6, 1.0f/6, 1.0f);

    t = 0;
    r = vector<vector<char>>(width, vector<char>(length, ' '));
    glutTimerFunc(1000, update, 0);
    glutMainLoop();
    return 0;
}

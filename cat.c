/* Command to run cat.c:

gcc -o main cat.c -lGL -lGLU -lglut -lm
./main

*/

#include <GL/glut.h>
#include <math.h>

void init() {
    glClearColor(0.0, 0.0, 0.0, 1.0);
    glColor3f(1, 1, 1);
    glMatrixMode(GL_PROJECTION);
    glShadeModel(GL_SMOOTH);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Rainbow tail of the cat
    float exitxL = -0.5;  // Example value for exitxL
    float exityL = 0.5;   // Example value for exityL
    float exityU = -0.5;  // Example value for exityU
    
    float dx = exitxL;
    float dy = exityL;
    float w = 0.014;
    float step = (exityL - exityU) / 5.0;
  

    for (int i = 0; i < 50; i++) {
        glBegin(GL_QUAD_STRIP);

        glColor3f(1, 0, 0);
        glVertex2f(dx, dy);
        glVertex2f(dx + w, dy);

        glColor3f(1, 0.6, 0);
        glVertex2f(dx, dy - step);
        glVertex2f(dx + w, dy - step);

        glColor3f(1, 1, 0);
        glVertex2f(dx, dy - step * 2);
        glVertex2f(dx + w, dy - step * 2);

        glColor3f(0.2, 1, 0);
        glVertex2f(dx, dy - step * 3);
        glVertex2f(dx + w, dy - step * 3);

        glColor3f(0, 0.6, 1);
        glVertex2f(dx, dy - step * 4);
        glVertex2f(dx + w, dy - step * 4);

        glColor3f(0.4, 0.2, 1);
        glVertex2f(dx, dy - step * 5);
        glVertex2f(dx + w, dy - step * 5);

        glEnd();

        dx += w;
        dy += 0.01 * sin(i * 3.14 / 5.0);
    }

    // Paws and tail
    float bx = dx;
    float by = dy;
    float bh = step * 5.0;
    float bw = bh * 0.80952;
    float round = 0.024;

    float th = 0.05;
    float ts = 0.01;
    float ty = by - bh * 0.8;

    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_QUAD_STRIP);
    glVertex2f(bx, ty);
    glVertex2f(bx, ty + th);
    ty += ts * 2;
    glVertex2f(bx - ts, ty);
    glVertex2f(bx - ts, ty + th);
    ty += ts * 1;
    glVertex2f(bx - ts * 2, ty);
    glVertex2f(bx - ts * 2, ty + th);
    ty += ts * 2;
    glVertex2f(bx - ts * 3, ty);
    glVertex2f(bx - ts * 3, ty + th);
    ty += ts * 3;
    glVertex2f(bx - ts * 4, ty);
    glVertex2f(bx - ts * 4, ty + th);
    glEnd();
    // Four paws
    float fr = 0.02;
    float fx = bx + bw;
    float fy = by - bh - fr;

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i));
    }
    glEnd();

    fx -= bw;
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i));
    }
    glEnd();

    fx = fx + bw * 0.8;
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i));
    }
    glEnd();

    fx = fx * 0.6;
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i));
    }
    glEnd();

    // Sparkly body
    glBegin(GL_POLYGON);
    glColor3f(0, 0, 0);
    glVertex2f(bx, by);
    glVertex2f(bx + round, by + round);
    glVertex2f(bx - round + bw, by + round);
    glVertex2f(bx + bw, by);
    glVertex2f(bx + bw, by - bh);
    glVertex2f(bx + bw - round, by - bh - round);
    glVertex2f(bx + round, by - bh - round);
    glVertex2f(bx, by - bh);
    glEnd();

    // Crust of pop tart body
    float scale = 0.95;
    round *= scale;
    bx += (bw - bw * scale) / 2.0;
    by -= (bh - bh * scale) / 2.0;
    bh *= scale;
    bw *= scale;

    glBegin(GL_POLYGON);
    glColor3f(1, 0.8, 0.6);
    glVertex2f(bx, by);
    glVertex2f(bx + round, by + round);
    glVertex2f(bx - round + bw, by + round);
    glVertex2f(bx + bw, by);
    glVertex2f(bx + bw, by - bh);
    glVertex2f(bx + bw - round, by - bh - round);
    glVertex2f(bx + round, by - bh - round);
    glVertex2f(bx, by - bh);
    glEnd();

    // Frosting
    scale = 0.86;
    round *= scale;
    bx += (bw - bw * scale) / 2.0;
    by -= (bh - bh * scale) / 2.0;
    bh *= scale;
    bw *= scale;

    glBegin(GL_POLYGON);
    glColor3f(1, 0.6, 1);
    glVertex2f(bx, by);
    glVertex2f(bx + round, by + round);
    glVertex2f(bx - round + bw, by + round);
    glVertex2f(bx + bw, by);
    glVertex2f(bx + bw, by - bh);
    glVertex2f(bx + bw - round, by - bh - round);
    glVertex2f    (bx + round, by - bh - round);
    glVertex2f(bx + round, by - bh - round);
    glVertex2f(bx, by - bh);
    glEnd();

    // Face
     fx = bx + bw;
     fy = by - bh * 0.8;
    fr = 0.07;

    glColor3f(0.6, 0.6, 0.6);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i));
    }
    glEnd();

    // Ear
    float ew = fr * 0.9;
    glBegin(GL_TRIANGLES);

    // Right ear
    glVertex2f(fx, fy);
    glVertex2f(fx + ew, fy);
    glVertex2f(fx + ew, fy + ew * 2);

    // Left ear
    glVertex2f(fx, fy);
    glVertex2f(fx - ew, fy);
    glVertex2f(fx - ew, fy + ew * 2);
    glEnd();

    // Left eye
    fr = 0.01;
    fx -= fr * 2.5;

    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i));
    }
    glEnd();

    // Gleam
    fr = 0.0025;

    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx - fr * 2 + fr * cos(i), fy + fr * 2 + fr * sin(i));
    }
    glEnd();

    // Right eye
    fr = 0.01;
    fx += fr * 4.5;

    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx - fr * cos(i), fy + fr * sin(i));
    }
    glEnd();

    // Gleam
    fr = 0.0025;
    glColor3f(1, 1, 1);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx - fr * 2 + fr * cos(i), fy + fr * 2 + fr * sin(i));
    }
    glEnd();

    // Nose
    fr = 0.005;  // Radius of the nose
    fx = bx + bw;
    fy *= 0.9;

    glColor3f(0, 0, 0);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx - fr * cos(i), fy + fr * sin(i));
    }
    glEnd();

        // Mouth
    fy *= 0.8;
    float mw = 5;  // Mouth width measured in nose widths
    float mh = 2;  // Mouth height measured in nose widths

    glLineWidth(2);
    glBegin(GL_LINE_STRIP);
    glVertex2f(fx - fr * mw, fy + fr * mh);
    glVertex2f(fx - fr * mw, fy);
    glVertex2f(fx, fy);
    glVertex2f(fx, fy + fr * mh);
    glVertex2f(fx, fy);
    glVertex2f(fx + fr * mw, fy);
    glVertex2f(fx + fr * mw, fy + fr * mh);
    glEnd();

    fr *= 1.4;
    glColor3f(1, 0.6, 0.6);
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx + mw * 1.2 * fr - fr * cos(i), fy + fr * sin(i) + fr * mh);
    }
    glEnd();

    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx - mw * 1.2 * fr - fr * cos(i), fy + fr * sin(i) + fr * mh);
    }
    glEnd();

    glFlush();
}
int main(int argc, char **argv) {
    // Initialize GLUT and create a window
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(1500, 1000);
    glutCreateWindow("Cat-astrophe Escape");

    // Set the display function
    glutDisplayFunc(display);

    // Initialize OpenGL settings
    init();

    // Enter the GLUT event loop
    glutMainLoop();

    return 0;
}



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
    
    float exitxL = -0.5;  // Example value for exitxL
    float exityL = 0.5;   // Example value for exityL
    float exityU = -0.5;  // Example value for exityU
    
    float bx = exitxL * 0.5;  // Half the length along the x-axis
    float by = exityL;
    float w = 0.014;
    float step = (exityL - exityU) / 5.0;
    float bh = step * 5.0;
    float bw = bh * 0.80952 * 0.5;  // Half the length along the x-axis
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
    
   // Dark grey color for the entire cat shape
	glBegin(GL_POLYGON);
	glColor3f(0.2, 0.2, 0.2);  // Dark grey color
	glVertex2f(bx, by-0.75);
	glVertex2f(bx-0.5 + round, by + round-0.75);
	glVertex2f(bx- round + bw, by + round-0.75);
	glVertex2f(bx+ bw, by-0.75);
	glVertex2f(bx + bw, (by - bh / 4)-0.75 );  // Reduce the height to half (divide by 2)
	glVertex2f(bx -0.75+ bw - round, (by - bh / 4 - round)-0.75 );
	glVertex2f(bx + round, (by - bh / 4 - round)-0.75 );
	glVertex2f(bx, (by - bh / 4)-0.75 );
	glEnd();

	// Light grey color for the inner rectangular polygon with rounded edges
	glBegin(GL_POLYGON);
	glColor3f(0.35, 0.35, 0.35); // Light grey color
	float innerRound = round * 0.8;  // Adjust the inner round value to make it smaller than the outer round value
	glVertex2f(bx + round, by - 0.75);
	glVertex2f(bx + round, (by - bh / 4 - round) - 0.75);
	glVertex2f(bx + bw - round, (by - bh / 4 - round) - 0.75);
	glVertex2f(bx + bw - round, by - 0.75);
	glVertex2f(bx + bw - innerRound, by - 0.75);
	glVertex2f(bx + bw - innerRound, (by - bh / 4 - innerRound) - 0.75);
	glVertex2f(bx + innerRound, (by - bh / 4 - innerRound) - 0.75);
	glVertex2f(bx + innerRound, by - 0.75);
	glEnd();

    // Four paws
    float fr = 0.02;
    float fx = bx + bw;
    float fy = by - bh - fr;

    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.6, 0.6, 0.6);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i));
    }
    glEnd();

    fx -= bw;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.6, 0.6, 0.6);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i));
    }
    glEnd();

    fx = fx + bw * 0.8;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.6, 0.6, 0.6);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i));
    }
    glEnd();

    fx = fx * 0.6;
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(0.6, 0.6, 0.6);
    for (int i = 0; i <= 200; i += 6) {
        glVertex2f(fx + fr * cos(i), fy + fr * sin(i));
    }
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
    glutInitWindowSize(800, 600);
    glutCreateWindow("Cat-astrophe Escape");

    // Set the display function
    glutDisplayFunc(display);

    // Initialize OpenGL settings
    init();

    // Enter the GLUT event loop
    glutMainLoop();

    return 0;
}


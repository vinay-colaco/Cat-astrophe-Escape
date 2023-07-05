#include <GL/glut.h>
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

// Number of stars
#define NUM_STARS 100

// Structure to hold star information
typedef struct {
    float x;
    float y;
    float size;
    float alpha;
    float speed;
} Star;

Star stars[NUM_STARS];

// Initialize stars with random values
void initStars() {
    int i;
    for (i = 0; i < NUM_STARS; i++) {
        stars[i].x = ((float)rand() / RAND_MAX) * 2.0 - 1.0; // Random x position between -1.0 and 1.0
        stars[i].y = ((float)rand() / RAND_MAX) * 0.55 + 0.45; // Random y position between 0.45 and 1.0
        stars[i].size = ((float)rand() / RAND_MAX) * 4.0 + 1.0; // Random size between 1.0 and 5.0
        stars[i].alpha = ((float)rand() / RAND_MAX) * 0.5 + 0.5; // Random alpha between 0.5 and 1.0
        stars[i].speed = ((float)rand() / RAND_MAX) * 0.01 + 0.005; // Random speed between 0.005 and 0.015
    }
}

// Update stars' positions
void updateStars() {
    int i;
    for (i = 0; i < NUM_STARS; i++) {
        stars[i].x -= stars[i].speed;
        if (stars[i].x < -1.0) {
            stars[i].x = 1.0;
        }
    }
}

// Display callback function
void display() {
    int i;

    glClear(GL_COLOR_BUFFER_BIT);

    glBegin(GL_POINTS);
    for (i = 0; i < NUM_STARS; i++) {
        glColor4f(1.0, 1.0, 1.0, stars[i].alpha);
        glPointSize(stars[i].size);
        glVertex2f(stars[i].x, stars[i].y);
    }
    glEnd();

    glutSwapBuffers();
}

// Timer callback function
void timer(int value) {
    updateStars();
    glutPostRedisplay();
    glutTimerFunc(16, timer, 0);
}

// Reshape callback function
void reshape(int width, int height) {
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Twinkling Stars");
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glPointSize(1.0);

    initStars();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);

    glutMainLoop();
    return 0;
}

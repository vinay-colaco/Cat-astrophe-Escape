#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>

// Global variables
float drumPosition = 1.0f;        // Current position of the drum on the road
float drumSpeed = -0.01f;         // Speed of the drum movement
float roadPosition = 0.0f;        // Current position of dashes on the road
float dashSpeed = 0.01f;          // Speed of the moving dashes
float drumRotation = 0.0f;        // Current rotation angle of the drum
float drumRotationSpeed = -1.0f;  // Speed of the drum rotation

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Set the color for the road
    glColor3f(0.4f, 0.4f, 0.4f);
    // Draw the road as a rectangle
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.25f);
    glVertex2f(1.0f, -0.25f);
    glVertex2f(1.0f, -1.0f);
    glVertex2f(-1.0f, -1.0f);
    glEnd();

    // Set the color for the moving dashes on the road
    glColor3f(1.0f, 1.0f, 1.0f);
    // Draw the moving dashes on the road
    glBegin(GL_QUADS);
    for (float x = -0.8f + roadPosition; x < 0.8f; x += 0.2f) {
        glVertex2f(x, -0.62f);
        glVertex2f(x, -0.64f);
        glVertex2f(x + 0.1f, -0.64f);
        glVertex2f(x + 0.1f, -0.62f);
    }
    glEnd();

    // Set the color for the drum
    glColor3f(1.0f, 0.0f, 0.0f);
    glPushMatrix();
    glTranslatef(drumPosition, -0.55f, 0.0f);
    glRotatef(drumRotation, 0.0f, 0.0f, 1.0f);
    // Draw the drum as a circle
    glBegin(GL_TRIANGLE_FAN);
    for (int i = 0; i <= 360; i++) {
        float theta = i * 3.14159f / 180.0f;
        float x = 0.05f * cos(theta);
        float y = 0.05f * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();
    glPopMatrix();

    glFlush();

    glutSwapBuffers();
}

void update(int value) {
    // Update the position of the drum
    drumPosition += drumSpeed;

    // Wrap the drum position when it reaches the left edge
    if (drumPosition < -1.2f)
        drumPosition = 1.0f;

    // Update the rotation angle of the drum
    drumRotation += drumRotationSpeed;

    // Wrap the drum rotation when it completes a full rotation
    if (drumRotation > 360.0f)
        drumRotation -= 360.0f;

    // Update the position of the dashes
    roadPosition -= dashSpeed;

    // Wrap the dashes around when they reach the left edge of the road
    if (roadPosition < -0.2f)
        roadPosition = 0.0f;

    glutPostRedisplay();

    // Call update function again after a specified interval
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Drum Rolling on Road");

    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();

    return 0;
}


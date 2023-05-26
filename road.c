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
int elapsedTime = 0;              // Elapsed time in milliseconds

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
    glPushMatrix();
    glTranslatef(drumPosition, -0.55f, 0.0f);
    glRotatef(drumRotation, 0.0f, 0.0f, 1.0f);
    // Draw the drum as a circle with rainbow stripes
    float stripeWidth = 0.05f;
    int numStripes = 6;
    float stripeAngle = 360.0f / numStripes;
    for (int i = 0; i < numStripes; i++) {
        float hue = (float)i / numStripes;
        glColor3f(hue, 1.0f - hue, 1.0f);
        glBegin(GL_QUADS);
        for (int angle = 0; angle < 180; angle += 10) {
            float theta1 = angle * 3.14159f / 180.0f;
            float theta2 = (angle + 10) * 3.14159f / 180.0f;
            float x1 = stripeWidth * cos(theta1);
            float y1 = stripeWidth * sin(theta1);
            float x2 = stripeWidth * cos(theta2);
            float y2 = stripeWidth * sin(theta2);
            glVertex2f(x1, y1);
            glVertex2f(x2, y2);
            glVertex2f(x2, -y2);
            glVertex2f(x1, -y1);
        }
        glEnd();
        glRotatef(stripeAngle, 0.0f, 0.0f, 1.0f);
    }
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

    elapsedTime += 16; // Update elapsed time

    // Increase dash and drum speed every 20 seconds
    if (elapsedTime >= 20000) {
        elapsedTime = 0; // Reset elapsed time
        dashSpeed += 0.001f; // Increase dash speed
        drumSpeed -= 0.001f; // Decrease drum speed
    }

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


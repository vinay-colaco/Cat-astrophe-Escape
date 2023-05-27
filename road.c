#include <GL/glut.h>
#include <stdbool.h>
#include <math.h>

// Global variables
float wheelPosition = 1.0f; // Current position of the wheel on the road
float wheelSpeed = -0.01f; // Speed of the wheel movement
float roadPosition = 0.0f; // Current position of dashes on the road
float dashSpeed = 0.01f; // Speed of the moving dashes
float wheelRotation = 0.0f; // Current rotation angle of the wheel
float wheelRotationSpeed = -1.0f; // Speed of the wheel rotation
float hydrantPosition = 1.0f; // Current position of the fire hydrant
float hydrantSpeed = -0.01f; // Speed of the fire hydrant movement
bool wheelActive = true; // Flag indicating if the wheel is active
bool hydrantActive = false; // Flag indicating if the fire hydrant is active
int elapsedTime = 0; // Elapsed time in milliseconds

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

    // Set the color for the moving dashes on the road
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw the moving dashes on the road
    glBegin(GL_QUADS);
    for (float x = -0.8f + roadPosition; x < 0.8f; x += 0.2f) {
        glVertex2f(x, -0.42f);
        glVertex2f(x, -0.44f);
        glVertex2f(x + 0.1f, -0.44f);
        glVertex2f(x + 0.1f, -0.42f);
    }
    glEnd();

    // Set the color for the wheel
    glPushMatrix();
    glTranslatef(wheelPosition, -0.32f, 0.0f);  // Adjust the y-coordinate for the wheel
    glRotatef(wheelRotation, 0.0f, 0.0f, 1.0f);

    // Draw the wheel as a circle with spokes
    int numSpokes = 12;
    float radius = 0.08f;  // Modify this value to change the radius of the wheel
    float spokeWidth = 0.01f;
    float spokeAngle = 360.0f / numSpokes;

    // Draw the outer rubber part of the wheel
    glColor3f(0.3f, 0.3f, 0.3f);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0f, 0.0f);
    for (float angle = 0.0f; angle <= 360.0f; angle += 10.0f) {
        float theta = angle * 3.14159f / 180.0f;
        float x = radius * cos(theta);
        float y = radius * sin(theta);
        glVertex2f(x, y);
    }
    glEnd();

    // Draw the spokes
    glColor3f(1.0f, 1.0f, 1.0f);
    glLineWidth(2.0f);
    glBegin(GL_LINES);
    for (int i = 0; i < numSpokes; i++) {
        float angle = i * spokeAngle;
        float theta = angle * 3.14159f / 180.0f;
        float x1 = (radius - spokeWidth) * cos(theta);
        float y1 = (radius - spokeWidth) * sin(theta);
        float x2 = (radius + spokeWidth) * cos(theta);
        float y2 = (radius + spokeWidth) * sin(theta);
        glVertex2f(x1, y1);
        glVertex2f(x2, y2);
    }
    glEnd();

    glPopMatrix();

    // Set the color for the fire hydrant
    if (hydrantActive) {
        glPushMatrix();
        glTranslatef(hydrantPosition, -0.37f, 0.0f);  // Adjust the y-coordinate for the fire hydrant

        // Draw the fire hydrant
        glColor3f(1.0f, 0.0f, 0.0f);

        // Draw the main body of the fire hydrant
        glBegin(GL_QUADS);
        glVertex2f(-0.03f, 0.0f);
        glVertex2f(-0.03f, 0.2f);
        glVertex2f(0.03f, 0.2f);
        glVertex2f(0.03f, 0.0f);
        glEnd();

        // Draw the top part of the fire hydrant
        glBegin(GL_TRIANGLE_FAN);
        glVertex2f(0.0f, 0.3f);
        for (float angle = 0.0f; angle <= 360.0f; angle += 10.0f) {
            float theta = angle * 3.14159f / 180.0f;
            float x = 0.03f * cos(theta);
            float y = 0.3f + 0.03f * sin(theta);
            glVertex2f(x, y);
        }
        glEnd();

        glPopMatrix();
    }

    glFlush();
    glutSwapBuffers();
}

void update(int value) {
    // Update the position of the wheel
    wheelPosition += wheelSpeed;

    // Wrap the wheel position when it reaches the left edge
    if (wheelPosition < -1.2f)
        wheelPosition = 1.0f;

    // Update the rotation angle of the wheel
    wheelRotation += wheelRotationSpeed;

    // Wrap the wheel rotation when it completes a full rotation
    if (wheelRotation > 360.0f)
        wheelRotation -= 360.0f;

    // Update the position of the dashes
    roadPosition -= dashSpeed;

    // Wrap the dashes around when they reach the left edge of the road
    if (roadPosition < -0.2f)
        roadPosition = 0.0f;

    // Update the position of the fire hydrant if it is active
    if (hydrantActive) {
        hydrantPosition += hydrantSpeed;

        // Deactivate the fire hydrant if it moves beyond the left edge
        if (hydrantPosition < -1.2f) {
            hydrantActive = false;
        }
    }

    // Activate the fire hydrant after a 5-second delay
    if (elapsedTime >= 5000 && !hydrantActive) {
        hydrantActive = true;
        hydrantPosition = 1.0f;
    }

    elapsedTime += 16; // Update elapsed time

    glutPostRedisplay();
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Obstacle Animation");

    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();
    return 0;
}


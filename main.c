


#include <GL/glut.h>

// Global variables
float roadPosition = 0.0f;   // Current position of dashes on the road
float dashSpeed = 0.01f;     // Speed of the moving dashes

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();

   // Set the color for the dashes
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw the moving dashes on the road
    glBegin(GL_QUADS);
    for (float x = -0.8f + roadPosition; x < 0.8f; x += 0.2f) {
        glVertex2f(x, -0.45f);
        glVertex2f(x, -0.47f);
        glVertex2f(x + 0.1f, -0.47f);
        glVertex2f(x + 0.1f, -0.45f);
    }
    glEnd();

    // Set the color for the road
    glColor3f(0.4f, 0.4f, 0.4f);

    // Draw the road as a rectangle
    glBegin(GL_QUADS);
    glVertex2f(-2.0f, -1.3f);
    glVertex2f(-2.0f, -1.5f);
    glVertex2f(2.0f, -1.5f);
    glVertex2f(2.0f, -1.3f);
    glEnd();

    glFlush();
}
void update(int value) {
    // Update the position of the dashes
    roadPosition -= dashSpeed;

    // Wrap the dashes around when they reach the left edge of the road
    if (roadPosition < -0.2f) {
        roadPosition = 0.0f;
    }

    glutPostRedisplay();

    // Call update function again after a specified interval
    glutTimerFunc(16, update, 0);
}

int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(800, 400);
    glutCreateWindow("Cat-astrophe escape");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black background color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();

    return 0;
}





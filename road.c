#include <GL/glut.h>

// Global variables
float roadPosition = 0.0f;   // Current position of dashes on the road
float dashSpeed = 0.01f;     // Speed of the moving dashes

void display() {
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    
    // Set the color for the road
    glColor3f(0.4f, 0.4f, 0.4f);
    // Draw the road as a rectangle
    glBegin(GL_QUADS);
    glVertex2f(-1.0f, -0.25f);  // Adjusted y-coordinate to -1.0f
    glVertex2f(1.0f, -0.25f);      // Adjusted y-coordinate to 0
    glVertex2f(1.0f, -1.0f);  // Adjusted y-coordinate to -1.0f
    glVertex2f(-1.0f, -1.0f);      // Adjusted y-coordinate to 0
    glEnd();

    glFlush();
    
    
    // Set the color for the dashes
    glColor3f(1.0f, 1.0f, 1.0f);

    // Draw the moving dashes on the road
    glBegin(GL_QUADS);
    for (float x = -0.8f + roadPosition; x < 0.8f; x += 0.2f) {
        glVertex2f(x, -0.62f);       // Adjusted y-coordinate to -0.75f
        glVertex2f(x, -0.64f);       // Adjusted y-coordinate to -0.77f
        glVertex2f(x + 0.1f, -0.64f); // Adjusted y-coordinate to -0.77f
        glVertex2f(x + 0.1f, -0.62f); // Adjusted y-coordinate to -0.75f
    }
    glEnd();
    
    glutSwapBuffers();
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
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB); // Double buffering for smoother animation
    glutInitWindowSize(1200, 750);
    glutCreateWindow("Cat-astrophe escape");
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f); // Black background color
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, 1.0);  // Adjusted the left and right parameters of glOrtho

    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);
    glutMainLoop();

    return 0;
}


#include <GL/glut.h>

// RGB values for VIBGYOR colors
float colors[][3] = {
    {1.0, 0.0, 0.0},    // Red
    {1.0, 0.5, 0.0},    // Orange
    {1.0, 1.0, 0.0},    // Yellow
    {0.0, 1.0, 0.0},    // Green
    {0.0, 0.0, 1.0},    // Blue
    {0.5, 0.0, 0.5},    // Indigo
    {1.0, 0.0, 1.0}     // Violet
};

int colorIndex = 0;     // Current color index

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3f(colors[colorIndex][0], colors[colorIndex][1], colors[colorIndex][2]);
    
    float roadWidth = 0.01; // Desired road width
    float dashLength = 0.02; // Desired dash length

    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0xF0F0); // Specify the dash pattern
    
    glBegin(GL_LINES);
    glVertex2f(-1.0, 0.0);    // Left end of the screen
    glVertex2f(1.0, 0.0);     // Right end of the screen
    glEnd();
    
    glDisable(GL_LINE_STIPPLE);
    
    glutSwapBuffers();
}

void update(int value)
{
    colorIndex = (colorIndex + 1) % 7;    // Increment color index
    
    glutPostRedisplay();
    glutTimerFunc(1000, update, 0);    // Repeat after 1 second
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowSize(800, 600);
    glutCreateWindow("Moving Line");
    
    glClearColor(0.0, 0.0, 0.0, 1.0);    // Set clear color to black
    
    gluOrtho2D(-1.0, 1.0, -1.0, 1.0);    // Set orthographic viewing
    
    glutDisplayFunc(display);
    glutTimerFunc(0, update, 0);    // Start the color update
    
    glutMainLoop();
    
    return 0;
}


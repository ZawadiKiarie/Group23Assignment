#include <GL/glut.h>
#include <cmath>
#include <cstdlib>
#include <cstdio>

// Polygon vertices
GLfloat vertices[][2] = {
    {8, 4},
    {2, 4},
    {0, 8},
    {3, 12},
    {7, 12},
    {10, 8}
};

const int numVertices = 6;

// Function to draw the grid
void drawGrid() {
    glColor3f(0.9, 0.9, 0.9);
    for (int i = -5; i <= 25; i++) {
        // Horizontal
        glBegin(GL_LINES);
        glVertex2f(-5, i);
        glVertex2f(25, i);
        glEnd();
        // Vertical
        glBegin(GL_LINES);
        glVertex2f(i, -5);
        glVertex2f(i, 25);
        glEnd();
    }
}

// Function to draw the axes and labels
void drawAxes() {
    glColor3f(0.0, 0.0, 0.0); // Black for axes

    // Drawing X and Y axes
    glBegin(GL_LINES);
    glVertex2f(0, 0); glVertex2f(25, 0); // X-axis start and end points
    glVertex2f(0, 0); glVertex2f(0, 25); // Y-axis start and end points
    glEnd();

    // Labeling points on the X-axis
    for (int i = 0; i <= 25; i+=2) {
        // Tick marks
        glBegin(GL_LINES);
        glVertex2f(i, -0.2f);
        glVertex2f(i, 0.2f);
        glEnd();

        // Numbering labels
        glRasterPos2f(i - 0.2f, -1.0f);
        char label[5];
        sprintf(label, "%d", i);
        for (char* c = label; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c);
        }
    }

    // Labeling points on the Y-axis
    for (int i = 0; i <= 25; i+=2) {
        // Tick marks
        glBegin(GL_LINES);
        glVertex2f(-0.2f, i);
        glVertex2f(0.2f, i);
        glEnd();

        // Numbering labels
        glRasterPos2f(-1.0f, i - 0.2f);
        char label[5];
        sprintf(label, "%d", i);
        for (char* c = label; *c != '\0'; c++) {
            glutBitmapCharacter(GLUT_BITMAP_HELVETICA_10, *c);
        }
    }

    // Axis labels
    glRasterPos2f(25.3f, -0.7f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'X');

    glRasterPos2f(-0.7f, 25.3f);
    glutBitmapCharacter(GLUT_BITMAP_HELVETICA_12, 'Y');
}

// Function to draw the initial polygon in red
void drawPolygon(GLfloat vertexArray[][2], int numVertices) {
    glColor3f(1.0, 0.0, 0.0); // Red
    glBegin(GL_POLYGON);
    for (int i = 0; i < numVertices; i++) {
        glVertex2f(vertexArray[i][0], vertexArray[i][1]);
    }
    glEnd();
}

// Function to fill the polygon with asterisks
void fillWithAsterisks(GLfloat vertexArray[][2], int numVertices) {
    glColor3f(0.0, 0.5, 0.0); // Darker green

    // Determine bounds
    GLfloat minX = vertexArray[0][0], maxX = vertexArray[0][0];
    GLfloat minY = vertexArray[0][1], maxY = vertexArray[0][1];
    for (int i = 1; i < numVertices; i++) {
        if (vertexArray[i][0] < minX) minX = vertexArray[i][0];
        if (vertexArray[i][0] > maxX) maxX = vertexArray[i][0];
        if (vertexArray[i][1] < minY) minY = vertexArray[i][1];
        if (vertexArray[i][1] > maxY) maxY = vertexArray[i][1];
    }

    for (float x = minX + 0.5; x < maxX; x += 0.5) {
        for (float y = minY + 0.5; y < maxY; y += 0.5) {
            int count = 0;
            for (int i = 0, j = numVertices - 1; i < numVertices; j = i++) {
                if (((vertexArray[i][1] > y) != (vertexArray[j][1] > y)) &&
                    (x < (vertexArray[j][0] - vertexArray[i][0]) * (y - vertexArray[i][1]) /
                        (vertexArray[j][1] - vertexArray[i][1]) + vertexArray[i][0])) {
                    count++;
                }
            }
            if (count % 2 == 1) {
                glRasterPos2f(x, y);
                glutBitmapCharacter(GLUT_BITMAP_8_BY_13, '*');
            }
        }
    }
}

// Display function
void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    drawGrid(); // Grid
    drawAxes(); // Axes and labels
    drawPolygon(vertices, numVertices); // Original polygon

    // Scale polygon by factor of 2
    GLfloat scaledVertices[numVertices][2];
    for (int i = 0; i < numVertices; i++) {
        scaledVertices[i][0] = vertices[i][0] * 2;
        scaledVertices[i][1] = vertices[i][1] * 2;
    }

    // Fill scaled polygon with asterisks
    fillWithAsterisks(scaledVertices, numVertices);

    glFlush();
}

// Initialization
void init() {
    glClearColor(1.0, 1.0, 1.0, 1.0); // White background
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(-5, 30, -5, 30); // Adjusted to fit labels
}

// Main function
int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Group 23: Transformation and Shapes");

    init();
    glutDisplayFunc(display);
    glutMainLoop();
    return 0;
}

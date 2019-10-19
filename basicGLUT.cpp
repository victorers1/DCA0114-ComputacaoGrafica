//g++ basicGLUT.cpp -o basic -lGL -lGLU -lglut -lm

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

/**
 * c: botão do teclado
 * (x, y): posição do mouse quando o botão foi pressioando
 */
void keyboard(unsigned char c, int x, int y)
{
    if (c == 27) //ESC
    {
        exit(0);
    }
    if (c == 32) // ESPAÇO
    {
        std::cout << "ESPAÇO\n";
    }
}

/**
 * button: botão do mouse
 * state: 
 * (x, y): posição do mouse
 */
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_RIGHT_BUTTON)
    {
        exit(0);
    }
}

void render(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glBegin(GL_TRIANGLES);
    glColor3f(1, 0, 0);
    glVertex2f(-0.5, -0.5);
    glColor3f(0, 1, 0);
    glVertex2f(0.5, -0.5);
    glColor3f(0, 0, 1);
    glVertex2f(0.0, 0.5);
    glEnd();

    glutSwapBuffers();
}

void init(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(640, 480);
    glutCreateWindow("Simple GLUT  Application");
    glutDisplayFunc(render);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
}

int main(int argc, char **argv)
{
    init(argc, argv);
    glutMainLoop();

    return 0;
}
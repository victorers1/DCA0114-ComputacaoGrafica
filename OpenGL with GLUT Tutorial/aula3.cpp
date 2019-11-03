//g++ aula3.cpp -o a3 -lGL -lGLU -lglut -lm
//Animated square

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

float x_pos = 0.0;
int sentido = 1;

void render(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity(); //aplicado à matriz MODEL/VIEW

    glTranslatef(x_pos, x_pos, 0.0);

    glShadeModel(GL_SMOOTH); // forma padrão de misturar cores de diferentes vértices
    glBegin(GL_POLYGON);     //GL_POLYGON, GL_QUADS
    glColor3f(1.0, 0.0, 0.0);
    glVertex2f(-1.0, 1.0);

    glColor3f(0.0, 1.0, 0.0);
    glVertex2f(-1.0, -1.0);

    glColor3f(0.0, 0.0, 1.0);
    glVertex2f(1.0, -1.0);

    glColor3f(1.0, 1.0, 1.0);
    glVertex2f(1.0, 1.0);
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();             // aplicado à matriz PROJECTION
    gluOrtho2D(-10, 10, -10, 10); // cria espaço cartesiano com limites em -10 à esquerda, 10 pra cima, -10 pra baixo e 10 à direita
    glMatrixMode(GL_MODELVIEW);
}

void keyboard(unsigned char c, int x, int y)
{
}

void mouse(int button, int state, int x, int y)
{
}

void timer(int)
{
    //lógica abaixo só funciona para valores positivos de 'vel'
    x_pos += 0.1 * sentido;
    if (x_pos >= 9)
    {
        sentido = -1;
    }
    else if (x_pos <= -9)
    {
        sentido = 1;
    }
    glutPostRedisplay();                // invoca a função glutDisplayFunc
    glutTimerFunc(1000 / 60, timer, 0); //invoca esta mesma função depois de 1000/60 segundos milisegundos, fazendo com que a aplicação tenha 60 FPS
}

void init(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glClearColor(0.0, 0.0, 0.0, 1.0);                 // cor da tela ao ser apagada (R, G, B, a)
    glutInitWindowPosition(200, 100);                 // posição inicial da janela em pixels
    glutInitWindowSize(500, 500);                     // tamanho inicial da janela
    glutCreateWindow("Translating Colorized Square"); // Título da janela

    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutKeyboardFunc(keyboard);
    glutMouseFunc(mouse);
}

int main(int argc, char **argv)
{
    init(argc, argv);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();

    return 0;
}
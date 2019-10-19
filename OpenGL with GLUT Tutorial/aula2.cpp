//g++ aula2.cpp -o a2 -lGL -lGLU -lglut -lm
//Animated square

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

float x_pos = -10.0;
int sentido = 1; // sentido de movimento do quadrado
float vel = 0.1; //velocidade do quadrado

void render(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity(); //aplicado à matriz MODEL/VIEW

    glBegin(GL_POLYGON); //GL_POLYGON, GL_QUADS
    glVertex2f(x_pos, 1.0);
    glVertex2f(x_pos, -1.0);
    glVertex2f(x_pos + 2.0, -1.0);
    glVertex2f(x_pos + 2, 1.0);
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
    switch (button)
    {
    case GLUT_RIGHT_BUTTON:
        vel += 0.01;
        break;

    case GLUT_LEFT_BUTTON:
        vel -= 0.01;
        break;
    default:
        break;
    }

    cout << "vel: " << vel << endl;
}

void timer(int)
{
    //lógica abaixo só funciona para valores positivos de 'vel'
    x_pos += vel * sentido;
    if (x_pos >= 8)
    {
        sentido = -1;
    }
    else if (x_pos <= -10)
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
    glClearColor(0.0, 0.0, 0.0, 1.0);    // cor da tela ao ser apagada (R, G, B, a)
    glutInitWindowPosition(200, 100);    // posição inicial da janela em pixels
    glutInitWindowSize(500, 500);        // tamanho inicial da janela
    glutCreateWindow("Animated Square"); // Título da janela

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
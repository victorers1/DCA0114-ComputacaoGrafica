//g++ aula1.cpp -o a1 -lGL -lGLU -lglut -lm

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

int re = 0; // reshape frame rate count

void render(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity(); //aplicado à matriz MODEL/VIEW

    glPointSize(10.0);
    glBegin(GL_POINTS);
        glVertex2f(5,5);
        glVertex2f(-5,-5);
    glEnd();

    glBegin(GL_TRIANGLES); //GL_POLYGON, GL_QUADS, GL_POINTS, GL_LINES, 
        glVertex2f(0.0, 5.0);//
        glVertex2f(4.0, -3.0);// Primeiro triângulo
        glVertex2f(-4.0, -3.0);//

        glVertex2f(10, 10);//
        glVertex2f(-10, 10);// Segundo triângulo
        glVertex2f(0., 5.0);//

        glVertex2f(-10.0, -10.0); // Não é exibido por não ter os outros dois vértices
    glEnd();

    glFlush();
}

void reshape(int w, int h)
{
    cout << "re: " << ++re << endl; // testando taxa de atualização desta função

    glViewport(0,0, (GLsizei) w, (GLsizei) h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity(); // aplicado à matriz PROJECTION
    gluOrtho2D(-10, 10, -10, 10); // cria espaço cartesiano com limites em -10 à esquerda, 10 pra cima, -10 pra baixo e 10 à direita
    glMatrixMode(GL_MODELVIEW);
}

void init(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB);
    glClearColor(0.0, 0.0, 0.0, 1.0); // cor da tela ao ser apagada (R, G, B, a)
    glutInitWindowPosition(200, 100); // posição inicial da janela em pixels
    glutInitWindowSize(500, 500);     // tamanho inicial da janela
    glutCreateWindow("Polygons");     // Título da janela

    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
}

int main(int argc, char **argv)
{
    init(argc, argv);
    glutMainLoop();

    return 0;
}
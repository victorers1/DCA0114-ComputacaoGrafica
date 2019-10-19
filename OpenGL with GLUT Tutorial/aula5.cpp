//g++ aula2.cpp -o a2 -lGL -lGLU -lglut -lm
//Animated colored cube - 

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <iostream>

using namespace std;

float angle = 0.0;

void render(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); //aplicado à matriz MODEL/VIEW

    glTranslatef(0.0, 0.0, -8.0);
    glRotatef(angle, 1.0, 1.0,1.0);

    glBegin(GL_QUADS); //GL_POLYGON, GL_TRIANGLES
        //front
        glColor3f(1.0,0.0,0.0);
        glVertex3f(-1.0,1.0,1.0);
        glVertex3f(-1.0,-1.0,1.0);
        glVertex3f(1.0,-1.0,1.0);
        glVertex3f(1.0,1.0,1.0);
        //back
        glColor3f(0.0,1.0,0.0);
        glVertex3f(1.0,1.0,-1.0);
        glVertex3f(1.0,-1.0,-1.0);
        glVertex3f(-1.0,-1.0,-1.0);
        glVertex3f(-1.0,1.0,-1.0);
        //right
        glColor3f(0.0,0.0,1.0);
        glVertex3f(1.0,1.0,1.0);
        glVertex3f(1.0,-1.0,1.0);
        glVertex3f(1.0,-1.0,-1.0);
        glVertex3f(1.0,1.0,-1.0);
        //left
        glColor3f(1.0,1.0,0.0);
        glVertex3f(-1.0,1.0,-1.0);
        glVertex3f(-1.0,-1.0,-1.0);
        glVertex3f(-1.0,-1.0,1.0);
        glVertex3f(-1.0,1.0,1.0);
        //top
        glColor3f(0.0,1.0,1.0);
        glVertex3f(-1.0,1.0,-1.0);
        glVertex3f(-1.0,1.0,1.0);
        glVertex3f(1.0,1.0,1.0);
        glVertex3f(1.0,1.0,-1.0);
        //bottom
        glColor3f(1.0,0.0,1.0);
        glVertex3f(-1.0,-1.0,-1.0);
        glVertex3f(-1.0,-1.0,1.0);
        glVertex3f(1.0,-1.0,1.0);
        glVertex3f(1.0,-1.0,-1.0);
    glEnd();

    glutSwapBuffers();
}

void reshape(int w, int h)
{
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();             // aplicado à matriz PROJECTION
    gluPerspective(60, 1, 2.0, 50.0); //fov, dy/dx, near clip palne, far clip plane
    glMatrixMode(GL_MODELVIEW);
}

void timer(int)
{
    glutPostRedisplay();                // invoca a função glutDisplayFunc
    glutTimerFunc(1000 / 60, timer, 0); //invoca esta mesma função depois de 1000/60 segundos milisegundos, fazendo com que a aplicação tenha 60 FPS

    angle +=0.6;
    if(angle>360){
        angle = 0;
    }
}

void init(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GL_DEPTH);

    glClearColor(0.0, 0.0, 0.0, 1.0);    // cor da tela ao ser apagada (R, G, B, a)
    glutInitWindowPosition(200, 100);    // posição inicial da janela em pixels
    glutInitWindowSize(500, 500);        // tamanho inicial da janela

    glutCreateWindow("3D Cube"); // Título da janela

    glutDisplayFunc(render);
    glutReshapeFunc(reshape);
    glutTimerFunc(0, timer, 0);
}

int main(int argc, char **argv)
{
    init(argc, argv);
    glutMainLoop();

    return 0;
}
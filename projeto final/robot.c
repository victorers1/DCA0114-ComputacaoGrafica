/* Comando de compilação
  gcc robot.c -o robot -lGL -lGLU -lglut -lm
*/

/* Manual de teclas:
  Cima: rotação anti-horária em torno de Z;
  Baixo: rotação horária em torno de Z;
  Esquerda: rotação em torno de Y;
  Direita: rotação em torno de Y;

  s, S: rotação ?;
  e, E: cotovelo;
  u, U: dedo anelar;
  i, I: dedo polegar;
  o, O: dedo indicador
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h> //rand
#include <stdio.h> //printf

void draw3DRectangle(float x, float y, float z, float w, float h, float l, float c[4][3][6]); //centro (x,y,z), dimensões (w,h,l), cores
void randomColors(float matriz[4][3][6]);

static int shoulder = 0, elbow = 0, d1 = 0, d2 = 0, d3 = 0, soma = 1, horizontal = 0, vertical = 0;
float ombro[4][3][6]; //cores do retângulo ombro
float antebraco[4][3][6]; //cores do retângulo amtebraço
float dedo1[4][3][6];
float dedo2[4][3][6];
float dedo3[4][3][6];

void init(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);
  glEnable(GL_DEPTH_TEST);

  randomColors(ombro);
  randomColors(antebraco);
  randomColors(dedo1);
  randomColors(dedo2);
  randomColors(dedo3);
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix(); //inicio-1
    glRotatef((GLfloat)shoulder, 1.0, 0.0, 0.0);
    glRotatef((GLfloat)horizontal, 0.0, 1.0, 0.0);
    glRotatef((GLfloat)vertical, 0.0, 0.0, 1.0);
    glTranslatef(-1.0, 0.0, 0.0);

    glTranslatef(0.0, 0.0, 0.0);
    glPushMatrix(); //inicio-2
      draw3DRectangle(0.0, 0.0, 0.0, 2.0, 0.4, 0.5, ombro);
    glPopMatrix(); //fim-2

    glTranslatef(1.0, 0.0, 0.0);
    glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
    glTranslatef(1.0, 0.0, 0.0);
    glPushMatrix(); //inicio-2
      draw3DRectangle(0.0, 0.0, 0.0, 2.0, 0.4, 0.5, antebraco);
    glPopMatrix(); //fim-2

    glTranslatef(1.0, 0.0, 0.0);

    glPushMatrix(); //inicio-2
      glTranslatef(0.0, -0.10, 0.0);
      glRotatef((GLfloat)d2, 0.0, 0.0, 1.0);
        glPushMatrix(); //inicio-3
        glTranslatef(0.25, -0.0, 0.0);
        draw3DRectangle(0.0, 0.0, 0.0, 0.5, 0.2, 0.15, dedo1);
      glPopMatrix(); //fim-3
    glPopMatrix(); //fim-2

    glPushMatrix(); //inicio-2
      glTranslatef(0.0, 0.10, -0.50 + .15);
      glRotatef((GLfloat)d1, 0.0, 0.0, 1.0);

      glPushMatrix(); //inicio-3
        glTranslatef(0.25, 0.0, -0.0);
        draw3DRectangle(0.0, 0.0, 0.0, 0.5, 0.2, 0.15, dedo2);
      glPopMatrix(); //fim-3

    glPopMatrix(); //fim-2

    glPushMatrix(); //inicio-2
      glTranslatef(0, 0.10, 0.5 - 0.15);
      glRotatef((GLfloat)d3, 0.0, 0.0, 1.0);

      glPushMatrix(); //inicio-3
        glTranslatef(0.25, 0, 0.0);
        draw3DRectangle(0.0, 0.0, 0.0, 0.5, 0.2, 0.15, dedo3);
      glPopMatrix(); //fim-3

    glPopMatrix(); //fim-2

  glPopMatrix(); //fim-1
  glutSwapBuffers();
}

void reshape(int w, int h) {
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //glTranslatef (0.0, 0.0, -5.0);
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void TeclasEspeciais(int key, int x, int y) {
  switch (key) {
  case GLUT_KEY_UP:
    vertical = (vertical + 1) % 360;
    break;
  case GLUT_KEY_DOWN:
    vertical = (vertical - 1) % 360;
    break;
  case GLUT_KEY_LEFT:
    horizontal = (horizontal + 1) % 360;
    break;
  case GLUT_KEY_RIGHT:
    horizontal = (horizontal - 1) % 360;
    break;
  }
  glutPostRedisplay();
}
void keyboard(unsigned char key, int x, int y) {
  switch (key) {
  case 's': /*  s key rotates at shoulder  */
    shoulder = (shoulder + soma) % 360;
    break;
  case 'S':
    shoulder = (shoulder - soma) % 360;
    break;
  case 'e': /*  e key rotates at elbow  */
    if (elbow >= -150)
      elbow = (elbow - soma);
    break;
  case 'E':
    if (elbow <= 0)
      elbow = (elbow + soma);
    break;
  case 'u':
    if (d1 >= -75)
      d1 = (d1 - soma);
    break;
  case 'U': //esquerda
    //a = ('u'-key)?soma:-soma;
    if (d1 <= 0)
      d1 = d1 + soma;
    break;
  case 'i': //esquerda-> meio
    if (d2 <= 75)
      d2 = (d2 + soma);
    break;
  case 'I':
    if (d2 >= 0)
      d2 = d2 - soma;
    break;
  case 'o': //esquerda-> meio
    if (d3 >= -75)
      d3 = (d3 - soma);
    break;
  case 'O':
    if (d3 <= 0)
      d3 = d3 + soma;
    break;
  default:
    break;
  }

  glutPostRedisplay();
}

int main(int argc, char **argv) {
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE | GLUT_DEPTH);
  glutInitWindowSize(500, 500);
  glutInitWindowPosition(100, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(TeclasEspeciais);
  glutMainLoop();
  return 0;
}

void draw3DRectangle(float x, float y, float z, float w, float h, float l, float c[4][3][6]) {

    w/=2;
    h/=2;
    glBegin(GL_QUADS); //GL_POLYGON, GL_TRIANGLES
      //front
      glColor3f(c[0][0][0], c[0][1][0], c[0][2][0]); glVertex3f(x-w, y+h, z+l);
      glColor3f(c[1][0][0], c[1][1][0], c[1][2][0]); glVertex3f(x-w, y-h, z+l);
      glColor3f(c[2][0][0], c[2][1][0], c[2][2][0]); glVertex3f(x+w, y-h, z+l);
      glColor3f(c[3][0][0], c[3][1][0], c[3][2][0]); glVertex3f(x+w, y+h, z+l);

      //back
      glColor3f(c[0][0][1], c[0][1][1], c[0][2][1]); glVertex3f(x+w, y+h, z-l);
      glColor3f(c[1][0][1], c[1][1][1], c[1][2][1]); glVertex3f(x+w, y-h, z-l);
      glColor3f(c[2][0][1], c[2][1][1], c[2][2][1]); glVertex3f(x-w, y-h, z-l);
      glColor3f(c[3][0][1], c[3][1][1], c[3][2][1]); glVertex3f(x-w, y+h, z-l);

      //right
      glColor3f(c[0][0][2], c[0][1][2], c[0][2][2]); glVertex3f(x+w, y+h, z+l);
      glColor3f(c[1][0][2], c[1][1][2], c[1][2][2]); glVertex3f(x+w, y-h, z+l);
      glColor3f(c[2][0][2], c[2][1][2], c[2][2][2]); glVertex3f(x+w, y-h, z-l);
      glColor3f(c[3][0][2], c[3][1][2], c[3][2][2]); glVertex3f(x+w, y+h, z-l);

      //left
      glColor3f(c[0][0][3], c[0][1][3], c[0][2][3]); glVertex3f(x-w, y+h, z-l);
      glColor3f(c[1][0][3], c[1][1][3], c[1][2][3]); glVertex3f(x-w, y-h, z-l);
      glColor3f(c[2][0][3], c[2][1][3], c[2][2][3]); glVertex3f(x-w, y-h, z+l);
      glColor3f(c[3][0][3], c[3][1][3], c[3][2][3]); glVertex3f(x-w, y+h, z+l);

      //top
      glColor3f(c[0][0][4], c[0][1][4], c[0][2][4]); glVertex3f(x-w, y+h, z-l);
      glColor3f(c[1][0][4], c[1][1][4], c[1][2][4]); glVertex3f(x-w, y+h, z+l);
      glColor3f(c[2][0][4], c[2][1][4], c[2][2][4]); glVertex3f(x+w, y+h, z+l);
      glColor3f(c[3][0][4], c[3][1][4], c[3][2][4]); glVertex3f(x+w, y+h, z-l);

      //bottom
      glColor3f(c[0][0][5], c[0][1][5], c[0][2][5]); glVertex3f(x-w, y-h, z-l);
      glColor3f(c[1][0][5], c[1][1][5], c[1][2][5]); glVertex3f(x-w, y-h, z+l);
      glColor3f(c[2][0][5], c[2][1][5], c[2][2][5]); glVertex3f(x+w, y-h, z+l);
      glColor3f(c[3][0][5], c[3][1][5], c[3][2][5]); glVertex3f(x+w, y-h, z-l);
    glEnd();
}

/**
  Atribui valores aleatórios aos elementos de uma matriz de floats [4][3][6]
*/
void randomColors(float matriz[4][3][6]) {
  for (int i = 0; i < 4; i++) {
    for (int j = 0; j < 3; j++) {
      for (int k = 0; k < 6; k++) {
        matriz[i][j][k] = (rand()%255) / 255.0;
        printf("colors[%u][%u][%u]: %f\n", i, j, k, matriz[i][j][k]);
      }
    }
  }
}

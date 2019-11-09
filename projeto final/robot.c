/* Comando de compilação
  gcc robot.c -o robot -lGL -lGLU -lglut -lm

  Comando de execução (Linux)
  ./robot
*/

/* Manual de teclas:
  Cima: rotação anti-horária em torno de Y;
  Baixo: rotação horária em torno de Y;
  Esquerda: rotação em torno de X;
  Direita: rotação em torno de X;

  s, S: ombro;
  e, E: cotovelo;
  d,D: punho;
  c, C: roda punho e antebraço juntos;
  u, U: dedo anelar;
  i, I: dedo polegar;
  o, O: dedo indicador;
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>
#include <stdlib.h> //rand
#include <stdio.h> //printf
#include <math.h>

# define PI 3.14159265358979323846

void randomColors(float matriz[8][3]); // são 8 vértices, cada um com 3 componentes de cores

static int shoulder = 0, elbow = -45, fist = -45, d1 = 0, d2 = 0, d3 = 0, soma = 1, horizontal = 0, vertical = 0;
//CORES
float ombro[8][3]; //cores do retângulo ombro
float antebraco[8][3]; //cores do retângulo antebraço
float punho[8][3];
float dedo1[8][3];
float dedo2[8][3]; //dedo do meio
float dedo3[8][3];
float cil[3] = {1.0, 1.0, 1.0};



//GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f}; //Color(0.2, 0.2, 0.2)
//GLfloat light0color[]    = { 1.0, 1.0, 1.0, 0.0 };
//GLfloat light0position[] = { -5.0, 0.0, 0.0, 0.0 };

void init(void) {
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_SMOOTH);

  glEnable(GL_DEPTH_TEST);
  // glEnable(GL_LIGHTING);
  // glEnable(GL_LIGHT0);
  // glEnable(GL_COLOR_MATERIAL);
  // glEnable(GL_NORMALIZE);

/*GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat mat_shininess[] = { 50.0 };

  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);
  glLightfv(GL_LIGHT0, GL_POSITION, light_position);*/


  GLfloat ambientColor[] = {0.4f, 0.4f, 0.4f, 1.0f}; //Color(0.2, 0.2, 0.2)
  GLfloat light0color[]    = { 1.0, 1.0, 1.0, 0.0 };
  GLfloat light0position[] = { 15.0, 5.0, 15.0, 0.0 };		// x, y, z, 1:directional 0:point

  GLfloat mat_diffuse[] = { 0.6, 0.6, 0.6, 1.0 };
  GLfloat mat_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
  GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
  GLfloat low_shininess[] = { 50.0 };

  glLightModelfv(GL_LIGHT_MODEL_AMBIENT, ambientColor);
  glLightfv(GL_LIGHT0, GL_DIFFUSE, light0color);
  glLightfv(GL_LIGHT0, GL_POSITION, light0position);

  glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
  glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
  glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
  glMaterialfv(GL_FRONT, GL_SHININESS, low_shininess);

  //Cria cores
  randomColors(ombro);
  randomColors(antebraco);
  randomColors(punho);
  randomColors(dedo1);
  randomColors(dedo2);
  randomColors(dedo3);
}

/**
Desenha um retângulo cujo centro está em (x, y, z), tem dimensões 'w', 'h' e 'l'
e seus vértices têm cores salvos na matriz c.
*/
void draw3DRectangle(float x, float y, float z, float w, float h, float l, float c[8][3]) {
  w/=2;
  h/=2;
  l/=2;
  glBegin(GL_QUADS); //GL_POLYGON, GL_TRIANGLES
    //front
    glColor3f(c[0][0], c[0][1], c[0][2]); glVertex3f(x-w, y+h, z+l); //-++
    glColor3f(c[1][0], c[1][1], c[1][2]); glVertex3f(x-w, y-h, z+l); //--+
    glColor3f(c[2][0], c[2][1], c[2][2]); glVertex3f(x+w, y-h, z+l); //+-+
    glColor3f(c[3][0], c[3][1], c[3][2]); glVertex3f(x+w, y+h, z+l); //+++

    //back
    glColor3f(c[4][0], c[4][1], c[4][2]); glVertex3f(x+w, y+h, z-l); //++-
    glColor3f(c[5][0], c[5][1], c[5][2]); glVertex3f(x+w, y-h, z-l); //+--
    glColor3f(c[6][0], c[6][1], c[6][2]); glVertex3f(x-w, y-h, z-l); //---
    glColor3f(c[7][0], c[7][1], c[7][2]); glVertex3f(x-w, y+h, z-l); //-+-

    //right
    glColor3f(c[3][0], c[3][1], c[3][2]); glVertex3f(x+w, y+h, z+l); //+++
    glColor3f(c[2][0], c[2][1], c[2][2]); glVertex3f(x+w, y-h, z+l); //+-+
    glColor3f(c[5][0], c[5][1], c[5][2]); glVertex3f(x+w, y-h, z-l); //+--
    glColor3f(c[4][0], c[4][1], c[4][2]); glVertex3f(x+w, y+h, z-l); //++-

    //left
    glColor3f(c[7][0], c[7][1], c[7][2]); glVertex3f(x-w, y+h, z-l); //-+-
    glColor3f(c[5][0], c[5][1], c[5][2]);  glVertex3f(x-w, y-h, z-l); //---
    glColor3f(c[1][0], c[1][1], c[1][2]); glVertex3f(x-w, y-h, z+l); //--+
    glColor3f(c[0][0], c[0][1], c[0][2]); glVertex3f(x-w, y+h, z+l); //-++

    //top
    glColor3f(c[7][0], c[7][1], c[7][2]); glVertex3f(x-w, y+h, z-l); //-+-
    glColor3f(c[0][0], c[0][1], c[0][2]); glVertex3f(x-w, y+h, z+l); //-++
    glColor3f(c[3][0], c[3][1], c[3][2]); glVertex3f(x+w, y+h, z+l); //+++
    glColor3f(c[4][0], c[4][1], c[4][2]); glVertex3f(x+w, y+h, z-l); //++-

    //bottom
    glColor3f(c[5][0], c[5][1], c[5][2]); glVertex3f(x-w, y-h, z-l); //---
    glColor3f(c[1][0], c[1][1], c[1][2]); glVertex3f(x-w, y-h, z+l); //--+
    glColor3f(c[2][0], c[2][1], c[2][2]); glVertex3f(x+w, y-h, z+l); //+-+
    glColor3f(c[5][0], c[5][1], c[5][2]); glVertex3f(x+w, y-h, z-l); //+--
  glEnd();
}

/**
Desenha um cilindro que se extende no eixo Z cujo centro é (x,y,z), tem altura h
e raio r. O cilindro tem corpo com cor dado em c[3] e as bases com cor dados em
t[3].
*/
void draw3DCylinder(float x, float y, float z, float h, float r, float c[3], float t[3],float rotacao) {
  int X = 180;
  glColor3f(c[0], c[1], c[2]);

  glPushMatrix();

    glTranslatef(x,y,z);
    glRotatef(((GLfloat)rotacao), .0, .0, 1.0);
    glBegin(GL_QUAD_STRIP); //exibe uma sequência de quadriláteros conectados a cada 4 vértices
      for (int i = 0; i <180-rotacao; i+=10) {
        glVertex3f(r*cos(i*PI/X), r*sin(i*PI/X), h/2.0);
        glVertex3f(r*cos(i*PI/X), r*sin(i*PI/X), -h/2.0);
      }

    for (int i = 0; i < 360; i+=10) {}
    glEnd();
  glPopMatrix();
}

void display(void) {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glPushMatrix(); //inicio-1
    glRotatef(90, .0, .0, 1.0);
    glRotatef((GLfloat)vertical, .0, 1.0, .0);
    glRotatef((GLfloat)horizontal, 1.0, .0, .0);
    glTranslatef(-1.0, 0.0, 0.0);



    glBegin(GL_QUADS); //CHÃO
      glColor3f(1.0, 1.0, 1.0); glVertex3f(-1.01, 5.0, 5.0); // coord. x está um pouco abaixo de 1 para que não dê pra ver o braço na parte de baixo do chão
      glColor3f(.6, .6, .6); glVertex3f(-1.01, -5.0, 5.0);
      glColor3f(.3, .3, .3); glVertex3f(-1.01, -5.0, -5.0);
      glColor3f(.0, .0, .0); glVertex3f(-1.01, 5.0, -5.0);
    glEnd();

    glTranslatef(-1.0, -.2, .0);
    glRotatef((GLfloat)shoulder, .0, .0, 1.0);
    glTranslatef(1.0, .2, .0);
    draw3DCylinder(1.0, -0.2, 0.0, 1, 0.4, cil, cil, elbow);
    draw3DRectangle(.0, .0, .0, 2.0, .4, 1.0, ombro);

    glTranslatef(1.0, -0.2, .0);
    glRotatef((GLfloat)elbow, .0, .0, 1.0); //rotaciona em torno do eixo Z do objeto
    glTranslatef(.5, .2, .0);
    draw3DCylinder(0.5, -0.2, 0.0, 1, 0.4, cil, cil,fist);
    draw3DRectangle(.0, .0, .0, 1.0, .4, 1.0, antebraco);

    glTranslatef(.5, -.2, .0);
    glRotatef((GLfloat)fist, .0, .0, 1.0); //rotaciona em torno do eixo Z do objeto
    glTranslatef(.75, .2, .0);
    draw3DRectangle(.0, .0, .0, 1.5, -.4, 1.0, punho);

    glTranslatef(.75, .0, .0);

    glPushMatrix(); //inicio-2
      glTranslatef(.0, -.1, .0);
      glRotatef((GLfloat)d2, .0, .0, 1.0);

      glPushMatrix(); //inicio-3
        glTranslatef(.25, .0, .0);
        draw3DRectangle(.0, .0, .0, .5, .2, .3, dedo2);
      glPopMatrix(); //fim-3

    glPopMatrix(); //fim-2

    glPushMatrix(); //inicio-2
      glTranslatef(.0, .1, -.5 + .15);
      glRotatef((GLfloat)d1, .0, -sin(-30*PI/180), cos(-30*PI/180)); //rotaciona o dedo torto na direção certa

      glPushMatrix(); //inicio-3
        glTranslatef(.25, .0, .0);
        glRotatef((GLfloat) 30, -1.0, .0, .0);
        draw3DRectangle(.0, .0, .0, .5, .2, .3, dedo1);
      glPopMatrix(); //fim-3

    glPopMatrix(); //fim-2

    glPushMatrix(); //inicio-2
      glTranslatef(.0, .10, .5 - .15);
      glRotatef((GLfloat)d3, .0, -sin(30*PI/180), cos(30*PI/180));

      glPushMatrix(); //inicio-3
        glTranslatef(.25, .0, .0);
        glRotatef((GLfloat) 30, 1.0, .0, .0);
        draw3DRectangle(.0, .0, .0, .5, .2, .3, dedo3);
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
    if (shoulder >= -60) shoulder -= soma;
    break;
  case 'S':
    if (shoulder <= 0) shoulder += soma;
    break;
  case 'e': /*  e key rotates at elbow  */
    if (elbow >= -150) elbow -= soma;
    break;
  case 'E':
    if (elbow <= 0) elbow += soma;
    break;
  case 'd': /*  d key rotates at fist  */
    if (fist >= -150) fist -= soma;
    break;
  case 'D':
    if (fist <= 0) fist += soma;
    break;
  case 'u':
    if (d1 >= -75) d1 -= soma;
    break;
  case 'U': //esquerda
    if (d1 <= 0) d1 += soma;
    break;
  case 'i': //esquerda-> meio
    if (d2 <= 75) d2 += soma;
    break;
  case 'I':
    if (d2 >= 0) d2 -= soma;
    break;
  case 'o': //esquerda-> meio
    if (d3 >= -75) d3 -= soma;
    break;
  case 'O':
    if (d3 <= 0) d3 += soma;
    break;
  case 'c':
    if (elbow >= -50) elbow -= soma;
    if (fist >= -50) fist -= soma;
    if (shoulder >= -50) shoulder -= soma;
    break;
  case 'C':
    if (elbow <= -1) elbow += soma;
    if (fist <= -1) fist += soma;
    if (shoulder <= 0) shoulder += soma;
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


/**
  Atribui valores aleatórios aos elementos de uma matriz de floats [8][3]
*/
void randomColors(float matriz[8][3]) {
  for (int i = 0; i < 8; i++) {
    for (int j = 0; j < 3; j++) {
      matriz[i][j] = (rand()%255) / 255.0;
      printf("colors[%u][%u]: %.4f\n", i, j, matriz[i][j]);
    }
  }
}

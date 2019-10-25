/* Comando de compilação
gcc robot.c -o robot -lGL -lGLU -lglut -lm
*/

/* Manual de teclas:
Cima: rotação vertical anti-horária;
Baixo: rotação vertical horária;
Esquerda: rotação horizontal;
Direita: rotação horizontal;

s, S: rotação ?;
e, E: cotovelo;
u, U: dedo anelar;
i, I: dedo polegar;
o, O: dedo indicador
*/

#include <GL/gl.h>
#include <GL/glu.h>
#include <GL/glut.h>

static int shoulder = 0, elbow = 0, d1 = 0, d2 = 0, d3 = 0, soma = 1, horizontal = 0, vertical = 0;

void init(void)
{
  glClearColor(0.0, 0.0, 0.0, 0.0);
  glShadeModel(GL_FLAT);
}

void display(void)
{
  glClear(GL_COLOR_BUFFER_BIT);
  glPushMatrix(); //inicio-1
  glRotatef((GLfloat)shoulder, 1.0, 0.0, 0.0);
  glRotatef((GLfloat)horizontal, 0.0, 1.0, 0.0);
  glRotatef((GLfloat)vertical, 0.0, 0.0, 1.0);
  glTranslatef(-1.0, 0.0, 0.0);

  glTranslatef(0.0, 0.0, 0.0);
  glPushMatrix(); //inicio-2
  glScalef(2.0, 0.4, 1.0);
  glutWireCube(1.0);
  glPopMatrix(); //fim-2

  glTranslatef(1.0, 0.0, 0.0);
  glRotatef((GLfloat)elbow, 0.0, 0.0, 1.0);
  glTranslatef(1.0, 0.0, 0.0);
  glPushMatrix(); //inicio-2
  glScalef(2.0, 0.4, 1.0);
  glutWireCube(1.0);
  glPopMatrix(); //fim-2

  glTranslatef(1.0, 0.0, 0.0);
  //glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);
  //glTranslatef (0.4, 0.1, 0.0);

  //
  glPushMatrix(); //inicio-2
  glTranslatef(0.0, -0.10, 0.0);
  glRotatef((GLfloat)d2, 0.0, 0.0, 1.0);
  glPushMatrix(); //inicio-3
  glTranslatef(0.25, -0.0, 0.0);
  glScalef(0.5, 0.20, 0.30);
  glutWireCube(1.0);
  glPopMatrix(); //fim-3
  glPopMatrix(); //fim-2

  //glTranslatef (1.0, 0.0, 0.0);
  //glRotatef ((GLfloat) elbow, 0.0, 0.0, 1.0);

  glPushMatrix(); //inicio-2
  glTranslatef(0.0, 0.10, -0.50 + .15);
  glRotatef((GLfloat)d1, 0.0, 0.0, 1.0);
  glPushMatrix(); //inicio-3
  glTranslatef(0.25, 0.0, -0.0);

  glScalef(0.5, 0.2, 1.0 / 3);
  glutWireCube(1.0);
  glPopMatrix(); //fim-3
  glPopMatrix(); //fim-2

  glPushMatrix(); //inicio-2

  //glRotatef ((GLfloat) d3, 0.0, 0.0, 1.0);
  glTranslatef(0, 0.10, 0.5 - 0.15);

  glRotatef((GLfloat)d3, 0.0, 0.0, 1.0);
  glPushMatrix(); //inicio-3
  glTranslatef(0.25, 0, 0.0);
  glScalef(0.5, 0.2, 0.30);
  glutWireCube(1.0);
  glPopMatrix(); //fim-3
  glPopMatrix(); //fim-2

  glPopMatrix(); //fim-1
  glutSwapBuffers();
}

void reshape(int w, int h)
{
  glViewport(0, 0, (GLsizei)w, (GLsizei)h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  gluPerspective(65.0, (GLfloat)w / (GLfloat)h, 1.0, 20.0);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  //glTranslatef (0.0, 0.0, -5.0);
  gluLookAt(0.0, 0.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
void TeclasEspeciais(int key, int x, int y)
{
  switch (key)
  {
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

void keyboard(unsigned char key, int x, int y)
{
  switch (key)
  {
  case 's': /*  s key rotates at shoulder  */
    shoulder = (shoulder + soma) % 360;
    break;
  case 'S':
    shoulder = (shoulder - soma) % 360;
    break;
  case 'e': /*  e key rotates at elbow  */
    if (elbow <= 150)
      elbow = (elbow + soma);
    break;
  case 'E':
    if (elbow > 0)
      elbow = (elbow - soma);
    break;
  case 'u':
    if (d1 <= 150)
      d1 = (d1 + soma);
    break;
  case 'U': //esquerda
    //a = ('u'-key)?soma:-soma;
    if (d1 > 0)
      d1 = d1 - soma;
    break;
  case 'i': //esquerda-> meio
    if (d2 <= 150)
      d2 = (d2 + soma);
    break;
  case 'I':
    if (d2 > 0)
      d2 = d2 - soma;
    break;
  case 'o': //esquerda-> meio
    if (d3 <= 150)
      d3 = (d3 + soma);
    break;
  case 'O':
    if (d3 > 0)
      d3 = d3 - soma;
    break;
  default:
    break;
  }

  glutPostRedisplay();
}

int main(int argc, char **argv)
{
  glutInit(&argc, argv);
  glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
  glutInitWindowSize(1000, 1000);
  glutInitWindowPosition(1000, 100);
  glutCreateWindow(argv[0]);
  init();
  glutDisplayFunc(display);
  glutReshapeFunc(reshape);
  glutKeyboardFunc(keyboard);
  glutSpecialFunc(TeclasEspeciais);
  glutMainLoop();
  return 0;
}

#include <GL/glut.h>
#include <stdlib.h>

GLsizei winWidth = 500,winHeight = 500;

void init (void){
    glClearColor (1.0,1.0, 1.0, 0.0);
}


static void resize(int width, int height)
{
    const float ar = (float) width / (float) height;

    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-ar, ar, -1.0, 1.0, 2.0, 100.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity() ;
}

static void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glColor3f(1.0,0.0,0.0);
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glPushMatrix();
        glTranslated(1.0,1.0,0.0);
        glutWireSphere(0.75,8,6);
    glPopMatrix();

    glPushMatrix();
        glTranslated(1.0,-0.5,0.5);
        glutWireCone(0.7,2.0,7,6);
    glPopMatrix();

    GLUquadricObj *cylinder;
    glPushMatrix();
    glTranslatef(0.0,1.2,0.8);
    cylinder = gluNewQuadric();
    gluQuadricDrawStyle(cylinder, GLU_LINE);
    gluCylinder(cylinder, 0.6, 0.6, 1.5, 6 ,4);
    glPopMatrix( );

    glFlush();
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowSize(winWidth,winHeight);
    glutInitWindowPosition(100,100);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    glutCreateWindow("wire-frame quadric surfaces");

    init();
    glutReshapeFunc(resize);
    glutDisplayFunc(display);

    glutMainLoop();

    return 0;
}
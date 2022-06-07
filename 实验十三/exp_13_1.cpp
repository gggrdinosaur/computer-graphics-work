#include <GL/glut.h>

GLsizei winWidth = 500,winHeight = 500;

void init (void){
    glClearColor (1.0,1.0, 1.0, 0.0);
}

void displayWirePolyhedra(void){
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0, 0.0, 1.0 );
    gluLookAt(5.0, 5.0, 5.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);

    glScalef( 1.5, 2.0, 1.0);
    glutWireCube(1.0);

    glScalef(0.8, 0.5, 0.8);
    glTranslatef(-6.0, -5.0, 0.0);
    glutWireDodecahedron();

    glTranslatef(8.6, 8.6, 2.0);
    glutWireTetrahedron();

    glTranslatef(-3.0, -1.0,0.0);
    glutWireOctahedron();

    glScalef(0.8,0.8,0.5);
    glTranslatef(4.3, -2.0, 0.5);
    glutWireIcosahedron();

    glFlush();

}

void winReshapeFcn (GLint newWidth, GLint newHeight){
    glViewport(0, 0, newWidth, newWidth);
    glMatrixMode(GL_PROJECTION);
    glFrustum(-1.0, 1.0, -1.0, 1.0, 2.0, 20.0);

    glMatrixMode(GL_MODELVIEW);
    glClear(GL_COLOR_BUFFER_BIT);

}

int main (int argc , char** argv){
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(winWidth,winHeight);
    glutCreateWindow("wire-frame  polyhedra");

    init();
    glutDisplayFunc(displayWirePolyhedra);
    glutReshapeFunc(winReshapeFcn);

    glutMainLoop();
    return 0;
}
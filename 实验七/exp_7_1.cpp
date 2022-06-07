#include <GL/glut.h>
GLsizei winWidth = 400, winHeight = 300;
void init (void)
{
    glClearColor(1.0,1.0,1.0,1.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0.0,200.0,0.0,200.0);
}

void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(1.0,0.0,0.0);
    glPointSize(3.0);
}

void winReshape(GLint newWidth, GLint newHeight)
{
    glViewport(0,0,newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,GLdouble(newWidth),0.0,GLdouble(newHeight));

    winWidth = newWidth;
    winHeight = newHeight;
}

void plotPoint(GLint x, GLint y)
{
    glBegin(GL_POINTS);
    glVertex2i(x,y);
    glEnd();
}
//鼠标交互
void mousePtPlot(GLint button, GLint action, GLint xmouse, GLint ymouse)
{
    if(button == GLUT_LEFT_BUTTON && action == GLUT_DOWN)
        plotPoint (xmouse,winHeight-ymouse);

    glFlush();
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow("Mouse Plot Points");

    init();
    glutDisplayFunc(display);
    glutReshapeFunc(winReshape);
    glutMouseFunc(mousePtPlot);

glutMainLoop();

    return 0;
}
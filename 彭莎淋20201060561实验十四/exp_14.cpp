#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

GLsizei winWidth = 600,winHeight = 600;
GLfloat xwcMin = -50.0, ywcMin = -50.0, xwcMax = 50.0, ywcMax = 50.0;

class wcPt3D{
public:
    GLfloat x,y,z;
};

void init (void){
    glClearColor (1.0,1.0, 1.0, 0.0);
}

void plotPoint(wcPt3D bezCurvePt)
{
    glBegin(GL_POINTS);
    glVertex2f(bezCurvePt.x, bezCurvePt.y);
    glEnd();
}

void binomialCoeffs(GLint n, GLint * c)
{
    GLint k,j;
    for(k = 0; k<= n;k++)
    {
        c[k] = 1;
        for(j = n; j >= k+1; j--)
            c[k] *= j;
        for(j = n - k; j >= 2; j--)
            c[k] /= j;
    }
}

void computerBezPt(GLfloat u, wcPt3D * bezPt, GLint nCtrlPts, wcPt3D * ctrlPts, GLint * c)
{
    GLint k , n = nCtrlPts - 1;
    GLfloat bezBlendFcn;

    bezPt->x = bezPt->y = bezPt->z =0.0;

    for(k = 0; k < nCtrlPts ; k++)
    {
        bezBlendFcn = c[k] * pow(u ,k ) * pow(1-u, n-k);
        bezPt->x += ctrlPts[k].x * bezBlendFcn;
        bezPt->y += ctrlPts[k].y * bezBlendFcn;
        bezPt->z += ctrlPts[k].z * bezBlendFcn;
    }
}
//计算其他点
void bezier (wcPt3D * ctrlPts, GLint nCtrlPts, GLint nBezCurvePts)
{
    wcPt3D bezCurvePt;
    GLfloat u;
    GLint *c,k;

    c = new GLint[nCtrlPts];

    binomialCoeffs(nCtrlPts - 1,c);
    for (k = 0; k <= nBezCurvePts; k++)
    {
        u = GLfloat(k) / GLfloat(nBezCurvePts);
        computerBezPt(u, &bezCurvePt, nCtrlPts, ctrlPts, c);
        plotPoint(bezCurvePt);
    }
    delete [ ] c;
}
//绘制函数
void displayFcn()
{
    GLint nCtrlPts = 4,nBezCurvePts = 1000;
    wcPt3D ctrlPts[4] = { {50.0,100.0,0.0},{100.0,400.0,0.0}, {150.0, 100.0,0.0}, {200.0,400.0,0.0} };

    glClear(GL_COLOR_BUFFER_BIT);
    glPointSize(4);
    glColor3f(1.0,1.0,0.0);

    bezier(ctrlPts, nCtrlPts, nBezCurvePts);
    glFlush();
}
//窗口重定义函数
void winReshapeFcn(GLint newWidth, GLint newHeight)
{
    glViewport(0,0,newWidth, newHeight);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,GLdouble(newWidth),0.0,GLdouble(newHeight));

    winWidth = newWidth;
    winHeight = newHeight;
}

int main(int argc, char *argv[])
{
    glutInit(&argc, argv);
    glutInitWindowPosition(50,50);
    glutInitWindowSize(winWidth,winHeight);

    glutInitDisplayMode( GLUT_SINGLE | GLUT_RGB);

    glutCreateWindow("Bezier Curve");

    init();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);


    glutMainLoop();

    return EXIT_SUCCESS;
}
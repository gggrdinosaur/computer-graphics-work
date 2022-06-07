#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*set initial display-window size*/
GLsizei winWidth = 600, winHeight = 600;

/*set range for world coordinates*/
GLfloat xwcMin = 0.0,xwcMax = 225.0;
GLfloat ywcMin = 0.0,ywcMax = 225.0;

class wcPt2D{
public :
    GLfloat x,y;
};

typedef GLfloat Matrix3x3  [3][3];
Matrix3x3 matComposite;
const GLdouble pi = 3.14159;
 void init (void)
 {
     /*set color of display window to white*/
     glClearColor(1.0,1.0,1.0,0.0);
     glColor3f(1.0, 0.0,0.0);
	 glPointSize(2);
 }
 /*Construct the 3 x 3 identity matrix*/
 void matrix3x3SetIdentity (Matrix3x3 matIdent3x3)
 {
     GLint row, col;

     for (row = 0; row < 3; row++)
        for (col = 0 ;col < 3; col++)
            matIdent3x3 [row][col] = (row == col);
 }
 /* premultiply matrix m1 times matrix m2, store result in m2*/
 //矩阵乘法
 void matrix3x3PreMultiply (Matrix3x3 m1, Matrix3x3 m2)
 {
     GLint row, col;
     Matrix3x3 matTemp;

     for (row = 0 ;row < 3 ; row++)
         for (col = 0; col < 3; col++)
             matTemp [row][col] = m1[row][0] * m2[0][col] + m1[row][1] * m2 [1][col] + m1[row][2] * m2[2][col];

    for (row = 0; row < 3;row++)
        for (col = 0 ;col < 3;col++)
            m2[row][col] = matTemp [row][col];
 }
 //平移
 void translate2D(GLfloat tx, GLfloat ty)
 {
     Matrix3x3 matTransl;
     matrix3x3SetIdentity(matTransl);

     matTransl[0][2] = tx;
     matTransl[1][2] = ty;

     matrix3x3PreMultiply (matTransl,matComposite);
 }
 //旋转
 void roate2D(wcPt2D pivotPt, GLfloat theta )
 {
     Matrix3x3  matRot;
     matrix3x3SetIdentity(matRot);

     matRot[0][0] = cos(theta);
     matRot[0][1] = -sin(theta);

     matRot[1][0] = sin(theta);
     matRot[1][1] = cos(theta);

     matrix3x3PreMultiply(matRot,matComposite);
 }
 //比例
 void scale2D (GLfloat sx, GLfloat sy, wcPt2D fixedPt)
 {
     Matrix3x3 matScale;
     matrix3x3SetIdentity(matScale);

     matScale[0][0] = sx;
     matScale[1][1] = sy;

     matrix3x3PreMultiply(matScale,matComposite);
}
//关于X轴对称
void symmetry(void)
{
    Matrix3x3 matSym;
    matrix3x3SetIdentity(matSym);

    matSym [0][0] = 1;
    matSym [1][1] = -1;

    matrix3x3PreMultiply(matSym,matComposite);
}
void transformVerts2D (GLint nVerts, wcPt2D *verts)
{
    GLint k;
    GLfloat temp;

    for(k = 0; k < nVerts; k++)
    {
        temp = matComposite[0][0] * verts[k].x + matComposite[0][1] * verts[k].y + matComposite[0][2];
        verts[k].y = matComposite[1][0] * verts[k].x + matComposite[1][1] * verts[k].y + matComposite[1][2];
        verts[k].x = temp;
    }
}
//画三角
void triangle(wcPt2D *verts)
{
    GLint k;

    glBegin(GL_TRIANGLES);
    for (k = 0 ;k < 3 ; k++)
        glVertex2f(verts[k].x, verts[k].y);
    glEnd();
}
void displayFcn(void)
{
    GLint nVerts = 3;
    wcPt2D verts [3] = { {100.0,50.0}, {250.0,50.0}, {200.0,200.0}};

    wcPt2D centroidPt;
    GLint k, xsum = 0, ysum = 0;

    for (k =0 ;k< nVerts ; k++)
    {
        xsum += verts[k].x;
        ysum += verts[k].y;
    }

    centroidPt.x = GLfloat(xsum) / GLfloat(nVerts);
    centroidPt.y = GLfloat(ysum) / GLfloat(nVerts);

    wcPt2D pivPt, fixedPt;
    pivPt = centroidPt;
    fixedPt = centroidPt;

    GLfloat tx = 100.0, ty = 100.0;
    GLfloat sx = 2.0, sy = 2.0;
    GLdouble theta = pi / 2.0;

    //初始图形
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(0.0,0.0,1.0);
    glViewport(200,200,200,200);
    triangle(verts);

    matrix3x3SetIdentity(matComposite);
    //平移
    translate2D(tx, ty);
    transformVerts2D(nVerts, verts);
    glColor3f(1.0,1.0,0.0);
    triangle(verts);

    //对称
    symmetry();
    transformVerts2D(nVerts, verts);
    glColor3f(1.0, 0.0, 1.0);
    triangle(verts);

    //比例
    scale2D(sx,sy,fixedPt);
    glColor3f(1.0,0.0,0.0);
    transformVerts2D(nVerts, verts);
    triangle(verts);\

    //旋转
    roate2D(pivPt,theta);
    glColor3f(0.0,1.0,0.0);
    transformVerts2D(nVerts, verts);
    triangle(verts);

    glFlush();
}
//窗口重定型函数
void winReshapeFcn( GLint newWidth, GLint newHeight)
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(-500,500,-500,500);

    glClear(GL_COLOR_BUFFER_BIT);
}
int main (int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(100,100);
    glutInitWindowSize(winWidth, winHeight);
    glutCreateWindow(" Geometric Transformation Sequence");

    init();
    glutDisplayFunc(displayFcn);
    glutReshapeFunc(winReshapeFcn);

    glutMainLoop();

    return 0;

}
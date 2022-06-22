#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include "math.h"

int s1=1, s2=1, s3=1;    //视角位置，全局变量

void Init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 0.0f);
}
void Reshape(int w, int h)
{
    glViewport(0, 0, w, h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
//3D
    glOrtho(-w/2,w/2,-h/2,h/2,-300,300);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void myDisplay(void)
{
 //顶点表
    int x[10] = { 50, 50, 25, 0, 0, 50, 50, 25, 0, 0 };
    int y[10] = { 0, 40, 60, 40, 0, 0, 40, 60,40, 0 };
    int z[10] = { 140,140,140,140,140, 0, 0, 0, 0,0 };
//面点表
    int f[7] = { 0,1,2,3,4,5,6 }; //面的号码
    int p[7] = { 6,5,6,5,5,5,5 }; //面的顶点数
    int fp[7][6] = { {0,1,2,3,4,0},{0,5,6,1,0,0},{5,9,8,7,6,5},{9,4,3,8,9,0},
    {1,6,7,2,1,0},{3,2,7,8,3,0},{0,4,9,5,0,0} }; //面的顶点序
    int i, j, k, SN;
    int p1, p2, p3, u1, u2, u3, v1, v2, v3;
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    gluLookAt(s1, s2, s3, 0, 0, 0, 0, 1, 0);
    glLineWidth(3);
     glColor3f(1.0, 0.0, 1.0);
   //Z-buffer算法
    for (i = 0; i < 7; i++)
    {
        p1 = fp[i][0]; p2 = fp[i][1]; p3 = fp[i][2]; 
        u1 = x[p2] - x[p1]; u2 = y[p2] - y[p1]; u3 = z[p2] - z[p1];
        v1 = x[p3] - x[p2]; v2 = y[p3] - y[p2]; v3 = z[p3] - z[p2];
        SN = s1*(u2 * v3 - u3 * v2) + s2*(u3 * v1 - u1 * v3) + s3*(u1 * v2 - u2 * v1);
        if (SN < 0) f[i] = -1;  
    }
    for (i = 0; i < 7; i++)
    {//消隐的部分
        if (f[i] == -1)
        {
            glEnable(GL_LINE_STIPPLE);  //画点线
            glLineStipple(2, 0x3333);
            glBegin(GL_LINE_STRIP);
            for (j = 0; j < p[i]; j++)
            {
                k = fp[i][j]; glVertex3i(x[k], y[k], z[k]);
            }
            glEnd();
            glFlush();
            glDisable(GL_LINE_STIPPLE);
        }
        //可见的部分
        else
        {
            glBegin(GL_LINE_STRIP);  //画线
            for (j = 0; j < p[i]; j++)
            {
                k = fp[i][j]; glVertex3i(x[k], y[k], z[k]);
            }
            glEnd();
            glFlush();
        }
    }
}

int main(int argc, char* argv[])
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(600, 600);
    glutCreateWindow("Z-buffer消隐算法");

    Init();
    glutDisplayFunc(myDisplay);
    glutReshapeFunc(Reshape);

glutMainLoop();

    return 0;
}

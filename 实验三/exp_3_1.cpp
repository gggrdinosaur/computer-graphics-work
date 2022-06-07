#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void init(void)
{//初始化函数
    glClearColor(1.0,1.0,1.0,0.0);  //设置窗口背景色为白色
    glMatrixMode (GL_PROJECTION);       //指定投影矩阵
    gluOrtho2D (30.0, 15.0, 30.0, 15.0);   //指定显示的区域
}

//画点函数
void setPixel (int x,int y)
{
    glPointSize(5.0f);
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
    glFlush();
}

//Bresenham算法
void lineBres(int x0,int y0,int xEnd,int yEnd)
{
    glColor3f(1.0,0.4,0.2);   //设置线条颜色
    glPointSize(3.0f); //设置像素点大小

    int dx = abs(xEnd - x0),dy = abs(yEnd - y0);
    int d = 2 *dy -dx;
    int twoDy = 2 * dy, twoDyMinusDx = 2 * ( dy -dx);
    int x,y;

    if(x0 > xEnd)
    {
        x = xEnd;
        y = yEnd;
        xEnd = x0;
    }
    else
    {
        x = x0;
        y = y0;
    }
    setPixel(x,y);
    while(x < xEnd)
    {
        x++;
        if(d < 0)
           d += twoDy;
        else
        {
            y++;
            d += twoDyMinusDx;
        }
        setPixel(x,y);
    }
}

//窗口大小改变登记函数
void changeSize(GLsizei w,GLsizei h)
{
    if (h == 0)
        h =1;
    glViewport(0,0,w,h);   //设置视区尺寸
    glMatrixMode(GL_PROJECTION);  //重置坐标系统
    glLoadIdentity();
    if(w <= h)   //建立修剪空间的范围
        glOrtho(0.0f,250.0f,0.0f,250.0f*h/w,1.0,-1.0);
    else
        glOrtho(0.0f,250.f*w/h,0.0f,250.0f,1.0,-1.0);
}
//调用函数
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);  //用当前背景色填充窗口
    lineBres(30,50,300,500);  //给定两个坐标
}

int main (int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(500,500);
    glutCreateWindow("LINE");
     glutDisplayFunc(display);
    glutReshapeFunc(changeSize);

    init ();
    glutMainLoop();

    return 0;
}
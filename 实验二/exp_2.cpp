#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

void init(void)
{//初始化函数
    glClearColor(1.0,1.0,1.0,0.0);  //设置窗口背景色为白色
    glMatrixMode (GL_PROJECTION);       //指定投影矩阵
    gluOrtho2D (30.0, 15.0, 30.0, 15.0);   //指定显示的区域
}

//取整函数
int Round (const float a )
{
    return (int)(a + 0.5);
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

//DDA算法
void lineDDA(int x0,int y0,int xEnd,int yEnd)
{
    glColor3f(1.0,0.4,0.2);   //设置线条颜色
    glPointSize(3.0f); //设置像素点大小
    int dx = xEnd - x0,dy = yEnd - y0,steps,k;
    float xIncrement,yIncrement,x = x0,y = y0;

    if(fabs(dx) > fabs(dy))  //确定步长，谁大取谁
        steps = fabs(dx);
    else
        steps = fabs(dy);
    xIncrement = float(dx) / float(steps);
    yIncrement = float(dy) / float(steps);

    setPixel(Round(x),Round(y));
    for(k = 0;k < steps;k++)
    {
        x+=xIncrement;
        y+=yIncrement;
        setPixel(Round(x),Round(y));
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
    lineDDA(30,50,300,500);  //给定两个坐标
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
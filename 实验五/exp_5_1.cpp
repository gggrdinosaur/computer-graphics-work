#include <GL/glut.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void init(void)
{//初始化函数
    glClearColor(1.0,1.0,1.0,0.0);  //设置窗口背景色为白色
    glMatrixMode (GL_PROJECTION);       //指定投影矩阵
    gluOrtho2D (-400.0, 400.0, -400.0, 400.0);   //指定显示的区域
}

//画点函数
void setPixel (int x,int y)
{
    glPointSize(1.0f);
    glBegin(GL_POINTS);
        glVertex2i(x,y);
    glEnd();
    glFlush();
}

//八分法画圆
void Circle(int x, int y)
{
	setPixel(x, y);
	setPixel(-x, y);
	setPixel(x, -y);
	setPixel(-x, -y);
	setPixel(y, x);
	setPixel(-y, x);
	setPixel(y, -x);
	setPixel(-y, -x);

}
//中点Bresenham画圆算法
void circleBres(int r)
{
    glColor3f(1.0,0.4,0.2);   //设置颜色
    glPointSize(1.0f); //设置像素点大小

	int x, y;
	double d;
	x = 0; y = r; d = 1.25 - r;
	while (x <= y)   //判断是否结束
	{
		Circle(x, y);//八分法画圆
		if (d < 0)
			d += 2 * x + 3;
		else
		{
			d += 2 * (x - y) + 5;
			y--;
		}
		x++;
	}
}
//调用函数
void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT);  //用当前背景色填充窗口
    circleBres(100);  //给定圆的半径
}
int main (int argc,char **argv)
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(200,200);
    glutInitWindowSize(500,500);
    glutCreateWindow("LINE");
     glutDisplayFunc(display);

    init ();
    glutMainLoop();

    return 0;
}
#include <GL/glut.h>
#include <stdlib.h>

typedef  float Color[3];

//比较颜色函数
int compareColor(Color c1,Color c2)
{
   if(c1[0] != c2[0] || c1[1] != c2[1]  || c1[2] != c2[2])
       return 0;
   else
       return 1;
}
//初始化函数
void init(void)
{
   glClearColor(1.0,1.0,1.0,0.0);
   glMatrixMode (GL_PROJECTION);
   gluOrtho2D (0.0, 200.0, 0.0, 200.0);

}
//画点函数
void setPixel(GLint x,  GLint y)
{
   glBegin(GL_POINTS);
   glVertex2i(x, y);
   glEnd();
   glFlush();
}
//获取像素点颜色
void getPixel(GLint x, GLint y, Color c)
{
    glReadPixels(x,y,1,1,GL_RGB,GL_FLOAT,c);
}

//四联通
void BoundaryFill4(int x, int y,Color fillColor,Color boarderColor)
{
    Color interiorColor;

    getPixel(x,y,interiorColor);
    if (compareColor(interiorColor,boarderColor) == 0 && compareColor(interiorColor,fillColor) == 0){
        setPixel(x,y);
        BoundaryFill4(x+1,y,fillColor,boarderColor);
        BoundaryFill4(x-1,y,fillColor,boarderColor);
        BoundaryFill4(x,y+1,fillColor,boarderColor);
        BoundaryFill4(x,y-1,fillColor,boarderColor);
    }
}

//泛滥填充
void FloudFill4(int x, int y,Color fillColor,Color initColor)
{
    Color interColor;

    getPixel(x,y,interColor);
    if (compareColor(interColor,initColor) ==1 && compareColor(interColor,fillColor)  == 0){
        setPixel(x,y);
        FloudFill4(x+1,y,fillColor,initColor);
        FloudFill4(x-1,y,fillColor,initColor);
        FloudFill4(x,y+1,fillColor,initColor);
        FloudFill4(x,y-1,fillColor,initColor);
    }
}

//八联通
void BoundaryFill8(int x, int y,Color fillColor,Color boarderColor)
{
    Color interiorColor,a,b,c,d;

    getPixel(x, y, interiorColor);
    getPixel(x + 1, y - 1, a);
    getPixel(x, y - 1, b);
    getPixel(x, y + 1, c);
    getPixel(x - 1, y, d);
    int i = 0;
    if (compareColor(a, boarderColor) == 1) i++;
    if (compareColor(b, boarderColor) == 1) i++;
    if (compareColor(c, boarderColor) == 1) i++;
    if (compareColor(d, boarderColor) == 1) i++;

    if(i <= 1)
       if (compareColor(interiorColor,boarderColor) == 0 && compareColor(interiorColor,fillColor) == 0){
          setPixel(x,y);
          BoundaryFill8(x+1,y,fillColor,boarderColor);
          BoundaryFill8(x-1,y,fillColor,boarderColor);
          BoundaryFill8(x,y+1,fillColor,boarderColor);
          BoundaryFill8(x,y-1,fillColor,boarderColor);
          BoundaryFill8(x+1,y+1,fillColor,boarderColor);
          BoundaryFill8(x-1,y-1,fillColor,boarderColor);
          BoundaryFill8(x-1,y+1,fillColor,boarderColor);
          BoundaryFill8(x-1,y-1,fillColor,boarderColor);
       }
}

//画多边形
void polygon_1()
{
     glBegin(GL_LINE_LOOP);
     glLineWidth(4.0);
       glVertex2i(90, 40);
       glVertex2i(120, 100);
       glVertex2i(90, 160);
       glVertex2i(60, 160);
       glVertex2i(60, 40);
     glEnd();

}
void polygon_2()
{
     glBegin(GL_POLYGON);
     glLineWidth(4.0);
       glVertex2i(90, 40);
       glVertex2i(120, 100);
       glVertex2i(90, 160);
       glVertex2i(60, 160);
       glVertex2i(60, 40);
     glEnd();
}

void display(void)
{
   Color fillcolor={1.0,0.0,0.0};    //填充颜色
   Color boardercolor={0.0,0.0,1.0};   //边界颜色

   glClear(GL_COLOR_BUFFER_BIT);
   glViewport(0,0,200,200);
   glColor3fv(boardercolor);
   polygon_1();
   glColor3fv(fillcolor);
   BoundaryFill4(60,60,fillcolor,boardercolor);    //四联通
   //BoundaryFill8(60,60,fillcolor,boardercolor);   //八联通

   glViewport(400,0,200,200);
   glColor3fv(boardercolor);
   polygon_2();
   glColor3fv(fillcolor);
   FloudFill4(90,60,fillcolor,boardercolor);  //泛滥填充
   glFlush();
}

int main(int argc, char *argv[])
{
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGB | GLUT_SINGLE);
   glutInitWindowPosition(100, 100);
   glutInitWindowSize(600, 200);
   glutCreateWindow("4连通");
   init();
   glutDisplayFunc(display);
   glutMainLoop();

   return 0;
}
#include <GL/glut.h>
#include <cstdlib>
#include <cstdio>
#include <cmath>
#define SOLID 1
#define WIRE 2
#define stripeImageWidth 32
#define stripeImageHeight 32

int moveX,moveY;
int spinX = 0;
int spinY = 0;
int des = 0;
char choice;

static GLfloat xequalzero[] = { 1.0, 1.0, 1.0, 0.0 };
static GLfloat slanted[] = { 0.0, 1.0, 0.0, 0.0 };
static GLfloat *currentCoeff;
static float roangles = 60.0f;
void init(void)
{
    glEnable(GL_LIGHTING);  //启动光照
    glEnable(GL_LIGHT0);   //启动0号光源
    glEnable(GL_AUTO_NORMAL);  //把光反射到各个方向
    glEnable(GL_NORMALIZE);  //在转换之后和光照之前将法线向量标准化成单位长度

    //定义光源的颜色和位置
   GLfloat ambient[] = { 0.0, 0.8, 0.1, 0.1 };
   GLfloat diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat specular[] = { 1.0, 1.0, 1.0, 1.0 };
   GLfloat position[] = { -80.0, 50.0, 25.0, 1.0 };
   //选择光照模型
   GLfloat lmodel_ambient[] = { 0.4, 0.4, 0.4, 1.0 };
   GLfloat local_view[] = { 50.0 };
   glClearColor(0.0, 0.0, 0.0, 0.0);
   glShadeModel(GL_SMOOTH);
   //设置环境光
   glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
   //设置漫射光
   glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuse);
   //镜面光
   glLightfv(GL_LIGHT0, GL_SPECULAR, specular);
   //设置光源位置
   glLightfv(GL_LIGHT0, GL_POSITION, position);
   glLightModelfv(GL_LIGHT_MODEL_AMBIENT, lmodel_ambient);
   glLightModelfv(GL_LIGHT_MODEL_LOCAL_VIEWER, local_view);
   //启动光照
   glEnable(GL_LIGHTING);
   //启用光源
   glEnable(GL_LIGHT0);
}

//茶壶
void display_teapot(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //圆点放坐标中心
	glLoadIdentity();
	gluLookAt(-2.0, -1.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//定义视角位置
    glPushMatrix();
    glRotated(spinX, 0, 1, 0);
	glRotated(spinY, 1, 0, 0);
    glRotatef(roangles, 0.0, 1.0, 0.0);
    glTranslated(0, 0, des);
    glutSolidTeapot(3);   //茶壶

     glPopMatrix();
    glFlush();
}

//窗口重定义函数
void reshape(int w, int h) {
    //定义视口大小
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    //投影显示
    glMatrixMode(GL_PROJECTION);
    //坐标原点在屏幕中心
    glLoadIdentity();
    //操作模型视角
    gluPerspective(60.0, (GLfloat) w/(GLfloat) h, 1.0, 40.0);
    glMatrixMode(GL_MODELVIEW);
}

//自动旋转函数
void idle()
{
    roangles += 0.01f;
    glutPostRedisplay();
}


int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(600, 600);
    glutInitWindowPosition(100, 100);
    glutCreateWindow(argv[0]);
    init();

    glutDisplayFunc(display_teapot);
    //自动旋转
    glutIdleFunc(idle);
    //窗口重定义
    glutReshapeFunc(reshape);

    glutMainLoop();
    return 0;
}

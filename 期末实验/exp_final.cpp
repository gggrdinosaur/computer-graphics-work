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

//纹理矩阵
GLubyte stripeImage[stripeImageWidth][stripeImageHeight][4];
void makeStripeImage(void)
{
    int i, j;
    for (i = 0; i < stripeImageWidth; i++)
    {
        for (j = 0; j < stripeImageHeight; j++)
        {
            stripeImage[i][j][0] = (GLubyte)(i * 10 - 3);
            stripeImage[i][j][1] = (GLubyte)(j * 6 - 4);
            stripeImage[i][j][2] = (GLubyte)70;
            stripeImage[i][j][3] = (GLubyte)255;
        }
    }
}
static GLfloat xequalzero[] = { 1.0, 1.0, 1.0, 0.0 };
static GLfloat slanted[] = { 0.0, 1.0, 0.0, 0.0 };
static GLfloat *currentCoeff;
static float roangles = 60.0f;
void init(void)
{
    //纹理渲染
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glEnable(GL_DEPTH_TEST);//启动深度测试
    glShadeModel(GL_SMOOTH);//明暗处理
    makeStripeImage();
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    //纹理过滤
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, 4, stripeImageWidth, stripeImageHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, stripeImage);
    glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
    currentCoeff = xequalzero;
    //纹理生成
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_OBJECT_LINEAR);
    glTexGeni(GL_S, GL_TEXTURE_GEN_MODE, GL_EYE_LINEAR);
    glTexGenfv(GL_S, GL_EYE_PLANE, currentCoeff);
    glEnable(GL_TEXTURE_GEN_S);  //启动贴图
    glEnable(GL_TEXTURE_2D);//启动纹理映射
    glEnable(GL_LIGHTING);  //启动光照
    glEnable(GL_LIGHT0);   //启动0号光源
    glEnable(GL_AUTO_NORMAL);  //把光反射到各个方向
    glEnable(GL_NORMALIZE);  //在转换之后和光照之前将法线向量标准化成单位长度


    //材质
    GLfloat mat_ambient[] = { 0.8, 0.8, 0.2, 1.0 };
    GLfloat mat_diffuse[] = { 0.1, 0.8, 0.5, 1.0 };
    GLfloat mat_specular[] = { 0.0, 0.0, 0.0, 1.0 };
    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT, mat_ambient);
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, mat_diffuse);
    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialf(GL_FRONT, GL_SHININESS, 100.0);


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

//画球
void drawBall(double R, double x, double y,double z, int MODE) {
	glPushMatrix();
	glTranslated(x,y,z);
	if (MODE == SOLID) {
		glutSolidSphere(R,20,20);  //实心图形
	} else if (MODE ==WIRE) {
		glutWireSphere(R,20,20);   //线框图
	}
	glPopMatrix();
}

//画半球
void drawHalfBall(double R, double x, double y,double z, int MODE) {
	glPushMatrix();
	glTranslated(x,y,z);
	GLdouble eqn[4]={0.0, 1.0, 0.0, 0.0};
	glClipPlane(GL_CLIP_PLANE0,eqn);
	glEnable(GL_CLIP_PLANE0);
	if (MODE == SOLID) {
		glutSolidSphere(R,20,20);  //实心图形
	} else if (MODE ==WIRE) {
		glutWireSphere(R,20,20);  //线框图
	}
	glDisable(GL_CLIP_PLANE0);
	glPopMatrix();
}

//画长方体
void drawSkewed(double l, double w, double h, double x, double y, double z, int MODE) {
	glPushMatrix();
	glScaled(l, w, h);
	glTranslated(x, y, z);
	if (MODE == SOLID) {
		glutSolidCube(1);  //实心图形
	} else if (MODE ==WIRE) {
		glutWireCube(1);   //线框图
	}
	glPopMatrix();
}
//机器人
void display_roboto(void) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    //圆点放坐标中心
	glLoadIdentity();
	gluLookAt(-2.0, -1.0, 20.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);//定义视角位置
    glPushMatrix();
    glRotated(spinX, 0, 1, 0);
	glRotated(spinY, 1, 0, 0);
    glRotatef(roangles, 0.0, 1.0, 0.0);
    glTranslated(0, 0, des);

    //头
	drawBall(2, 0, 1, 0, SOLID);
	//身体
	drawSkewed(5, 4.4, 4, 0, -0.75, 0, SOLID);
	//肩膀
	drawHalfBall(1, 3.5, -2.1, 0, SOLID);
	drawHalfBall(1, -3.5, -2.1, 0, SOLID);
	//胳膊
	drawSkewed(1, 3, 1, 3.5, -1.3, 0, SOLID);
	drawSkewed(1, 3, 1, -3.5, -1.3, 0, SOLID);
	//手
	drawBall(1, 3.5, -6.4, 0, SOLID);
	drawBall(1, -3.5, -6.4, 0, SOLID);
	//腿
	drawSkewed(1.2, 3, 2, 1, -2.4, 0, SOLID);
	drawSkewed(1.2, 3, 2, -1, -2.4, 0, SOLID);
	//脚
	drawSkewed(1.5, 1, 3, 0.9, -9.2, 0, SOLID);
	drawSkewed(1.5, 1, 3, -0.9, -9.2, 0, SOLID);

    glPopMatrix();
    glFlush();
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

//鼠标点击事件，设置光照
void mouseClick(int btn, int state, int x, int y) {
    moveX = x;
	moveY = y;
	GLfloat ambient[] = { (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, (float)rand() / RAND_MAX, 0.1 };
	 //设置环境光
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambient);
	//启用光源
	glEnable(GL_LIGHT0);
}

//键盘事件，移动、旋转物体
void keyPressed(unsigned char key, int x, int y) {
    switch (key) {
    case 'A':
        spinX -= 2;
        break;
    case 'D':
         spinX += 2;
        break;
    case 'W':
        des += 2;
        break;
    case 'S':
        des -= 2;
		break;
	}
	glutPostRedisplay();
}
// 鼠标移动事件，点击鼠标不放可移动物体
void mouseMove(int x, int y) {
	int dx = x - moveX;
	int dy = y - moveY;
	spinX += dx;
	spinY += dy;
	glutPostRedisplay();
	moveX = x;
	moveY = y;
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
    do{
    printf("请选择需要查看的图形：1、机器人 2、茶壶 \n");
	scanf("%c",&choice);
	getchar();
	if(choice=='1'){
		glutDisplayFunc(display_roboto);
        glutReshapeFunc(reshape);
        //鼠标点击事件，鼠标点击或者松开时调用
        glutMouseFunc(mouseClick);
	    //鼠标移动事件，鼠标按下并移动时调用
        glutMotionFunc(mouseMove);
	    //键盘事件
	    glutKeyboardFunc(keyPressed);
	}else if(choice=='2'){
		glutDisplayFunc(display_teapot);
		//自动旋转
		glutIdleFunc(idle);
		//窗口重定义
		glutReshapeFunc(reshape);

	}else{
	printf("输入有误\n");
	}
    }while(choice != '1' && choice != '2');

    glutMainLoop();
    return 0;
}

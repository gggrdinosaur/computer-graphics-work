#include<GL/glut.h>
#include<iostream>
#include<algorithm>
#include<cmath>
#include<vector>
using namespace std;

const int MAXN=200;
const int INF=1<<30;
const double eps=1e-10;
int winWidth=1000,winHeight=600;
int MyPointNum=0;
double PI=acos(-1.0);
double anga=PI/4,angb=PI/6;;
double Matrix[4][4]= {{1,0,0,0},{0,1,0,0},{0,0,1,0},{500,300,300,1}};
double Chang[4][4]= {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}; //基本变换矩阵;
double Touying[4][4]= {{1,0,0,0},{0,1,0,0},{0,0,0,0},{0,0,0,1}};
vector<int>MyFace[10];
int MyFaceNum=0;
struct point
{
    double x,y,z,tag;
} MyPoint[MAXN],ProcessPoint[MAXN],ResultPoint[MAXN];
struct piexl
{
    int color;
    double deepth;
} MyPiexl[1024][10240];

double GetZ(point TmpPoint[],int id1,int id2,int id3,double x,double y)
{
    double x2_x1=TmpPoint[id2].x-TmpPoint[id1].x;
    double x3_x1=TmpPoint[id3].x-TmpPoint[id1].x;

    double y2_y1=TmpPoint[id2].y-TmpPoint[id1].y;
    double y3_y1=TmpPoint[id3].y-TmpPoint[id1].y;

    double Z2_Z1=TmpPoint[id2].z-TmpPoint[id1].z;
    double Z3_Z1=TmpPoint[id3].z-TmpPoint[id1].z;

    double tmp=(x-TmpPoint[id1].x)*y2_y1*Z3_Z1+(x3_x1)*(y-TmpPoint[id1].y)*Z2_Z1-y3_y1*Z2_Z1*((x-TmpPoint[id1].x))
               -Z3_Z1*x2_x1*(y-TmpPoint[id1].y);
    if((y2_y1*x3_x1-x2_x1*y3_y1)==0)
        return -INF;//投影成一条线
    return (tmp+TmpPoint[id1].z*(y2_y1*x3_x1-x2_x1*y3_y1))/(y2_y1*x3_x1-x2_x1*y3_y1);
}


void XiaoYin(point TmpPoint[],int id)//消隐算法的实现
{
    int size=MyFace[id].size();
    int MinY=INF,MaxY=-INF;
    for(int i=0; i<size; i++)
    {
        if(TmpPoint[MyFace[id][i]].y>MaxY)
            MaxY=TmpPoint[MyFace[id][i]].y;
        if(TmpPoint[MyFace[id][i]].y<MinY)
            MinY=TmpPoint[MyFace[id][i]].y;
    }
    for(int y=MinY; y<=MaxY; y++)
    {
        vector<int>Vec;
        for(int i=0; i<size; i++)
        {
            if(TmpPoint[MyFace[id][i]].y==y)
            {
                Vec.push_back(TmpPoint[MyFace[id][i]].x);
                if((TmpPoint[MyFace[id][(i+1)%size]].y-TmpPoint[MyFace[id][i]].y)*(TmpPoint[MyFace[id][(i-1+size)%size]].y-TmpPoint[MyFace[id][i]].y)>0)
                {
                    Vec.push_back(TmpPoint[MyFace[id][i]].x);
                }
            }
            if((TmpPoint[MyFace[id][i]].y<y&&TmpPoint[MyFace[id][(i+1)%size]].y>y)||(TmpPoint[MyFace[id][i]].y>y&&TmpPoint[MyFace[id][(i+1)%size]].y<y))//y∈(y1,y2)或y∈(y2,y1)
            {
                int x=TmpPoint[MyFace[id][i]].x+(y-TmpPoint[MyFace[id][i]].y)*(TmpPoint[MyFace[id][(i+1)%size]].x-TmpPoint[MyFace[id][i]].x)
                      /(TmpPoint[MyFace[id][(i+1)%size]].y-TmpPoint[MyFace[id][i]].y);//此处暂直接取整
                Vec.push_back(x);
            }
        }
        sort(Vec.begin(),Vec.end());
        int tmpsize=Vec.size();
        for(int i=0; i<tmpsize; i+=2)
        {
            for(int j=Vec[i]; j<=Vec[i+1]; j++)
            {
                double tmpz=GetZ(TmpPoint,MyFace[id][0],MyFace[id][1],MyFace[id][2],j,y);
                if(tmpz>MyPiexl[j][y].deepth)
                {
                    MyPiexl[j][y].deepth=tmpz,MyPiexl[j][y].color=id;
                }
            }
        }
    }
}


void PiexInit()//初始化
{
    for(int i=0; i<800; i++)
    {
        for(int j=0; j<800; j++)
        {
            MyPiexl[i][j].color=-1;
            MyPiexl[i][j].deepth=-INF;
        }
    }
}

void MycubeInit()//初始化长方体
{
    MyPointNum=8;
    MyPoint[0].x=0,MyPoint[0].y=0,MyPoint[0].z=0,MyPoint[0].tag=1;
    MyPoint[1].x=100,MyPoint[1].y=0,MyPoint[1].z=0,MyPoint[1].tag=1;
    MyPoint[2].x=100,MyPoint[2].y=100,MyPoint[2].z=0,MyPoint[2].tag=1;
    MyPoint[3].x=0,MyPoint[3].y=100,MyPoint[3].z=0,MyPoint[3].tag=1;

    MyPoint[4].x=0,   MyPoint[4].y=0,   MyPoint[4].z=250,  MyPoint[4].tag=1;
    MyPoint[5].x=100, MyPoint[5].y=0,   MyPoint[5].z=250,  MyPoint[5].tag=1;
    MyPoint[6].x=100, MyPoint[6].y=100, MyPoint[6].z=250,  MyPoint[6].tag=1;
    MyPoint[7].x=0, MyPoint[7].y=100,   MyPoint[7].z=250,  MyPoint[7].tag=1;

    MyFaceNum=6;
    MyFace[0].push_back(0);
    MyFace[0].push_back(1);
    MyFace[0].push_back(2);
    MyFace[0].push_back(3);
    MyFace[1].push_back(0);
    MyFace[1].push_back(1);
    MyFace[1].push_back(5);
    MyFace[1].push_back(4);
    MyFace[2].push_back(1);
    MyFace[2].push_back(2);
    MyFace[2].push_back(6);
    MyFace[2].push_back(5);
    MyFace[3].push_back(2);
    MyFace[3].push_back(3);
    MyFace[3].push_back(7);
    MyFace[3].push_back(6);
    MyFace[4].push_back(3);
    MyFace[4].push_back(0);
    MyFace[4].push_back(4);
    MyFace[4].push_back(7);
    MyFace[5].push_back(4);
    MyFace[5].push_back(5);
    MyFace[5].push_back(6);
    MyFace[5].push_back(7);

}


void MyTriangularPrismInit()//初始化三棱锥
{
    MyPointNum=6;
    MyPoint[0].x=0,   MyPoint[0].y=0,   MyPoint[0].z=0,    MyPoint[0].tag=1;
    MyPoint[1].x=0,   MyPoint[1].y=200, MyPoint[1].z=0,    MyPoint[1].tag=1;
    MyPoint[2].x=0,   MyPoint[2].y=100, MyPoint[2].z=100,  MyPoint[2].tag=1;

    MyPoint[3].x=300, MyPoint[3].y=0,   MyPoint[3].z=0,    MyPoint[3].tag=1;
    MyPoint[4].x=300, MyPoint[4].y=200, MyPoint[4].z=0,    MyPoint[4].tag=1;
    MyPoint[5].x=300, MyPoint[5].y=100, MyPoint[5].z=100,  MyPoint[5].tag=1;

    MyFaceNum=6;
    MyFace[0].push_back(0);
    MyFace[0].push_back(1);
    MyFace[0].push_back(2);
    MyFace[1].push_back(0);
    MyFace[1].push_back(1);
    MyFace[1].push_back(4);
    MyFace[1].push_back(3);
    MyFace[3].push_back(1);
    MyFace[3].push_back(2);
    MyFace[3].push_back(5);
    MyFace[3].push_back(4);
    MyFace[4].push_back(2);
    MyFace[4].push_back(0);
    MyFace[4].push_back(3);
    MyFace[4].push_back(5);
    MyFace[5].push_back(3);
    MyFace[5].push_back(4);
    MyFace[5].push_back(5);
}

void MyTrans(point NewPoint[],point OldPoint[],double Tran[4][4])//获得变换后的用户图形的顶点
{
    double tx,ty,tz,ttag;
    for(int i=0; i<MyPointNum; i++)
    {
        tx=OldPoint[i].x,ty=OldPoint[i].y,tz=OldPoint[i].z,ttag=OldPoint[i].tag;
        NewPoint[i].x=tx*Tran[0][0]+ty*Tran[1][0]+tz*Tran[2][0]+ttag*Tran[3][0];
        NewPoint[i].y=tx*Tran[0][1]+ty*Tran[1][1]+tz*Tran[2][1]+ttag*Tran[3][1];
        NewPoint[i].z=tx*Tran[0][2]+ty*Tran[1][2]+tz*Tran[2][2]+ttag*Tran[3][2];
        NewPoint[i].tag=tx*Tran[0][3]+ty*Tran[1][3]+tz*Tran[2][3]+ttag*Tran[3][3];
    }
}


void OnDraw(point TmpPoint[])//绘制
{
    glBegin(GL_POINTS);
    for(int i=0; i<800; i++)
    {
        for(int j=0; j<800; j++)
        {
            switch(MyPiexl[i][j].color)
            {
            case 0:
                glColor3f(1.0f,1.0f,0.0f);
                break;
            case 1:
                glColor3f(0.0f,1.0f,1.0f);
                break;
            case 2:
                glColor3f(1.0f,0.0f,0.0f);
                break;
            case 3:
                glColor3f(0.0f,1.0f,0.0f);
                break;
            case 4:
                glColor3f(0.0f,0.0f,1.0f);
                break;
            case 5:
                glColor3f(0.0f,1.0f,1.0f);
                break;
            default:
                glColor3f(0.0f,0.0f,0.0f);
                break;
            }
            glVertex2i(i,j);
        }
    }
    glEnd();
}

void Display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    OnDraw(ResultPoint);
    glutSwapBuffers();
}

void GetProcess()
{
    PiexInit();
    MyTrans(ProcessPoint,MyPoint,Chang);
    MyTrans(ResultPoint,ProcessPoint,Matrix);
    for(int i=0; i<MyFaceNum; i++) //依次计算所有面
        XiaoYin(ResultPoint,i);
    MyTrans(ResultPoint,ResultPoint,Touying);//进行投影
}

void MyInit()//窗口初始化
{
    glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
    MyTriangularPrismInit();
    anga=PI/4;
    angb=PI/6;
    GetProcess();
}

void ChangeSize(int w, int h)
{
    winWidth=w;
    winHeight=h;
    glViewport(0,0,w,h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,winWidth,0.0,winHeight);
}

void MyKeyPcocess(int key,int x,int y)//键盘响应函数
{
    if(key==GLUT_KEY_UP)
        anga+=PI/180;
    if(key==GLUT_KEY_DOWN)
        anga-=PI/180;
    if(key==GLUT_KEY_LEFT)
        angb+=PI/180;
    if(key==GLUT_KEY_RIGHT)
        angb-=PI/180;
    double Sina=sin(anga),  Cosa=cos(anga),   Sinb=sin(angb),  Cosb=cos(angb);
    Chang[0][0]=Cosa,   Chang[0][1]=-Sina*Sinb,   Chang[0][2]=Sina*Cosb;
    Chang[1][0]=0,      Chang[1][1]=Cosb,         Chang[1][2]=Sinb;
    Chang[2][0]=-Sina,  Chang[2][1]= -Cosa*Sinb,  Chang[2][2]=Cosa*Cosb;
    GetProcess();
    Display();
}

void MyMenuProcess(int value)
{
    for(int i=0; i<10; i++)
        MyFace[i].clear();
    if(1==value)
        MycubeInit();
    if(2==value)
        MyTriangularPrismInit();
    GetProcess();
    glutPostRedisplay();
}

int main(int argc, char* argv[])//主函数
{
    glutInit(&argc,argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGB);
    glutInitWindowSize(600,600);
    glutInitWindowPosition(100,100);
    glutCreateWindow("三维图形消隐");
    glutDisplayFunc(Display);
    glutReshapeFunc(ChangeSize);
    glutSpecialFunc(MyKeyPcocess);
    glutCreateMenu(MyMenuProcess);
    glutAddMenuEntry("三棱柱",2);
    glutAttachMenu(GLUT_RIGHT_BUTTON);
    MyInit();
    glutMainLoop();
    return 0;
}

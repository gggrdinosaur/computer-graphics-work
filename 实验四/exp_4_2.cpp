#include<GL/glut.h>
const int POINTNUM = 4;   //多边形的顶点数

void init(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(50, 100);
    glutInitWindowSize(400, 400);
    glutCreateWindow("Polygon Fill");
    glClearColor(1.0, 1.0, 1.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    gluOrtho2D(0, 400, 0, 400);
}

//定义边表
typedef struct XET
{
    float x;    //当前扫描线与边的交点的x坐标
    float dx;  //边斜率的倒数
    float ymax;   //边的上端点y坐标
    XET * next;    //指向下一条边的指针
} AET, NET;

//定义多边形
struct point
{
    float x;  //多边形顶点x坐标
    float y;  //多边形顶点y坐标
} polypoint[POINTNUM] = { {100,300},{50,150},{120,50},{150,270} };

//扫描线填充算法
void PolyScan()
{
    int MaxY = 0;
    int i;
    for(i = 0; i < POINTNUM; i ++)   //找到多边形最大的y坐标
        if(polypoint[i].y > MaxY)
            MaxY = polypoint[i].y;
    AET * pAET = new AET;  //初始化活性边表AET为空
    pAET->next = NULL;
    NET * pNET[1024];
    for(i=0; i <= MaxY; i ++)    //初始化新边表头指针
    {
        pNET[i] = new NET;
        pNET[i]->next = NULL;
    }
    glClear(GL_COLOR_BUFFER_BIT);   //用当前背景颜色填充窗口
    glColor3f(1.0, 0.5, 0.0);   //填充颜色
    glBegin(GL_POINTS);
    for(i = 0; i <= MaxY; i ++)   //扫描线与多边形顶点求交
    {
        for(int j = 0; j < POINTNUM; j ++)
            if(polypoint[j].y == i)      //有交点，求交点坐标
            {
                if(polypoint[(j - 1 + POINTNUM) % POINTNUM].y > polypoint[j].y)
                {
                    NET * p = new NET;
                    p->x = polypoint[j].x;      //当前扫描线与边交点的x坐标
                    p->ymax = polypoint[(j - 1 + POINTNUM) % POINTNUM].y;   //边的上端点y坐标
                    p->dx = (polypoint[(j - 1 + POINTNUM) % POINTNUM].x - polypoint[j].x) / (polypoint[(j - 1 + POINTNUM) % POINTNUM].y - polypoint[j].y);   //计算边斜率的倒数
                    p->next = pNET[i]->next;
                    pNET[i]->next = p;
                }
                if(polypoint[(j + 1 + POINTNUM) % POINTNUM].y > polypoint[j].y)
                {
                    NET * p = new NET;
                    p->x = polypoint[j].x;
                    p->ymax = polypoint[(j + 1 + POINTNUM) % POINTNUM].y;
                    p->dx = (polypoint[(j + 1 + POINTNUM) % POINTNUM].x - polypoint[j].x) / (polypoint[(j + 1 + POINTNUM) % POINTNUM].y - polypoint[j].y);
                    p->next = pNET[i]->next;
                    pNET[i]->next = p;
                }
            }
    }

    //排序
    for(i = 0; i <= MaxY; i ++)
    {
        NET * p = pAET->next;
        while(p)  //修改x坐标，使x=x+dx  (dx为1/k)
        {
            p->x = p->x + p->dx;
            p = p->next;
        }
        AET * tq = pAET;
        p = pAET->next;
        tq->next = NULL;
        while(p)  //按x坐标递增顺序排序
        {
            while(tq->next && p->x >= tq->next->x)
                tq = tq->next;
            NET * s = p->next;
            p->next = tq->next;
            tq->next = p;
            p = s;
            tq = pAET;
        }
        AET * q = pAET;
        p = q->next;
        while(p)  //遍历AET，将ymax = i的结点从AET表中删除
        {
            if(p->ymax == i)
            {
                q->next = p->next;
                delete p;
                p = q->next;
            }
            else
            {
                q = q->next;
                p = q->next;
            }
        }
        p = pNET[i]->next;
        q = pAET;
        while(p)   //重新排序，将交点按x递增顺序排序
        {
            while(q->next && p->x >= q->next->x)
                q = q->next;
            NET * s = p->next;
            p->next = q->next;
            q->next = p;
            p = s;
            q = pAET;
        }

        p = pAET->next;
        while(p && p->next)   //遍历AET表，填充颜色
        {
            for(float j = p->x; j <= p->next->x; j++)
                glVertex2i(static_cast<int>(j), i);
            p = p->next->next;
        }
    }
    glEnd();
    glFlush();
}
void myDisplay(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    glColor3f(1.0, 1.0, 1.0);
    glPointSize(1);
    glBegin(GL_POINTS);
    PolyScan();
    glEnd();
    glFlush();
}

int main(int argc, char** argv)
{
    init(argc, argv);
    glutDisplayFunc(myDisplay);
    glutMainLoop();

    return 0;
}
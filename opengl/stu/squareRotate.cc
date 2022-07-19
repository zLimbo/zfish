#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

#include <cmath>
#include <cstdio>
#include <cstdlib>

#define WINDOW_WIDTH 500
#define WINDOW_HEIGHT 500
#define WINDOW_POS_X 400
#define WINDOW_POS_Y 100

#define OPTION_LINE 00
#define OPTION_TRIANGLE 01
#define OPTION_RECTANGLE 02
#define OPTION_HEXAGON 03

#define OPTION_RED 10
#define OPTION_GREEN 11
#define OPTION_BLUE 12
#define OPTION_WHITE 13

#define OPTION_ADD 20
#define OPTION_DEC 21

#define OPTION_MOVE_UP 30
#define OPTION_MOVE_DOWN 31
#define OPTION_MOVE_LEFT 32
#define OPTION_MOVE_RIGHT 33

#define OPTION_CLOCKWISE 40
#define OPTION_ANTICLOCKWISE 41

#define DEGREES_TO_RADIANS (3.1415926 / 180.0f);

int TriangleCount = 0;

GLfloat theta = 0.0f;
GLfloat Red = 1.0f;
GLfloat Green = 1.0f;
GLfloat Blue = 1.0f;
GLfloat Size = 1.0f;
GLfloat X1 = -0.5, Y1 = -0.5, X2 = 0.5, Y2 = 0.5;
GLfloat X3 = -0.5, Y3 = 0.5;

void (*drawGraph)();  // ����ָ��

/**��������
 *
 */
void drawHexagon() {
    int t = 0;
    glBegin(GL_POLYGON);
    while (t < 6) {  // ����
        GLfloat radian = (theta + t * 60) * DEGREES_TO_RADIANS;
        glVertex2f(cos(radian) * Size, sin(radian) * Size);
        ++t;
    }
    glEnd();
}

/**����
 *
 */
void drawLine() {
    glBegin(GL_LINES);
    glVertex2f(X1 * Size, Y1 * Size);
    glVertex2f(X2 * Size, Y2 * Size);
    glEnd();
}

/**��������
 *
 */
void drawTriangle() {
    glBegin(GL_TRIANGLES);
    glVertex2f(X1 * Size, Y1 * Size);
    glVertex2f(X2 * Size, Y2 * Size);
    glVertex2f(X3 * Size, Y3 * Size);
    glEnd();
}

/**������
 *
 */
void drawRectangle() {
    glBegin(GL_QUADS);
    glVertex2f(X1 * Size, Y1 * Size);
    glVertex2f(X2 * Size, Y1 * Size);
    glVertex2f(X2 * Size, Y2 * Size);
    glVertex2f(X1 * Size, Y2 * Size);
    glEnd();
}

/**��ʾ����
 *
 */
void myDisplayFunc() {
    glClear(GL_COLOR_BUFFER_BIT);
    (*drawGraph)();
    glutSwapBuffers();
}

/**ͼ�β˵��¼�
 *
 */
void pocessGraphMenuEvent(int graph_) {
    switch (graph_) {
        case OPTION_LINE:  // ����
            drawGraph = &drawLine;
            break;
        case OPTION_TRIANGLE:  // ��������
            drawGraph = &drawTriangle;
            break;
        case OPTION_RECTANGLE:  // ������
            drawGraph = &drawRectangle;
            break;
        case OPTION_HEXAGON:
            drawGraph = &drawHexagon;
        default:
            break;
    }
    if (drawGraph == &drawTriangle) {
        TriangleCount = 1;
    } else {
        TriangleCount = 0;
    }
    glLoadIdentity();
    glutPostRedisplay();  //�����ػ�
}

/**��С�˵��¼�
 *
 */
void pocessSizeMenuEvent(int size_) {
    if (size_ == OPTION_ADD) {
        Size += 0.1;
    } else if (size_ == OPTION_DEC && Size > 0.1) {
        Size -= 0.1;
    }
    glutPostRedisplay();  //�����ػ�
}

/**��ɫ�˵��¼�
 *
 */
void pocessColorMenuEvent(int color_) {
    switch (color_) {
        case OPTION_RED:  // ��ɫ
            glColor3f(1.0f, 0.0f, 0.0f);
            break;
        case OPTION_GREEN:  // ��ɫ
            glColor3f(0.0f, 1.0f, 0.0f);
            break;
        case OPTION_BLUE:  // ��ɫ
            glColor3f(0.0f, 0.0f, 1.0f);
            break;
        case OPTION_WHITE:  // ��ɫ
            glColor3f(1.0f, 1.0f, 1.0f);
            break;
        default:
            break;
    }
    glutPostRedisplay();  //�����ػ�
}

/**�ƶ��˵��¼�
 *
 */
void pocessMoveMenuEvent(int move_) {
    switch (move_) {
        case OPTION_MOVE_UP:  //����
            glTranslatef(0.0f, 0.1f, 0.0f);
            break;
        case OPTION_MOVE_DOWN:  //����
            glTranslatef(0.0f, -0.1f, 0.0f);
            break;
        case OPTION_MOVE_LEFT:  //����
            glTranslatef(-0.1f, 00.0f, 0.0f);
            break;
        case OPTION_MOVE_RIGHT:  //����
            glTranslatef(0.1f, 00.0f, 0.0f);
            break;
        default:
            break;
    }
    glutPostRedisplay();  //�����ػ�
}

/**��ת�˵��¼�
 *
 */
void pocessRotateMenuEvent(int rotate_) {
    switch (rotate_) {
        case OPTION_CLOCKWISE:  // ˳ʱ��
            glRotatef(-15.0f, 0.0f, 0.0f, 1.0f);
            break;
        case OPTION_ANTICLOCKWISE:  // ��ʱ��
            glRotatef(15.0f, 0.0f, 0.0f, 1.0f);
            break;
        default:
            break;
    }
    glutPostRedisplay();
}

/**�����˵�
 *
 */
void createMyMenu() {
    // �˵�
    int mainMenu;
    int graphMenu;
    int colorMenu;
    int sizeMenu;
    int moveMenu;
    int rotateMenu;

    // ͼ�β˵�
    graphMenu = glutCreateMenu(pocessGraphMenuEvent);
    glutAddMenuEntry("�߶�", OPTION_LINE);
    glutAddMenuEntry("������", OPTION_TRIANGLE);
    glutAddMenuEntry("����", OPTION_RECTANGLE);
    glutAddMenuEntry("������", OPTION_HEXAGON);

    // ��ɫ�˵�
    colorMenu = glutCreateMenu(pocessColorMenuEvent);
    glutAddMenuEntry("��", OPTION_RED);
    glutAddMenuEntry("��", OPTION_GREEN);
    glutAddMenuEntry("��", OPTION_BLUE);
    glutAddMenuEntry("��", OPTION_WHITE);

    // ��С�˵�
    sizeMenu = glutCreateMenu(pocessSizeMenuEvent);
    glutAddMenuEntry("����", OPTION_ADD);
    glutAddMenuEntry("��С", OPTION_DEC);

    // �ƶ��˵�
    moveMenu = glutCreateMenu(pocessMoveMenuEvent);
    glutAddMenuEntry("����", OPTION_MOVE_UP);
    glutAddMenuEntry("����", OPTION_MOVE_DOWN);
    glutAddMenuEntry("����", OPTION_MOVE_LEFT);
    glutAddMenuEntry("����", OPTION_MOVE_RIGHT);

    // ��ת�˵�
    rotateMenu = glutCreateMenu(pocessRotateMenuEvent);
    glutAddMenuEntry("˳ʱ��", OPTION_CLOCKWISE);
    glutAddMenuEntry("��ʱ��", OPTION_ANTICLOCKWISE);

    // ���˵�
    mainMenu = glutCreateMenu(NULL);
    glutAddSubMenu("ͼ��", graphMenu);
    glutAddSubMenu("��ɫ", colorMenu);
    glutAddSubMenu("��С", sizeMenu);
    glutAddSubMenu("�ƶ�", moveMenu);
    glutAddSubMenu("��ת", rotateMenu);

    // �Ҽ�����
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void idle() {}

/**����¼���Ӧ
 *
 */
void myMouseFunc(int btn_, int state_, int x_, int y_) {
    if (btn_ == GLUT_LEFT_BUTTON) {
        if (TriangleCount == 0) {  // ��������
            if (state_ == GLUT_DOWN) {
                X1 = (GLfloat)x_ / WINDOW_WIDTH * 2 - 1.0f;
                Y1 = 1.0f - (GLfloat)y_ / WINDOW_HEIGHT * 2;
            }
            if (state_ == GLUT_UP) {
                X2 = (GLfloat)x_ / WINDOW_WIDTH * 2 - 1.0f;
                Y2 = 1.0f - (GLfloat)y_ / WINDOW_HEIGHT * 2;
                glutPostRedisplay();  //�����ػ�
            }
        } else if (state_ == GLUT_DOWN) {  // ������
            if (TriangleCount == 1) {
                X1 = (GLfloat)x_ / WINDOW_WIDTH * 2 - 1.0f;
                Y1 = 1.0f - (GLfloat)y_ / WINDOW_HEIGHT * 2;
                TriangleCount = 2;
            } else if (TriangleCount == 2) {  // �����εĵڶ�������
                X2 = (GLfloat)x_ / WINDOW_WIDTH * 2 - 1.0f;
                Y2 = 1.0f - (GLfloat)y_ / WINDOW_HEIGHT * 2;
                TriangleCount = 3;
            } else if (TriangleCount == 3) {  // �����εĵ���������
                X3 = (GLfloat)x_ / WINDOW_WIDTH * 2 - 1.0f;
                Y3 = 1.0f - (GLfloat)y_ / WINDOW_HEIGHT * 2;
                glutPostRedisplay();  //�����ػ�
                TriangleCount = 1;
            }
        }
    }
}

/**��ʼ��
 *
 */
void myInitial() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glColor3f(1.0f, 1.0f, 1.0f);
    glShadeModel(GL_FLAT);
    drawGraph = &drawHexagon;
}

/**������
 *
 */
int main(int argc, char** argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    // ����
    glutInitWindowPosition(WINDOW_POS_X, WINDOW_POS_Y);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutCreateWindow("MyDrawing");
    myInitial();

    glutDisplayFunc(&myDisplayFunc);
    glutMouseFunc(&myMouseFunc);
    createMyMenu();
    // �¼�ѭ���ص�
    glutMainLoop();

    return 0;
}
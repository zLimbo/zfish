/*
 *  simple2.c
 *  This program draws a white rectangle on a black background.
 */

#include <GL/glut.h> /* glut.h includes gl.h and glu.h*/

void display(void)

{
    /* clear window */

    glClear(GL_COLOR_BUFFER_BIT);

    /* draw unit square polygon */

    glBegin(GL_POLYGON);
    glVertex2f(-0.5, -0.5);
    glVertex2f(-0.5, 0.5);
    glVertex2f(0.5, 0.5);
    glVertex2f(0.5, -0.5);
    glEnd();

    /* flush GL buffers */

    glFlush();
}

void init() {
    /* set clear color to black */

    glClearColor(0.0, 1.0, 0.0, 0.0);
    /* set fill  color to white */

    glColor3f(1.0, 0.0, 0.0);

    /* set up standard orthogonal view with clipping */
    /* box as cube of side 2 centered at origin */
    /* This is default view and these statement could be removed */

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(-0.0, 1.0, -0.0, 1.0, -1.0, 1.0);
}

int main(int argc, char** argv) {
    /* Initialize mode and open a window in upper left corner of screen */
    /* Window title is name of program (arg[0]) */

    /* ��ʼ�����������в������д��� */
    glutInit(&argc, argv);

    /* �趨���ڵ���ʾģʽ���������ͺ���ɫ��Ϊ�������RGB��ɫģ�� */
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);

    /* ���崰�ڿ���Ϊ300���أ��߶�Ϊ300���� */
    glutInitWindowSize(400, 400);

    /* ���崰��λ�ã�������Ļ��߽�0���أ�������Ļ�ϱ߽�0����
     */
    glutInitWindowPosition(100, 300);

    /* ����һ����Ϊ��simple���Ĵ��� */
    glutCreateWindow("�ҵĳ���");

    /* ���õ�ǰ���ڵ���ʾ�ص����� */
    glutDisplayFunc(display);

    /* ��ɴ��ڳ�ʼ�����趨��ͼ���� */
    init();

    /* ������GLUT�¼�����ѭ�� */
    glutMainLoop();

    return 0;
}
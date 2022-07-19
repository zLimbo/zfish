
#include <GL/glut.h>

void initial() {
    glClearColor(1.0, 1.0, 1.0, 0.0);
}

void DrawTriangle() {
    glBegin(GL_TRIANGLES);
    glVertex2f(20.0, 20.0);
    glVertex2f(80.0, 30.0);
    glVertex2f(50.0, 70.0);
    glEnd();
}

void display() {
    glClear(GL_COLOR_BUFFER_BIT);

    glColor3f(0.0, 0.0, 0.0);  // ��ɫ
    DrawTriangle();

    /* ƽ�� */
    glColor3f(1.0, 0.0, 0.0);       // ��ɫ
    glTranslatef(40.0, 70.0, 0.0);  //ƽ��
    DrawTriangle();

    /* ��ת */
    glColor3f(0.0, 1.0, 0.0);      // ��ɫ
    glRotatef(30, 0.0, 0.0, 1.0);  //��ת
    glTranslatef(80.0, 0.0, 0.0);  // ƽ��
    DrawTriangle();
    glRotatef(-30, 0.0, 0.0, 1.0);  //��ת��

    /* ���� */
    glColor3f(0.0, 0.0, 1.0);      // ��ɫ
    glScalef(2.0, 2.0, 2.0);       //�����Ŵ�
    glTranslatef(0.0, 20.0, 0.0);  //ƽ��
    DrawTriangle();

    glFlush();
}

void reshape(int w, int h) {
    glViewport(0, 0, (GLsizei)w, (GLsizei)h);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, (GLdouble)w, 0.0, (GLdouble)h);
}

int main(int argc, char **argv) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(300, 300);
    glutInitWindowPosition(200, 200);
    glutCreateWindow("Triangle");
    initial();
    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}

/*
    3. �Զ���ΪV1V2V3�������ν���
    ƽ�ơ���ת�����������еȻ����任��
    �����ζ��������Ϊ��
    V1(20.0,20.0)��V2(80.0,30.0)��V3(50.0,70.0)��
*/
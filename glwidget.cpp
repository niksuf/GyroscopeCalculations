#include "glwidget.h"
#include <QMouseEvent>
#include <QWheelEvent>

GLWidget:: GLWidget(QWidget *parent) : QOpenGLWidget(parent)
{

}
void GLWidget::initializeGL()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0,0,0,0);
}

void GLWidget::resizeGL(int w, int h)
{
    glViewport(0,0,w,h);
}

void GLWidget::paintGL()
{
    int W = QWidget::width();
    int H = QWidget::height();
    float aspect = W / H;

    glClearColor(0, 0, 0, 0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(-aspect, aspect, -1,1,1,500);

    glTranslatef(0, 0, -4);
    glRotatef(-60,1,0,0);
    glRotatef(250,0,0,1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glBegin(GL_LINES);
        glColor3f(1.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(3.0f,0.0f,0.0f);

        glColor3f(0.0f,1.0f,0.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,3.0f,0.0f);

        glColor3f(0.0f,0.0f,1.0f);
        glVertex3f(0.0f,0.0f,0.0f);
        glVertex3f(0.0f,0.0f,3.0f);
     glEnd();

     glMatrixMode(GL_MODELVIEW);
     glLoadIdentity();
     glRotatef(pitch,1,0,0);
     glRotatef(roll,0,1,0);
     glRotatef(yaw,0,0,1);

     glColor3f(0.2,0.8,0.2);

     glBegin(GL_QUADS);
        glVertex3f(2,2, -0.1);
        glVertex3f(2,-2, -0.1);
        glVertex3f(-2,-2, -0.1);
        glVertex3f(-2,2, -0.1);

        glVertex3f(2,2, +0.1);
        glVertex3f(2,-2, +0.1);
        glVertex3f(-2,-2, +0.1);
        glVertex3f(-2,2, +0.1);

        glVertex3f(2,2, -0.1);
        glVertex3f(2,-2, -0.1);
        glVertex3f(2,-2, +0.1);
        glVertex3f(2,2, +0.1);

        glVertex3f(2,-2, -0.1);
        glVertex3f(-2,-2, -0.1);
        glVertex3f(-2,-2, +0.1);
        glVertex3f(2,-2, +0.1);

        glVertex3f(-2,-2, -0.1);
        glVertex3f(-2,2, -0.1);
        glVertex3f(-2,2, +0.1);
        glVertex3f(-2,-2, +0.1);

        glVertex3f(-2,2, -0.1);
        glVertex3f(2,2, -0.1);
        glVertex3f(2,2, +0.1);
        glVertex3f(-2,2, +0.1);
     glEnd();
}

void GLWidget::mousePressEvent (QMouseEvent* e)
{

}

void GLWidget::mouseMoveEvent (QMouseEvent* e)
{

}

void GLWidget::wheelEvent (QWheelEvent* e)
{

}

void GLWidget::SetAngles(float pitch, float roll, float yaw)
{
    this->pitch = pitch;
    this->roll = roll;
    this->yaw = yaw;
}

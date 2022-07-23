#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QWidget>
#include <QObject>
#include <QOpenGLWidget>

class GLWidget : public QOpenGLWidget
{
    //Q_OBJECT
public:
    /*explicit*/ GLWidget(QWidget *parent=nullptr);
    void SetAngles(float pitch, float roll, float yaw);

protected:
    void initializeGL() override;

    void resizeGL(int w, int h) override;

    void paintGL() override;

    void mousePressEvent (QMouseEvent* e) override;

    void mouseMoveEvent (QMouseEvent* e) override;

    void wheelEvent (QWheelEvent* e) override;

    //void drawCube();

private:
    float pitch, roll, yaw;

};

#endif // GLWIDGET_H

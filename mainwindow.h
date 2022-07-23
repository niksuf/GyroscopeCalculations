#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <winsock2.h>
#include <QTimer>
#include <QtNetwork/QTcpSocket>
#include <QtNetwork/QHostAddress>
#include <math.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void ready();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void refresh();

    void updateData();

private:
    Ui::MainWindow *ui;
    QTcpSocket s;
    QTimer timer, timerspeed;
    struct Data
    {
        float gx, gy, gz;
        float pitch, roll, yaw;
        int prevTime;
    };
    Data *output;
    Data set;
    struct Packs
    {
        int time;
        float gx, gy, gz;
    } msg;
    bool flag=false;
    float pkgcount=0, speed;
};
#endif // MAINWINDOW_H

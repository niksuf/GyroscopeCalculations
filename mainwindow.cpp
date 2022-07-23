#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <ws2tcpip.h>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    timer.start(1);
    timerspeed.start(1000);
    connect(&timerspeed, SIGNAL(timeout()), SLOT(updateData()));

    set.gx=0;
    set.gy=0;
    set.gz=0;
    set.pitch=0;
    set.roll=0;
    set.yaw=0;
    set.prevTime=0;
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString host = ui->lineEdit->text();
    if (host.isEmpty()==true)
    {
        ui->textEdit->setText("Введите ip-адрес!");
        return;
    }

    QString portDurty = ui->lineEdit_2->text();
    if (portDurty.isEmpty()==true)
    {
        ui->textEdit->setText("Введите адрес порта!");
        return;
    }
    quint16 port = portDurty.toInt();
    ui->textEdit->clear();

    s.connectToHost(host, port);

    if(s.state()>1)
    {
        ui->textEdit->setText("Соединение установлено!");
    }
    else
    {
        ui->textEdit->setText("Ошибка!");
    }
    connect (&s, SIGNAL(readyRead()), this, SLOT(ready()));
}

void MainWindow::on_pushButton_2_clicked()
{
    s.close();
    ui->textEdit->setText("Отключено!");
}

void MainWindow::on_pushButton_3_clicked()
{
    ui->doubleSpinBox->setValue(0);
    ui->doubleSpinBox_2->setValue(0);
    ui->doubleSpinBox_3->setValue(0);
    set.gx=0;
    set.gy=0;
    set.gz=0;
    ui->textEdit->setText("Очищено gx, gy, gz!");
}

void MainWindow::on_pushButton_4_clicked()
{
    ui->doubleSpinBox_4->setValue(0);
    ui->doubleSpinBox_5->setValue(0);
    ui->doubleSpinBox_6->setValue(0);
    set.pitch=0;
    set.roll=0;
    set.yaw=0;
    flag=false;
    ui->textEdit->setText("Очищено pitch, roll, yaw!");
}

void MainWindow::ready()
{
    int p1=0, timeChange;
    do
    {
        p1 = s.read((char*)&msg, sizeof(Packs));

        if (p1 > 0)
        {
            pkgcount++;
            set.gx=msg.gx;
            set.gy=msg.gy;
            set.gz=msg.gz;

            if (flag==true)
            {
                timeChange=msg.time-set.prevTime;
                set.pitch += 0.000015 * set.gx * timeChange;
                if (set.pitch < -360)
                    set.pitch += 360;
                else if (set.pitch > 360)
                    set.pitch -= 360;

                set.roll += 0.000015 * set.gy * timeChange;
                if (set.roll < -360)
                    set.roll += 360;
                else if (set.roll > 360)
                    set.roll -= 360;

                set.yaw += 0.000015 * set.gz * timeChange;
                if (set.yaw < -360)
                   set.yaw += 360;
                else if (set.yaw > 360)
                    set.yaw -= 360;

                set.prevTime = msg.time;

                refresh();
            }
            else if (flag==false && set.gx!=0 && set.gy!=0 && set.gz!=0)
            {
                set.prevTime=msg.time;
                flag=true;
            }
        }
    } while (p1>0);
}

void MainWindow::refresh()
{
    ui->doubleSpinBox->setValue(set.gx);
    ui->doubleSpinBox_2->setValue(set.gy);
    ui->doubleSpinBox_3->setValue(set.gz);

    ui->doubleSpinBox_4->setValue(set.pitch);
    ui->doubleSpinBox_5->setValue(set.roll);
    ui->doubleSpinBox_6->setValue(set.yaw);

    ui->widget->SetAngles(set.pitch, set.roll, set.yaw);
    ui->widget->update();
}

void MainWindow::updateData()
{
    speed=(float)(pkgcount*16.0f)/1024.0f;
    pkgcount=0;
    ui->doubleSpinBox_7->setValue(speed);
}

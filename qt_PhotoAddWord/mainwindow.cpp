#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>

#define   VERSION    "PhotoAddWord_V1.0.0;Date:2020.11.17"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(VERSION);

    QPixmap pix(":/Po/show.jpg");
    if(pix.isNull()){
        qDebug("isNUll\n");
    }
    pix.scaled(QSize(481, 481), Qt::KeepAspectRatio);
    ui->lab_preview->setPixmap(pix);
    ui->lab_preview->setScaledContents(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}

//功能：btn_input导入图片或者拖拽图片路径
void MainWindow::on_btn_input_clicked()
{

}


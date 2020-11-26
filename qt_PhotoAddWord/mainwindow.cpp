#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>
#include <QDropEvent>

#define   VERSION    "PhotoAddWord_V0.0.1;Date:2020.11.26"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(VERSION);    //设置title
    ui->btn_input->setStyleSheet("QPushButton{background-color: transparent;}");

    QPixmap pix(":/Po/show.jpg");
    if(pix.isNull()){
        qDebug("isNUll\n");
    }
    pix.scaled(QSize(481, 481), Qt::KeepAspectRatio);
    ui->lab_preview->setPixmap(pix);
    ui->lab_preview->setScaledContents(true);

//    QPixmap pixmap = QPixmap::grabWidget(ui->tedit_word); //让使用QWidget::grab进行替换也就是可以直接使用对应的grab方法替换grabWidget如下:
    QPixmap pixmap = ui->tedit_word->grab();
    pixmap.scaled(QSize(100, 50));
    pixmap.save("txt.jpg");
    ui->lab_display->setPixmap(pixmap);
    ui->lab_display->setScaledContents(true);

}

MainWindow::~MainWindow()
{
    delete ui;
}


//功能：btn_input导入图片或者拖拽图片路径
void MainWindow::on_btn_input_clicked()
{
    QString filename = NULL;
    filename = QFileDialog::getOpenFileName(this, tr("Open Images"), \
               "", tr("Image Files (*.png *.jpg *.bmp)"));
    if(filename != NULL)
    {
        ui->lab_display->setPixmap(QPixmap(filename));
    }
}




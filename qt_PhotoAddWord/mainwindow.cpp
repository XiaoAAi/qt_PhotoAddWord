#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>
#include <QDropEvent>
#include <QPainter>

#define   VERSION    "PhotoAddWord_V0.0.2;Date:2020.11.28"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(VERSION);    //设置title
    ui->btn_input->setStyleSheet("QPushButton{background-color: transparent;}");
    ui->ledit_w->setStyleSheet("QLineEdit{background-color:white;border-width:0;border-style:outset; font:20px bold}");//背景白色  无边框  font 20px bold
    ui->ledit_w->setAlignment( Qt::AlignHCenter);
    //QLineEdit
    //QFont font;
    //font.setPixelSize(20);
    //font.setBold(true);
    //ui->ledit_w->setFont(font);
    //ui->ledit_w->adjustSize();
    //ui->ledit_w->setMaxLength(50);



//    QPixmap pix(":/Po/show.jpg");
//    if(pix.isNull()){
//        qDebug("isNUll\n");
//    }
//    pix.scaled(QSize(481, 481), Qt::KeepAspectRatio);
//    ui->lab_preview->setPixmap(pix);
//    ui->lab_preview->setScaledContents(true);

//    QPixmap pixmap = QPixmap::grabWidget(ui->tedit_word); //让使用QWidget::grab进行替换也就是可以直接使用对应的grab方法替换grabWidget如下:



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
        src_pixmap = QPixmap(filename);
        ui->lab_display->setPixmap(src_pixmap);
    }
}

//拼接图片
QPixmap MainWindow::stitchPixmap(QPixmap src_pix, QPixmap obj_pix)
{
    QPixmap stitchPix(src_pix.width(), src_pix.height()+obj_pix.height());
    QPainter painter(&stitchPix);
    QPixmap tmp_pix((src_pix.width()-obj_pix.width())/2, obj_pix.height());
    tmp_pix.fill(Qt::white);

    //绘制两幅小图到QPixmap上
    painter.drawPixmap(0, 0, src_pix.width(), src_pix.height(), src_pix);
    painter.drawPixmap(0, src_pix.height(), (src_pix.width()-obj_pix.width())/2, obj_pix.height(), tmp_pix);
    painter.drawPixmap((src_pix.width()-obj_pix.width())/2, src_pix.height(), obj_pix.width(), obj_pix.height(), obj_pix);
    painter.drawPixmap((src_pix.width()+obj_pix.width())/2, src_pix.height(), (src_pix.width()-obj_pix.width())/2, obj_pix.height(), tmp_pix);

    return stitchPix;
}





void MainWindow::on_btn_load_clicked()
{
    if(!obj_pixmap.isNull())
    {
        obj_pixmap.save("obj.png");
    }
}


//预览按键事件
void MainWindow::on_btn_preview_clicked()
{
    src_world = ui->ledit_w->grab();
    src_world.scaled(QSize(100, 50));
    //ui->lab_display->setPixmap(src_world);
    //ui->lab_display->setScaledContents(true);


    obj_pixmap = stitchPixmap(src_pixmap, src_world);
    ui->lab_preview->setPixmap(obj_pixmap);

}




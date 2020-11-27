#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>
#include <QDropEvent>
#include <QPainter>

#define   VERSION    "PhotoAddWord_V0.0.1;Date:2020.11.26"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(VERSION);    //设置title
    ui->btn_input->setStyleSheet("QPushButton{background-color: transparent;}");
    ui->ledit_w->setStyleSheet("QLineEdit{background-color:white;}");

    //QLineEdit
    QFont font;
    font.setPixelSize(50);
    font.setBold(true);
    ui->ledit_w->setText(QString("heloo baby jdiagigagaighiahidgahidghiahgiah"));
    ui->ledit_w->setFont(font);
    ui->ledit_w->setAlignment( Qt::AlignHCenter);
    ui->ledit_w->adjustSize();



    QPixmap pix(":/Po/show.jpg");
    if(pix.isNull()){
        qDebug("isNUll\n");
    }
    pix.scaled(QSize(481, 481), Qt::KeepAspectRatio);
    ui->lab_preview->setPixmap(pix);
    ui->lab_preview->setScaledContents(true);

//    QPixmap pixmap = QPixmap::grabWidget(ui->tedit_word); //让使用QWidget::grab进行替换也就是可以直接使用对应的grab方法替换grabWidget如下:
    QPixmap pixmap = ui->ledit_w->grab();
    pixmap.scaled(QSize(100, 50));
    pixmap.save("txt.jpg");
    ui->lab_display->setPixmap(pixmap);
    ui->lab_display->setScaledContents(true);

    QPixmap p1("txt.jpg");
    QPixmap tmp_pixmap = stitchPixmap(pix, p1);
    ui->lab_preview->setPixmap(tmp_pixmap);

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




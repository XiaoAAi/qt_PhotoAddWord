#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QDebug>
#include <QFileDialog>
#include <QDropEvent>
#include <QPainter>

#define   VERSION    "PhotoAddWord_V0.0.3;Date:2020.11.28"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle(VERSION);    //设置title
    ui->btn_input->setStyleSheet("QPushButton{background-color: transparent;font:100px bold;}");//背景透明   字体100px
    ui->ledit_w->setStyleSheet("QLineEdit{background-color:white;border-width:0;border-style:outset; font:20px bold}");//背景白色  无边框  font 20px bold
    ui->ledit_w2->setStyleSheet("QLineEdit{background-color:white;border-width:0;border-style:outset; font:20px bold}");//背景白色  无边框  font 20px bold
    ui->ledit_w3->setStyleSheet("QLineEdit{background-color:white;border-width:0;border-style:outset; font:20px bold}");//背景白色  无边框  font 20px bold


    ui->lab_display->setAlignment(Qt::AlignCenter);//设置居中
    ui->lab_preview->setAlignment(Qt::AlignCenter);//设置居中

    ui->ledit_w->setAlignment( Qt::AlignHCenter);
    ui->ledit_w2->setAlignment( Qt::AlignHCenter);
    ui->ledit_w3->setAlignment( Qt::AlignHCenter);
    //qDebug() << "maxLen:" << ui->ledit_w->maxLength() << endl;
    //ui->ledit_w->setFixedWidth(200);

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
    if(!filename.isEmpty())
    {     
        src_pixmap = QPixmap(filename);
        ui->lab_display->setPixmap(src_pixmap);
        ui->btn_input->setText("");
    }
}

//拼接图片
QPixmap MainWindow::stitchPixmap(QPixmap src_pix, QPixmap obj_pix)
{
    int width_max = qMax(src_pix.width() ,obj_pix.width()); //取最大width
    int height_all = src_pix.height() + obj_pix.height(); //总heigth
    QPixmap stitchPix(width_max, height_all);   //声明新QPixmap
    QPainter painter(&stitchPix);//画QPixmap

    if(src_pix.width() != obj_pix.width())
    {
        int fill_height = src_pix.width() > obj_pix.width() ?  obj_pix.height() : src_pix.height();
        int diff_val = qAbs(src_pix.width()-obj_pix.width())/2;
        int diff_add_val = (src_pix.width()+obj_pix.width())/2;
        //qDebug() << "fh:" << fill_height << "fv:" << diff_val << "fav:" << diff_add_val << "wm:" << width_max << "ha:" << height_all << "src_w:" << src_pix.width();
        QPixmap tmp_pix(qAbs(src_pix.width()-obj_pix.width())/2, fill_height); //填充空白QPixmap
        tmp_pix.fill(Qt::white);

        if(src_pix.width() < obj_pix.width()){
            //首先填充上部分空间
            painter.drawPixmap(0, 0, tmp_pix.width(), tmp_pix.height(), tmp_pix);
            painter.drawPixmap(diff_val, 0, src_pix.width(), src_pix.height(), src_pix);
            painter.drawPixmap(diff_add_val, 0, tmp_pix.width(), tmp_pix.height(), tmp_pix);
            painter.drawPixmap(0, src_pix.height(), obj_pix.width(), obj_pix.height(), obj_pix);
        }
        else if(src_pix.width() > obj_pix.width()){
            painter.drawPixmap(0, 0, src_pix.width(), src_pix.height(), src_pix);
            painter.drawPixmap(0, src_pix.height(), tmp_pix.width(), tmp_pix.height(), tmp_pix);
            painter.drawPixmap(diff_val, src_pix.height(), obj_pix.width(), obj_pix.height(), obj_pix);
            painter.drawPixmap(diff_add_val, src_pix.height(), tmp_pix.width(), tmp_pix.height(), tmp_pix);
        }
    }else{
        //qDebug() << "width same";
        painter.drawPixmap(0, 0, src_pix.width(), src_pix.height(), src_pix);
        painter.drawPixmap(0, src_pix.height(), obj_pix.width(), obj_pix.height(), obj_pix);
    }

    return stitchPix;
}




//DownLoad Photo
void MainWindow::on_btn_load_clicked()
{
    if(!obj_pixmap.isNull())
    {
        QString filename = QFileDialog::getSaveFileName(this,tr("Save Image"),"object.png",tr("Images (*.png *.bmp *.jpg)")); //选择路径
        //qDebug() << filename;
        if(!filename.isEmpty()){
            obj_pixmap.save(filename);
        }

    }
}


//预览按键事件
void MainWindow::on_btn_preview_clicked()
{
    if(!ui->ledit_w->text().isEmpty())
    {
        src_world = ui->ledit_w->grab();
    }
    if(!ui->ledit_w2->text().isEmpty())
    {
        src_world2 = ui->ledit_w2->grab();
    }
    if(!ui->ledit_w3->text().isEmpty())
    {
        src_world3 = ui->ledit_w3->grab();
    }
    //ui->lab_display->setPixmap(src_world);
    //ui->lab_display->setScaledContents(true);
    obj_pixmap = stitchPixmap(src_pixmap, src_world);
    obj_pixmap = stitchPixmap(obj_pixmap, src_world2);
    obj_pixmap = stitchPixmap(obj_pixmap, src_world3);
    ui->lab_preview->setPixmap(obj_pixmap);
}



//设置QLineEdit_w的长度设置  结束处理及判断
void MainWindow::on_ledit_len_editingFinished()
{
    //qDebug() <<  "come ledit_len" << ui->ledit_len->text() << "--" << ui->ledit_len->text().toUInt()  ;

    if(ui->ledit_len->text().toInt() > 5000 || ui->ledit_len->text().toInt() <= 0)
    {
        ui->ledit_len->setText(NULL);
    }else{
        ui->ledit_w->setFixedWidth(ui->ledit_len->text().toUInt());
        ui->ledit_w2->setFixedWidth(ui->ledit_len->text().toUInt());
        ui->ledit_w3->setFixedWidth(ui->ledit_len->text().toUInt());
    }
}

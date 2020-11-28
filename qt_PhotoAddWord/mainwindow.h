#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QDropEvent>
#include <QMainWindow>

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
    void on_btn_input_clicked();

    void on_btn_load_clicked();

    void on_btn_preview_clicked();

private:
    QPixmap stitchPixmap(QPixmap src_pix, QPixmap obj_pix);
    QPixmap src_pixmap;//源pixmap
    QPixmap src_world; //源字符生成pixmap
    QPixmap obj_pixmap;//目标生成obj_pixmap

//protected:
//    void dropEvent(QDropEvent *event);
//    void dragEnterEvent(QDragEnterEvent *event);

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

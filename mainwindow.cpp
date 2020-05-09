#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QButtonGroup>
#include "constants.h"
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QColorDialog>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _scene(new MyScene(this))
    , _bg()
{
    ui->setupUi(this);
    ui->graphicsView->setScene(_scene);
    connect(_scene, &MyScene::mouse_moved, this, &MainWindow::scene_mouse_moved);

    connect(ui->horizontalSlider, &QSlider::sliderMoved, ui->lb_brush_size,
            static_cast<void(QLabel::*)(int)> (&QLabel::setNum));
}

MainWindow::~MainWindow()
{
    delete _scene;
    delete ui;
}

void MainWindow::scene_mouse_moved(double x, double y)
{
    ui->statusbar->showMessage(QString("%1 x %2").arg(x).arg(y));
}


void MainWindow::on_pb_rect_clicked()
{
   _scene->set_primitive(rectangle);
}

void MainWindow::on_pb_ellipse_clicked()
{
    _scene->set_primitive(ellipse);
}

void MainWindow::on_help_center_action_triggered()
{
    QDesktopServices::openUrl(QUrl("www.google.com"));
}

void MainWindow::on_report_action_triggered()
{
   QDesktopServices::openUrl(QUrl("www.stackoverflow.com"));
}

void MainWindow::on_open_action_triggered()
{
    QFile file = QFileDialog::getOpenFileName();

    if (file.exists()) {
        QPixmap p(file.fileName());
        _scene->addPixmap(p);
    }
}

void MainWindow::on_save_action_triggered()
{
    // todo: saving file
}

void MainWindow::on_exit_action_triggered()
{
   delete _scene;
   delete ui;
   exit(0);
}


void MainWindow::on_clear_scene_action_triggered()
{
   _scene->clear();
}


void MainWindow::on_pb_color_clicked()
{
    QColor color = QColorDialog::getColor();
    _scene->set_color(color);
}

void MainWindow::on_filling_scene_action_triggered()
{
    QColor color = QColorDialog::getColor();
    _scene->setBackgroundBrush(QBrush(color));
}

void MainWindow::on_pb_border_color_clicked()
{
    QColor color = QColorDialog::getColor();
    _scene->set_border_color(color);
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
   _scene->set_border_width(position);
}

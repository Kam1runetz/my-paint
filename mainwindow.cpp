#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDesktopServices>
#include <QUrl>
#include <QFileDialog>
#include <QColorDialog>
#include <QPainter>


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , _scene(new MyScene(this))
{
    ui->setupUi(this);
    ui->graphicsView->setScene(_scene);
    ui->graphicsView->setMouseTracking(true);
    connect(_scene, &MyScene::mouse_moved, this, &MainWindow::scene_mouse_moved);

    connect(ui->horizontalSlider, &QSlider::sliderMoved, ui->lb_brush_size,
            static_cast<void(QLabel::*)(int)> (&QLabel::setNum));

    ui->pb_border_color->setStyleSheet(QString("background-color: %1").arg(QColor(Qt::black).name()));
    ui->pb_color->setStyleSheet(QString("background-color: %1").arg(QColor(Qt::white).name()));
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
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
   _scene->set_primitive(MyScene::rectangle);
}

void MainWindow::on_pb_ellipse_clicked()
{
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
    _scene->set_primitive(MyScene::ellipse);
}

void MainWindow::on_pb_brush_clicked()
{
    ui->graphicsView->setDragMode(QGraphicsView::NoDrag);
    _scene->set_primitive(MyScene::brush);
}

void MainWindow::on_pb_selector_clicked()
{
   ui->graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
   _scene->set_primitive(MyScene::none);
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
    QString fileName = QFileDialog::getSaveFileName(this, "Save image", QCoreApplication::applicationDirPath(), "BMP Files (*.bmp);;JPEG (*.JPEG);;PNG (*.png)" );
    if (!fileName.isNull())
    {
        qreal h = _scene->height();
        qreal w = _scene->width();
        QImage image(w, h, QImage::Format_RGB888);
        QPainter painter(&image);
        _scene->render(&painter, QRect(0, 0, h, w));
        image.save(fileName);
    }
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
    QColor color = QColorDialog::getColor(Qt::white, nullptr,
                                          QString(), QColorDialog::ShowAlphaChannel);
    _scene->set_color(color);
    ui->pb_color->setStyleSheet(QString("background-color: %1").arg(color.name()));
}

void MainWindow::on_filling_scene_action_triggered()
{
    QColor color = QColorDialog::getColor(Qt::white, nullptr,
                                          QString(), QColorDialog::ShowAlphaChannel);
    _scene->setBackgroundBrush(QBrush(color));
}

void MainWindow::on_pb_border_color_clicked()
{
    QColor color = QColorDialog::getColor(Qt::white, nullptr,
                                          QString(), QColorDialog::ShowAlphaChannel);
    _scene->set_border_color(color);
    ui->pb_border_color->setStyleSheet(QString("background-color: %1").arg(color.name()));
}

void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
   _scene->set_border_width(position);
}


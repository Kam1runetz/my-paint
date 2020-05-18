#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QButtonGroup>
#include <QMainWindow>
#include "myscene.h"

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
    void scene_mouse_moved(double x, double y);

    void on_pb_rect_clicked();

    void on_help_center_action_triggered();

    void on_report_action_triggered();

    void on_open_action_triggered();

    void on_save_action_triggered();

    void on_exit_action_triggered();

    void on_clear_scene_action_triggered();

    void on_pb_ellipse_clicked();

    void on_pb_color_clicked();

    void on_filling_scene_action_triggered();

    void on_pb_border_color_clicked();

    void on_horizontalSlider_sliderMoved(int position);

    void on_pb_brush_clicked();

    void on_pb_selector_clicked();

private:
    Ui::MainWindow *ui;
    MyScene *_scene;
    QButtonGroup _bg;

};
#endif // MAINWINDOW_H

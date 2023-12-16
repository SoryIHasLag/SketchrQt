#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDragEnterEvent>
#include <QDropEvent>
#include <QCloseEvent>

#include "screenselection.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent *event) override;
    void dropEvent(QDropEvent *event) override;
    void closeEvent(QCloseEvent *event) override;

private:
    QWidget* gui;
    ScreenSelection* selection;
    QImage* srcImage;

    void RefreshImage();

private slots:
    void on_spinbox_midvalue_valueChanged(int arg1);
    void on_slider_midvalue_valueChanged(int value);
    void on_button_donate_clicked();
    void on_button_start_clicked();
    void on_button_sketch_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H

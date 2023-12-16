#include "mainwindow.h"

#include <QMimeData>
#include <QDebug>
#include <QProcess>
#include <QDesktopServices>

#include "ui_mainwindow.h"
#include "imagemanipulator.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow), gui(new QWidget(this)), selection(nullptr), srcImage(nullptr) {
    ui->setupUi(this);

    setWindowTitle("SketchrQt");

    gui->setLayout(ui->layout_main);
    setCentralWidget(gui);
}

MainWindow::~MainWindow() {
    delete srcImage;
    delete gui;
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *event) {
    event->accept();
}

void MainWindow::dropEvent(QDropEvent *event) {
    const QMimeData *mimeData = event->mimeData();

    if (mimeData->hasUrls()) {
        QList<QUrl> urlList = mimeData->urls();

        for (const QUrl &url : urlList) {
            QString filePath = url.toLocalFile();

            delete srcImage;
            srcImage = new QImage(filePath);

            RefreshImage();

            ui->spinbox_midvalue->setEnabled(true);
            ui->spinbox_delay->setEnabled(true);
            ui->slider_midvalue->setEnabled(true);
            ui->button_start->setEnabled(true);
        }
    }
}

void MainWindow::closeEvent(QCloseEvent *event) {
    QMainWindow::closeEvent(event);
    QCoreApplication::quit();
}

void MainWindow::on_spinbox_midvalue_valueChanged(int arg1) {
    ui->slider_midvalue->setValue(arg1);
    RefreshImage();
}

void MainWindow::on_slider_midvalue_valueChanged(int value) {
    ui->spinbox_midvalue->setValue(value);
    RefreshImage();
}

void MainWindow::on_button_donate_clicked() {
    QDesktopServices::openUrl(QUrl("https://www.buymeacoffee.com/soryihaslag"));
}

void MainWindow::on_button_start_clicked() {
    if (!selection) {
        selection = new ScreenSelection(nullptr, this, srcImage);
        selection->show();
        ui->button_start->setText("Cancel");
        ui->button_sketch->setEnabled(true);
    } else {
        delete selection;
        selection = nullptr;
        ui->button_start->setText("Continue");
        ui->button_sketch->setEnabled(false);
    }
}


void MainWindow::on_button_sketch_clicked() {
    QRect area = *(selection->getArea());
    QImage* image = new QImage(srcImage->scaled(area.size()));

    if (image) {
        on_button_start_clicked();
        showMinimized();

        ImageManipulator::saveImageToFile(image, ui->slider_midvalue->value());

        QProcess process;
        process.setWorkingDirectory(QCoreApplication::applicationDirPath());
        process.start("java", QStringList() << "Main" << QString::number(area.x()) << QString::number(area.y()) << QString::number(ui->spinbox_delay->value() * 1000));
        if (process.waitForFinished(-1)) {
            qDebug() << "Sketch output: " << process.readAllStandardError();
        }
        process.deleteLater();

        delete image;
    } else {
        qDebug() << "Error: getScaledImage returned nullptr";
    }
}


void MainWindow::RefreshImage() {
    QImage scaled = ImageManipulator::scaleToLabel(srcImage,  ui->label_image);
    QImage processed = ImageManipulator::toBlackAndWhite(&scaled,  ui->slider_midvalue->value());

    ui->label_image->setPixmap(QPixmap::fromImage(processed));
}

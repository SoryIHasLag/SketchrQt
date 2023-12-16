#include "screenselection.h"

ScreenSelection::ScreenSelection(QWidget *parent, QWidget *mainWindow, QImage *image)
    : QWidget(parent), mainWindow(mainWindow), image(image), label(nullptr), band(nullptr) {
    setWindowOpacity(0.6);
    setStyleSheet("background-color: black;");
    setWindowFlags(Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
    setWindowState(Qt::WindowFullScreen);

    this->mainWindow->hide();
}

QRect* ScreenSelection::getArea() {
    return &area;
}

void ScreenSelection::mousePressEvent(QMouseEvent *event) {
    area = QRect(event->pos(), QSize());

    if(label && band) {
        delete label;
        delete band;
    }

    label = new QLabel(this);
    label->setGeometry(area);
    label->setPixmap(QPixmap::fromImage(*image));

    band = new QRubberBand(QRubberBand::Rectangle, this);
    band->setGeometry(area);

    label->show();
    band->show();

    mainWindow->hide();
}

void ScreenSelection::mouseReleaseEvent(QMouseEvent *event) {
    area = label->geometry();
    mainWindow->show();
}

void ScreenSelection::mouseMoveEvent(QMouseEvent *event) {
    if(label && image) {
        QRect newGeometry(area.topLeft(), event->pos());
        label->setGeometry(newGeometry.normalized());
        band->setGeometry(newGeometry.normalized());

        label->setPixmap(QPixmap::fromImage(image->scaled(label->width(), label->height())));
    }
}

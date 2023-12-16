#ifndef SCREENSELECTION_H
#define SCREENSELECTION_H

#include <QLabel>
#include <QRubberBand>
#include <QMouseEvent>

class ScreenSelection : public QWidget {
    Q_OBJECT

public:
    explicit ScreenSelection(QWidget *parent = nullptr, QWidget* mainWindow = nullptr, QImage* image = nullptr);
    QRect* getArea();

protected:
    void mousePressEvent(QMouseEvent* event) override;
    void mouseReleaseEvent(QMouseEvent* event) override;
    void mouseMoveEvent(QMouseEvent* event) override;

private:
    QRect area;
    QLabel* label;
    QRubberBand* band;
    QWidget* mainWindow;
    QImage* image;
};

#endif

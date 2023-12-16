#ifndef IMAGEMANIPULATOR_H
#define IMAGEMANIPULATOR_H

#include <QImage>
#include <QLabel>

class ImageManipulator
{
public:
    static void saveImageToFile(QImage *input_image, int middle_value);
    static QImage toBlackAndWhite(QImage *input_image, int middle_value);
    static QImage scaleToLabel(QImage *input_image, QLabel *input_label);
};

#endif // IMAGEMANIPULATOR_H

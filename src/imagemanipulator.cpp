#include "imagemanipulator.h"

#include <fstream>

const char* TEMP_SAVE_FILE = ".tempsave.txt";

void ImageManipulator::saveImageToFile(QImage* inputImage, int middleValue) {
    int streamStart = 0;
    int streamEnd = 0;
    bool started = false;

    std::ofstream file(TEMP_SAVE_FILE);

    if (file.is_open()) {
        QImage grayscaleImage = inputImage->convertToFormat(QImage::Format_Grayscale8);

        for (int y = 0; y < grayscaleImage.height(); ++y) {
            for (int x = 0; x < grayscaleImage.width(); ++x) {
                int grayValue = qGray(grayscaleImage.pixel(x, y));

                if (grayValue < middleValue) {
                    if (!started) {
                        streamStart = x;
                        started = true;
                    }
                } else {
                    if (started) {
                        streamEnd = x - 1;
                        file << streamStart << ":" << streamEnd << ";";
                        started = false;
                    }
                }
            }
            file << std::endl;
        }
    } else {
        qDebug() << "Error: error opening the file";
    }
}

QImage ImageManipulator::toBlackAndWhite(QImage* inputImage, int middleValue) {
    QImage grayscaleImage = inputImage->convertToFormat(QImage::Format_Grayscale8);
    QImage outputImage = QImage(grayscaleImage.size(), QImage::Format_Mono);

    for (int y = 0; y < grayscaleImage.height(); ++y) {
        for (int x = 0; x < grayscaleImage.width(); ++x) {
            int grayValue = qGray(grayscaleImage.pixel(x, y));
            outputImage.setPixel(x, y, (grayValue < middleValue) ? 0 : 1);
        }
    }

    return outputImage;
}

QImage ImageManipulator::scaleToLabel(QImage* inputImage, QLabel* inputLabel) {
    float scaleValue = std::max(inputImage->width(), inputImage->height()) / static_cast<float>(inputLabel->width());
    return inputImage->scaled(inputImage->width() / scaleValue, inputImage->height() / scaleValue);
}

#ifndef IMAGE_H
#define IMAGE_H

#include <memory>
#include <string>
#include <vector>

#include <QPixmap>
#include <QPointF>

#include "FitnessFunctionCalculator.h"

class QColor;
class QRectF;

class Image
{
public:
    class MultiplePointsDrawer
    {
    public:
        void publish(QPixmap& pixmap, const QColor& color);
        void drawPoint(double x, double y);

    private:
        std::vector<QPointF> points;
    };

    Image(const QPixmap& pixmap, double width, double height);
    Image(const std::string& formula, double width, double height);

    void prepare(const QRectF& crect);
    void prepareWithScale(const QRectF& crect, double dividor, QPixmap* output);
    void drawPoint(double x, double y, const QColor& color = QColor(Qt::yellow));

    QPixmap image;

private:
    double getNormalization(double value, std::pair<double, double> minMax) const;
    std::pair<double, double> getMinMaxOfFunction(double width, double height) const;

    std::unique_ptr<common::FitnessFunctionCalculator> calculator;
    double width;
    double height;
};

#endif // IMAGE_H

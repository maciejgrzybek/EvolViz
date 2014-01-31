#include "Image.h"

#include <QPainter>

void Image::MultiplePointsDrawer::publish(QPixmap& pixmap, const QColor& color)
{
    QPainter painter(&pixmap);
    painter.setPen(QPen(color, 2));
    painter.drawPoints(&points[0], points.size());
}

void Image::MultiplePointsDrawer::drawPoint(double x, double y)
{
    points.push_back(QPointF(x, y));
}


Image::Image(const QPixmap& pixmap, double width, double height)
    : image(pixmap),
      width(width),
      height(height)
{}

Image::Image(const std::string& formula, double width, double height)
    : calculator(new common::FitnessFunctionCalculator(formula)),
      width(width),
      height(height)
{}

void Image::prepare(const QRectF& crect)
{
    prepareWithScale(crect, 1, &image);
}

void Image::prepareWithScale(const QRectF& crect, double dividor, QPixmap* output)
{
    assert(dividor > 0);
    assert(calculator); // FIXME not valid when constructor without formula used!

    const QRectF rect = crect.normalized();
    QPixmap img(rect.width()/dividor, rect.height()/dividor);
    QPainter painter(&img);

    const std::pair<double, double> minMax = getMinMaxOfFunction(width, height);

    const double widthFactor = width/rect.width();
    const double heightFactor = height/rect.height();

    for (int i = 0; i < rect.width()/dividor; ++i)
    {
        for (int j = 0; j < rect.height()/dividor; ++j)
        {
            const double value = (*calculator)(dividor*i * widthFactor, dividor*j * heightFactor);
            const double normalization = std::min(getNormalization(value, minMax), 1.0);
            assert(normalization >= 0.0 && normalization <= 1.0);

            painter.setPen(QPen(QColor(255 * normalization, 0, 0), 1));
            painter.drawPoint(i, j);
        }
    }

    *output = img.scaled(QSize(rect.width(), rect.height()));
}

void Image::drawPoint(double x, double y, const QColor& color)
{
    const double widthFactor = (double)width/image.width();
    const double heightFactor = (double)height/image.height();

    QPainter painter;
    painter.begin(&image);
    painter.setPen(QPen(color, 2));
    painter.drawPoint(x/widthFactor, y/heightFactor);
    painter.end();
}

double Image::getNormalization(double value, std::pair<double, double> minMax) const
{
    const double distance = minMax.second - minMax.first;
    const double v = value - minMax.first;
    if (distance == 0)
        return 1.0;
    const double result = std::max(std::min(v/distance, 1.0), 0.0);
    return result;
}

std::pair<double, double> Image::getMinMaxOfFunction(double width, double height) const
{
    assert(width > 0 && height > 0);

    double min = std::numeric_limits<double>::max();
    double max = std::numeric_limits<double>::min();

    for (int i = 0; i < width; ++i)
    {
        for (int j = 0; j < height; ++j)
        {
            const double value = (*calculator)(i, j);
            if (value < min)
                min = value;
            if (value > max)
                max = value;
        }
    }

    return std::make_pair(min, max);
}

#ifndef RECTANGLEFIGURE_H
#define RECTANGLEFIGURE_H
#include "figure.h"
#include <QPoint>
#include <QColor>
#include <QPainter>
class RectangleFigure : public Figure
{
public:
    QPoint topLeft;
    int width;
    int height;
    RectangleFigure(QPoint c, int w, int h, QColor color, int penWidth);
    void draw(QPainter &painter) override;
    void move(int dx, int dy) override;
    void resize(double factor) override;
    bool containsPoint(const QPoint &point) override;

    QTimer *timer = nullptr;
    void startAnimation(QWidget *widget);
private:
    int dx = 0;
    int dy = 5;
};
#endif // RECTANGLEFIGURE_H

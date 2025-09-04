#ifndef CIRCLEFIGURE_H
#define CIRCLEFIGURE_H

#include "Figure.h"
#include <QPoint>

class CircleFigure : public Figure {
public:
    QPoint center;
    int radius;

    CircleFigure(QPoint c, int r, QColor color, int penWidth);

    void draw(QPainter &painter) override;
    void move(int dx, int dy) override;
    void resize(double factor) override;
    bool containsPoint(const QPoint &point) override;

    QTimer *timer = nullptr;
    void startAnimation(QWidget *widget);
private:
    int dx = -5;
    int dy = 5;
};

#endif // CIRCLEFIGURE_H

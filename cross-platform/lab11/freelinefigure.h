#ifndef FREELINEFIGURE_H
#define FREELINEFIGURE_H

#include "Figure.h"
#include <QVector>
#include <QPoint>

class FreeLineFigure : public Figure {
public:
    QVector<QPoint> points;

    FreeLineFigure(const QColor &color, int penWidth);

    void addPoint(const QPoint &point);

    void draw(QPainter &painter) override;
    void move(int dx, int dy) override;
    void resize(double factor) override;
    bool containsPoint(const QPoint &point) override;

    QTimer *timer = nullptr;
    void startAnimation(QWidget *widget);
private:
    int dx = 5;
    int dy = 5;
};

#endif // FREELINEFIGURE_H

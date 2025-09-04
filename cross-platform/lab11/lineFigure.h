#ifndef LINEFIGURE_H
#define LINEFIGURE_H

#include "Figure.h"
#include <QPoint>

class LineFigure : public Figure {
public:
    QPoint p1, p2;

    LineFigure(QPoint start, QPoint end, QColor c, int w);

    void draw(QPainter &painter) override;
    void move(int dx, int dy) override;
    void resize(double factor) override;
    bool containsPoint(const QPoint &point) override;

    QTimer *timer = nullptr;

    void startAnimation(QWidget *widget) override;

private:
    int dx = 5;
    int dy = 0;
};

#endif // LINEFIGURE_H

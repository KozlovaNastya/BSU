#include "lineFigure.h"
#include <QPen>
#include <QLineF>
#include <QTimer>
#include <QWidget>

LineFigure::LineFigure(QPoint start, QPoint end, QColor c, int w) {
    p1 = start;
    p2 = end;
    color = c;
    penWidth = w;
}

void LineFigure::draw(QPainter &painter) {
    QPen pen(color, penWidth);
    painter.setPen(pen);
    painter.drawLine(p1, p2);
}

void LineFigure::move(int dx, int dy) {
    p1 += QPoint(dx, dy);
    p2 += QPoint(dx, dy);
}

void LineFigure::resize(double factor) {
    QPoint center = (p1 + p2) / 2;
    p1 = center + (p1 - center) * factor;
    p2 = center + (p2 - center) * factor;
}

bool LineFigure::containsPoint(const QPoint &point) {
    QLineF line(p1, p2);
    return std::abs(QLineF(p1, point).length() + QLineF(point, p2).length() - line.length()) < 3.0;
}
void LineFigure::startAnimation(QWidget *widget) {
    if (!timer) {
        timer = new QTimer();
        QObject::connect(timer, &QTimer::timeout, [this, widget]() {
            QRect bounds = widget->rect();
            if (p1.x() + dx < 0 || p2.x() + dx > bounds.width()) {
                dx = -dx;
            }
            if (p1.y() + dy < 0 || p2.y() + dy > bounds.height()) {
                dy = -dy;
            }
            this->move(dx, dy);
            widget->update();
        });

    }
    timer->start(50);
}

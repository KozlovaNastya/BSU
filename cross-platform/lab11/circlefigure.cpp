#include "circleFigure.h"
#include <QPainter>
#include <cmath>

CircleFigure::CircleFigure(QPoint c, int r, QColor col, int w) {
    center = c;
    radius = r;
    color = col;
    penWidth = w;
}

void CircleFigure::draw(QPainter &painter) {
    QPen pen(color, penWidth);
    painter.setPen(pen);
    painter.drawEllipse(center, radius, radius);
}

void CircleFigure::move(int dx, int dy) {
    center += QPoint(dx, dy);
}

void CircleFigure::resize(double factor) {
    radius *= factor;
}

bool CircleFigure::containsPoint(const QPoint &point) {
    return std::hypot(point.x() - center.x(), point.y() - center.y()) <= radius;
}
void CircleFigure::startAnimation(QWidget *widget) {
    if (!timer) {
        timer = new QTimer();
        QObject::connect(timer, &QTimer::timeout, [this, widget]() {
            QRect bounds = widget->rect();
            if (center.x() - radius + dx < 0 || center.x() + dx + radius > bounds.width()) {
                dx = -dx;
            }
            if (center.y() - radius + dy < 0 || center.y() + radius + dy > bounds.height()) {
                dy = -dy;
            }
            this->move(dx, dy);
            widget->update();
        });

    }
    timer->start(50);
}


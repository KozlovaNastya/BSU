#include "freeLineFigure.h"
#include <QPainter>
#include <QPen>
#include <QLineF>

FreeLineFigure::FreeLineFigure(const QColor &c, int w) {
    color = c;
    penWidth = w;
}

void FreeLineFigure::addPoint(const QPoint &point) {
    points.append(point);
}

void FreeLineFigure::draw(QPainter &painter) {
    if (points.size() < 2) return;

    QPen pen(color, penWidth);
    painter.setPen(pen);

    for (int i = 0; i < points.size() - 1; ++i) {
        painter.drawLine(points[i], points[i + 1]);
    }
}

void FreeLineFigure::move(int dx, int dy) {
    for (QPoint &pt : points) {
        pt += QPoint(dx, dy);
    }
}

void FreeLineFigure::resize(double factor) {
    if (points.isEmpty()) return;
    QPoint center = points[0];
    for (QPoint &pt : points) {
        pt = center + (pt - center) * factor;
    }
}

bool FreeLineFigure::containsPoint(const QPoint &point) {
    for (int i = 0; i < points.size() - 1; ++i) {
        QLineF segment(points[i], points[i + 1]);
        if (segment.length() - QLineF(points[i], point).length() - QLineF(points[i + 1], point).length() < 3.0)
            return true;
    }
    return false;
}
void FreeLineFigure::startAnimation(QWidget *widget) {
    if (!timer) {
        timer = new QTimer();
        QObject::connect(timer, &QTimer::timeout, [this, widget]() {
            QRect bounds = widget->rect();
            for (const QPoint &pt : points) {
                if (pt.x() + dx < 0 || pt.x() + dx > bounds.width()) {
                    dx = -dx;
                    break;
                }
            }
            for (const QPoint &pt : points) {
                if (pt.y() + dy < 0 || pt.y() + dy > bounds.height()) {
                    dy = -dy;
                    break;
                }
            }

            this->move(dx, dy);
            widget->update();
        });
    }
    timer->start(50);
}

#include "rectangleFigure.h"

RectangleFigure::RectangleFigure(QPoint c, int w, int h, QColor col, int penW) {
    topLeft = c;
    width = w;
    height = h;
    color = col;
    penWidth = penW;
}

void RectangleFigure::draw(QPainter &painter) {
    QPen pen(color, penWidth);
    painter.setPen(pen);
    painter.drawRect(QRect(topLeft, QSize(width, height)));
}

void RectangleFigure::move(int dx, int dy) {
    topLeft += QPoint(dx, dy);
}

void RectangleFigure::resize(double factor) {
    width *= factor;
    height *= factor;
}

bool RectangleFigure::containsPoint(const QPoint &point) {
    QRect rect(topLeft, QSize(width, height));
    return rect.contains(point);
}

void RectangleFigure::startAnimation(QWidget *widget) {
    if (!timer) {
        timer = new QTimer();
        QObject::connect(timer, &QTimer::timeout, [this, widget]() {
            QRect bounds = widget->rect();
            if (topLeft.x() + dx < 0 || topLeft.x() + width + dx > bounds.width()) {
                dx = -dx;
            }
            if (topLeft.y() + dy < 0 || topLeft.y() + height + dy > bounds.height()) {
                dy = -dy;
            }
            this->move(dx, dy);
            widget->update();
        });

    }
    timer->start(50);
}

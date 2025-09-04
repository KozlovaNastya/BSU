#ifndef FIGURE_H
#define FIGURE_H

#include <QPainter>
#include <QColor>
#include <QPoint>
#include <QObject>
#include <QTimer>
#include <QWidget>

class Figure : public QObject {
     Q_OBJECT
public:
    virtual ~Figure() {}
    virtual void draw(QPainter &painter) = 0;
    virtual void move(int dx, int dy) = 0;
    virtual void resize(double factor) = 0;
    virtual bool containsPoint(const QPoint &point) = 0;
    virtual void startAnimation(QWidget *widget) = 0;

    QColor color;
    int penWidth;
};

#endif // FIGURE_H

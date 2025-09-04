#include "Canvas.h"
#include "lineFigure.h"
#include "circlefigure.h"
#include "rectanglefigure.h"
#include <QMouseEvent>
#include <QPainter>

Canvas::Canvas(QWidget *parent)
    : QWidget(parent), currentColor(Qt::black), currentPenWidth(2), currentType("Line") {}

void Canvas::setCurrentFigureType(const QString &type) {
    currentType = type;
}

void Canvas::setCurrentColor(const QColor &color) {
    currentColor = color;
}

void Canvas::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    if (!backgroundImage.isNull())
        painter.drawPixmap(0, 0, backgroundImage.scaled(size()));
    for (Figure *fig : figures) {
        fig->draw(painter);
    }
}

void Canvas::saveImage(const QString &filename) {
    QPixmap pixmap(size());
    pixmap.fill(Qt::white);

    QPainter painter(&pixmap);
    for (Figure *fig : figures)
        fig->draw(painter);

    pixmap.save(filename);
}
void Canvas::loadImage(const QString &filename) {
    backgroundImage.load(filename);
    qDeleteAll(figures);
    figures.clear();
    update(); // перерисовать
}
void Canvas::mouseMoveEvent(QMouseEvent *event) {
    if (event->buttons() & Qt::LeftButton) {
        if (currentType == "FreeLine" && currentFreeLine) {
            currentFreeLine->addPoint(event->pos());
            update();
        }
    }
}

void Canvas::mousePressEvent(QMouseEvent *event) {
    startPoint = event->pos();

    if (event->button() == Qt::LeftButton) {
        if (currentType == "Line") {
            Figure *line = new LineFigure(startPoint, startPoint + QPoint(100, 0), currentColor, currentPenWidth);
            figures.append(line);
        } else if (currentType == "Circle") {
            Figure *circle = new CircleFigure(startPoint, currentRadius, currentColor, currentPenWidth); // Радиус 50 по умолчанию
            figures.append(circle);
        }
        else if (currentType == "Rectangle") {
            Figure *rect = new RectangleFigure(startPoint,  currentRectWidth, currentRectHeight, currentColor, currentPenWidth);
            figures.append(rect);
        }
        else if (currentType == "FreeLine") {
            currentFreeLine = new FreeLineFigure(currentColor, currentPenWidth);
            currentFreeLine->addPoint(event->pos());
            figures.append(currentFreeLine);
        }
        update();
    }
    else if (event->button() == Qt::RightButton) {
        QPoint clickPos = event->pos();
        for (Figure *fig : figures) {
            if (fig->containsPoint(clickPos)) {
                fig->startAnimation(this);
                break;
            }
        }
    }
}

#ifndef CANVAS_H
#define CANVAS_H

#include <QWidget>
#include <QList>
#include <QPixmap>
#include "Figure.h"
#include "freeLineFigure.h"

class Canvas : public QWidget {
    Q_OBJECT

public:
    explicit Canvas(QWidget *parent = nullptr);

    void setCurrentFigureType(const QString &type);
    void setCurrentColor(const QColor &color);

    void setPenWidth(int width) { currentPenWidth = width; }
    void setRadius(int r) { currentRadius = r; }
    void setRectWidth(int w) { currentRectWidth = w; }
    void setRectHeight(int h) { currentRectHeight = h; }

    int getPenWidth() const { return currentPenWidth; }
    int getRadius() const { return currentRadius; }
    int getRectWidth() const { return currentRectWidth; }
    int getRectHeight() const { return currentRectHeight; }


public slots:
    void saveImage(const QString &filename);
    void loadImage(const QString &filename);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QList<Figure *> figures;
    QString currentType;
    QColor currentColor;
    int currentPenWidth;
    QPoint startPoint;
    FreeLineFigure *currentFreeLine = nullptr;
    QPixmap backgroundImage;

    int currentRadius = 50;
    int currentRectWidth = 100;
    int currentRectHeight = 50;

};

#endif // CANVAS_H

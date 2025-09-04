#include "dotchart.h"
#include <QPainter>
#include <QPainterPath>
#include <QFontMetrics>
#include <QDebug>
#include <QMenu>
#include <QActionGroup>
#include <QContextMenuEvent>

DotChart::DotChart(QWidget *parent)
    : QWidget(parent), pen(Qt::black, 1), brush(Qt::blue)
{
    setMinimumSize(300, 200);
}

DotChart::DotChart(const QVector<int> &data, const QPen &pen, const QBrush &brush, QWidget *parent)
    : QWidget(parent), data(data), pen(pen), brush(brush) {}

DotChart::DotChart(const DotChart &other)
    : QWidget(other.parentWidget()), data(other.data), pen(other.pen), brush(other.brush) {}

void DotChart::setData(const QVector<int> &newData) {
    data = newData;
    update();
}

void DotChart::setPen(const QPen &newPen) {
    pen = newPen;
    update();
}

void DotChart::setBrush(const QBrush &newBrush) {
    brush = newBrush;
    update();
}

QVector<int> DotChart::getData() const {
    return data;
}

QPen DotChart::getPen() const {
    return pen;
}
QBrush DotChart::getBrush() const {
    return brush;
}

DotChart& DotChart::operator=(const DotChart& other) {
    if (this != &other) {
        data = other.data;
        pen = other.pen;
        brush = other.brush;
    }
    return *this;
}


void DotChart::resizeEvent(QResizeEvent *) {
    update();
}

void DotChart::paintEvent(QPaintEvent *) {
    QPainter painter(this);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen(pen);

    drawChart(painter);
}
void DotChart::drawAxes(QPainter &painter, int margin, int w, int h, int maxVal, int n) {
    painter.save();

    painter.setPen(QPen(Qt::black, 1));

    painter.drawLine(margin, height() - margin, width() - margin, height() - margin);

    painter.drawLine(margin, margin, margin, height() - margin);

    int xDivisions = n > 1 ? n - 1 : 1;
    int yDivisions = maxVal > 10 ? 10 : maxVal;

    float xStep = static_cast<float>(w) / xDivisions;
    for (int i = 0; i <= xDivisions; ++i) {
        int x = margin + static_cast<int>(i * xStep);
        int y = height() - margin;

        painter.drawLine(x, y, x, y + 5);

        QString label = QString::number(i);
        QFontMetrics fm = painter.fontMetrics();
        int labelWidth = fm.horizontalAdvance(label);
        painter.drawText(x - labelWidth / 2, y + 20, label);
    }

    float yStep = static_cast<float>(h) / yDivisions;
    for (int i = 0; i <= yDivisions; ++i) {
        int y = height() - margin - static_cast<int>(i * yStep);
        int x = margin;

        painter.drawLine(x, y, x - 5, y);

        int labelVal = static_cast<int>(i * (static_cast<float>(maxVal) / yDivisions));
        QString label = QString::number(labelVal);
        QFontMetrics fm = painter.fontMetrics();
        int labelWidth = fm.horizontalAdvance(label);
        int labelHeight = fm.height();

        painter.drawText(x - labelWidth - 8, y + labelHeight / 4, label);
    }

    painter.restore();
}

void DotChart::drawChart(QPainter &painter) {
    if (data.isEmpty())
        return;

    const int margin = 30;
    int w = width() - 2 * margin;
    int h = height() - 2 * margin;
    int n = data.size();

    int maxVal = *std::max_element(data.begin(), data.end());
    if (maxVal == 0) maxVal = 1;

    drawAxes(painter, margin, w, h, maxVal, n);

    float xStep = static_cast<float>(w) / (n - 1);
    float yScale = static_cast<float>(h) / maxVal;

    QVector<QPointF> points;
    for (int i = 0; i < n; ++i) {
        float x = margin + i * xStep;
        float y = height() - margin - data[i] * yScale;
        points.append(QPointF(x, y));
    }

    QPainterPath path;
    path.moveTo(points[0]);

    for (int i = 0; i < points.size() - 1; ++i) {
        QPointF p0 = i == 0 ? points[0] : points[i - 1];
        QPointF p1 = points[i];
        QPointF p2 = points[i + 1];
        QPointF p3 = (i + 2 < points.size()) ? points[i + 2] : points[i + 1];

        QPointF c1 = p1 + (p2 - p0) / 18.0;
        QPointF c2 = p2 - (p3 - p1) / 18.0;

        path.cubicTo(c1, c2, p2);
    }
    painter.drawPath(path);

    for (int i = 0; i < n; ++i) {
        painter.setBrush(brush);
        painter.drawEllipse(points[i], 4, 4);

        QString valueStr = QString::number(data[i]);
        QFontMetrics fm = painter.fontMetrics();
        int textWidth = fm.horizontalAdvance(valueStr);
        painter.drawText(QPointF(points[i].x() - textWidth / 2, points[i].y() - 8), valueStr);
    }
}

void DotChart::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);

    QActionGroup *penWidthGroup = new QActionGroup(&menu);
    penWidthGroup->setExclusive(true);

    QAction *penWidth1 = new QAction(tr("1 px"), &menu);
    penWidth1->setCheckable(true);
    penWidth1->setChecked(pen.width() == 1);

    QAction *penWidth2 = new QAction(tr("2 px"), &menu);
    penWidth2->setCheckable(true);
    penWidth2->setChecked(pen.width() == 2);

    QAction *penWidth3 = new QAction(tr("3 px"), &menu);
    penWidth3->setCheckable(true);
    penWidth3->setChecked(pen.width() == 3);

    penWidthGroup->addAction(penWidth1);
    penWidthGroup->addAction(penWidth2);
    penWidthGroup->addAction(penWidth3);

    menu.addAction(penWidth1);
    menu.addAction(penWidth2);
    menu.addAction(penWidth3);

    connect(penWidthGroup, &QActionGroup::triggered, this, [this](QAction *action){
        int width = 1;
        if (action->text() == "1 px") width = 1;
        else if (action->text() == "2 px") width = 2;
        else if (action->text() == "3 px") width = 3;

        pen.setWidth(width);
        update();
        emit penWidthChanged(width);
    });

    menu.exec(event->globalPos());
}

void DotChart::setPenWidth(int width) {
    QPen p = pen;
    p.setWidth(width);
    setPen(p);
    emit penWidthChanged(width);
}

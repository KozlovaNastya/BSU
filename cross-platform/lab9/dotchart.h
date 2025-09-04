#ifndef DOTCHART_H
#define DOTCHART_H

#include <QWidget>
#include <QVector>
#include <QPen>
#include <QBrush>

class DotChart : public QWidget
{
    Q_OBJECT

public:
    explicit DotChart(QWidget *parent = nullptr);
    DotChart(const QVector<int> &data, const QPen &pen = QPen(Qt::black, 1), const QBrush &brush = QBrush(Qt::blue), QWidget *parent = nullptr);
    DotChart(const DotChart &other);

    void setData(const QVector<int>& newData);
    void setPen(const QPen& newPen);
    void setBrush(const QBrush& newBrush);

    DotChart& operator=(const DotChart& other);

    QVector<int> getData() const;
    QPen getPen() const ;
    QBrush getBrush() const;

signals:
    void penWidthChanged(int newWidth);

public slots:
    void setPenWidth(int width);

protected:
    void paintEvent(QPaintEvent *event) override;
    void resizeEvent(QResizeEvent *event) override;
    void contextMenuEvent(QContextMenuEvent *event) override;

private:
    QVector<int> data;
    QPen pen;
    QBrush brush;

    void drawAxes(QPainter &painter, int margin, int w, int h, int maxVal, int n);
    void drawChart(QPainter& painter);
};

#endif // DOTCHART_H

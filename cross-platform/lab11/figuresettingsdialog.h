#ifndef FIGURESETTINGSDIALOG_H
#define FIGURESETTINGSDIALOG_H

#include <QDialog>
#include <QColor>

class QSpinBox;
class QComboBox;

class FigureSettingsDialog : public QDialog {
    Q_OBJECT

public:
    FigureSettingsDialog(QWidget *parent = nullptr);

    int getPenWidth() const;
    int getRadius() const;
    int getRectWidth() const;
    int getRectHeight() const;

private:
    QSpinBox *penWidthSpin;
    QSpinBox *radiusSpin;
    QSpinBox *rectWidthSpin;
    QSpinBox *rectHeightSpin;
};

#endif // FIGURESETTINGSDIALOG_H

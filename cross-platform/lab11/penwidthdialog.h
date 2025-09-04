#ifndef PENWIDTHDIALOG_H
#define PENWIDTHDIALOG_H

#include <QDialog>

class QSpinBox;

class PenWidthDialog : public QDialog {
    Q_OBJECT

public:
    explicit PenWidthDialog(int currentWidth, QWidget *parent = nullptr);
    int penWidth() const;

private:
    QSpinBox *spinBox;
};

#endif // PENWIDTHDIALOG_H

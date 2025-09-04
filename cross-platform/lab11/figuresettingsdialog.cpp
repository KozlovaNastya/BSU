#include "FigureSettingsDialog.h"
#include <QVBoxLayout>
#include <QSpinBox>
#include <QFormLayout>
#include <QDialogButtonBox>

FigureSettingsDialog::FigureSettingsDialog(QWidget *parent)
    : QDialog(parent) {

    setWindowTitle("Figure Parameters");

    QFormLayout *formLayout = new QFormLayout;

    penWidthSpin = new QSpinBox;
    penWidthSpin->setRange(1, 20);
    penWidthSpin->setValue(2);

    radiusSpin = new QSpinBox;
    radiusSpin->setRange(1, 200);
    radiusSpin->setValue(50);

    rectWidthSpin = new QSpinBox;
    rectWidthSpin->setRange(10, 400);
    rectWidthSpin->setValue(100);

    rectHeightSpin = new QSpinBox;
    rectHeightSpin->setRange(10, 400);
    rectHeightSpin->setValue(50);

    formLayout->addRow("Pen Width:", penWidthSpin);
    formLayout->addRow("Circle Rdius:", radiusSpin);
    formLayout->addRow("Rectangle Width:", rectWidthSpin);
    formLayout->addRow("Rectangle Height:", rectHeightSpin);

    QDialogButtonBox *buttons = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttons, &QDialogButtonBox::accepted, this, &QDialog::accept);
    connect(buttons, &QDialogButtonBox::rejected, this, &QDialog::reject);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->addLayout(formLayout);
    layout->addWidget(buttons);
    setLayout(layout);
}
int FigureSettingsDialog::getPenWidth() const {
    return penWidthSpin->value();
}
int FigureSettingsDialog::getRadius() const{
    return radiusSpin->value();
}
int FigureSettingsDialog::getRectWidth() const{
    return rectWidthSpin->value();
}
int FigureSettingsDialog::getRectHeight() const{
    return rectHeightSpin->value();
}

#include "PenWidthDialog.h"
#include <QVBoxLayout>
#include <QDialogButtonBox>
#include <QSpinBox>
#include <QLabel>

PenWidthDialog::PenWidthDialog(int currentWidth, QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Set Pen Width");

    spinBox = new QSpinBox(this);
    spinBox->setRange(1, 20);
    spinBox->setValue(currentWidth);

    auto *layout = new QVBoxLayout(this);
    layout->addWidget(new QLabel("Pen Width:"));
    layout->addWidget(spinBox);

    auto *buttonBox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    layout->addWidget(buttonBox);

    connect(buttonBox, &QDialogButtonBox::accepted, this, &PenWidthDialog::accept);
    connect(buttonBox, &QDialogButtonBox::rejected, this, &PenWidthDialog::reject);
}

int PenWidthDialog::penWidth() const {
    return spinBox->value();
}

#include "records.h"
#include "ui_records.h"

records::records(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::records)
{
    ui->setupUi(this);
}
void records::setRecords(const QVector<QPair<int, QString>>& records)
{
    ui->recordtableWidget->setRowCount(0);
    for (int i = 0; i < records.size(); ++i) {
        ui->recordtableWidget->insertRow(i);
        ui->recordtableWidget->setItem(i, 0, new QTableWidgetItem(QString::number(records[i].first)));
        ui->recordtableWidget->setItem(i, 1, new QTableWidgetItem(records[i].second));
    }
}
records::~records()
{
    delete ui;
}

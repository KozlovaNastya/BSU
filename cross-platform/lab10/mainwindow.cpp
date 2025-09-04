#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "records.h"
#include <random>
#include <QMessageBox>
#include <QInputDialog>
#include <algorithm>
#include <QFile>
#include <QTextStream>
#include <QRegularExpression>
#include <QRegularExpressionValidator>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->pushButton_3->setEnabled(false);
    loadRecordsFromFile("records.txt");

    QRegularExpression regex("^\\d{4}$"); // Только 4 цифры
    QValidator *validator = new QRegularExpressionValidator(regex, this);
    ui->lineEdit->setValidator(validator);

    setFixedSize(this->size());
}

MainWindow::~MainWindow()
{
    delete ui;
    saveRecordsToFile("records.txt");
}
void MainWindow::saveRecordsToFile(const QString& filename)
{
    QFile file(filename);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&file);
        for (const auto& record : listOfRecords) {
            out << record.first << " " << record.second << "\n";
        }
        file.close();
    }
    else{
        QMessageBox::warning(this, "Ошибка записи",
                             QString("Не удалось открыть файл для записи: %1").arg(filename));
    }
}

void MainWindow::loadRecordsFromFile(const QString& filename)
{
    QFile file(filename);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&file);
        listOfRecords.clear();
        while (!in.atEnd()) {
            QString line = in.readLine().trimmed();
            if (line.isEmpty()) continue;

            QStringList parts = line.split(" ");
            if (parts.size() >= 2) {
                bool ok;
                int attempts = parts[0].toInt(&ok);
                if (ok) {
                    QString name = parts.mid(1).join(" ");
                    listOfRecords.append(qMakePair(attempts, name));
                }
            }
        }
        file.close();
    }
    else {
        QMessageBox::warning(this, "Ошибка записи",
                         QString("Не удалось открыть файл для чтенния: %1").arg(filename));
    }
}
void MainWindow::on_pushButton_clicked()
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(0, 9);
    int index = 0;
    number = QString(4, ' ');
    while (index < 4) {
        int digit = dist(gen);
        if (index == 0 && digit == 0)
            continue;
        bool isUnique = true;
        for (int j = 0; j < index; ++j) {
            if (number[j] == QChar('0' + digit)) {
                isUnique = false;
                break;
            }
        }
        if (isUnique) {
            number[index] = QChar('0' + digit);
            ++index;
        }
    }
    ui->tableWidget->setRowCount(0);
    ui->label->setText("игра начата");
    ui->pushButton_3->setEnabled(true);
    ui->label_3->setText(number);
    ui->lineEdit->clear();
}

void MainWindow::on_pushButton_2_clicked()
{
    records *dialog = new records(this);
    dialog->setRecords(listOfRecords);
    dialog->exec();
}

void MainWindow::on_pushButton_3_clicked()
{
    QString getNumber = ui->lineEdit->text();
    int cows = 0, buls = 0;

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++){
            if(number[i] == getNumber[j]){
                if(i == j) buls++;
                else cows++;
            }
        }
    }

    int rowCount = ui->tableWidget->rowCount();
    ui->tableWidget->insertRow(rowCount);
    ui->tableWidget->setItem(rowCount, 0, new QTableWidgetItem(getNumber));
    ui->tableWidget->setItem(rowCount, 1, new QTableWidgetItem(QString("быков: %1, коров: %2").arg(buls).arg(cows)));

    if(buls == 4){
        ui->label->setText("Победа!!");
        ui->pushButton_3->setEnabled(false);

        bool isOk;
        QString playerName = QInputDialog::getText(this, "Победа!",
                                                   "Вы угадали число!\nВведите ваше имя для таблицы рекордов:",
                                                   QLineEdit::Normal, "", &isOk);

        if(isOk && !playerName.isEmpty()){
            listOfRecords.append(qMakePair(ui->tableWidget->rowCount(), playerName));
            std::sort(listOfRecords.begin(), listOfRecords.end(), [](const QPair<int, QString>& a, const QPair<int, QString>& b) {
                return a.first < b.first;
            });
            if(listOfRecords.size() > 10){
                listOfRecords.erase(listOfRecords.begin() + 10, listOfRecords.end());
            }
        }
    }
    else{
        ui->label->setText("Неверно..");
    }
}

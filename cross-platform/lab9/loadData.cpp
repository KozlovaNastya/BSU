#include "loadData.h"
#include <QVector>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QRegularExpression>

void readDataFromResource(QVector<int>& data) {
    QFile file(":/data/data.txt");
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error("Error with openning file");
    }

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList tokens = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);

        for (const QString& token : tokens) {
            bool ok;
            int value = token.toInt(&ok);

            if (!ok || value < 0) {
                throw std::runtime_error("Error: There is non integer or negative number");
            }

            data.append(value);
        }
    }
}

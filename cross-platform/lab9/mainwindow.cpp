#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "loadData.h"

#include <QFileDialog>
#include <QMessageBox>
#include <QCloseEvent>
#include <QColorDialog>
#include <QIcon>
#include <QPixmap>
#include <QActionGroup>
#include <QRegularExpression>
#include <QString>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    chart = new DotChart(this);
    setCentralWidget(chart);

    try {
        readDataFromResource(data);
        chart->setData(data);
    } catch (const std::runtime_error& e) {
        QMessageBox::critical(this, "Error!", e.what());
    }


    createActions();
    createMenus();

    openAct->setEnabled(false);
    closeAct->setEnabled(false);

    connect(chart, &DotChart::penWidthChanged, this, &MainWindow::updateStatusBar);

    updateStatusBar();
}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setShortcut(QKeySequence("Ctrl+O"));
    connect(openAct, &QAction::triggered, this, &MainWindow::openFile);

    saveAct = new QAction(tr("&Save"), this);
    saveAct->setShortcut(QKeySequence("Ctrl+S"));
    connect(saveAct, &QAction::triggered, this, &MainWindow::saveFile);

    saveAsAct = new QAction(tr("Save &As..."), this);
    connect(saveAsAct, &QAction::triggered, this, &MainWindow::saveFileAs);

    closeAct = new QAction(tr("&Close"), this);
    closeAct->setShortcut(QKeySequence("Ctrl+W"));
    connect(closeAct, &QAction::triggered, this, &MainWindow::closeChart);

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setShortcut(QKeySequence("Alt+X"));
    connect(exitAct, &QAction::triggered, this, &MainWindow::exitApp);

    penColorAct = new QAction(tr("&Color..."), this);
    connect(penColorAct, &QAction::triggered, this, &MainWindow::penColor);

    penStyleSolidAct = new QAction(tr("&Solid"), this);
    penStyleSolidAct->setCheckable(true);
    penStyleDashAct = new QAction(tr("&Dash"), this);
    penStyleDashAct->setCheckable(true);
    penStyleDotAct = new QAction(tr("&Dot"), this);
    penStyleDotAct->setCheckable(true);

    connect(penStyleSolidAct, &QAction::triggered, this, &MainWindow::penStyleSolid);
    connect(penStyleDashAct, &QAction::triggered, this, &MainWindow::penStyleDash);
    connect(penStyleDotAct, &QAction::triggered, this, &MainWindow::penStyleDot);

    brushColorAct = new QAction(tr("&Color..."), this);
    connect(brushColorAct, &QAction::triggered, this, &MainWindow::brushColor);

    aboutAct = new QAction(tr("&About"), this);
    connect(aboutAct, &QAction::triggered, this, &MainWindow::showAbout);
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addAction(saveAct);
    fileMenu->addAction(saveAsAct);
    fileMenu->addAction(closeAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    penMenu = menuBar()->addMenu(tr("&Pen"));
    penMenu->addAction(penColorAct);

    QMenu *penStyleMenu = penMenu->addMenu(tr("Style"));
    penStyleMenu->addAction(penStyleSolidAct);
    penStyleMenu->addAction(penStyleDashAct);
    penStyleMenu->addAction(penStyleDotAct);

    QActionGroup *penStyleGroup = new QActionGroup(this);
    penStyleGroup->addAction(penStyleSolidAct);
    penStyleGroup->addAction(penStyleDashAct);
    penStyleGroup->addAction(penStyleDotAct);
    penStyleSolidAct->setChecked(true);

    brushMenu = menuBar()->addMenu(tr("&Brush"));
    brushMenu->addAction(brushColorAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
}

void MainWindow::openFile()
{
    if (!maybeSave())
        return;

    QString fileName = QFileDialog::getOpenFileName(this, tr("Open Data File"), "", tr("Text Files (*.txt);;All Files (*)"));
    if (!fileName.isEmpty()) {
        try {
            loadFromFile(fileName);
            setCurrentFile(fileName);
            openAct->setEnabled(true);
            closeAct->setEnabled(true);
            isModified = false;
        } catch (const std::exception &e) {
            QMessageBox::critical(this, "Error", e.what());
        }
    }
}

void MainWindow::saveFile()
{
    try {
        if (currentFile.isEmpty()) {
            saveFileAs();
        } else {
            saveToFile(currentFile);
        }
    } catch (const std::exception &e) {
        QMessageBox::warning(this, "Save Image", e.what());
    }
}

void MainWindow::saveFileAs()
{
    try{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save Image"), "", tr("PNG Images (*.png);;JPEG Images (*.jpg);;All Files (*)"));
        if (!fileName.isEmpty()) {
            saveToFile(fileName);
            setCurrentFile(fileName);
            openAct->setEnabled(true);
            closeAct->setEnabled(true);
            isModified = false;
        }
    }
    catch(const std::exception &e){
        QMessageBox::warning(this, "Save Image As", e.what());
    }
}

void MainWindow::closeChart()
{
    if (!maybeSave())
        return;

    data.clear();
    chart->setData(data);
    currentFile.clear();
    setWindowTitle("DotChart Application");
    openAct->setEnabled(false);
    closeAct->setEnabled(false);
    isModified = false;
}

void MainWindow::exitApp()
{
    close();
}

bool MainWindow::maybeSave()
{
    if (!isModified)
        return true;

    auto ret = QMessageBox::warning(this, tr("Application"),
                                    tr("The image has been modified.\n"
                                       "Do you want to save your changes?"),
                                    QMessageBox::Save | QMessageBox::Discard | QMessageBox::Cancel);

    if (ret == QMessageBox::Save) {
        saveFile();
        return !isModified;
    } else if (ret == QMessageBox::Cancel) {
        return false;
    }
    return true;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if (maybeSave())
        event->accept();
    else
        event->ignore();
}

void MainWindow::loadFromFile(const QString &filename)
{
    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        throw std::runtime_error(QString("Cannot open file %1").arg(filename).toStdString());
    }

    QVector<int> newData;
    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList tokens = line.split(QRegularExpression("\\s+"), Qt::SkipEmptyParts);
        for (const QString& token : tokens) {
            bool ok;
            int val = token.toInt(&ok);
            if (!ok || val < 0) {
                throw std::runtime_error("Invalid data in file");
            }
            newData.append(val);
        }
    }
    file.close();

    data = newData;
    chart->setData(data);
    isModified = false;
}

void MainWindow::saveToFile(const QString &filename)
{
    QPixmap pixmap(chart->size());
    chart->render(&pixmap);

    if (!pixmap.save(filename)) {
        throw std::runtime_error("Failed to save file");
    }
    isModified = false;
}


void MainWindow::setCurrentFile(const QString &filename)
{
    currentFile = filename;
    QString shownName = currentFile.isEmpty() ? "Untitled" : QFileInfo(currentFile).fileName();
    setWindowTitle(tr("%1 - DotChart Application").arg(shownName));
    updateStatusBar();
}

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(chart->getPen().color(), this, tr("Choose Pen Color"));
    if (newColor.isValid()) {
        QPen pen = chart->getPen();
        pen.setColor(newColor);
        chart->setPen(pen);
        isModified = true;
        updateStatusBar();
    }
}

void MainWindow::penStyleSolid()
{
    QPen pen = chart->getPen();
    pen.setStyle(Qt::SolidLine);
    chart->setPen(pen);
    isModified = true;
    updateStatusBar();
}

void MainWindow::penStyleDash()
{
    QPen pen = chart->getPen();
    pen.setStyle(Qt::DashLine);
    chart->setPen(pen);
    isModified = true;
    updateStatusBar();
}

void MainWindow::penStyleDot()
{
    QPen pen = chart->getPen();
    pen.setStyle(Qt::DotLine);
    chart->setPen(pen);
    isModified = true;
    updateStatusBar();
}

void MainWindow::brushColor()
{
    QColor newColor = QColorDialog::getColor(chart->getBrush().color(), this, tr("Choose Brush Color"));
    if (newColor.isValid()) {
        QBrush brush(newColor);
        chart->setBrush(brush);
        isModified = true;
        updateStatusBar();
    }
}

void MainWindow::showAbout()
{
    QMessageBox::about(this, tr("About"), tr("Author: Козлова Анастасия Олеговна\nGroup: 10\nVariant: 17"));
}

void MainWindow::updateStatusBar()
{
    QString fileName = currentFile.isEmpty() ? tr("Untitled") : QFileInfo(currentFile).fileName();

    QPen pen = chart->getPen();

    int width = pen.width();

    QColor color = pen.color();
    QString colorName = color.name();

    QString styleStr;
    switch (pen.style()) {
    case Qt::SolidLine: styleStr = tr("Solid"); break;
    case Qt::DashLine: styleStr = tr("Dash"); break;
    case Qt::DotLine: styleStr = tr("Dot"); break;
    case Qt::DashDotLine: styleStr = tr("Dash-Dot"); break;
    case Qt::DashDotDotLine: styleStr = tr("Dash-Dot-Dot"); break;
    default: styleStr = tr("Custom");
    }

    QString statusText = tr("File: %1 | Width: %2 px | Color: %3 | Style: %4").arg(fileName).arg(width).arg(colorName).arg(styleStr);

    statusBar()->showMessage(statusText);
}

MainWindow::~MainWindow()
{
    delete ui;
}

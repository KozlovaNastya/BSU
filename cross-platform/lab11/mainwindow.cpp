#include "MainWindow.h"
#include "PenWidthDialog.h"
#include <figuresettingsdialog.h>
#include <QMenuBar>
#include <QStatusBar>
#include <QColorDialog>
#include <QAction>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
{
    canvas = new Canvas(this);
    setCentralWidget(canvas);
    resize(600, 600);
    createMenus();
    statusBar()->showMessage("Ready");
}

MainWindow::~MainWindow() {}

void MainWindow::createMenus()
{
    QMenu *figureMenu = menuBar()->addMenu("Figure");

    QAction *lineAction = new QAction("Line", this);
    connect(lineAction, &QAction::triggered, this, [=]() {
        canvas->setCurrentFigureType("Line");
        statusBar()->showMessage("Line selected");
    });
    figureMenu->addAction(lineAction);

    QAction *circleAction = new QAction("Circle", this);
    connect(circleAction, &QAction::triggered, this, [=]() {
        canvas->setCurrentFigureType("Circle");
        statusBar()->showMessage("Circle selected");
    });
    figureMenu->addAction(circleAction);

    QAction *rectangleAction = new QAction("Rectangle", this);
    connect(rectangleAction, &QAction::triggered, this, [=]() {
        canvas->setCurrentFigureType("Rectangle");
        statusBar()->showMessage("Rectangle selected");
    });
    figureMenu->addAction(rectangleAction);

    QAction *freeLineAction = new QAction("Free Line", this);
    connect(freeLineAction, &QAction::triggered, this, [=]() {
        canvas->setCurrentFigureType("FreeLine");
        statusBar()->showMessage("Free Line selected");
    });
    figureMenu->addAction(freeLineAction);

    // Цвет
    QMenu *optionsMenu = menuBar()->addMenu("Options");

    QAction *colorAction = new QAction("Color", this);
    connect(colorAction, &QAction::triggered, this, [=]() {
        QColor color = QColorDialog::getColor();
        if (color.isValid())
            canvas->setCurrentColor(color);
    });
    optionsMenu->addAction(colorAction);

    QAction *penWidthAction = new QAction("Pen Width", this);
    connect(penWidthAction, &QAction::triggered, this, [=]() {
        PenWidthDialog dialog(canvas->getPenWidth(), this);
        if (dialog.exec() == QDialog::Accepted) {
            canvas->setPenWidth(dialog.penWidth());
        }
    });
    optionsMenu->addAction(penWidthAction);
    QAction *properties = new QAction("Properties", this);
    connect(properties, &QAction::triggered, this, [=]() {
    FigureSettingsDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        canvas->setPenWidth(dialog.getPenWidth());
        canvas->setRadius(dialog.getRadius());
        canvas->setRectHeight(dialog.getRectHeight());
        canvas->setRectWidth(dialog.getRectWidth());
    }
    });
    optionsMenu->addAction(properties);

    QMenu *fileMenu = menuBar()->addMenu("File");
    QAction *exportImageAction = new QAction("Export as Image", this);
    connect(exportImageAction, &QAction::triggered, this, [=]() {
        QString fileName = QFileDialog::getSaveFileName(this, "Save Image", "", "PNG Images (*.png)");
        if (!fileName.isEmpty()) {
            canvas->saveImage(fileName);
        }
    });
    fileMenu->addAction(exportImageAction);

    QAction *loadImageAction = new QAction("Load Image", this);
    connect(loadImageAction, &QAction::triggered, this, [=]() {
        QString fileName = QFileDialog::getOpenFileName(this, "Load Image", "", "PNG Images (*.png *.jpg)");
        if (!fileName.isEmpty()) {
            canvas->loadImage(fileName);
        }
    });
    fileMenu->addAction(loadImageAction);
}

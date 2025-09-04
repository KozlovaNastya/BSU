#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "dotchart.h"
#include <QMainWindow>
#include <QAction>
#include <QMenu>
#include <QColor>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void closeEvent(QCloseEvent *event) override;

private slots:
    void openFile();
    void saveFile();
    void saveFileAs();
    void closeChart();
    void exitApp();

    void penColor();
    void penStyleSolid();
    void penStyleDash();
    void penStyleDot();

    void brushColor();

    void showAbout();

private:
    Ui::MainWindow *ui;
    DotChart* chart;

    QVector<int> data;
    QString currentFile;
    bool isModified = false;

    QMenu *fileMenu;
    QAction *openAct;
    QAction *saveAct;
    QAction *saveAsAct;
    QAction *closeAct;
    QAction *exitAct;

    QMenu *penMenu;
    QAction *penColorAct;
    QAction *penStyleSolidAct;
    QAction *penStyleDashAct;
    QAction *penStyleDotAct;

    QMenu *brushMenu;
    QAction *brushColorAct;

    QMenu *helpMenu;
    QAction *aboutAct;

    void createActions();
    void createMenus();

    bool maybeSave();
    void loadFromFile(const QString &filename);
    void saveToFile(const QString &filename);
    void setCurrentFile(const QString &filename);
    void updateStatusBar();
};
#endif // MAINWINDOW_H

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "electrodeMap.h"
#include "electrodewindow2d.h"
#include "electrodewindow3d.h"
#include "dummyFilter.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void showWindows();

private:
    Ui::MainWindow *ui;

    ElectrodeMap _electrodeMap;
    ElectrodeWindow2D _electrodeWindow2D;
    ElectrodeWindow3D _electrodeWindow3D;
    DummyFilter dummyFilter;
};

#endif // MAINWINDOW_H

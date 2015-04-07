#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "electrodeMap.h"
#include "electrodewindow2d.h"
#include "electrodewindow3d.h"
#include "dummyFilter.h"
#include "electrodeMapDialog.h"
#include "opensignalfiledialog.h"
#include "filterDialog.h"
#include "inputModule.h"
#include "player.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    virtual void closeEvent (QCloseEvent *event);

    void showWindows();

    void closeWindows();

private slots:
    void openSignalFileDialogOk();

    void on_actionOpenSignalFile_triggered();

    void on_playButton_clicked();

    void on_rewindButton_clicked();

    void on_actionPlayer_triggered();

    void on_actionShow_2D_triggered();

    void on_actionShow_3D_triggered();

    void on_actionElectrode_map_triggered();

    void electrodeMapChanged();

    void on_actionBasic_triggered();

private:
    Ui::MainWindow *ui;

    ElectrodeMap _electrodeMap;
    ElectrodeWindow2D _electrodeWindow2D;
    ElectrodeWindow3D _electrodeWindow3D;
    DummyFilter dummyFilter;

    OpenSignalFileDialog _openSignalFileDialog;
    ElectrodeMapDialog _electrodeMapDialog;
    FilterDialog _filterDialog;

    Player _player;
    InputModule* _inputModule;
};

#endif // MAINWINDOW_H

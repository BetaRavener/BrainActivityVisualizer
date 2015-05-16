// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

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

/**
 * @brief The MainWindow class represents main application window which contains multichart view as
 * its main element and provides access to other dialogs and windows via menu bar.
 */
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    /**
     * @brief Event that is called when the window is closed. When main window is closed, all other windows
     * are closed as well and the application exits.
     * @param event
     */
    virtual void closeEvent (QCloseEvent *event);

    /**
     * @brief Closses all child windows.
     */
    void closeWindows();

private slots:
    /**
     * @brief Slot used when the signal file dialog was closed by pressing Ok.
     */
    void openSignalFileDialogOk();

    /**
     * @brief Slot used when user chooses to open signal file dialog.
     */
    void on_actionOpenSignalFile_triggered();

    /**
     * @brief Slot used when the play button is clicked. Plays or pauses the animation playback.
     */
    void on_playButton_clicked();

    /**
     * @brief Slot used when the rewind button is clicked. Resets the animation to beggining.
     */
    void on_rewindButton_clicked();

    /**
     * @brief Slot used when user chooses to open player settings dialog.
     */
    void on_actionPlayer_triggered();

    /**
     * @brief Slot used when user chooses to open 2D electrode window.
     */
    void on_actionShow_2D_triggered();

    /**
     * @brief Slot used when user chooses to open 3D electrode window.
     */
    void on_actionShow_3D_triggered();

    /**
     * @brief Slot used when user chooses to open electrode map dialog.
     */
    void on_actionElectrode_map_triggered();

    /**
     * @brief Slot used when the electrode map changes.
     */
    void electrodeMapChanged();

    /**
     * @brief Slot used when user chooses to open basic filtering dialog.
     */
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

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "fileInputModule.h"
#include "QMessageBox"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _electrodeWindow2D(nullptr),
    _electrodeWindow3D(nullptr),
    _inputModule(nullptr)
{
    ui->setupUi(this);

    QSurfaceFormat format;
    format.setSamples(2);
    format.setMajorVersion(3);
    format.setMinorVersion(3);
    format.setProfile(QSurfaceFormat::CoreProfile);
    format.setRenderableType(QSurfaceFormat::OpenGL);

    QSurfaceFormat format2 = format;
    format2.setSamples(1);

    QSurfaceFormat format3 = format;
    format3.setSamples(4);

    _electrodeWindow3D.electrodeView()->setFormat(format);
    _electrodeWindow2D.electrodeView()->setFormat(format2);
    ui->graphView2D->setFormat(format3);
    ui->graphView2D->addLabels(ui->horizontalGraphLabels, ui->verticalGraphLabels);
    ui->graphView2D->addScrollBars(ui->graphHorizontalScroll, ui->graphVerticalScroll);
    connect(ui->graphView2D, SIGNAL(requestTime(double)), &_player, SLOT(changeTime(double)));
    connect(ui->graphHorizontalScroll, SIGNAL(valueChanged(int)), ui->horizontalScrollArea->horizontalScrollBar(), SLOT(setValue(int)));
    connect(ui->graphVerticalScroll, SIGNAL(valueChanged(int)), ui->verticalScrollArea->verticalScrollBar(), SLOT(setValue(int)));
    ui->horizontalScrollArea->viewport()->installEventFilter(&dummyFilter);
    ui->verticalScrollArea->viewport()->installEventFilter(&dummyFilter);
    ui->graphHorizontalScroll->installEventFilter(&dummyFilter);
    ui->graphVerticalScroll->installEventFilter(&dummyFilter);

    _electrodeWindow2D.electrodeView()->electrodes(_electrodeMap.allElectrodes());
    _electrodeWindow3D.electrodeView()->electrodes(_electrodeMap.allElectrodes());

    _openSignalFileDialog.setElectrodeMap(&_electrodeMap);
    _openSignalFileDialog.setModal(true);
    connect(&_openSignalFileDialog, SIGNAL(accepted()), this, SLOT(openSignalFileDialogOk()));

    _electrodeMapDialog.assignElectrodeMap(&_electrodeMap);
    connect(&_electrodeMapDialog, SIGNAL(electrodeMapImported()), this, SLOT(electrodeMapChanged()));
    connect(&_electrodeMapDialog, SIGNAL(electrodeMapImported()), &_openSignalFileDialog, SLOT(electrodeMapChanged()));

    connect(&_filterDialog, SIGNAL(dataFiltered()), ui->graphView2D, SLOT(dataChanged()));

    _player.assignPlayButton(ui->playButton);
    connect(&_player, SIGNAL(timeChanged(double)), ui->graphView2D, SLOT(timeChanged(double)));
    connect(&_player, SIGNAL(timeChanged(double)), _electrodeWindow2D.electrodeView(), SLOT(repaint()));
    connect(&_player, SIGNAL(timeChanged(double)), _electrodeWindow3D.electrodeView(), SLOT(repaint()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    Q_UNUSED(event);
    closeWindows();
}

void MainWindow::showWindows()
{
    _electrodeWindow2D.show();
    _electrodeWindow3D.show();
}

void MainWindow::closeWindows()
{
    _electrodeWindow2D.close();
    _electrodeWindow3D.close();
}

void MainWindow::openSignalFileDialogOk()
{
    for (Electrode::WeakPtr electrode : _electrodeMap.allElectrodes())
        electrode->setInactive();

    SignalBatch::Ptr dialogResult = _openSignalFileDialog.getResult();
    if (_inputModule)
    {
        delete _inputModule;
        _inputModule = nullptr;
    }

    _inputModule = new FileInputModule(dialogResult);
    ui->graphView2D->signalBatch(_inputModule->signalBatch());
    _player.init(_inputModule->signalBatch());
}

void MainWindow::on_actionOpenSignalFile_triggered()
{
    _openSignalFileDialog.exec();
}

void MainWindow::on_playButton_clicked()
{
    if (_player.isPlaying())
        _player.pause();
    else
        _player.play();
}

void MainWindow::on_rewindButton_clicked()
{
    _player.rewind();
}

void MainWindow::on_actionPlayer_triggered()
{
    _player.openSettingsDialog();
}

void MainWindow::on_actionShow_2D_triggered()
{
    try
    {
        _electrodeWindow2D.show();
    }
    catch(std::exception e)
    {
        QMessageBox::critical(this, "Error", QString("Missing components required by 2D view"));
        _electrodeWindow2D.hide();
    }
}

void MainWindow::on_actionShow_3D_triggered()
{
    try
    {
        _electrodeWindow3D.show();
    }
    catch(std::exception e)
    {
        QMessageBox::critical(this, "Error", QString("Missing components required by 3D view"));
        _electrodeWindow3D.hide();
    }
}

void MainWindow::on_actionElectrode_map_triggered()
{
    _electrodeMapDialog.exec();
}

void MainWindow::electrodeMapChanged()
{
    if (_inputModule && _inputModule->signalBatch())
    {
        _inputModule->signalBatch()->clearElectrodeMappings();
    }
    _electrodeWindow2D.electrodeView()->electrodes(_electrodeMap.allElectrodes());
    _electrodeWindow3D.electrodeView()->electrodes(_electrodeMap.allElectrodes());
}

void MainWindow::on_actionBasic_triggered()
{
    if (_inputModule && _inputModule->signalBatch())
    {
        _filterDialog.reset();
        _filterDialog.assignSignalBatch(_inputModule->signalBatch());
        _filterDialog.exec();
    }
    else
    {
        QMessageBox::information(this, "No data available", "Open a file before using filters");
    }
}

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _electrodeWindow2D(this),
    _electrodeWindow3D(this)
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
    connect(ui->graphHorizontalScroll, SIGNAL(valueChanged(int)), ui->horizontalScrollArea->horizontalScrollBar(), SLOT(setValue(int)));
    connect(ui->graphVerticalScroll, SIGNAL(valueChanged(int)), ui->verticalScrollArea->verticalScrollBar(), SLOT(setValue(int)));
    ui->horizontalScrollArea->viewport()->installEventFilter(&dummyFilter);
    ui->verticalScrollArea->viewport()->installEventFilter(&dummyFilter);
    ui->graphHorizontalScroll->installEventFilter(&dummyFilter);
    ui->graphVerticalScroll->installEventFilter(&dummyFilter);

    _electrodeWindow2D.electrodeView()->electrodeMap(&_electrodeMap);
    _electrodeWindow3D.electrodeView()->electrodeMap(&_electrodeMap);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::showWindows()
{
    _electrodeWindow2D.show();
    _electrodeWindow3D.show();
}

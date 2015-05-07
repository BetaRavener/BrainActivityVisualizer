#include "electrodewindow2d.h"
#include "ui_electrodewindow2d.h"

ElectrodeWindow2D::ElectrodeWindow2D(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ElectrodeWindow2D)
{
    ui->setupUi(this);
}

ElectrodeWindow2D::~ElectrodeWindow2D()
{
    delete ui;
}

ElectrodeView2D *ElectrodeWindow2D::electrodeView()
{
    return ui->electrodeView2D;
}

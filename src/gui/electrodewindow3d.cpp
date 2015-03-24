#include "electrodewindow3d.h"
#include "ui_electrodewindow3d.h"

ElectrodeWindow3D::ElectrodeWindow3D(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ElectrodeWindow3D)
{
    ui->setupUi(this);
}

ElectrodeWindow3D::~ElectrodeWindow3D()
{
    delete ui;
}

ElectrodeView3D *ElectrodeWindow3D::electrodeView()
{
    return ui->electrodeView3D;
}

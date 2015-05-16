// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "electrodewindow3d.h"
#include "ui_electrodewindow3d.h"

ElectrodeWindow3D::ElectrodeWindow3D(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ElectrodeWindow3D)
{
    ui->setupUi(this);
    ui->electrodeView3D->showElectrodeNames(ui->showNamesCheckBox->checkState() == Qt::Checked);
}

ElectrodeWindow3D::~ElectrodeWindow3D()
{
    delete ui;
}

ElectrodeView3D *ElectrodeWindow3D::electrodeView()
{
    return ui->electrodeView3D;
}

void ElectrodeWindow3D::on_resetViewButton_clicked()
{
    ui->electrodeView3D->resetView(true);
}

void ElectrodeWindow3D::on_showNamesCheckBox_toggled(bool checked)
{
    ui->electrodeView3D->showElectrodeNames(checked);
}

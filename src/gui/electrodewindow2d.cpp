// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "electrodewindow2d.h"
#include "ui_electrodewindow2d.h"

ElectrodeWindow2D::ElectrodeWindow2D(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ElectrodeWindow2D)
{
    ui->setupUi(this);
    ui->electrodeView2D->showElectrodeNames(ui->showNamesCheckBox->checkState() == Qt::Checked);
}

ElectrodeWindow2D::~ElectrodeWindow2D()
{
    delete ui;
}

ElectrodeView2D *ElectrodeWindow2D::electrodeView()
{
    return ui->electrodeView2D;
}

void ElectrodeWindow2D::on_resetViewButton_clicked()
{
    ui->electrodeView2D->resetView(true);
}

void ElectrodeWindow2D::on_showNamesCheckBox_toggled(bool checked)
{
    ui->electrodeView2D->showElectrodeNames(checked);
}

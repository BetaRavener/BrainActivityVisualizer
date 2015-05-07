#include "electrodeMapDialog.h"
#include "ui_electrodeMapDialog.h"

#include <QFileDialog>
#include <QMessageBox>
#include <stdexcept>

ElectrodeMapDialog::ElectrodeMapDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ElectrodeMapDialog),
    _electrodeMap(nullptr)
{
    ui->setupUi(this);
}

ElectrodeMapDialog::~ElectrodeMapDialog()
{
    delete ui;
}

void ElectrodeMapDialog::assignElectrodeMap(ElectrodeMap *electrodeMap)
{
    _electrodeMap = electrodeMap;
}

void ElectrodeMapDialog::on_importButton_clicked()
{
    if (_electrodeMap == nullptr)
        return;

    QString path = QFileDialog::getOpenFileName(this, "Select map file", "electrodes", "Electrode map (*.elmap)");
    if (path == "")
        return;

    try
    {
        _electrodeMap->load(path.toStdString());
        emit electrodeMapImported();
    }
    catch (std::runtime_error re)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(re.what()));
    }
}

void ElectrodeMapDialog::on_exportButton_clicked()
{
    if (_electrodeMap == nullptr)
        return;

    QString path = QFileDialog::getSaveFileName(this, "Select map file", "electrodes", "Electrode map (*.elmap)");
    if (path == "")
        return;

    try
    {
        _electrodeMap->save(path.toStdString());
    }
    catch (std::runtime_error re)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(re.what()));
    }
}

void ElectrodeMapDialog::on_import3DButton_clicked()
{
    QString path = QFileDialog::getOpenFileName(this, "Select positions file", "electrodes", "Electrode positions (*.obj)");
    if (path == "")
        return;

    try
    {
        _electrodeMap->import3D(path.toStdString());
        emit electrodeMapImported();
    }
    catch (std::runtime_error re)
    {
        QMessageBox::critical(this, "Error", QString::fromStdString(re.what()));
    }
}

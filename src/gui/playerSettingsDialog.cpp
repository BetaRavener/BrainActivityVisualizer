// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "playerSettingsDialog.h"
#include "ui_playerSettingsDialog.h"

PlayerSettingsDialog::PlayerSettingsDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PlayerSettingsDialog)
{
    ui->setupUi(this);

    ui->transformationComboBox->addItem("None");
    ui->transformationComboBox->addItem("FFT");
}

PlayerSettingsDialog::~PlayerSettingsDialog()
{
    delete ui;
}

double PlayerSettingsDialog::gain()
{
    return ui->gainSpinBox->value();
}

void PlayerSettingsDialog::gain(double gain)
{
    ui->gainSpinBox->setValue(gain);
}

double PlayerSettingsDialog::refreshRate()
{
    return ui->refreshRateSpinBox->value();
}

void PlayerSettingsDialog::refreshRate(double rate)
{
    ui->refreshRateSpinBox->setValue(rate);
}

double PlayerSettingsDialog::speedFactor()
{
    return ui->speedFactorSpinBox->value();
}

void PlayerSettingsDialog::speedFactor(double factor)
{
    ui->speedFactorSpinBox->setValue(factor);
}

ElectrodeAdapter::TransformationType PlayerSettingsDialog::transformationType()
{
    switch(ui->transformationComboBox->currentIndex())
    {
    case 0:
        return ElectrodeAdapter::TransformationType::None;
    case 1:
        return ElectrodeAdapter::TransformationType::FFT;
    default:
        return ElectrodeAdapter::TransformationType::None;
    }
}

void PlayerSettingsDialog::transformationType(ElectrodeAdapter::TransformationType type)
{
    switch(type)
    {
    case ElectrodeAdapter::TransformationType::None:
        ui->transformationComboBox->setCurrentIndex(0);
        break;
    case ElectrodeAdapter::TransformationType::FFT:
        ui->transformationComboBox->setCurrentIndex(1);
        break;
    }
}

double PlayerSettingsDialog::transformationBeginFreq()
{
    return ui->beginFreqSpinBox->value();
}

void PlayerSettingsDialog::transformationBeginFreq(double freq)
{
    ui->beginFreqSpinBox->setValue(freq);
}

double PlayerSettingsDialog::transformationEndFreq()
{
    return ui->endFreqSpinBox->value();
}

void PlayerSettingsDialog::transformationEndFreq(double freq)
{
    ui->endFreqSpinBox->setValue(freq);
}

void PlayerSettingsDialog::on_buttonBox_rejected()
{

}

void PlayerSettingsDialog::on_buttonBox_accepted()
{
    emit changed();
}

void PlayerSettingsDialog::on_refreshRateSpinBox_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    emit changed();
}

void PlayerSettingsDialog::on_gainSpinBox_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    emit changed();
}

void PlayerSettingsDialog::on_speedFactorSpinBox_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    emit changed();
}

void PlayerSettingsDialog::on_transformationComboBox_currentIndexChanged(int index)
{
    switch(index)
    {
    case 0:
        ui->beginFreqSpinBox->setEnabled(false);
        ui->endFreqSpinBox->setEnabled(false);
        break;
    case 1:
        ui->beginFreqSpinBox->setEnabled(true);
        ui->endFreqSpinBox->setEnabled(true);
        break;
    case 2:
        ui->beginFreqSpinBox->setEnabled(true);
        ui->endFreqSpinBox->setEnabled(true);
        break;
    }

    emit changed();
}

void PlayerSettingsDialog::on_beginFreqSpinBox_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    emit changed();
}

void PlayerSettingsDialog::on_endFreqSpinBox_valueChanged(double arg1)
{
    Q_UNUSED(arg1);
    emit changed();
}

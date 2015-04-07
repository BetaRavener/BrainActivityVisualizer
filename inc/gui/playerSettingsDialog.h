#ifndef PLAYERSETTINGSDIALOG_H
#define PLAYERSETTINGSDIALOG_H

#include <QDialog>

#include "electrodeAdapter.h"

namespace Ui {
class PlayerSettingsDialog;
}

class PlayerSettingsDialog : public QDialog
{
    Q_OBJECT

signals:
    void changed();

public:
    explicit PlayerSettingsDialog(QWidget *parent = 0);
    ~PlayerSettingsDialog();

    double gain();
    void gain(double gain);

    double refreshRate();
    void refreshRate(double rate);

    double speedFactor();
    void speedFactor(double factor);

    ElectrodeAdapter::TransformationType transformationType();
    void transformationType(ElectrodeAdapter::TransformationType type);

    double transformationBeginFreq();
    void transformationBeginFreq(double freq);

    double transformationEndFreq();
    void transformationEndFreq(double freq);

private slots:
    void on_buttonBox_rejected();

    void on_buttonBox_accepted();

    void on_refreshRateSpinBox_valueChanged(double arg1);

    void on_gainSpinBox_valueChanged(double arg1);

    void on_speedFactorSpinBox_valueChanged(double arg1);

    void on_transformationComboBox_currentIndexChanged(int index);

    void on_beginFreqSpinBox_valueChanged(double arg1);

    void on_endFreqSpinBox_valueChanged(double arg1);

private:
    Ui::PlayerSettingsDialog *ui;
};

#endif // PLAYERSETTINGSDIALOG_H

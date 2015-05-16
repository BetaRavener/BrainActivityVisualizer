// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef PLAYERSETTINGSDIALOG_H
#define PLAYERSETTINGSDIALOG_H

#include <QDialog>

#include "electrodeAdapter.h"

namespace Ui {
class PlayerSettingsDialog;
}

/**
 * @brief The PlayerSettingsDialog class represents a dialog for changing the player configuration.
 */
class PlayerSettingsDialog : public QDialog
{
    Q_OBJECT

signals:
    /**
     * @brief Signal fires when the settings has changed and player should update its configuration.
     */
    void changed();

public:
    explicit PlayerSettingsDialog(QWidget *parent = 0);
    ~PlayerSettingsDialog();

    /**
     * @brief Getter.
     * @return Gain value used to multiply signal amplitude.
     */
    double gain();

    /**
     * @brief Setter.
     * @param gain Gain value used to multiply signal amplitude.
     */
    void gain(double gain);

    /**
     * @brief Getter.
     * @return Refresh rate (the update frequency) for the animation.
     */
    double refreshRate();

    /**
     * @brief Setter.
     * @return Refresh rate (the update frequency) for the animation.
     */
    void refreshRate(double rate);

    /**
     * @brief Getter.
     * @return Animation speed multiplier.
     */
    double speedFactor();

    /**
     * @brief Setter.
     * @param factor Animation speed multiplier.
     */
    void speedFactor(double factor);

    /**
     * @brief Getter.
     * @return Transformation type used for animating the electrodes.
     */
    ElectrodeAdapter::TransformationType transformationType();

    /**
     * @brief Setter.
     * @param type Transformation type used for animating the electrodes.
     */
    void transformationType(ElectrodeAdapter::TransformationType type);

    /**
     * @brief Getter.
     * @return The first frequency of transformation frequency range.
     */
    double transformationBeginFreq();

    /**
     * @brief Setter.
     * @param freq The first frequency of transformation frequency range.
     */
    void transformationBeginFreq(double freq);

    /**
     * @brief Getter.
     * @return The last frequency of transformation frequency range.
     */
    double transformationEndFreq();

    /**
     * @brief Setter.
     * @param freq last first frequency of transformation frequency range.
     */
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

// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#ifndef PLAYER_H
#define PLAYER_H

#include <QPushButton>
#include <QWidget>
#include <QTimer>
#include <QTime>
#include <QLabel>
#include "signalBatch.h"
#include "electrodeAdapter.h"
#include "playerSettingsDialog.h"

/**
 * @brief The Player class represents a class that drives the electrode animation.
 */
class Player : public QObject
{
    Q_OBJECT

public:
    Player();

    /**
     * @brief Initializes class before usage.
     * @param signalBatch Signal batch that will be used as a source of data for the animation.
     */
    void init(SignalBatch::WeakPtr signalBatch);

    /**
     * @brief Setter.
     * @param playButton Button that is used for playing / pausing.
     */
    void assignPlayButton(QPushButton* playButton);

    /**
     * @brief Setter.
     * @param playButton Label that displays current animation time.
     */
    void assignTimeLabel(QLabel* timeLabel);

    /**
     * @brief Plays the electrode animation.
     */
    void play();

    /**
     * @brief Pauses the electrode animation.
     */
    void pause();

    /**
     * @brief Resets the animation time to the beggining.
     */
    void rewind();

    /**
     * @brief Getter.
     * @return True if the animation is being played.
     */
    bool isPlaying();

    /**
     * @brief Opens the settings dialog associated with player.
     */
    void openSettingsDialog();

signals:
    /**
     * @brief Signal fires when animation time changes (after every tick).
     * @param time Current animation time.
     */
    void timeChanged(double time);

public slots:
    /**
     * @brief Slot used for chaning the animation time.
     * @param time New animation time.
     */
    void changeTime(double time);

private slots:
    /**
     * @brief Slot used when specified time interval passed and the animation
     * should upadte.
     */
    void tick();

    /**
     * @brief Slot used when the player settings has changed.
     */
    void settingsChanged();

    /**
     * @brief Slot used when the specified transformation operation used for playback has changed.
     */
    void transformationChanged();

private:
    void updateTime(double time);

    QPushButton *_playButton;
    QLabel *_timeLabel;

    QTimer _timer;
    QTime _controlTimer;
    double _animationTime;

    double _interval;
    double _speedFactor;

    SignalBatch::WeakPtr _signalBatch;
    ElectrodeAdapter _electrodeAdapter;
    PlayerSettingsDialog _settingsDialog;
};

#endif

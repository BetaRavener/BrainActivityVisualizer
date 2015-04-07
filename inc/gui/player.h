#ifndef PLAYER_H
#define PLAYER_H

#include <QPushButton>
#include <QWidget>
#include <QTimer>
#include "signalBatch.h"
#include "electrodeAdapter.h"
#include "playerSettingsDialog.h"

class Player : public QObject
{
    Q_OBJECT

public:
    Player();

    void init(SignalBatch::WeakPtr signalBatch);
    void assignPlayButton(QPushButton* playButton);

    void play();
    void pause();
    void rewind();

    bool isPlaying();

    void openSettingsDialog();

signals:
    void timeChanged(double time);

public slots:
    void changeTime(double time);

private slots:
    void tick();
    void settingsChanged();
    void transformationChanged();

private:
    void updateTime(double time);

    QPushButton *_playButton;

    QTimer _timer;
    double _animationTime;

    double _interval;
    double _speedFactor;

    SignalBatch::WeakPtr _signalBatch;
    ElectrodeAdapter _electrodeAdapter;
    PlayerSettingsDialog _settingsDialog;
};

#endif

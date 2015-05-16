// Author: Ivan Sevcik <ivan-sevcik@hotmail.com>
// Licensed under BSD 3-Clause License (see licenses/LICENSE.txt)

#include "player.h"

Player::Player()

{
    _interval = 0.033;
    _speedFactor = 1.0;

    _settingsDialog.gain(_electrodeAdapter.gain());
    _settingsDialog.refreshRate(1.0 / _interval);
    _settingsDialog.speedFactor(_speedFactor);
    _settingsDialog.transformationType(_electrodeAdapter.transformationType());

    connect(&_timer, SIGNAL(timeout()), this, SLOT(tick()));
    connect(&_settingsDialog, SIGNAL(changed()), this, SLOT(settingsChanged()));
}

void Player::init(SignalBatch::WeakPtr signalBatch)
{
    _signalBatch = signalBatch;
    _electrodeAdapter.init(signalBatch);
    pause();
    rewind();
}

void Player::assignPlayButton(QPushButton *playButton)
{
    _playButton = playButton;
}

void Player::assignTimeLabel(QLabel *timeLabel)
{
    _timeLabel = timeLabel;
}

void Player::play()
{
    _playButton->setText("||");

    if (_timer.isActive())
        return;

    _timer.start(_interval * 1000);
    _controlTimer.restart();
}

void Player::pause()
{
    _playButton->setText(">");

    if (_timer.isActive())
    {
        _timer.stop();
    }
}

void Player::rewind()
{
    _animationTime = 0;
    updateTime(_animationTime);
}

bool Player::isPlaying()
{
    return _timer.isActive();
}

void Player::openSettingsDialog()
{
    _settingsDialog.exec();
}

void Player::changeTime(double time)
{
    updateTime(time);
}

void Player::tick()
{
    int elapsed = _controlTimer.elapsed();
    _controlTimer.restart();
    updateTime(_animationTime + (double)elapsed / 1000.0 * _speedFactor);
}

void Player::settingsChanged()
{
    _electrodeAdapter.gain(_settingsDialog.gain());
    _interval = 1.0 / _settingsDialog.refreshRate();
    _speedFactor = _settingsDialog.speedFactor();
    if (_timer.isActive())
    {
        _timer.stop();
        _timer.start(_interval * 1000);
    }

    _electrodeAdapter.transformationType(_settingsDialog.transformationType());
    _electrodeAdapter.transformationBeginFreq(_settingsDialog.transformationBeginFreq());
    _electrodeAdapter.transformationEndFreq(_settingsDialog.transformationEndFreq());
}

void Player::transformationChanged()
{

}

void Player::updateTime(double time)
{
    if (_signalBatch)
    {
        _animationTime = time;
        if (_animationTime > _signalBatch->duration())
        {
            _animationTime = _signalBatch->duration();
            pause();
        }
    }
    else
    {
        _animationTime = 0.0;
        pause();
    }
    _electrodeAdapter.setTime(_animationTime);
    _timeLabel->setText(QString::number(_animationTime));
    emit timeChanged(_animationTime);
}

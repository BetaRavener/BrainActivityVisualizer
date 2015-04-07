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

void Player::play()
{
    _playButton->setText("||");

    if (_timer.isActive())
        return;

    _timer.start(_interval * 1000);
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
    updateTime(_animationTime + _interval * _speedFactor);
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
    emit timeChanged(_animationTime);
}

#include <ESC.h>

int ESC::channel_next_free = 0;

ESC::ESC(int pin, int minPulseWidth, int maxPulseWidth){
    _resetFields();
    ESC::attach(pin, CHANNEL_NOT_ATTACHED, MIN_SPEED, MAX_SPEED, minPulseWidth, maxPulseWidth);
}

bool ESC::attach(int pin, int channel, 
                   int minSpeed, int maxSpeed, 
                   int minPulseWidth, int maxPulseWidth) 
{
    if(channel == CHANNEL_NOT_ATTACHED) {
        if(channel_next_free == CHANNEL_MAX_NUM) {
            return false;
        }
        _channel = channel_next_free;
        channel_next_free++;
    } else {
        _channel = channel;
    }

    _pin = pin;
    _minSpeed = minSpeed;
    _maxSpeed = maxSpeed;
    _minPulseWidth = minPulseWidth;
    _maxPulseWidth = maxPulseWidth;

    ledcSetup(_channel, 50, 16); // channel X, 50 Hz, 16-bit depth
    ledcAttachPin(_pin, _channel);
    return true;
}

void ESC::write(int degrees) {
    degrees = constrain(degrees, _minSpeed, _maxSpeed);
    writeMicroseconds(_speedToUs(degrees));
}

void ESC::writeMicroseconds(int pulseUs) {
    if (!attached()) {
        return;
    }
    pulseUs = constrain(pulseUs, _minPulseWidth, _maxPulseWidth);
    _pulseWidthDuty = _usToDuty(pulseUs);
    ledcWrite(_channel, _pulseWidthDuty);
}

bool ESC::attached() const { return _pin != PIN_NOT_ATTACHED; }

void ESC::_resetFields(void) {
    _pin = PIN_NOT_ATTACHED;
    _pulseWidthDuty = 0;
    _channel = CHANNEL_NOT_ATTACHED;
    _minSpeed = MIN_SPEED;
    _maxSpeed = MAX_SPEED;
    _minPulseWidth = MIN_PULSE_WIDTH;
    _maxPulseWidth = MAX_PULSE_WIDTH;
}
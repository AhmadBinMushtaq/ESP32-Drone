#ifndef ESC_H
#define ESC_H

#pragma once
#include "Arduino.h"

class ESC
{
    // Default min/max pulse widths (in microseconds) and speeds (in
    // percentages).  Values chosen for Arduino compatibility.  These values
    // are part of the public API; DO NOT CHANGE THEM.
    static const int MIN_SPEED = 0;
    static const int MAX_SPEED = 100;

    static const int MIN_PULSE_WIDTH = 1000;        // the shortest pulse sent to an esc
    static const int MAX_PULSE_WIDTH = 2000;        // the longest pulse sent to an esc
    static const int MAX_COMPARE = ((1 << 16) - 1); // 65535

    static const int TAU_MSEC = 20;
    static const int TAU_USEC = (TAU_MSEC * 1000);

    static const int CHANNEL_MAX_NUM = 16;

public:
    static const int CHANNEL_NOT_ATTACHED = -1;

    // Pin number of unattached pins
    static const int PIN_NOT_ATTACHED = -1;

    /**
     * @brief Construct a new ESC instance.
     *
     * The new instance will not be attached to any pin.
     */

    ESC(int, int, int);

    /**
    * @brief Associate this instance with a esc whose input is
    *        connected to pin.

    * @param pin Pin connected to the esc pulse wave input. This
    *            pin must be capable of PWM output (all ESP32 pins).
    *
    * @param channel Channel which is set to ESP32 Arduino function ledcSetup().
    *                Channel must be number between 0 - 15.
    *                It is possible to use automatic channel setup with constant
    *                ESC::CHANNEL_NOT_ATTACHED.
    *
    * @param minSpeed Target speed (percentage) associated with
    *                 minPulseWidth.  Defaults to
    *                 min_speed = 0.
    *
    * @param maxSpeed Target speed (percentage) associated with
    *                 maxPulseWidth.  Defaults to
    *                 MAX_SPEED = 100.
    *
    * @param minPulseWidth Minimum pulse width to write to pin, in
    *                      microseconds.  This will be associated
    *                      with a minSpeed.  Defaults to
    *                      MIN_PULSE_WIDTH = 1000.
    *
    * @param maxPulseWidth Maximum pulse width to write to pin, in
    *                      microseconds.  This will be associated
    *                      with a maxSpeed. Defaults to
    *                      MAX_PULSE_WIDTH = 2000.
    *
    * @sideeffect May set pinMode(pin, PWM).
    *
    * @return true if successful, false when pin doesn't support PWM.
    */
    bool attach(int pin, int channel = CHANNEL_NOT_ATTACHED,
                int minSpeed = MIN_SPEED, int maxSpeed = MAX_SPEED,
                int minPulseWidth = MIN_PULSE_WIDTH, int maxPulseWidth = MAX_PULSE_WIDTH);

    /**
     * @brief Set the ESC target Speed.
     *
     * @param speed Target speed (percentage).  If the target speed is
     *              outside the range specified at attach() time, it
     *              will be clamped to lie in that range.
     *
     * @see ESC::attach()
     */
    void write(int speed);

    /**
     * @brief Set the pulse width, in microseconds.
     *
     * @param pulseWidth Pulse width to send to the ESC, in
     *                   microseconds. If outside of the range
     *                   specified at attach() time, it is clamped to
     *                   lie in that range.
     *
     * @see ESC::attach()
     */
    void writeMicroseconds(int pulseUs);

    /**
     * @brief Check if this instance is attached to an ESC.
     * @return true if this instance is attached to an ESC, false otherwise.
     * @see ESC::attachedPin()
     */
    bool attached() const;

private:
    void _resetFields(void);

    int _usToDuty(int us) { return map(us, 0, TAU_USEC, 0, MAX_COMPARE); }
    int _dutyToUs(int duty) { return map(duty, 0, MAX_COMPARE, 0, TAU_USEC); }
    int _usToSpeed(int us) { return map(us, _minPulseWidth, _maxPulseWidth, _minSpeed, _maxSpeed); }
    int _speedToUs(int angle) { return map(angle, _minSpeed, _maxSpeed, _minPulseWidth, _maxPulseWidth); }

    static int channel_next_free;

    int _pin;
    int _pulseWidthDuty;
    int _channel;
    int _min, _max;
    int _minPulseWidth, _maxPulseWidth;
    int _minSpeed, _maxSpeed;
};

#endif
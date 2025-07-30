// rb_pwm.h
#ifndef RB_PWM_H
#define RB_PWM_H

// Channel 0: Servo
// Channel 1: LED

int rb_pwm_export(int channel);
int rb_pwm_unexport(int channel);
int rb_pwm_enable(int channel);
int rb_pwm_disable(int channel);
int rb_pwm_set_period_ns(int channel, int period_ns);
int rb_pwm_set_frequency(int channel, int frequency_hz);
int rb_pwm_set_duty_percent(int channel, float percent);
int rb_pwm_set_duty_ns(int channel, int duty_ns); // Set duty cycle in ns directly using period

#endif // RB_PWM_H


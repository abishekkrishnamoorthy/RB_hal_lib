// rb_pwm.c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <errno.h>
#include "rb_pwm.h"

#define PWM_CHIP     "/sys/class/pwm/pwmchip0"
#define PWM_PATH(ch) (ch == 0 ? PWM_CHIP "/pwm0" : PWM_CHIP "/pwm1")

static int write_to_file(const char *path, const char *value) {
    int fd = open(path, O_WRONLY);
    if (fd < 0) return -1;
    write(fd, value, strlen(value));
    close(fd);
    return 0;
}

int rb_pwm_export(int channel) {
    char buf[2];
    snprintf(buf, sizeof(buf), "%d", channel);
    return write_to_file(PWM_CHIP "/export", buf);
}

int rb_pwm_unexport(int channel) {
    char buf[2];
    snprintf(buf, sizeof(buf), "%d", channel);
    return write_to_file(PWM_CHIP "/unexport", buf);
}

int rb_pwm_enable(int channel) {
    char path[64];
    snprintf(path, sizeof(path), "%s/enable", PWM_PATH(channel));
    return write_to_file(path, "1");
}

int rb_pwm_disable(int channel) {
    char path[64];
    snprintf(path, sizeof(path), "%s/enable", PWM_PATH(channel));
    return write_to_file(path, "0");
}

int rb_pwm_set_period_ns(int channel, int period_ns) {
    char path[64], buf[32];
    snprintf(path, sizeof(path), "%s/period", PWM_PATH(channel));
    snprintf(buf, sizeof(buf), "%d", period_ns);
    return write_to_file(path, buf);
}

int rb_pwm_set_frequency(int channel, int frequency_hz) {
    if (frequency_hz <= 0) return -1;
    int period_ns = 1000000000 / frequency_hz;
    return rb_pwm_set_period_ns(channel, period_ns);
}

int rb_pwm_set_duty_percent(int channel, float percent) {
    if (percent < 0.0 || percent > 100.0) return -1;
    char path[64], buf[32];
    char period_path[64];
    snprintf(period_path, sizeof(period_path), "%s/period", PWM_PATH(channel));

    FILE *fp = fopen(period_path, "r");
    if (!fp) return -1;

    int period_ns = 0;
    fscanf(fp, "%d", &period_ns);
    fclose(fp);

    int duty_ns = (int)(period_ns * (percent / 100.0));
    snprintf(path, sizeof(path), "%s/duty_cycle", PWM_PATH(channel));
    snprintf(buf, sizeof(buf), "%d", duty_ns);
    return write_to_file(path, buf);
}

int rb_pwm_set_duty_ns(int channel, int duty_ns) {
    char path[64], buf[32];
    snprintf(path, sizeof(path), "%s/duty_cycle", PWM_PATH(channel));
    snprintf(buf, sizeof(buf), "%d", duty_ns);
    return write_to_file(path, buf);
}


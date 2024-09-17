#ifndef TIME_MANAGEMENT_H
#define TIME_MANAGEMENT_H

extern unsigned char seconds;
extern unsigned char minutes;
extern unsigned char hours;
extern unsigned char mode;

void check_mode_toggle(void);
void check_time_adjustment(void);

#endif // TIME_MANAGEMENT_H

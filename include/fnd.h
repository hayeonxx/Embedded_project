#ifndef __FND_H__
#define __FND_H__

#include "main.h"

void Fnd_Initialize(void);
void Fnd_Self_Test(void);
void Fnd_Display(int8_t num, int8_t position, uint32_t time_ms);
void Fnd_Display_dp(int8_t num, int8_t position, uint32_t time_ms);
void Fnd_temperature_show(int8_t num, int8_t position, uint32_t time_ms, int dot_flag);
void Fnd_Zero(void);
void fnd_second(int T);
void fnd_look(int count);
void fnd_minute(int T);
// void fnd_display(void);

#endif

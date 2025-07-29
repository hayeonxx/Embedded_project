#ifndef BUZZER_H
#define BUZZER_H

void Buzzer_Init(void);
void Buzzer_On(void);
void Buzzer_Off(void);
void Buzzer_PlayCompleteSound(void);
void Buzzer_SetFrequency(uint32_t frequency);

#endif // BUZZER_H

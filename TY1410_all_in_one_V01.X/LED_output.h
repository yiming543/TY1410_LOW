/*
 * File:   LED_output.h
 * Author: T00904
 *
 * Created on February 9, 2026, 1:03 PM
 */

#ifndef LED_OUTPUT_H
#define LED_OUTPUT_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mcc_generated_files/pin_manager.h"
#include "mcc_generated_files/epwm1.h"
#include "mcc_generated_files/pwm4.h"
#include <stdbool.h>
#include <stdint.h> //uint8_t
#include <xc.h>

void DRL_ON_HiPe(void);
void POS_ON_HiPe(void);
void DRL_POS_OFF_HiPe(void);
void LOBEAM_ON(void);
void LOBEAM_OFF(void);
void P2_POS2_ON(void);
void P2_POS2_OFF(void);
void HIBEAM_ON(void);
void HIBEAM_OFF(void);
bool Is_HiPe(void);

// duty 100%
#define PWM1_DUTY_0_PERCENT (0)
#define PWM1_DUTY_40_PERCENT (320)
#define PWM1_DUTY_60_PERCENT (480)
#define PWM1_DUTY_80_PERCENT (640)
#define PWM1_DUTY_100_PERCENT (804)
#define POS_DUTY (80) //10%
#define DRL_DUTY (804) //100%
#define LOBEAM_DUTY (804) //100%


// #define Is_HiPe() (fLamp_Conf == LAMP_HiPe)
#define LAMP_LoPe 0 // 低配
#define LAMP_HiPe 1 // 高配

// #define Is_R_Side() (fLamp_RL_Side==LAMP_R_SIDE)
// #define LAMP_R_SIDE 0 // 右邊
// #define LAMP_L_SIDE 1 // 左邊

#ifdef __cplusplus
}
#endif

#endif /* LED_OUTPUT_H */

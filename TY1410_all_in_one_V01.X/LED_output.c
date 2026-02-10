/*
 * File:   LED_output.c
 * Author: T00904
 *
 * Created on February 9, 2026, 1:07 PM
 */

#include "LED_output.h"
extern bool fLamp_Conf;

void DRL_ON_HiPe(void) {
    PWM4_LoadDutyValue(DRL_DUTY); //DRL POS OFF
}

void POS_ON_HiPe(void) {
    PWM4_LoadDutyValue(POS_DUTY); //DRL POS OFF
}

void DRL_POS_OFF_HiPe(void) {
    PWM4_LoadDutyValue(0); //DRL POS OFF
}

void LOBEAM_ON(void) {
    EPWM1_LoadDutyValue(LOBEAM_DUTY); //LOWBEAM/DRL OFF
}

void LOBEAM_OFF(void) {
    EPWM1_LoadDutyValue(0); //LOWBEAM OFF
}

void P2_POS2_ON(void) { P2_enable_LAT = 1; }
void P2_POS2_OFF(void) { P2_enable_LAT = 0; }

void HIBEAM_ON(void) { HiBeam_enable_LAT = 0; }
void HIBEAM_OFF(void) { HiBeam_enable_LAT = 1; }

bool Is_HiPe(void) {
  if (fLamp_Conf == LAMP_HiPe)
    return true;
  else
    return false;
}

/*
 * File:   tundra.c
 * Author: T00904
 * MCU:PIC16F1936
 * toyoya tundra PWM receiver
 * Created on January 14, 2026, 9:37 AM
 */

#include "tundra.h"
#include "LED_output.h"

// Function declaration
void ECCP3_CallBack(uint16_t capturedValue);
void TMR0_EvenHandler(void);
void Exception_handling(void);
void analysis_of_data(void);
void receiver_frame_data(void);
void check_unlock_even(void);
void check_lamp_off_even(void);
void to_do_unlock(void);
void to_do_lamp_off(void);
void to_do_signal_timeout(void);
void LED_control(void);
void LED_control_HiPe(void);
void LED_control_LoPe(void);


// Declaring variables(RAM)
sflag_D2 D2;
sflag_D3 D3;
sflag_CS_index csFlag;
uint8_t rx_buf[11];
uint8_t rx_data = 0;
volatile bool fReceiver_Byte = 0;
volatile bool fFrame_OK = 0;
volatile uint8_t Communication_timer = 0; // 單位:10ms
uint8_t positive_pulse_width_us_max = 0;
uint8_t positive_pulse_width_us_min = 255;
eLAMP_EVEN eLamp_even = eEVEN_SIGNAL_NOTHING;
bool fLamp_Conf = 0;
bool fLamp_RL_Side = 0;

// ROM
static const uint8_t CS[64] = {
    // 行車,晝行,近燈,遠燈,左方,右方
    0x4C, // 000000 關
    0x9F, // 000001 右方
    0xED, // 000010 左方
    0x3E, // 000011 右方+左方(警示)

    0x66, // 000100 遠燈
    0xB5, // 000101 遠燈+右方
    0xC7, // 000110 遠燈+左方
    0x14, // 000111 遠燈+右方+左方(警示)

    0x59, // 001000 近燈
    0x8A, // 001001 近燈+右方
    0xF8, // 001010 近燈+左方
    0x2B, // 001011 近燈+右方+左方(警示)

    0x73, // 001100 遠燈+近燈(超車)
    0xA0, // 001101 遠燈+近燈(超車)+右方
    0xD2, // 001110 遠燈+近燈(超車)+左方
    0x01, // 001111 遠燈+近燈(超車)+右方+左方(警示)

    0x8E, // 010000 晝行
    0x5D, // 010001 晝行+右方
    0x2F, // 010010 晝行+左方
    0xFC, // 010011 晝行+右方+左方(警示)

    0xA4, // 010100 晝行+遠燈
    0x77, // 010101 晝行+遠燈+右方
    0x05, // 010110 晝行+遠燈+左方
    0xD6, // 010111 晝行+遠燈+右方+左方(警示)

    0x9B, // 011000 晝行+近燈
    0x48, // 011001 晝行+近燈+右方
    0x3A, // 011010 晝行+近燈+左方
    0xE9, // 011011 晝行+近燈+右方+左方(警示)

    0xB1, // 011100 畫行+遠燈+近燈(超車)
    0x62, // 011101 畫行+遠燈+近燈(超車)+右方
    0x10, // 011110 畫行+遠燈+近燈(超車)+左方
    0xC3, // 011111 晝行+遠燈+近燈(超車)+右方+左方(警示)

    0x2D, // 100000 行車
    0xFE, // 100001 行車+右方
    0x8C, // 100010 行車+左方
    0x5F, // 100011 行車+右方+左方(警示)

    0x07, // 100100 行車+遠燈
    0xD4, // 100101 行車+遠燈+右方
    0xA6, // 100110 行車+遠燈+左方
    0x75, // 100111 行車+遠燈+右方+左方(警示)

    0x38, // 101000 行車+近燈
    0xEB, // 101001 行車+近燈+右方
    0x99, // 101010 行車+近燈+左方
    0x4A, // 101011 行車+近燈+右方+左方(警示)

    0x12, // 101100 行車+遠燈+近燈(超車)
    0xC1, // 101101 行車+遠燈+近燈(超車)+右方
    0xB3, // 101110 行車+遠燈+近燈(超車)+左方
    0x60, // 101111 行車+遠燈+近燈(超車)+右方+左方(警示)

    0xEF, // 110000 行車+晝行
    0x3C, // 110001 行車+晝行+右方
    0x4E, // 110010 行車+晝行+左方
    0x9D, // 110011 行車+晝行+右方+左方(警示)

    0xC5, // 110100 行車+晝行+遠燈
    0x16, // 110101 行車+晝行+遠燈+右方
    0x64, // 110110 行車+晝行+遠燈+左方
    0xB7, // 110111 行車+晝行+遠燈+右方+左方(警示)

    0xFA, // 111000 行車+晝行+近燈
    0x29, // 111001 行車+晝行+近燈+右方
    0x5B, // 111010 行車+晝行+近燈+左方
    0x88, // 111011 行車+晝行+近燈+右方+左方(警示)

    0xD0, // 111100 行車+晝行+遠燈+近燈
    0x03, // 111101 行車+晝行+遠燈+近燈+右方
    0x71, // 111110 行車+晝行+遠燈+近燈+左方
    0xA2, // 111111 行車+晝行+遠燈+近燈(超車)+右方+左方(警示)
};

// 消除未呼叫警告 假裝有使用這些函數
void Clear_No_Call_Warning(void) {
  uint8_t i = 0;
  if (i == 1) {
    TMR0_Reload();
    TMR0_ReadTimer();
    TMR0_WriteTimer(0);
  } else if (i == 2) {
    TMR1_StartTimer();
    TMR1_StopTimer();
    TMR1_ReadTimer();
    TMR1_WriteTimer(0);
    TMR1_Reload();
    TMR1_StartSinglePulseAcquisition();
    TMR1_CheckGateValueStatus();
    TMR1_HasOverflowOccured();
  } else if (i == 3) {
    TMR2_HasOverflowOccured();
    TMR2_LoadPeriodRegister(0);
    TMR2_WriteTimer(0);
    TMR2_ReadTimer();
    TMR2_StopTimer();
    TMR2_StartTimer();
  } else if (i == 4) {
    PIN_MANAGER_IOC();
  } else if (i == 5) {
  } else if (i == 6) {
  }
}

// 解析資料
void analysis_of_data(void) {
  D2.Byte = rx_buf[2];
  D3.Byte = rx_buf[3];
  sflag_CS_index temp_index;
  temp_index.Byte = 0;
  uint8_t crc8 = 0;

  if (!fFrame_OK) {
    return;
  }
  fFrame_OK = 0;

  // 行車
  if (D2.POS) {
    temp_index.POS = 1;
  }

  // 晝行
  if (D2.DRL) {
    temp_index.DRL = 1;
  }

  // 近燈
  if (D2.LoBeam) {
    temp_index.LoBeam = 1;
  }

  // 遠燈
  if (D2.HiBeam) {
    temp_index.HiBeam = 1;
  }

  // 左方向
  if (D3.turnLight_L) {
    temp_index.turnLight_L = 1;
  }

  // 右方向
  if (D3.turnLight_R) {
    temp_index.turnLight_R = 1;
  }

  crc8 = CS[temp_index.Byte];
  // CRC檢查
  if (rx_buf[10] != crc8) {
//    rx_buf[10] = 0;
    eLamp_even = eEVEN_SIGNAL_NOTHING;
    return;
  }

  // PID檢查
  if (rx_buf[0] != LIGHT_PID) {
    rx_buf[0] = 0;
    eLamp_even = eEVEN_SIGNAL_NOTHING;
    return;
  }

  // 資料長度檢查
  if (rx_buf[1] != DATA_LENGTH) {
    rx_buf[1] = 0;
    eLamp_even = eEVEN_SIGNAL_NOTHING;
    return;
  }

  // 訊框頭正確
  csFlag.Byte = temp_index.Byte;
  Communication_timer = 0; // 重置通訊計時器
  eLamp_even = eEVEN_SIGNAL_OK;
  // 清除資料
  // for (uint8_t i = 0; i < BUF_LENGTH; i++) {
  //   rx_buf[i] = 0;
  // }
}

// 檢查unlck事件
void check_unlock_even(void) {
  if ((rx_buf[2] == 6) && (rx_buf[10] == 0xD5)) {
    eLamp_even = eEVEN_SIGNAL_UNLOCK;
    Communication_timer = 0;
  }
}

// 檢查lamp off事件
void check_lamp_off_even(void) {
  if ((rx_buf[2] == 2) && (rx_buf[10] == 0xB4)) {

    eLamp_even = eEVEN_SIGNAL_CLEAR;
    Communication_timer = 0;
  }
}

// 執行 信號超時
void to_do_signal_timeout(void) {
  // 亮行車(P2)和近燈
  //  POS_EN = 1;
  P2_POS2_ON();
  HIBEAM_OFF();
  LOBEAM_ON();
  POS_ON_HiPe();
  eLamp_even = eEVEN_SIGNAL_NOTHING;
}

// 執行 unlock
void to_do_unlock(void) {
  // P2 ON,HIBEAM/LOBEAM OFF
  P2_POS2_ON();
  HIBEAM_OFF();
  LOBEAM_OFF();
  POS_ON_HiPe();
  eLamp_even = eEVEN_SIGNAL_NOTHING;
}

// 執行 lamp off
void to_do_lamp_off(void) {
  // P2 OFF
  P2_POS2_OFF();
  LOBEAM_OFF();
  HIBEAM_OFF();
  DRL_POS_OFF_HiPe();
  eLamp_even = eEVEN_SIGNAL_NOTHING;
}

// LED控制
void LED_control(void) {
  if (Is_HiPe()) {
    LED_control_HiPe();
  } else {
    LED_control_LoPe();
  }
}

void LED_control_HiPe(void) {
  if (csFlag.POS)
    P2_POS2_ON();
  else
    P2_POS2_OFF();

  if (csFlag.LoBeam == 0 && csFlag.HiBeam == 0 && csFlag.DRL == 0 && csFlag.POS == 0) { // 0
    LOBEAM_OFF();
    HIBEAM_OFF();
    DRL_POS_OFF_HiPe();
  } else if (csFlag.HiBeam == 0 && csFlag.LoBeam == 0 && csFlag.DRL == 0 && csFlag.POS == 1) { // 1
    LOBEAM_OFF();
    HIBEAM_OFF();
    POS_ON_HiPe();
  } else if (csFlag.HiBeam == 0 && csFlag.LoBeam == 0 && csFlag.DRL == 1 && csFlag.POS == 0) { // 2
    LOBEAM_OFF();
    HIBEAM_OFF();
    DRL_ON_HiPe();
  } else if (csFlag.HiBeam == 0 && csFlag.LoBeam == 0 && csFlag.DRL == 1 && csFlag.POS == 1) { // 3
    LOBEAM_OFF();
    HIBEAM_OFF();
    DRL_ON_HiPe();
  } else if (csFlag.HiBeam == 0 && csFlag.LoBeam == 1 && csFlag.DRL == 0 && csFlag.POS == 0) { // 4
    LOBEAM_ON();
    HIBEAM_OFF();
    DRL_POS_OFF_HiPe();
  } else if (csFlag.HiBeam == 0 && csFlag.LoBeam == 1 && csFlag.DRL == 0 && csFlag.POS == 1) { // 5
    LOBEAM_ON();
    HIBEAM_OFF();
    POS_ON_HiPe();
  } else if (csFlag.HiBeam == 0 && csFlag.LoBeam == 1 && csFlag.DRL == 1 && csFlag.POS == 0) { // 6
    LOBEAM_ON();
    HIBEAM_OFF();
    POS_ON_HiPe(); //有Lobeam DRL變POS
  } else if (csFlag.HiBeam == 0 && csFlag.LoBeam == 1 && csFlag.DRL == 1 && csFlag.POS == 1) { // 7
    LOBEAM_ON();
    HIBEAM_OFF();
    POS_ON_HiPe(); //有Lobeam DRL變POS
  } else if (csFlag.HiBeam == 1 && csFlag.LoBeam == 0 && csFlag.DRL == 0 && csFlag.POS == 0) { // 8
    LOBEAM_OFF();
    HIBEAM_OFF();
    DRL_POS_OFF_HiPe();
  } else if (csFlag.HiBeam == 1 && csFlag.LoBeam == 0 && csFlag.DRL == 0 && csFlag.POS == 1) { // 9
    LOBEAM_OFF();
    HIBEAM_OFF();
    POS_ON_HiPe();
  } else if (csFlag.HiBeam == 1 && csFlag.LoBeam == 0 && csFlag.DRL == 1 && csFlag.POS == 0) { // 10
    LOBEAM_OFF();
    HIBEAM_OFF();
    DRL_ON_HiPe();
  } else if (csFlag.HiBeam == 1 && csFlag.LoBeam == 0 && csFlag.DRL == 1 && csFlag.POS == 1) { // 11
    LOBEAM_OFF();
    HIBEAM_OFF();
    DRL_ON_HiPe();
  } else if (csFlag.HiBeam == 1 && csFlag.LoBeam == 1 && csFlag.DRL == 0 && csFlag.POS == 0) { // 12
    LOBEAM_ON();
    HIBEAM_ON();
    DRL_POS_OFF_HiPe();
  } else if (csFlag.HiBeam == 1 && csFlag.LoBeam == 1 && csFlag.DRL == 0 && csFlag.POS == 1) { // 13
    LOBEAM_ON();
    HIBEAM_ON();
    POS_ON_HiPe();
  } else if (csFlag.HiBeam == 1 && csFlag.LoBeam == 1 && csFlag.DRL == 1 && csFlag.POS == 0) { // 14
    LOBEAM_ON();
    HIBEAM_ON();
    POS_ON_HiPe(); //有Lobeam DRL變POS
  } else if (csFlag.HiBeam == 1 && csFlag.LoBeam == 1 && csFlag.DRL == 1 && csFlag.POS == 1) { // 15
    LOBEAM_ON();
    HIBEAM_ON();
    POS_ON_HiPe(); //有Lobeam DRL變POS
  } 
}

void LED_control_LoPe(void) {
  // 行車
  if (csFlag.POS) {
    P2_POS2_ON();
  } else {
    P2_POS2_OFF();
  }

  if (csFlag.LoBeam == 0 && csFlag.HiBeam == 0 && csFlag.DRL == 0) { // 0
    // OFF
    HIBEAM_OFF();                             // 遠燈 OFF
    EPWM1_LoadDutyValue(PWM1_DUTY_0_PERCENT); // PWM 0%
  } else if (csFlag.LoBeam == 0 && csFlag.HiBeam == 0 && csFlag.DRL == 1) { // 1
    //  DRL
    if (CCPR1L == 0) { // PWM原本為0%則可以一次到位
      HIBEAM_OFF();    // 遠燈 OFF
      EPWM1_LoadDutyValue(PWM1_DUTY_40_PERCENT);  // PWM 40%
    } else if (CCPR1L != 80) {                    // PWM 40%
      HIBEAM_OFF();                               // 遠燈 OFF
      EPWM1_LoadDutyValue(PWM1_DUTY_100_PERCENT); // PWM 100%
      __delay_ms(10);
      EPWM1_LoadDutyValue(PWM1_DUTY_80_PERCENT); // PWM 80%
      __delay_ms(10);
      EPWM1_LoadDutyValue(PWM1_DUTY_60_PERCENT); // PWM 60%
      __delay_ms(10);
      EPWM1_LoadDutyValue(PWM1_DUTY_40_PERCENT); // PWM 40%
    }
  } else if (csFlag.HiBeam == 0 && csFlag.LoBeam == 1 && csFlag.DRL == 0) { // 2
    // LOBEAM
    HIBEAM_OFF();                               // 遠燈 OFF
    EPWM1_LoadDutyValue(PWM1_DUTY_100_PERCENT); // PWM 100%
  } else if (csFlag.HiBeam == 0 && csFlag.LoBeam == 1 && csFlag.DRL == 1) { // 3
    // LOBEAM
    HIBEAM_OFF();                               // 遠燈 OFF
    EPWM1_LoadDutyValue(PWM1_DUTY_100_PERCENT); // PWM 0%
  } else if (csFlag.HiBeam == 1 && csFlag.LoBeam == 0 && csFlag.DRL == 0) { // 4
    // HIBEAM
    HIBEAM_OFF();                             // 遠燈 OFF
    EPWM1_LoadDutyValue(PWM1_DUTY_0_PERCENT); // PWM 0%
  } else if (csFlag.HiBeam == 1 && csFlag.LoBeam == 0 && csFlag.DRL == 1) { // 5
    // HIBEAM
    if (CCPR1L != 80) {                           // PWM 40%
      HIBEAM_OFF();                               // 遠燈 OFF
      EPWM1_LoadDutyValue(PWM1_DUTY_100_PERCENT); // PWM 100%
      __delay_ms(10);
      EPWM1_LoadDutyValue(PWM1_DUTY_80_PERCENT); // PWM 80%
      __delay_ms(10);
      EPWM1_LoadDutyValue(PWM1_DUTY_60_PERCENT); // PWM 60%
      __delay_ms(10);
      EPWM1_LoadDutyValue(PWM1_DUTY_40_PERCENT); // PWM 40%
    }
  } else if (csFlag.HiBeam == 1 && csFlag.LoBeam == 1 && csFlag.DRL == 0) { // 6
    // HIBEAM
    HIBEAM_ON();                                // 遠燈 ON
    EPWM1_LoadDutyValue(PWM1_DUTY_100_PERCENT); // PWM 100%
  } else if (csFlag.HiBeam == 1 && csFlag.LoBeam == 1 && csFlag.DRL == 1) { // 7
    // HIBEAM
    HIBEAM_ON();                                // 晝行+超車
    EPWM1_LoadDutyValue(PWM1_DUTY_100_PERCENT); // PWM 100%
  }
}

// 接收資料 11 Byte
void receiver_frame_data(void) {
  static eRECEIVE_STATE eReceiver_step = eRECEIVE_PID;

  if (!fReceiver_Byte) {
    return;
  }
  fReceiver_Byte = 0;

  switch (eReceiver_step) {
  case eRECEIVE_PID:
    if (rx_data == LIGHT_PID) {
      eReceiver_step++;
      rx_buf[0] = rx_data;
    }
    break;
  case eRECEIVE_Byte1:
    if (rx_data == DATA_LENGTH) {
      rx_buf[1] = rx_data;
      eReceiver_step++;
    } else {
      eReceiver_step = eRECEIVE_PID;
    }
    break;
  case eRECEIVE_Byte2:
    rx_buf[2] = rx_data;
    eReceiver_step++;
    break;
  case eRECEIVE_Byte3:
    rx_buf[3] = rx_data;
    eReceiver_step++;
    break;
  case eRECEIVE_Byte4:
    rx_buf[4] = rx_data;
    eReceiver_step++;
    break;
  case eRECEIVE_Byte5:
    rx_buf[5] = rx_data;
    eReceiver_step++;
    break;
  case eRECEIVE_Byte6:
    rx_buf[6] = rx_data;
    eReceiver_step++;
    break;
  case eRECEIVE_Byte7:
    rx_buf[7] = rx_data;
    eReceiver_step++;
    break;
  case eRECEIVE_Byte8:
    rx_buf[8] = rx_data;
    eReceiver_step++;
    break;
  case eRECEIVE_Byte9:
    rx_buf[9] = rx_data;
    eReceiver_step++;
    break;
  case eRECEIVE_CS:
    rx_buf[10] = rx_data;
    fFrame_OK = 1;
    eReceiver_step = eRECEIVE_PID;
    break;
  default:
    eReceiver_step = eRECEIVE_PID;
    break;
  }
}

// 接收資料 8 bit
void ECCP3_CallBack(uint16_t capturedValue) {
  static uint16_t negative_pulse_width = 0;
  static uint16_t positive_pulse_width = 0;
  static uint8_t positive_pulse_width_us = 0;
  static uint8_t negative_pulse_width_us = 0;
  static uint8_t diff_us = 0;
  static uint16_t falling_edge_time = 0;
  static uint16_t rising_edge_time = 0;
  static uint8_t bit_cnt = 0;
  static bool fRise_edge = 0;
  static bool fStart_bit = 0;

  if (CCP3CON == FALLING_EDGE_TRIG) {
    // 計算正脈波寬度
    falling_edge_time = capturedValue; // 125ns
    CCP3CON = RISING_EDGE_TRIG;        // set to rising edge trigger
    if (fRise_edge) {
      fRise_edge = 0;

      if (falling_edge_time >= rising_edge_time) {
        positive_pulse_width = falling_edge_time - rising_edge_time;
      } else {
        // 二補數
        positive_pulse_width = ~rising_edge_time + 1 + falling_edge_time;
      }
      // 125ns*8 ==> 1us
      negative_pulse_width_us = (positive_pulse_width >> 3) & 0xff;
      positive_pulse_width_us = (negative_pulse_width >> 3) & 0xff;

      // PWM 變成 UART 19200 baud
      if (positive_pulse_width_us > UART_LEVEL) {
        UART_TX = 0;
      } else {
        UART_TX = 1;
      }

      if (positive_pulse_width_us > negative_pulse_width_us)
        diff_us = positive_pulse_width_us - negative_pulse_width_us;
      else
        diff_us = negative_pulse_width_us - positive_pulse_width_us;

      // 測試正脈波寬度範圍
      // if (positive_pulse_width_us > positive_pulse_width_us_max) {
      //   positive_pulse_width_us_max = positive_pulse_width_us;
      // }
      // if (positive_pulse_width_us < positive_pulse_width_us_min) {
      //   positive_pulse_width_us_min = positive_pulse_width_us;
      // }

      // UART receiver
      if (!fStart_bit) {
        // uart start bit
        if (diff_us < LOGIC_LEVEL) {
          // logical '0'
          fStart_bit = 1;
          bit_cnt = 0;
        }
      } else {
        // uart data
        if (diff_us < LOGIC_LEVEL) {
          // logical '0'
          rx_data &= ~(1 << bit_cnt);
        } else {
          // logical '1'
          rx_data |= (1 << bit_cnt);
        }

        bit_cnt++;
        // uart stop bit
        if (bit_cnt > BIT_7) {
          fStart_bit = 0;
          fReceiver_Byte = 1;
        }
      }
    }

  } // rising edge tringgered
  else if (CCP3CON == RISING_EDGE_TRIG) {
    // 計算負脈波寬度
    rising_edge_time = capturedValue;
    CCP3CON = FALLING_EDGE_TRIG; // set to falling edge trigger set to falling
    // edge trigger

    // 計算低電位脈衝寬度
    if (rising_edge_time >= falling_edge_time) {
      negative_pulse_width = rising_edge_time - falling_edge_time;
    } else {
      // 二補數
      negative_pulse_width = ~falling_edge_time + 1 + rising_edge_time;
    }
    fRise_edge = 1;
  }
}

void sofaware_initialize(void) {
  EPWM1_LoadDutyValue(0);
  PWM4_LoadDutyValue(0);
  HIBEAM_OFF();
  fLamp_Conf = Lamp_LOW_EN_PORT;
  // fLamp_RL_Side = Lamp_R_EN_PORT;
  Clear_No_Call_Warning();
}

// TMR0 ISR
void TMR0_10MS_Even(void) {
  Communication_timer++;
  if (Communication_timer >= 200) { // 2000ms
    eLamp_even = eEVEN_SIGNAL_TIMEOUT;
    Communication_timer = 0;
  }
}

// tundra main
void tundra_main(void) {
  receiver_frame_data();
  analysis_of_data();
  check_unlock_even();
  check_lamp_off_even();

  switch (eLamp_even) {
  case eEVEN_SIGNAL_OK:
    LED_control();
    break;
  case eEVEN_SIGNAL_TIMEOUT:
    to_do_signal_timeout();
    break;
  case eEVEN_SIGNAL_UNLOCK:
    to_do_unlock();
    break;
  case eEVEN_SIGNAL_CLEAR:
    to_do_lamp_off();
    break;
  case eEVEN_SIGNAL_NOTHING:
    NOP();
    break;
  default:
    NOP();
    break;
  }
}

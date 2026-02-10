/*
 * File:   tundra.h
 * Author: T00904
 *
 * Created on January 14, 2026, 9:36 AM
 */

#ifndef TUNDRA_H
#define TUNDRA_H

#ifdef __cplusplus
extern "C" {
#endif

#include "mcc_generated_files/mcc.h"
#include <stdint.h> //uint8_t
#include <xc.h>

// 供外部呼叫函數
extern void tundra_main(void);
// extern void Clear_No_Call_Warning(void);
extern void ECCP3_CallBack(uint16_t capturedValue);
extern void TMR0_10MS_Even(void);
extern void sofaware_initialize(void);

extern bool fLamp_Conf;
// Declaration Definition
#define UART_TX UR_TX_LAT

// Define structure
typedef union {
  struct {
    _Bool b0 : 1;
    _Bool b1 : 1;
    _Bool POS : 1;
    _Bool DRL : 1;
    _Bool LoBeam : 1;
    _Bool HiBeam : 1;
    _Bool b6 : 1;
    _Bool b7 : 1;
  };
  uint8_t Byte;
} sflag_D2;

typedef union {
  struct {
    _Bool b0 : 1;
    _Bool b1 : 1;
    _Bool b2 : 1;
    _Bool b3 : 1;
    _Bool b4 : 1;
    _Bool turnLight_L : 1;
    _Bool turnLight_R : 1;
    _Bool b7 : 1;
  };
  uint8_t Byte;
} sflag_D3;

typedef union {
  struct {
    _Bool turnLight_R : 1;
    _Bool turnLight_L : 1;
    _Bool HiBeam : 1;
    _Bool LoBeam : 1;
    _Bool DRL : 1;
    _Bool POS : 1;
    _Bool b6 : 1;
    _Bool b7 : 1;
  };
  uint8_t Byte;
} sflag_CS_index;

typedef enum {
  eRECEIVE_PID = 0,
  eRECEIVE_Byte1,
  eRECEIVE_Byte2,
  eRECEIVE_Byte3,
  eRECEIVE_Byte4,
  eRECEIVE_Byte5,
  eRECEIVE_Byte6,
  eRECEIVE_Byte7,
  eRECEIVE_Byte8,
  eRECEIVE_Byte9,
  eRECEIVE_CS,
} eRECEIVE_STATE;

typedef enum {
  eEVEN_SIGNAL_NOTHING = 0,
  eEVEN_SIGNAL_OK,
  eEVEN_SIGNAL_TIMEOUT,
  eEVEN_SIGNAL_UNLOCK,
  eEVEN_SIGNAL_CLEAR,
} eLAMP_EVEN;

// 定義常數
const uint8_t LIGHT_PID = 0xC8;
const uint8_t DATA_LENGTH = 0x8B;
const uint8_t LOGIC_LEVEL = 16;
const uint8_t UART_LEVEL = 25; // 34-22
const uint8_t BUF_LENGTH = 11;
const uint8_t RISING_EDGE_TRIG = 5;  // 上升緣觸發
const uint8_t FALLING_EDGE_TRIG = 4; // 下降緣觸發
const uint8_t BIT_7 = 7;

#ifdef __cplusplus
}
#endif

#endif /* TUNDRA_H */

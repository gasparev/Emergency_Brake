/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: AEB_master.h
 *
 * Code generated for Simulink model 'AEB_master'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Sat Jul 30 18:30:22 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_AEB_master_h_
#define RTW_HEADER_AEB_master_h_
#include <string.h>
#ifndef AEB_master_COMMON_INCLUDES_
# define AEB_master_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* AEB_master_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_AEB_master_T RT_MODEL_AEB_master_T;

/* Block signals (auto storage) */
typedef struct {
  real_T error;                        /* '<S1>/Distance_sensor_check' */
  real_T brake_status;                 /* '<S1>/Controller_selftest' */
  real_T blue_status;                  /* '<S1>/Controller_selftest' */
  real_T brake_request;                /* '<S1>/Brake_decision' */
  real_T blue_led;                     /* '<S1>/Brake_decision' */
} B_AEB_master_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint8_T is_active_c1_AEB_master;     /* '<S1>/Distance_sensor_check' */
  uint8_T is_c1_AEB_master;            /* '<S1>/Distance_sensor_check' */
  uint8_T is_active_c2_AEB_master;     /* '<S1>/Controller_selftest' */
  uint8_T is_c2_AEB_master;            /* '<S1>/Controller_selftest' */
  uint8_T is_active_c3_AEB_master;     /* '<S1>/Brake_decision' */
  uint8_T is_c3_AEB_master;            /* '<S1>/Brake_decision' */
} DW_AEB_master_T;

/* Real-time Model Data Structure */
struct tag_RTM_AEB_master_T {
  const char_T * volatile errorStatus;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    B_AEB_master_T *blockIO;
    DW_AEB_master_T *dwork;
  } ModelData;
};

/* Model entry point functions */
extern void AEB_master_initialize(RT_MODEL_AEB_master_T *const AEB_master_M,
  real_T *AEB_master_U_distance, real_T *AEB_master_U_actual_speed, boolean_T
  *AEB_master_Y_master_brake_request, real_T *AEB_master_Y_master_status);
extern void AEB_master_step(RT_MODEL_AEB_master_T *const AEB_master_M, real_T
  AEB_master_U_distance, real_T AEB_master_U_actual_speed, boolean_T
  *AEB_master_Y_master_brake_request, real_T *AEB_master_Y_master_status);
extern void AEB_master_terminate(RT_MODEL_AEB_master_T *const AEB_master_M);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Blue_led_master' : Unused code path elimination
 * Block '<S1>/Master_status' : Unused code path elimination
 * Block '<S1>/Master_status1' : Unused code path elimination
 */

/*-
 * The generated code includes comments that allow you to trace directly
 * back to the appropriate location in the model.  The basic format
 * is <system>/block_name, where system is the system number (uniquely
 * assigned by Simulink) and block_name is the name of the block.
 *
 * Note that this particular code originates from a subsystem build,
 * and has its own system numbers different from the parent model.
 * Refer to the system hierarchy for this subsystem below, and use the
 * MATLAB hilite_system command to trace the generated code back
 * to the parent model.  For example,
 *
 * hilite_system('aebMS/AEB_master')    - opens subsystem aebMS/AEB_master
 * hilite_system('aebMS/AEB_master/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'aebMS'
 * '<S1>'   : 'aebMS/AEB_master'
 * '<S2>'   : 'aebMS/AEB_master/Brake_decision'
 * '<S3>'   : 'aebMS/AEB_master/Controller_selftest'
 * '<S4>'   : 'aebMS/AEB_master/Distance_sensor_check'
 */
#endif                                 /* RTW_HEADER_AEB_master_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */


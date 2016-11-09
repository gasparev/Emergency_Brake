/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: AEB_slave.h
 *
 * Code generated for Simulink model 'AEB_slave'.
 *
 * Model version                  : 1.2
 * Simulink Coder version         : 8.10 (R2016a) 10-Feb-2016
 * C/C++ source code generated on : Sat Jul 30 18:31:36 2016
 *
 * Target selection: ert.tlc
 * Embedded hardware selection: ARM Compatible->ARM Cortex
 * Code generation objectives: Unspecified
 * Validation result: Not run
 */

#ifndef RTW_HEADER_AEB_slave_h_
#define RTW_HEADER_AEB_slave_h_
#include <string.h>
#ifndef AEB_slave_COMMON_INCLUDES_
# define AEB_slave_COMMON_INCLUDES_
#include "rtwtypes.h"
#endif                                 /* AEB_slave_COMMON_INCLUDES_ */

/* Macros for accessing real-time model data structure */
#ifndef rtmGetErrorStatus
# define rtmGetErrorStatus(rtm)        ((rtm)->errorStatus)
#endif

#ifndef rtmSetErrorStatus
# define rtmSetErrorStatus(rtm, val)   ((rtm)->errorStatus = (val))
#endif

/* Forward declaration for rtModel */
typedef struct tag_RTM_AEB_slave_T RT_MODEL_AEB_slave_T;

/* Block signals (auto storage) */
typedef struct {
  real_T brake_request;                /* '<S1>/Brake_decision' */
} B_AEB_slave_T;

/* Block states (auto storage) for system '<Root>' */
typedef struct {
  uint8_T is_active_c4_AEB_slave;      /* '<S1>/Brake_decision' */
  uint8_T is_c4_AEB_slave;             /* '<S1>/Brake_decision' */
} DW_AEB_slave_T;

/* Real-time Model Data Structure */
struct tag_RTM_AEB_slave_T {
  const char_T * volatile errorStatus;

  /*
   * ModelData:
   * The following substructure contains information regarding
   * the data used in the model.
   */
  struct {
    B_AEB_slave_T *blockIO;
    DW_AEB_slave_T *dwork;
  } ModelData;
};

/* Model entry point functions */
extern void AEB_slave_initialize(RT_MODEL_AEB_slave_T *const AEB_slave_M, real_T
  *AEB_slave_U_distance, real_T *AEB_slave_U_actual_speed, boolean_T
  *AEB_slave_U_slave_status, boolean_T *AEB_slave_U_Masted_blu_led, boolean_T
  *AEB_slave_Y_brakerequest);
extern void AEB_slave_step(RT_MODEL_AEB_slave_T *const AEB_slave_M, real_T
  AEB_slave_U_distance, real_T AEB_slave_U_actual_speed, boolean_T
  AEB_slave_U_slave_status, boolean_T *AEB_slave_Y_brakerequest);
extern void AEB_slave_terminate(RT_MODEL_AEB_slave_T *const AEB_slave_M);

/*-
 * These blocks were eliminated from the model due to optimizations:
 *
 * Block '<S1>/Blue_led' : Unused code path elimination
 * Block '<S1>/Blue_led1' : Unused code path elimination
 * Block '<S1>/Data Type Conversion2' : Unused code path elimination
 * Block '<S1>/Logical Operator' : Unused code path elimination
 * Block '<S1>/Logical Operator1' : Unused code path elimination
 * Block '<S1>/SlaveStatus' : Unused code path elimination
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
 * hilite_system('aebMS/AEB_slave')    - opens subsystem aebMS/AEB_slave
 * hilite_system('aebMS/AEB_slave/Kp') - opens and selects block Kp
 *
 * Here is the system hierarchy for this model
 *
 * '<Root>' : 'aebMS'
 * '<S1>'   : 'aebMS/AEB_slave'
 * '<S2>'   : 'aebMS/AEB_slave/Brake_decision'
 */
#endif                                 /* RTW_HEADER_AEB_slave_h_ */

/*
 * File trailer for generated code.
 *
 * [EOF]
 */


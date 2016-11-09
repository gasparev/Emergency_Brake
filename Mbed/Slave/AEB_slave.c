/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: AEB_slave.c
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

#include "AEB_slave.h"

/* Named constants for Chart: '<S1>/Brake_decision' */
#define AEB_slave_IN_NO_ACTIVE_CHILD   ((uint8_T)0U)
#define AEB_slave_IN_No_brake          ((uint8_T)1U)
#define AEB_slave_IN_brake             ((uint8_T)2U)

/*===========*
 * Constants *
 *===========*/
#define RT_PI                          3.14159265358979323846
#define RT_PIF                         3.1415927F
#define RT_LN_10                       2.30258509299404568402
#define RT_LN_10F                      2.3025851F
#define RT_LOG10E                      0.43429448190325182765
#define RT_LOG10EF                     0.43429449F
#define RT_E                           2.7182818284590452354
#define RT_EF                          2.7182817F

/*
 * UNUSED_PARAMETER(x)
 *   Used to specify that a function parameter (argument) is required but not
 *   accessed by the function body.
 */
#ifndef UNUSED_PARAMETER
# if defined(__LCC__)
#   define UNUSED_PARAMETER(x)                                   /* do nothing */
# else

/*
 * This is the semi-ANSI standard way of indicating that an
 * unused function parameter is required.
 */
#   define UNUSED_PARAMETER(x)         (void) (x)
# endif
#endif

/* Model step function */
void AEB_slave_step(RT_MODEL_AEB_slave_T *const AEB_slave_M, real_T
                    AEB_slave_U_distance, real_T AEB_slave_U_actual_speed,
                    boolean_T AEB_slave_U_slave_status, boolean_T
                    *AEB_slave_Y_brakerequest)
{
  B_AEB_slave_T *AEB_slave_B = ((B_AEB_slave_T *) AEB_slave_M->ModelData.blockIO);
  DW_AEB_slave_T *AEB_slave_DW = ((DW_AEB_slave_T *)
    AEB_slave_M->ModelData.dwork);

  /* Chart: '<S1>/Brake_decision' incorporates:
   *  Inport: '<Root>/actual_speed'
   *  Inport: '<Root>/distance'
   *  Inport: '<Root>/slave_status'
   */
  /* Gateway: AEB_slave/Brake_decision */
  /* During: AEB_slave/Brake_decision */
  if (AEB_slave_DW->is_active_c4_AEB_slave == 0U) {
    /* Entry: AEB_slave/Brake_decision */
    AEB_slave_DW->is_active_c4_AEB_slave = 1U;

    /* Entry Internal: AEB_slave/Brake_decision */
    /* Transition: '<S2>:2' */
    AEB_slave_DW->is_c4_AEB_slave = AEB_slave_IN_No_brake;

    /* Entry 'No_brake': '<S2>:1' */
    /* '<S2>:1:1' brake_request= 0; */
    AEB_slave_B->brake_request = 0.0;

    /* '<S2>:1:1' blue_led=0; */
  } else if (AEB_slave_DW->is_c4_AEB_slave == AEB_slave_IN_No_brake) {
    /* During 'No_brake': '<S2>:1' */
    /* '<S2>:4:1' sf_internal_predicateOutput = ... */
    /* '<S2>:4:1' v*v*0.01>= d&&slave_status==0&&(d>0.02||d<4); */
    if ((AEB_slave_U_actual_speed * AEB_slave_U_actual_speed * 0.01 >=
         AEB_slave_U_distance) && (!AEB_slave_U_slave_status) &&
        ((AEB_slave_U_distance > 0.02) || (AEB_slave_U_distance < 4.0))) {
      /* Transition: '<S2>:4' */
      AEB_slave_DW->is_c4_AEB_slave = AEB_slave_IN_brake;

      /* Entry 'brake': '<S2>:3' */
      /* '<S2>:3:1' brake_request= 1; */
      AEB_slave_B->brake_request = 1.0;

      /* '<S2>:3:1' blue_led=1 */
    }
  } else {
    /* During 'brake': '<S2>:3' */
    /* '<S2>:5:1' sf_internal_predicateOutput = ... */
    /* '<S2>:5:1' v*v*0.01< d||slave_status==1; */
    if ((AEB_slave_U_actual_speed * AEB_slave_U_actual_speed * 0.01 <
         AEB_slave_U_distance) || AEB_slave_U_slave_status) {
      /* Transition: '<S2>:5' */
      AEB_slave_DW->is_c4_AEB_slave = AEB_slave_IN_No_brake;

      /* Entry 'No_brake': '<S2>:1' */
      /* '<S2>:1:1' brake_request= 0; */
      AEB_slave_B->brake_request = 0.0;

      /* '<S2>:1:1' blue_led=0; */
    }
  }

  /* End of Chart: '<S1>/Brake_decision' */

  /* Outport: '<Root>/brake request' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion'
   */
  *AEB_slave_Y_brakerequest = (AEB_slave_B->brake_request
    != 0.0);
}

/* Model initialize function */
void AEB_slave_initialize(RT_MODEL_AEB_slave_T *const AEB_slave_M, real_T
  *AEB_slave_U_distance, real_T *AEB_slave_U_actual_speed, boolean_T
  *AEB_slave_U_slave_status, boolean_T *AEB_slave_U_Masted_blu_led, boolean_T
  *AEB_slave_Y_brakerequest)
{
  DW_AEB_slave_T *AEB_slave_DW = ((DW_AEB_slave_T *)
    AEB_slave_M->ModelData.dwork);
  B_AEB_slave_T *AEB_slave_B = ((B_AEB_slave_T *) AEB_slave_M->ModelData.blockIO);

  /* Registration code */

  /* block I/O */
  (void) memset(((void *) AEB_slave_B), 0,
                sizeof(B_AEB_slave_T));

  /* states (dwork) */
  (void) memset((void *)AEB_slave_DW, 0,
                sizeof(DW_AEB_slave_T));

  /* external inputs */
  (*AEB_slave_U_distance) = 0.0;
  (*AEB_slave_U_actual_speed) = 0.0;
  (*AEB_slave_U_slave_status) = false;
  (*AEB_slave_U_Masted_blu_led) = false;

  /* external outputs */
  (*AEB_slave_Y_brakerequest) = false;

  /* SystemInitialize for Chart: '<S1>/Brake_decision' */
  AEB_slave_DW->is_active_c4_AEB_slave = 0U;
  AEB_slave_DW->is_c4_AEB_slave = AEB_slave_IN_NO_ACTIVE_CHILD;
}

/* Model terminate function */
void AEB_slave_terminate(RT_MODEL_AEB_slave_T *const AEB_slave_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(AEB_slave_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */


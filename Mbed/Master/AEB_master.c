/*
 * Academic License - for use in teaching, academic research, and meeting
 * course requirements at degree granting institutions only.  Not for
 * government, commercial, or other organizational use.
 *
 * File: AEB_master.c
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

#include "AEB_master.h"

/* Named constants for Chart: '<S1>/Brake_decision' */
#define AEB_master_IN_NO_ACTIVE_CHILD  ((uint8_T)0U)
#define AEB_master_IN_No_brake         ((uint8_T)1U)
#define AEB_master_IN_brake            ((uint8_T)2U)

/* Named constants for Chart: '<S1>/Controller_selftest' */
#define AEB_master_IN_controller_ko    ((uint8_T)1U)
#define AEB_master_IN_controller_ok    ((uint8_T)2U)

/* Named constants for Chart: '<S1>/Distance_sensor_check' */
#define AEB_master_IN_No_errors        ((uint8_T)1U)
#define AEB_master_IN_Yes_errors       ((uint8_T)2U)

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
void AEB_master_step(RT_MODEL_AEB_master_T *const AEB_master_M, real_T
                     AEB_master_U_distance, real_T AEB_master_U_actual_speed,
                     boolean_T *AEB_master_Y_master_brake_request, real_T
                     *AEB_master_Y_master_status)
{
  B_AEB_master_T *AEB_master_B = ((B_AEB_master_T *)
    AEB_master_M->ModelData.blockIO);
  DW_AEB_master_T *AEB_master_DW = ((DW_AEB_master_T *)
    AEB_master_M->ModelData.dwork);

  /* Chart: '<S1>/Distance_sensor_check' incorporates:
   *  Inport: '<Root>/distance'
   */
  /* Gateway: AEB_master/Distance_sensor_check */
  /* During: AEB_master/Distance_sensor_check */
  if (AEB_master_DW->is_active_c1_AEB_master == 0U) {
    /* Entry: AEB_master/Distance_sensor_check */
    AEB_master_DW->is_active_c1_AEB_master = 1U;

    /* Entry Internal: AEB_master/Distance_sensor_check */
    /* Transition: '<S4>:2' */
    AEB_master_DW->is_c1_AEB_master = AEB_master_IN_No_errors;

    /* Entry 'No_errors': '<S4>:1' */
    /* '<S4>:1:1' error=0; */
    AEB_master_B->error = 0.0;
  } else if ((AEB_master_DW->is_c1_AEB_master == AEB_master_IN_No_errors) &&
             ((AEB_master_U_distance < 0.02) || (AEB_master_U_distance > 4.0)))
  {
    /* During 'No_errors': '<S4>:1' */
    /* '<S4>:4:1' sf_internal_predicateOutput = ... */
    /* '<S4>:4:1' d<0.02||d>4; */
    /* Transition: '<S4>:4' */
    AEB_master_DW->is_c1_AEB_master = AEB_master_IN_Yes_errors;

    /* Entry 'Yes_errors': '<S4>:3' */
    /* '<S4>:3:1' error=1; */
    AEB_master_B->error = 1.0;
  } else {
    /* During 'Yes_errors': '<S4>:3' */
  }

  /* End of Chart: '<S1>/Distance_sensor_check' */

  /* Chart: '<S1>/Brake_decision' incorporates:
   *  Inport: '<Root>/actual_speed'
   *  Inport: '<Root>/distance'
   */
  /* Gateway: AEB_master/Brake_decision */
  /* During: AEB_master/Brake_decision */
  if (AEB_master_DW->is_active_c3_AEB_master == 0U) {
    /* Entry: AEB_master/Brake_decision */
    AEB_master_DW->is_active_c3_AEB_master = 1U;

    /* Entry Internal: AEB_master/Brake_decision */
    /* Transition: '<S2>:2' */
    AEB_master_DW->is_c3_AEB_master = AEB_master_IN_No_brake;

    /* Entry 'No_brake': '<S2>:1' */
    /* '<S2>:1:1' brake_request= 0; */
    AEB_master_B->brake_request = 0.0;

    /* '<S2>:1:1' blue_led=0; */
    AEB_master_B->blue_led = 0.0;
  } else if (AEB_master_DW->is_c3_AEB_master == AEB_master_IN_No_brake) {
    /* During 'No_brake': '<S2>:1' */
    /* '<S2>:4:1' sf_internal_predicateOutput = ... */
    /* '<S2>:4:1' v*v*0.01>= d && e==0; */
    if ((AEB_master_U_actual_speed * AEB_master_U_actual_speed * 0.01 >=
         AEB_master_U_distance) && (AEB_master_B->error == 0.0)) {
      /* Transition: '<S2>:4' */
      AEB_master_DW->is_c3_AEB_master = AEB_master_IN_brake;

      /* Entry 'brake': '<S2>:3' */
      /* '<S2>:3:1' brake_request= 1; */
      AEB_master_B->brake_request = 1.0;

      /* '<S2>:3:1' blue_led=1 */
      AEB_master_B->blue_led = 1.0;
    }
  } else {
    /* During 'brake': '<S2>:3' */
    /* '<S2>:5:1' sf_internal_predicateOutput = ... */
    /* '<S2>:5:1' v*v*0.01< d || e==1; */
    if ((AEB_master_U_actual_speed * AEB_master_U_actual_speed * 0.01 <
         AEB_master_U_distance) || (AEB_master_B->error == 1.0)) {
      /* Transition: '<S2>:5' */
      AEB_master_DW->is_c3_AEB_master = AEB_master_IN_No_brake;

      /* Entry 'No_brake': '<S2>:1' */
      /* '<S2>:1:1' brake_request= 0; */
      AEB_master_B->brake_request = 0.0;

      /* '<S2>:1:1' blue_led=0; */
      AEB_master_B->blue_led = 0.0;
    }
  }

  /* End of Chart: '<S1>/Brake_decision' */

  /* Chart: '<S1>/Controller_selftest' */
  /* Gateway: AEB_master/Controller_selftest */
  /* During: AEB_master/Controller_selftest */
  if (AEB_master_DW->is_active_c2_AEB_master == 0U) {
    /* Entry: AEB_master/Controller_selftest */
    AEB_master_DW->is_active_c2_AEB_master = 1U;

    /* Entry Internal: AEB_master/Controller_selftest */
    /* Transition: '<S3>:2' */
    AEB_master_DW->is_c2_AEB_master = AEB_master_IN_controller_ok;

    /* Entry 'controller_ok': '<S3>:1' */
    /* '<S3>:1:1' brake_status=brake_request; */
    AEB_master_B->brake_status = AEB_master_B->brake_request;

    /* Outport: '<Root>/master_status' */
    /* '<S3>:1:1' master_status=safe_state; */
    *AEB_master_Y_master_status = AEB_master_B->error;

    /* '<S3>:1:3' blue_status=blue_led; */
    AEB_master_B->blue_status = AEB_master_B->blue_led;
  } else if (AEB_master_DW->is_c2_AEB_master == AEB_master_IN_controller_ko) {
    /* Outport: '<Root>/master_status' */
    /* During 'controller_ko': '<S3>:3' */
    /* '<S3>:3:1' master_status=1; */
    *AEB_master_Y_master_status = 1.0;

    /* '<S3>:3:1' blue_status=0; */
    AEB_master_B->blue_status = 0.0;

    /* '<S3>:3:1' brake_status=0; */
    AEB_master_B->brake_status = 0.0;
  } else {
    /* During 'controller_ok': '<S3>:1' */
    /* '<S3>:4:1' sf_internal_predicateOutput = ... */
    /* '<S3>:4:1'  (((brake_status==1&&master_status==0&&blue_status==1))||((brake_status==0&&blue_status==0))||((master_status==0&&blue_status==0&&brake_status==0)))~=1; */
    if (!(((AEB_master_B->brake_status == 1.0) && (*AEB_master_Y_master_status ==
           0.0) && (AEB_master_B->blue_status == 1.0)) ||
          ((AEB_master_B->brake_status == 0.0) && (AEB_master_B->blue_status ==
           0.0)) || ((*AEB_master_Y_master_status == 0.0) &&
                     (AEB_master_B->blue_status == 0.0) &&
                     (AEB_master_B->brake_status == 0.0)))) {
      /* Transition: '<S3>:4' */
      AEB_master_DW->is_c2_AEB_master = AEB_master_IN_controller_ko;

      /* Outport: '<Root>/master_status' */
      /* Entry 'controller_ko': '<S3>:3' */
      /* '<S3>:3:1' master_status=1; */
      *AEB_master_Y_master_status = 1.0;

      /* '<S3>:3:1' blue_status=0; */
      AEB_master_B->blue_status = 0.0;

      /* '<S3>:3:1' brake_status=0; */
      AEB_master_B->brake_status = 0.0;
    } else {
      /* '<S3>:1:1' brake_status=brake_request; */
      AEB_master_B->brake_status = AEB_master_B->brake_request;

      /* Outport: '<Root>/master_status' */
      /* '<S3>:1:1' master_status=safe_state; */
      *AEB_master_Y_master_status = AEB_master_B->error;

      /* '<S3>:1:3' blue_status=blue_led; */
      AEB_master_B->blue_status = AEB_master_B->blue_led;
    }
  }

  /* End of Chart: '<S1>/Controller_selftest' */

  /* Outport: '<Root>/master_brake_request' incorporates:
   *  DataTypeConversion: '<S1>/Data Type Conversion'
   */
  *AEB_master_Y_master_brake_request = (AEB_master_B->brake_status
    != 0.0);
}

/* Model initialize function */
void AEB_master_initialize(RT_MODEL_AEB_master_T *const AEB_master_M, real_T
  *AEB_master_U_distance, real_T *AEB_master_U_actual_speed, boolean_T
  *AEB_master_Y_master_brake_request, real_T *AEB_master_Y_master_status)
{
  DW_AEB_master_T *AEB_master_DW = ((DW_AEB_master_T *)
    AEB_master_M->ModelData.dwork);
  B_AEB_master_T *AEB_master_B = ((B_AEB_master_T *)
    AEB_master_M->ModelData.blockIO);

  /* Registration code */

  /* block I/O */
  (void) memset(((void *) AEB_master_B), 0,
                sizeof(B_AEB_master_T));

  /* states (dwork) */
  (void) memset((void *)AEB_master_DW, 0,
                sizeof(DW_AEB_master_T));

  /* external inputs */
  (*AEB_master_U_distance) = 0.0;
  (*AEB_master_U_actual_speed) = 0.0;

  /* external outputs */
  (*AEB_master_Y_master_brake_request) = false;
  (*AEB_master_Y_master_status) = 0.0;

  /* SystemInitialize for Chart: '<S1>/Distance_sensor_check' */
  AEB_master_DW->is_active_c1_AEB_master = 0U;
  AEB_master_DW->is_c1_AEB_master = AEB_master_IN_NO_ACTIVE_CHILD;

  /* SystemInitialize for Chart: '<S1>/Brake_decision' */
  AEB_master_DW->is_active_c3_AEB_master = 0U;
  AEB_master_DW->is_c3_AEB_master = AEB_master_IN_NO_ACTIVE_CHILD;

  /* SystemInitialize for Chart: '<S1>/Controller_selftest' */
  AEB_master_DW->is_active_c2_AEB_master = 0U;
  AEB_master_DW->is_c2_AEB_master = AEB_master_IN_NO_ACTIVE_CHILD;
}

/* Model terminate function */
void AEB_master_terminate(RT_MODEL_AEB_master_T *const AEB_master_M)
{
  /* (no terminate code required) */
  UNUSED_PARAMETER(AEB_master_M);
}

/*
 * File trailer for generated code.
 *
 * [EOF]
 */


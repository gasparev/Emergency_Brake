#include "mbed.h"


extern "C"
{
#include "AEB_slave.h"                 /* Model's header file */
#include "rtwtypes.h"
}
DigitalOut led_blue(LED_BLUE);
DigitalOut trigger(D2);
InterruptIn echo(D4);
DigitalIn master_status(D5);
Timer t;
Ticker scheduler;
Serial pc(USBTX, USBRX); // tx, rx
char  new_speed[4];
float c=0;
static RT_MODEL_AEB_slave_T AEB_slave_M_;
static RT_MODEL_AEB_slave_T *const AEB_slave_M = &AEB_slave_M_;/* Real-time model */
static B_AEB_slave_T AEB_slave_B;      /* Observable signals */
static DW_AEB_slave_T AEB_slave_DW;    /* Observable states */

/* '<Root>/distance' */
static real_T AEB_slave_U_distance;

/* '<Root>/actual_speed' */
static real_T AEB_slave_U_actual_speed;

/* '<Root>/slave_status' */
static boolean_T AEB_slave_U_slave_status;

/* '<Root>/Masted_blu_led' */
static boolean_T AEB_slave_U_Masted_blu_led;

/* '<Root>/brake request' */
static boolean_T AEB_slave_Y_brakerequest;

//copy from ert.main the void funcition rt_one step

void rt_OneStep(RT_MODEL_AEB_slave_T *const AEB_slave_M);
void rt_OneStep(RT_MODEL_AEB_slave_T *const AEB_slave_M)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(AEB_slave_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  AEB_slave_step(AEB_slave_M, AEB_slave_U_distance, AEB_slave_U_actual_speed,
                 AEB_slave_U_slave_status, &AEB_slave_Y_brakerequest);

  /* Get model outputs here */

  /* Indicate task complete */
  OverrunFlag = false;

  /* Disable interrupts here */
  /* Restore FPU context here (if necessary) */
  /* Enable interrupts here */
}
//END COPY


void do_step(void)
{
    rt_OneStep(AEB_slave_M);
}
void start( void )
{
    t.start();
}
void stop( void )
{
    t.stop();
    AEB_slave_U_distance = t.read_us()/5800.0;
    c++;
    t.reset();
}
int main()
{
    //copy from ert_main.c
   /* Pack model data into RTM */
  AEB_slave_M->ModelData.blockIO = &AEB_slave_B;
  AEB_slave_M->ModelData.dwork = &AEB_slave_DW;

  /* Initialize model */
  AEB_slave_initialize(AEB_slave_M, &AEB_slave_U_distance,
                       &AEB_slave_U_actual_speed, &AEB_slave_U_slave_status,
                       &AEB_slave_U_Masted_blu_led, &AEB_slave_Y_brakerequest);

// end copy//


    AEB_slave_U_actual_speed=9;
    AEB_slave_Y_brakerequest=0;
    led_blue=1;
    scheduler.attach( &do_step, 0.1 );

    t.reset();
    echo.rise( &start );
    echo.fall( &stop );

    AEB_slave_U_distance = 2;
    trigger = 0;

    while (true) {

        trigger = 1;
        wait_us( 10 );
        trigger = 0;
        AEB_slave_U_slave_status=!master_status;
        if (AEB_slave_U_slave_status==0) {
                if(c==2){
                pc.printf("insert speed in the format nnn, insert 0 in front if speed under 100 Kmh\n");
                pc.gets(new_speed,4);
                AEB_slave_U_actual_speed=atof(new_speed);
                pc.printf( "\n\r slave distance: %.3f\n\r \n\r speed: %.3f\n\r", AEB_slave_U_distance, AEB_slave_U_actual_speed);
                c=0;
                }
            
            led_blue=!AEB_slave_Y_brakerequest;
            
        }



    }
}

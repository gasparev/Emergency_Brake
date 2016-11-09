#include "mbed.h"


extern "C"
{
#include "AEB_master.h"                /* Model's header file */
#include "rtwtypes.h"
}
DigitalOut led_blue(LED_BLUE);
DigitalOut led_red(LED_RED);
DigitalOut trigger(D2);
InterruptIn echo(D4);
DigitalOut master_status(D5);
Timer t;
Ticker scheduler;
Serial pc(USBTX, USBRX); // tx, rx
char  new_speed[4];
float c=0;
//copy from ert_many.c
//



static RT_MODEL_AEB_master_T AEB_master_M_;
static RT_MODEL_AEB_master_T *const AEB_master_M = &AEB_master_M_;/* Real-time model */
static B_AEB_master_T AEB_master_B;    /* Observable signals */
static DW_AEB_master_T AEB_master_DW;  /* Observable states */

/* '<Root>/distance' */
static real_T AEB_master_U_distance;

/* '<Root>/actual_speed' */
static real_T AEB_master_U_actual_speed;

/* '<Root>/master_brake_request' */
static boolean_T AEB_master_Y_master_brake_request;

/* '<Root>/master_status' */
static real_T AEB_master_Y_master_status;

//copy from ert.main the void funcition rt_one step

void rt_OneStep(RT_MODEL_AEB_master_T *const AEB_master_M);
void rt_OneStep(RT_MODEL_AEB_master_T *const AEB_master_M)
{
  static boolean_T OverrunFlag = false;

  /* Disable interrupts here */

  /* Check for overrun */
  if (OverrunFlag) {
    rtmSetErrorStatus(AEB_master_M, "Overrun");
    return;
  }

  OverrunFlag = true;

  /* Save FPU context here (if necessary) */
  /* Re-enable timer or interrupt here */
  /* Set model inputs here */

  /* Step the model */
  AEB_master_step(AEB_master_M, AEB_master_U_distance, AEB_master_U_actual_speed,
                  &AEB_master_Y_master_brake_request,
                  &AEB_master_Y_master_status);

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
    rt_OneStep(AEB_master_M);
}
void start( void )
{
    t.start();
}
void stop( void )
{
    t.stop();
    AEB_master_U_distance = t.read_us()/5800.0;
    c++;
    t.reset();
}
int main()
{
    //copy from ert_main.c
    /* Pack model data into RTM */
  AEB_master_M->ModelData.blockIO = &AEB_master_B;
  AEB_master_M->ModelData.dwork = &AEB_master_DW;

  /* Initialize model */
  AEB_master_initialize(AEB_master_M, &AEB_master_U_distance,
                        &AEB_master_U_actual_speed,
                        &AEB_master_Y_master_brake_request,
                        &AEB_master_Y_master_status);
// end copy//


    scheduler.attach( &do_step, 0.1 );

    t.reset();
    echo.rise( &start );
    echo.fall( &stop );

    trigger = 0;
    led_blue=1;
    led_red=1;

    while (true) {
        trigger = 1;
        wait_us( 10 );
        trigger = 0;
        
        if (AEB_master_Y_master_status==0) {
            if (c==2) {
                pc.printf("insert speed in the format nnn, insert 0 in front if speed under 100 Kmh\n");
                pc.gets(new_speed,4);
                AEB_master_U_actual_speed=atof(new_speed);
                c=0;
            }
            master_status=AEB_master_Y_master_status;
            led_blue=!AEB_master_Y_master_brake_request;
            led_red=!AEB_master_Y_master_status;
            pc.printf( "\n\r master distance: %.3f\n\r \n\r speed: %.3f\n\r %f\n\r", AEB_master_U_distance, AEB_master_U_actual_speed),c;
            
        }
    }
}

#include "mbed.h"
#include <stdint.h>
#include "math.h" 
#include "path_1d.h"
#include "GPA.h"
#include "ControllerLoop.h"
#include "Mirror_Kinematic.h"
#include "data_structs.h"
#include "uart_comm_thread.h"
#include "FastPWM.h"
#include "sensors_actuators.h"
 
static BufferedSerial serial_port(USBTX, USBRX);

float Ts=.0002f;                    // sampling time
void pressed(void);
void released(void); 
//------------- DEFINE FILTERS ----------------
// missing
//------------- Define In/Out -----------------

//------------------------------------------
// ----- User defined functions -----------
Timer glob_ti;                                  // the global timer
//----------------------------------------- global variables (uhh!) ---------------------------
//init values:    (f0,   f1, nbPts, A0, A1, Ts)
GPA          myGPA(5 , 2400,    40, 60, 50, Ts);


//******************************************************************************
//---------- main loop -------------
//******************************************************************************

int main()
{

    // --------- Mirror kinematik, define values, trafos etc there
    Data_Xchange data;
    Mirror_Kinematic mk(&data);
    uart_comm_thread uart_com(&data, &mk,&serial_port,.05f);   // this is the communication thread
    sensors_actuators hardware(&data, Ts);
    ControllerLoop loop(&data,&hardware,Ts);                        // this is forthe main controller loop


    serial_port.set_baud(115200);
    serial_port.set_format(8,BufferedSerial::None,1);
    serial_port.set_blocking(false); // force to send whenever possible and data is there
    mk.set_offsets(982,-167);          // individal set values for global position
    mk.trafo_is_on = true;

    loop.init_controllers();
    uart_com.start_uart();
    loop.start_loop();
    ThisThread::sleep_for(200);
    uart_com.send_text((char *)"Start Mirroractuator 2.0");
   /* p1.initialize(300,10,A,0,0,0);
    p2.initialize(300,10,-A,0,0,A);*/
    //for(int wk =0;wk<5;wk++)
    while(1)
        {
        ThisThread::sleep_for(200);
        }
}   // END OF main

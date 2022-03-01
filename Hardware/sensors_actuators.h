#pragma once
/* class sensors_actuators
Tasks for students:
    - scale ios correctly
    - define derivative filter correctly
*/
#include <cstdint>
#include "DiffCounter.h"
#include "EncoderCounter.h"
#include "EncoderCounterIndex.h"
#include "DiffCounter.h"
#include "IIR_filter.h"
#include "LinearCharacteristics.h"
#include "Unwrapper_2pi.h"
#include "data_structs.h"


class sensors_actuators
{
public:
    sensors_actuators(Data_Xchange *,float Ts);        // default constructor
    virtual ~sensors_actuators();   // deconstructor
    void read_encoders(void);       // read both encoders and calculate speeds
    float get_phi(uint8_t);         // get angle of motor k
    float get_om(uint8_t);          // get speed of motor k
    void set_des_current(uint8_t);  // set desired current on actuator
    void enable_motors(void);
    void disable_motors(void);

private:

    DiffCounter di1;
    DiffCounter di2;
    DigitalIn big_button;         // Enable button an backside
    ///------------- Encoder -----------------------
    EncoderCounter counter1;    // initialize counter on PA_6 and PC_7
    InterruptIn indexpulse1;
    EncoderCounterIndex index1;   
    // ------------------------------------
    EncoderCounter counter2;    // initialize counter on PB_6 and PB_7
    InterruptIn indexpulse2;
    EncoderCounterIndex index2;    // 
    DigitalOut i_enable;
    DigitalOut laser_on;
    //-------------------------------------
    LinearCharacteristics i2u;
    LinearCharacteristics u2i;
    Unwrapper_2pi uw2pi1;
    Unwrapper_2pi uw2pi2;
    Data_Xchange *m_data;



};
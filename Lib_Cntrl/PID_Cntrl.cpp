#include "PID_Cntrl.h"

// Matlab
// Tn = .005;
// Gpi= tf([Tn 1],[Tn 0]);
// Kp = 0.0158;
// pid(Kp*Gpi);

PID_Cntrl::PID_Cntrl(float kp, float ki, float kd, float tau_f, float Ts, float uMin, float uMax)
{
    // ------------------
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->tau_f = tau_f;
    this->Ts = Ts;
    this->uMin = uMin;
    this->uMax = uMax;
    reset(0);
}

PID_Cntrl::~PID_Cntrl() {}

void PID_Cntrl::setup(float kp, float ki, float kd, float tau_f, float Ts, float uMin, float uMax)
{
    // ------------------
    this->kp = kp;
    this->ki = ki;
    this->kd = kd;
    this->tau_f = tau_f;
    this->Ts = Ts;
    this->uMin = uMin;
    this->uMax = uMax;
}



void PID_Cntrl::reset(float initValue)
{
    Ipart = 0;
    Dpart = 0;
    e_old = 0;
    
}


float PID_Cntrl::update(float e)
{
    // the main update PID COntroller is descretized with tustin see Blatt 2 
    float Ppart = kp * e;
    Ipart = Ipart + ki * Ts/2.0f * (e + e_old);
    e_old = e;

    Ipart = saturate(Ipart);
    
    return saturate(Ppart + Ipart); 
   
}

float PID_Cntrl::saturate(float x)
{
if(x > uMax)
    return uMax;
else if(x < uMin)
    return uMin;
return x;
}
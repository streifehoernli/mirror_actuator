#ifndef PID_CNTRL_H_
#define PID_CNTRL_H_

class PID_Cntrl
{
public:

    PID_Cntrl(float kp, float ki, float kd, float tau_f, float Ts, float uMin, float uMax);
    PID_Cntrl() {};
    void setup(float kp, float ki, float kd, float tau_f, float Ts, float uMin, float uMax);

    float operator()(float e)
    {
        return update(e);
    }

    virtual ~PID_Cntrl();

    void    reset(float initValue);
    void    setCoefficients(float kp, float ki, float kd, float tau_f, float Ts, float uMin, float uMax);
    float   update(float e);
    float   saturate(float);


private:
    float kp,ki,kd,tau_f,Ts,uMax,uMin;
    float Ipart,Dpart,e_old;

};

#endif
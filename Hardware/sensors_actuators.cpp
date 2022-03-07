#include "sensors_actuators.h"

#define PI 3.1415927
// constructors


// Deconstructor
sensors_actuators::sensors_actuators(Data_Xchange *data,float Ts) : di1(.01,Ts),di2(.01,Ts),big_button(PC_3),counter1(PA_6, PC_7),
                            indexpulse1(PA_8),index1(counter1,indexpulse1), counter2(PB_6, PB_7),indexpulse2(PB_4),index2(counter2,indexpulse2),
                            i_enable(PC_4),laser_on(PB_0), uw1(4000,16),uw2(4000,16)
{
    this->m_data = data;
    i2u.setup(-.80,.80,0.0f,1.0f);
    u2i.setup(0.0,1.0,-1.0,1.0);
    i_enable = 0;       // disable current first
    counter1.reset();   // encoder reset
    counter2.reset();   // encoder reset
}
sensors_actuators::~sensors_actuators() {} 

void sensors_actuators::read_encoders_calc_speed(void)
{
    m_data->sens_phi[0] = uw1(counter1);
    m_data->sens_phi[1] = uw2(counter2);
    m_data->sens_Vphi[0] = di1(m_data->sens_phi[0]);
    m_data->sens_Vphi[0] = di2(m_data->sens_phi[1]);
}
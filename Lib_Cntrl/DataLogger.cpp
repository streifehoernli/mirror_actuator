#include "DataLogger.h"
#include "math.h"

DataLogger::DataLogger(uint8_t dum)
{
    init_data();
}

DataLogger::~DataLogger() {}

void DataLogger::init_data(void)
{
    for(uint8_t k=0;k<this->N;k++)
        for(uint8_t j=0;j<3;j++)
            this->log_data[k][j] = (float)k*.1;
    this->log_status = 1;   // 0 = IDLE, 1 = ready, wait for trigger, 2 = logging, 3 = init_sending, 4 = sending
    this->input_type = 1;
    this->N = N1;
    this->count = 0;
    new_data_available = false;
    ti_offset = 0;
    packet = 0;
}
void DataLogger::reset_data(void)
{
    for(uint8_t k=0;k<this->N;k++)
        for(uint8_t j=0;j<3;j++)
            this->log_data[k][j] = (float)k;
    this->count = 0;
    new_data_available = false;
}

void DataLogger::write_to_log(float ti,float u,float x)
{
    if(log_status == 2 )
        {
        log_data[count][0] = ti - ti_offset;
        log_data[count][1] = u;
        log_data[count++][2] = x;
        if(count >= N)
            {
            log_status = 3;
            new_data_available = true;
            packet = 0;
            }
        }
}

float DataLogger::get_set_value(float ti)
{
    float Amp = 200;
    float om = 2*3.1415927 * 20;
    if(log_status == 2 )
        {
        if(count == 0)
            ti_offset = ti;
        if(input_type == 1)
            {
            if((ti-ti_offset) > .002)
                return Amp;
            else
                return 0;
            }
        else if(input_type == 2)
            return Amp*sinf(om*(ti-ti_offset));
        }
    return 0;
}
#pragma once
#include <stdint.h>

#define N1 200

class DataLogger
{
public:
    DataLogger(uint8_t);
    DataLogger() {};
   
    virtual ~DataLogger();

    void    start_logging(void);
    uint16_t N;
    uint16_t packet;
     float log_data[N1][3];
    uint8_t log_status; // 0 = IDLE, 1 = ready, wait for trigger, 2 = start_logging, 3 = init_sending, 4 = sending
    uint8_t input_type;       // 1 = step, 2 = sine
    void reset_data(void);
    bool new_data_available;
    void write_to_log(float,float,float);
    float get_set_value(float);
private:
    void init_data(void);
    float ti_offset;
    uint16_t count;
};

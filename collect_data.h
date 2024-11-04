#ifndef __COLLECT_D_H_
#define __COLLECT_D_H_

#include <stdbool.h>
#include <stdint.h>

// Data structure for holding collected data
typedef struct {
    uint8_t imei[16];
    uint8_t iccid[21];
    uint8_t GPRSsignal;
    uint8_t DeviceEtat;
    uint8_t DeviceBattery;
    bool IgnitionStatus;
    bool DIN1;
    bool DOUT0;
    bool DOUT1;
    uint16_t AN;
    uint32_t DataTime;
    float latitude;
    float longitude;
    float speed;
    uint32_t LastTime;
    uint8_t satTrack;
    uint32_t hourMeter;
    uint8_t VehicleEtat;
    float VehicleBattery;
    float distance;
    bool stationary;
    float ax[10];
    float ay[10];
    float az[10];
    float gx[10];
    float gy[10];
    float gz[10];
} PBDATA_t;

#define BATCH_SIZE 10  // Define how many records to batch

// Function prototypes
void collect_init();
bool collect_Data(char* buf, uint8_t** dbuf, int16_t* len);
void edatatojson(uint8_t* data, char* buf, uint16_t* len);
void add_data_to_batch(PBDATA_t *data);
void store_data_batch();

extern uint16_t lenthpbd;

#endif // __COLLECT_D_H_

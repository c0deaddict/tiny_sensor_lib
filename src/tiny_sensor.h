#include <stdint.h>

#define TINY_SENSOR_VERSION 0x01

#define CAP_TEMP_NONE     0
#define CAP_TEMP_DS18B20  1
#define CAP_TEMP_DHT22    2
#define CAP_TEMP_DHT11    3

#define CAP_SW_NONE       0
#define CAP_SW_REED       1
#define CAP_SW_PIR        2

#define CAP_LDR_NONE      0
#define CAP_LDR_PRESENT   1

#define TEMP_ERROR        0xffff
#define HUMID_ERROR       0xffff

struct cap {
  uint8_t temp : 3;
  uint8_t sw : 3;
  uint8_t ldr : 1;
  uint8_t reserved : 1;
} __attribute__ ((packed));

struct sw {
  uint8_t val : 1;
  uint8_t intr : 1;
} __attribute__((packed));

struct packet {
  uint8_t version;
  uint8_t sensor_id;
  uint16_t seq;
  struct cap cap;
  struct {
    struct sw sw;
    uint16_t vcc; // mV
    uint16_t temp; // micro degrees Celsius
    uint16_t humid; // micro percent
    uint16_t lux;
  } state;
  // crc must be last
  uint8_t crc;
} __attribute__ ((packed));

uint8_t crc8(const uint8_t *data, int len);

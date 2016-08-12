#ifndef _PM1001_H_
#define _PM1001_H_

#include <Arduino.h>
#include <SoftwareSerial.h>

class Sensor_PM1001 {
  public:
    void begin(unsigned long baudrate, uint8_t rx, uint8_t tx);
    void beginSerial(unsigned long baudrate);
#if defined (__AVR_ATmega1280__) || defined (__AVR_ATmega128__) || defined (__AVR_ATmega2560__)
    void beginSerial1(unsigned long baudrate);
    void beginSerial2(unsigned long baudrate);
    void beginSerial3(unsigned long baudrate);
#endif
    
    void sendCmd(void);
    void readCmd(void);
	int available(void);
    unsigned long get_pcs(void);
    float get_ug(void);
    
  private:
    boolean FLAG_hwSerial;
    boolean FLAG_beginSerial;
    
    SoftwareSerial *swSerial;
    HardwareSerial *hwSerial;
    
    const uint8_t send_data[4] = {0x11, 0x01, 0x01, 0xED};
    uint8_t receive_buff[16];
    unsigned long pcs;
    float ug;
    unsigned char recv_cnt = 0;

    uint8_t calc_checksum(uint8_t*);
};

extern Sensor_PM1001 DustSensor;

#endif

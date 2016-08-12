#include "pm1001.h"

Sensor_PM1001 DustSensor;

void Sensor_PM1001::begin(unsigned long baudrate, uint8_t rx, uint8_t tx) {
  FLAG_beginSerial = true;

  swSerial = new SoftwareSerial(rx, tx);
  swSerial->begin(baudrate);
}
#if defined (__AVR_ATmega1280__) || defined (__AVR_ATmega128__) || defined (__AVR_ATmega2560__)
void Sensor_PM1001::beginSerial(unsigned long baudrate) {
  FLAG_hwSerial = true;
  FLAG_beginSerial = true;

  hwSerial = &Serial;
  hwSerial->begin(baudrate);
}

void Sensor_PM1001::beginSerial1(unsigned long baudrate) {
  FLAG_hwSerial = true;
  FLAG_beginSerial = true;

  hwSerial = &Serial1;
  hwSerial->begin(baudrate);
}

void Sensor_PM1001::beginSerial2(unsigned long baudrate) {
  FLAG_hwSerial = true;
  FLAG_beginSerial = true;

  hwSerial = &Serial2;
  hwSerial->begin(baudrate);
}

void Sensor_PM1001::beginSerial3(unsigned long baudrate) {
  FLAG_hwSerial = true;
  FLAG_beginSerial = true;

  hwSerial = &Serial3;
  hwSerial->begin(baudrate);
}
#endif

unsigned long Sensor_PM1001::get_pcs(void) {
  return pcs;
}

float Sensor_PM1001::get_ug(void) {
  return ug;
}

int Sensor_PM1001::available(void) {
	if(FLAG_hwSerial) {
		return hwSerial->available();
	} else {
		return swSerial->available();
	}
}

void Sensor_PM1001::sendCmd(void) {
  int i = 0;

  while(i < sizeof(send_data)) {
    if(FLAG_hwSerial) {
      if(hwSerial->availableForWrite()) {
        hwSerial->write(send_data[i]);
      }
    } else {
      swSerial->write(send_data[i]);
    }

    i++;
    delay(1);
  }
}

void Sensor_PM1001::readCmd(void) {  
  if (FLAG_hwSerial) {
    receive_buff[recv_cnt++] = hwSerial->read();
  } else {
    if (*swSerial) {
      receive_buff[recv_cnt++] = swSerial->read();
    }
  }

  if (recv_cnt > 15) {
    recv_cnt = 0;
    
    if(calc_checksum(receive_buff) == receive_buff[15]) {
      pcs = (unsigned long)receive_buff[3] << 24 |
            (unsigned long)receive_buff[4] << 16 |
            (unsigned long)receive_buff[5] << 8  |
            (unsigned long)receive_buff[6];       // 수량

      ug = (float)pcs * 3528 / 100000; // PM1001 only!! 
    }
  }
}

uint8_t Sensor_PM1001::calc_checksum(uint8_t *recv_buff) {
  uint8_t sum = 0;

  for(int i = 0; i < 15; i++) {
    sum += recv_buff[i];
  }

  return 256 - sum;
}


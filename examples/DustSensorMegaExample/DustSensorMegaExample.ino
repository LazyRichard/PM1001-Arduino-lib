#include "pm1001"

void setup() {
	// for output
	Serial.begin(9600);
	
	// init pm1001 with hardware serial2
	DustSensor.beginSerial2(9600);
}

void loop() {
	DustSensor.sendCmd();
	Serial.print("PCS: "); Serial.print(DustSensor.get_pcs());
	Serial.print("UG: "); Serial.println(DustSensor.get_ug());
	delay(1000);
}

// 초기화한 시리얼 포트랑 이벤트랑 맞는지 확인하세요!
void serialEvent2(){
	while(DustSensor.available()) {
		DustSensor.readCmd();
	}

}

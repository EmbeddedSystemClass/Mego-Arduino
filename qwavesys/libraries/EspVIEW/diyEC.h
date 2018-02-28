
#ifndef DIYEC_H
#define DIYEC_H

#include <OneWire.h>
#include <DallasTemperature.h>

class diyEC {
private:
	uint8_t ECPower;
    float Temperature;
	float k1;
	float v1;
	float k2;
	float v2;
	float Vin;
	int ppm;
	float calVolt;
	float calK;
	OneWire * onewire;
	DallasTemperature * sensors;
public:
	void begin(uint8_t temp_pin, uint8_t ECPower, float ECVolt, float Kmin, float Vmin, float Kmax, float Vmax);
	float GetEC(uint8_t ECPin, int R1, uint8_t count);
	float CalibrationEC(uint8_t ECPin, int R1, uint8_t count, float knownEC);
	float GetK(void);
	float GetVolt(void);
	float GetTemperature(void);
	float GetPPM(void);
};


#endif

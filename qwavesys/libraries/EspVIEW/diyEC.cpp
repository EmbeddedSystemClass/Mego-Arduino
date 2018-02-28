
#include "diyEC.h"

//*********** Converting to ppm [Learn to use EC it is much better**************//
// Hana      [USA]        PPMconverion:    0.5
// Eutech    [EU]         PPMconversion:  0.64
// Tranchen  [Australia]  PPMconversion:   0.7
#define PPMconversion 0.5

//*************Compensating for temperature ************************************//
//The value below will change depending on what chemical solution we are measuring
//0.019 is generaly considered the standard for plant nutrients [google "Temperature compensation EC" for more info
#define TemperatureCoef 0.019  //this changes depending on what chemical we are measuring

//#define k1        1.98
//#define v1        0.93
//#define k2        2.38
//#define v2        1.76
//#define Vin       5.00

#define Ra        25

void diyEC::begin(uint8_t temp_pin, uint8_t ECPowerPin, float ECVolt, float Kmin, float Vmin, float Kmax, float Vmax) {
	onewire = new OneWire(temp_pin);
	sensors = new DallasTemperature(onewire);
	sensors->begin();
	
	ECPower = ECPowerPin;
	pinMode(ECPower,OUTPUT);
	digitalWrite(ECPower,LOW);
	
	k1 = Kmin;
	v1 = Vmin;
	k2 = Kmax;
	v2 = Vmax;
	
	Vin = ECVolt;
}

float diyEC::GetTemperature(void) {
	return Temperature;
}

float diyEC::GetPPM(void) {
	return ppm;
}

float diyEC::GetVolt(void) {
	return calVolt;
}

float diyEC::GetK(void) {
	return calK;
}

float diyEC::GetEC(uint8_t ECPin, int R1, uint8_t count){
 
	//*********Reading Temperature Of Solution *******************//
	sensors->requestTemperatures();            // Send the command to get temperatures
	Temperature = sensors->getTempCByIndex(0); //Stores Value in Variable

	uint32_t DAC = 0;

	float Vdrop;
	float Rc;
	for(int i=0;i<count;i++) {
    
		// ************Estimates Resistance of Liquid ****************
		digitalWrite(ECPower,HIGH);
		delay(1);
		DAC += analogRead(ECPin);
		digitalWrite(ECPower,LOW);
		delay(5);
	}
	DAC /= count;
  
    //*********** Calculates R relating to Calibration fluid **************
    Vdrop = ((float)DAC*Vin)/4095;
	Rc = (Vdrop*R1)/(Vin-Vdrop);
	Rc = Rc-Ra;

    float m = (k2-k1)/(v2-v1);
	// Absolute Value
	m = abs(m);
    float K;
    if(Vdrop <= v2) {
      K = k2-(m*(v2-Vdrop));
    } else {
      K = (m*(Vdrop-v2))+k2;
    }
    float EC = 1000/(Rc*K);
 
    //*************Compensating For Temperaure********************
    EC /= (1+ TemperatureCoef*(Temperature-25.0));
	ppm = (EC)*(PPMconversion*1000);
	
	//********** Usued for Debugging ************
  
	Serial.print("Temperature: ");
	Serial.print(Temperature);
	Serial.println(" *C ");
	Serial.print("Slope m: ");
	Serial.println(m);
	Serial.print("K: ");
	Serial.println(K);
	Serial.print("Vdrop: ");
	Serial.println(Vdrop);
	Serial.print("Rc: ");
	Serial.print(Rc);
	Serial.println(" ohm");
  
	//********** end of Debugging Prints *********

	return EC;
}

float diyEC::CalibrationEC(uint8_t ECPin, int R1, uint8_t count, float knownEC) {
 
	//*********Reading Temperature Of Solution *******************//
	sensors->requestTemperatures();            // Send the command to get temperatures
	Temperature = sensors->getTempCByIndex(0); //Stores Value in Variable

	uint32_t DAC = 0;

	float Vdrop;
	float Rc;
	for(int i=0;i<count;i++) {
    
		// ************Estimates Resistance of Liquid ****************
		digitalWrite(ECPower,HIGH);
		delay(1);
		DAC += analogRead(ECPin);
		digitalWrite(ECPower,LOW);
		delay(5);
	}
	DAC /= count;
	
	sensors->requestTemperatures(); 
	float TemperatureFinish = sensors->getTempCByIndex(0);
	
	//*************Compensating For Temperaure********************//
	knownEC = knownEC*(1+(TemperatureCoef*(TemperatureFinish-25.0))) ;

    //********** Calculates R relating to Calibration fluid *************
    Vdrop = ((float)DAC*Vin)/4096;
	Rc = (Vdrop*R1)/(Vin-Vdrop);
	Rc = Rc-Ra;

    float K = 1000/(Rc*knownEC);
	calVolt = Vdrop;
	calK = K;
	
	//********** Usued for Debugging ************
  
	Serial.print("Temperature: ");
	Serial.print(Temperature);
	Serial.println(" *C ");
	Serial.print("Calibration Fluid EC: ");
	Serial.print(knownEC);
	Serial.println(" S  ");  //add units here
	Serial.print("Cell Constant K: ");
	Serial.println(K);
	Serial.print(" Vdrop: ");
	Serial.print(Vdrop);
	Serial.println(" V");
  
	//********** end of Debugging Prints *********
	//float diff = TemperatureFinal - Temperature;
	//return ((diff)>0?(diff):-(diff));
	return abs(TemperatureFinish - Temperature);
}

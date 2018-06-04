#include "mego.h"
#include "SoftwareSerial.h"
#include "RS485_non_blocking.h"

#define RS485_RX  D3
#define RS485_TX  D4
#define BAUD_RATE 9600

unsigned int buffSize = 32;

SoftwareSerial rs485(RS485_RX, RS485_TX, false, buffSize);

// callbacks for the non-blocking RS485 library
size_t fWrite (const byte what) {
  rs485.write (what);
}

int fAvailable () {
  return rs485.available ();
}

int fRead () {
  return rs485.read ();
}

// RS485 library instance
RS485 myChannel (fRead, fAvailable, fWrite, buffSize);
  
void setup() {
  // debugging prints
  Serial.begin (115200);
  Serial.println("\nRS485 Test!");
  
  // software serial for talking to other devices
  rs485.begin (BAUD_RATE);
  // initialize the RS485 library
  myChannel.begin ();
  myChannel.reset();
  
  const byte msg [] = "Hello world";
  myChannel.sendMsg (msg, sizeof (msg));
  delay (1000); 
}

void loop() {
  if (myChannel.update ()) {
    Serial.write (myChannel.getData (), myChannel.getLength ()); 
  }
}

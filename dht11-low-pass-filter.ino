#include <Wire.h>
#include <SFE_MicroOLED.h>
#include "DHT.h"

#define DHTPIN 0
#define DHTTYPE DHT11

DHT dht( DHTPIN, DHTTYPE );

#define PIN_RESET 255  //
#define DC_JUMPER 0  // I2C Addres: 0 - 0x3C, 1 - 0x3D

MicroOLED oled( PIN_RESET, DC_JUMPER );

// https://www.norwegiancreations.com/2015/10/tutorial-potentiometers-with-arduino-and-filtering/
float EMA_a = 0.1;
float EMA_S = 0.0;

void setup() {
  oled.begin();
  oled.clear( ALL );
  oled.display();

  oled.setFontType( 3 );

  Serial.begin( 9600 );

  dht.begin();
  EMA_S = dht.readTemperature( true );
}

void loop() {
  delay( 2000 );

  float temp = dht.readTemperature( true );
  Serial.println( temp );
  EMA_S = ( EMA_a * temp ) + ( ( 1 - EMA_a ) * EMA_S );
  
  oled.clear( PAGE );
  oled.setCursor( 20, 0 );
  oled.print( (int) EMA_S );
  oled.display();
}


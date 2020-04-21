#include <DHT.h>
// Arduino Pinmap
// D0 - GPIO 16       
// D1 - GPIO 5 / SCL  - OLED SCL
// D2 - GPIO 4 / SDA  - OLED SDA
// D3 - GPIO 0        - PM Pin
// D4 - GPIO 2        - DHT11
// D5 - GPIO 14       - NeoPixel  
// D6 - GPIO 12       - Touch SW(Input)
// D7 - GPIO 13       - FAN
// D8 - GPIO 15
// TX
// RX

#include <PMsensor.h>
#include "U8glib.h"
#include <Adafruit_NeoPixel.h>

#include <ESP8266WiFi.h>
#include <time.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 0
Adafruit_SSD1306 display(OLED_RESET);

// DHT11
#define DHTPIN D4         // DHT Digital Pin
#define DHTTYPE DHT11     // DHT Model - DHT11
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor.

// PM sensor(GP2Y1014AU0F)
PMsensor PM;

int delayCnt = 0;

// Touch SW
#define SW D6

// NeoPixel
#define LEDPIN D5
#define NUMPIXELS 8
Adafruit_NeoPixel pixels(NUMPIXELS, LEDPIN, NEO_GRB + NEO_KHZ800);

// FAN
#define FAN D7

// Wifi
const char* ssid = "KT_WLAN_4C5F";
const char* password = "ajaj2015";

void setup() {
  Serial.begin(9600);
  Serial.println("Air Tower ver1.0, April 2020");

  dht.begin();
  
  PM.init(D3, 0);  // Digital Pin(infrared LED pin, D3(=GPIO 0))
                    // Analog Pin(sensor pin, A0)
                    
  pinMode(SW, INPUT); // Setting pinmode of Touch SW
  //attachInterrupt(digitalPinToInterrupt(SW), swISR, CHANGE);

  pinMode(FAN, OUTPUT);
  
  pixels.begin();


  display.begin();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Air Tower V1.0");
  display.display(); 
}

void loop() {

  // ****************************
  // [START] DHT11 Sensor
  // ****************************
  // Wait a few seconds between measurements.
  delay(100);

  delayCnt++;
  float dhtHumid = 0;
  float dhtTemp = 0;
  float dhtTempF = 0;
  float PM2p5 = 0;
  if(delayCnt > 30){
      // Reading temperature or humidity takes about 250 milliseconds!
      // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
      dhtHumid = dht.readHumidity();
      // Read temperature as Celsius (the default)
      dhtTemp = dht.readTemperature();
      // Read temperature as Fahrenheit (isFahrenheit = true)
      dhtTempF = dht.readTemperature(true);
      
      // Check if any reads failed and exit early (to try again).
      if (isnan(dhtHumid) || isnan(dhtTemp) || isnan(dhtTempF)) {
        Serial.println(F("Failed to read from DHT sensor!"));
        return;
      }
      // ****************************
      // [END] DHT11 Sensor
      // ****************************
    
      // ****************************
      // [START] PM Sensor(GP2Y1014AU0F)
      // ****************************
      PM2p5 = 0;
      int err = PMsensorErrSuccess;
      if ((err = PM.read(&PM2p5, true, 0.1)) != PMsensorErrSuccess) {
        Serial.print("PM data Error = ");
        Serial.println(err);
        //delay(3000);
        //return;
      }
      // ****************************
      // [END] PM Sensor (GP2Y1014AU0F)
      // ****************************

      // ****************************
      // [START] Serial Print
      // ****************************
      Serial.print(dhtTemp);
      Serial.print("°C ");
      Serial.print(dhtHumid);
      Serial.print("% ");
      Serial.print(PM2p5);
      Serial.print("ug/m3 ");
      //Serial.print("SW : ");
      //Serial.print(statSW);
      Serial.println("");
      // ****************************
      // [END] Serial Print
      // ****************************

      delayCnt = 0;

      // ****************************
      // [START] Display
      // ****************************
      
        // Clear the buffer.
      display.clearDisplay();
      display.setTextSize(1);
      display.setTextColor(WHITE);
      display.setCursor(0,0);
      
      display.println("Air Tower V1.0");
      
      display.print("Temp = ");
      display.print(dhtTemp);
      display.println("C");
    
      display.print("Humidity = ");
      display.print(dhtHumid);
      display.println("%");
    
      display.print("PM2.5 = ");
      display.print(PM2p5);
      display.println("ug/m3");
    
      display.display();
      // ****************************
      // [END] Display
      // ****************************
  }
  
  // ****************************
  // [START] Touch SW
  // ****************************
  int statSW = digitalRead(SW);
  // ****************************
  // [END] Touch SW
  // ****************************

  // ****************************
  // [START] NeoPixel
  // ****************************  
  if(statSW == 1){
    for(int i=0; i<NUMPIXELS; i++){
      pixels.setPixelColor(i, pixels.Color(150, 150, 150));
    }
    pixels.show();

    digitalWrite(FAN, HIGH);
  }
  else{
    pixels.clear();
    pixels.show();

    digitalWrite(FAN, LOW);
  }
  // ****************************
  // [END] NeoPixel
  // ****************************



  

}

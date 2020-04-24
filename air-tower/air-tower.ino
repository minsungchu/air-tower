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

// Blynk Port
// Temperature : V0
// Humidity : V1
// PM : V2

#include <DHT.h>
#include <PMsensor.h>
#include <Adafruit_NeoPixel.h>

#include <ESP8266WiFi.h>
#include <time.h>
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#define OLED_RESET 0
Adafruit_SSD1306 display(OLED_RESET);

#include <BlynkSimpleEsp8266.h>

// DHT11
#define DHTPIN D4         // DHT Digital Pin
#define DHTTYPE DHT11     // DHT Model - DHT11
DHT dht(DHTPIN, DHTTYPE); // Initialize DHT sensor.

// PM sensor(GP2Y1014AU0F)
PMsensor PM;

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

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "vvtvziNZKUWGT6e77KIhBf-zXICGuLRJ";
BlynkTimer timer;

int delayCnt = 0;

void setup() {
  // init Serial Communication
  Serial.begin(9600);
  Serial.println("Air Tower ver1.0, April 2020");

  // init DHT11 sensor
  dht.begin();  

  // init PM sensor
  // Digital Pin(infrared LED pin, D3(=GPIO 0))
  // Analog Pin(sensor pin, A0)
  PM.init(D3, 0);  

  // init Neopixel LED
  pixels.begin();
  
  // init OLED Display
  display.begin();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(WHITE);
  display.setCursor(0,0);
  display.println("Air Tower V1.0");
  display.display();

  // Setting pinmode of Touch SW
  pinMode(SW, INPUT); 

  // Setting pinmode of FAN
  pinMode(FAN, OUTPUT);

  // init Blynk app
  Blynk.begin(auth, ssid, password);
}

void loop() {

  // Wait a few seconds between measurements.
  delay(100);

  Blynk.run();
  
  delayCnt++;
  float dhtHumid = 0;
  float dhtTemp = 0;
  float dhtTempF = 0;
  float PM2p5 = 0;
  if(delayCnt > 30){
      // ****************************
      // [START] DHT11 Sensor
      // ****************************
      
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
      Serial.println("");
      // ****************************
      // [END] Serial Print
      // ****************************


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
      display.println("°C");
    
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

      Blynk.virtualWrite(V0, dhtTemp);
      Blynk.virtualWrite(V1, dhtHumid);
      Blynk.virtualWrite(V2, PM2p5);
  
      delayCnt = 0;
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

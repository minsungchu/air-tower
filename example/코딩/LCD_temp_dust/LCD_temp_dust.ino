#include <SimpleDHT.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PMsensor.h>

PMsensor PM;
// for DHT11, 
//      VCC: 5V or 3V
//      GND: GND
//      DATA: 6
int pinDHT11 = 6;
SimpleDHT11 dht11(pinDHT11);
LiquidCrystal_I2C lcd(0x3F, 16, 2);

void setup()
{
  Serial.begin(9600);
  PM.init(2, A0);
	lcd.begin();
	lcd.backlight();
  lcd.clear();
  lcd.setCursor(0,0);
	lcd.print("Hello, world!");
  lcd.setCursor(0,1);
  lcd.print("HaHaHa!");
  delay(1000);
  lcd.begin();   
}

void loop()
{
  // start working...
  Serial.println("=================================");
  Serial.println("Sample DHT11...");
  
  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err);delay(1000);
    return;
  }
  
  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, "); 
  Serial.print((int)humidity); Serial.println(" H");
  Serial.println("=================================");
  Serial.println("Read PM2.5");
  
  float data = 0;
  int dust_err = PMsensorErrSuccess;
  if ((err = PM.read(&data, true, 0.1)) != PMsensorErrSuccess) {
    Serial.print("data Error = ");
    Serial.println(dust_err);
    delay(3000);
    return;
  }
  
  Serial.println(data);
  delay(3000);  
  // DHT11 sampling rate is 1HZ.
  delay(1500);
  //----------------------ㅣlcd part 시작
  lcd.setCursor(0,0);
  lcd.print("T : ");
  lcd.setCursor(5,0);
  lcd.print(temperature);
  lcd.setCursor(9,0);
  lcd.print("H : ");
  lcd.setCursor(13,0);
  lcd.print(humidity);  
  lcd.setCursor(0,1);
  lcd.print("pm2.5 : ");
  lcd.setCursor(9,1);
  lcd.print(data);
  //----------------------ㅣlcd part 끝  
}

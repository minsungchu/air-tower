//YWROBOT
//Compatible with the Arduino IDE 1.0
//Library version:1.1
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <PMsensor.h>

#include <SimpleDHT.h>
// for DHT11,
//      VCC: 5V or 3V
//      GND: GND
//      DATA:6
int pinDHT11 = 6;
SimpleDHT11 dht11;

PMsensor PM;
LiquidCrystal_I2C lcd(0x27, 16, 2); // set the LCD address to 0x27 for a 16 chars and 2 line display
// 0x27은 LCD의 주소입니다.

int redPin = 3;
int greenPin = 9;
int bluePin = 5;

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  Serial.begin(9600);
  PM.init(2, A0);
  lcd.init();                      // initialize the lcd ,LCD 초기화

  // Print a message to the LCD.
  lcd.backlight();
  lcd.setCursor(3, 0); //LCD 첫번째 줄을 의미한다.3은 3번째칸, 0은 첫번째 줄
  lcd.print("Hello, world!");
  lcd.setCursor(0, 1);
  lcd.print("Ywrobot Arduino!");
  delay(1000);
  lcd.init(); //LCD 초기화
}


void loop()
{

  temp_sensing();
}
void temp_sensing() {
  // //DHT11 start working....start
  Serial.println("=================================");
  Serial.println("Sample DHT11...");

  // read without samples.
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(pinDHT11, &temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.println(err); delay(1000);
    return;
  }

  Serial.print("Sample OK: ");
  Serial.print((int)temperature); Serial.print(" *C, ");
  Serial.print((int)humidity); Serial.println(" H");

  // DHT11 sampling rate is 1HZ.
  delay(1500);
  //DHT11 start working....end
  Serial.println("=================================");
  Serial.println("Read PM2.5");

  float data = 0;
  int dust_err = PMsensorErrSuccess;
  if ((dust_err = PM.read(&data, true, 0.1)) != PMsensorErrSuccess) {//먼저 가져오는 값을 얼마로 할지(즉, 초기값을) 0.1로 잡음
    Serial.print("data Error = ");
    Serial.println(err);
    delay(1000);
    return;
  }

  Serial.println(data);
  delay(1000);

  //------------------------LCD part 시작

  lcd.setCursor(0, 0); //
  lcd.print("T : ");
  lcd.setCursor(4, 0);// 4은 4번째칸
  lcd.print(temperature);
  lcd.print((char)0xdf);
  lcd.setCursor(8, 0); //
  lcd.print("H : ");
  lcd.setCursor(12, 0);// 4은 4번째칸
  lcd.print(humidity);
  lcd.print("%");
  lcd.setCursor(0, 1); //
  lcd.print("PM2.5:");
  lcd.setCursor(6, 1); //
  lcd.print(data);
  lcd.print("ug/m3");

  //------------------------LCD part 끝

  if (data <= 16)
  {
    setColor(0, 0, 255);
  }
  else if (16 < data <= 36)
  {
    setColor(0, 255, 0);
  }
  else if (36 < data < 80)
  {
    setColor(150, 255, 0);
  }
  else
  {
    setColor(0, 0, 255);
  }

}
void setColor(int red, int green, int blue)
{
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);
}

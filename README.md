# air-tower

### 1.Wemos pro mini 보드매니저 및 usb 드라이버

1. 참조사이트 : https://ieatt.tistory.com/47
2. USB 드라이버 깃헙 : https://github.com/adrianmihalko/ch340g-ch34g-ch34x-mac-os-x-driver

### 2.라이브러리

1. Adafruit 기본라이브러리 깃헙 : https://github.com/adafruit/Adafruit_Sensor
2. DHT 센서 라이브러리 깃헙 : https://github.com/adafruit/DHT-sensor-library
3. NeoPixel 라이브러리
4. PMsensor 라이브러리 : 먼지센서 라이브러리

### 3.모바일 앱 / 와이파이 연동

1. Blynk 앱 활용 : https://ko.howto-wp.com/55070-Blink-a-LED-With-Blynk-App-Wemos-D1-Mini-Pro-41

   1. Blynk 앱 활용시, 테스트용 앱을 만드는 것은 무료이나, 앱 퍼블리시는 월 \$166 유료임.
   2. 테스트용 앱을 만들때에도, 대시보드의 아이템들을 사용할때마다 포인트가 차감되며, 기본으로 제공되는 2000포인트 소진시에는 포인트를 충전해야 하고 이것은 유료임.

2. OLED & 와이파이 연동
   1. http://blog.daum.net/rockjjy99/2615 : 빌트인포트를 4에서 0으로 수정하고, begin함수의 인자값 삭제해야 함.
   2. https://automatedhome.party/2017/04/17/connect-an-inexpensive-oled-display-to-a-esp8266wemos-d1-mini/ : 그대로 실행 가능

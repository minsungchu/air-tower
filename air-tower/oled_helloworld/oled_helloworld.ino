// U8glib 헤더파일 필요

#include "U8glib.h" //U8glib 헤더파일 호출

U8GLIB_SSD1306_128X64 u8g(U8G_I2C_OPT_NONE); // 사용IC와 통신방법에 따른 설정

void draw() { // 화면출력함수
  u8g.setFont(u8g_font_unifont); // 폰트설정
  u8g.drawStr( 0, 20, "Hello World!"); // 좌표 및 출력 문구 설정
}

void setup() { //초기화

}

void loop() { // 무한루프
  u8g.firstPage(); // 첫번째 페이지설정
  do {
    draw(); // draw에서 설정했던 화면을 출력
  } while( u8g.nextPage() ); // 다음페이지 설정이 있다면 호출
  delay(1000); // 딜레이 1초
}

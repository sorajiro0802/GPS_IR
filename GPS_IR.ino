#include <M5StickC.h>
#include <TinyGPSPlus.h>

HardwareSerial GPSRaw(2);
TinyGPSPlus gps;
RTC_TimeTypeDef TimeStruct;
int cnt = 0;

void setup() {
  M5.begin();
  M5.Lcd.setRotation(3);
  GPSRaw.begin(9600, SERIAL_8N1, 33, 32);
  while (GPSRaw.available() > 0) {
    if (gps.encode(GPSRaw.read())) break;
  }
  M5.Lcd.printf("RTC Setting...");

  TimeStruct.Hours = gps.time.hour();
  TimeStruct.Minutes = gps.time.minute();
  TimeStruct.Seconds = gps.time.second();
  M5.Rtc.SetTime(&TimeStruct);
}

void loop() {
  M5.Lcd.setCursor(0, 0, 2);
  M5.Lcd.fillScreen(BLACK);
  M5.Lcd.printf("----- GPS TEST -----\n");
  while (GPSRaw.available() > 0) {
    if (gps.encode(GPSRaw.read())) {
      break;
    }
  }
  int timediff = 9;
  if (gps.time.isValid()) {
    M5.Lcd.printf("TIME: %02d:%02d:%02d\n", gps.time.hour(), gps.time.minute(), gps.time.second());
    // Serial.println(gps.time.value());
  }
  if (gps.satellites.isValid()) {
    M5.Lcd.printf("SATELLITE NUM: %d\n", gps.satellites.value());
  }
  if (gps.location.isValid()) {
    M5.Lcd.printf("LAT: %.6f\n", gps.location.lat());
    M5.Lcd.printf("LNG: %.6f\n", gps.location.lng());
  }
  /*Serial.printf("%d\t", gps.time.value());
  M5.Rtc.GetTime(&TimeStruct);
  Serial.printf("%02d:%02d:%02d\n", TimeStruct.Hours, TimeStruct.Minutes, TimeStruct.Seconds);*/
  delay(500);
}

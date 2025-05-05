#include <FastLED.h>
#define SENSOR_PIN A0
#define LED_PIN 6
#define NUM_LEDS 19

CRGB leds[NUM_LEDS];
void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<SK6812, LED_PIN, GRB>(leds, NUM_LEDS);
  FastLED.setBrightness(150);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int lectura = analogRead(SENSOR_PIN);
  float voltaje = lectura * (5.0 / 1023);
  float temp = (voltaje - 0.5) * 100;

  CRGB color;

  if(temp <= 20){
    color = CRGB::Blue;
  } else if (temp <= 25){
    color = CRGB::Green;
  } else if (temp <= 30) {
    color = CRGB::Yellow;
  } else {
    color = CRGB::Red;
  }

  fill_solid(leds, NUM_LEDS, color);
  FastLED.show();

  delay(1000);
}

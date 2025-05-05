#include <FastLED.h> //incluir librería
#define LED_PIN 6 //pin salida
#define NUM_LEDS 19 //numero de leds
#define BRIGHTNESS 120 //Brillo (0-255)
#define LED_TYPE SK6812 //tipo de led
#define COLOR_ORDER GRB //orden de los colores rojo, verde y azul

CRGB leds[NUM_LEDS];

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS); //inicializar
  FastLED.setBrightness(BRIGHTNESS); //ajustar el brillo
  
  leds[0] = CRGB::Blue; //Añadir el color azul al primer LED
  //leds[0] = CRGB::Red; // El primer LED se pone rojo
  //leds[1] = CRGB(0,255,0); // El segundo LED se pone verde con valores RGB directos
  //leds[2].r = 255; // Puedes cambiar solo el rojo del tercer LED

  FastLED.show(); //mostrar el color

}

void loop() {
  // put your main code here, to run repeatedly:

}

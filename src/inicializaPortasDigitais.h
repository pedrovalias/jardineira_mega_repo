#include <Arduino.h>

void inicializaPortasDigitais() {
  // Define os pinos como saída e inicializa as válvulas de agua como desligadas
  pinMode(pinoValvula1, OUTPUT);
  digitalWrite(pinoValvula1, HIGH);

  pinMode(pinoValvula2, OUTPUT);
  digitalWrite(pinoValvula2, HIGH);

  pinMode(pinoValvula3, OUTPUT);
  digitalWrite(pinoValvula3, HIGH);

  pinMode(pinoValvula4, OUTPUT);
  digitalWrite(pinoValvula4, HIGH);

  pinMode(pinoValvula5, OUTPUT);
  digitalWrite(pinoValvula5, HIGH);

  // Inicializando as instâncias das fitas LED e definindo os pinos de saída
  FastLED.addLeds<NEOPIXEL, 22>(leds[0], NUM_LEDS_POR_FITA);    //Fita LED 1 no pin 22
  FastLED.addLeds<NEOPIXEL, 23>(leds[1], NUM_LEDS_POR_FITA);    //Fita LED 2 no pin 23
  FastLED.addLeds<NEOPIXEL, 24>(leds[2], NUM_LEDS_POR_FITA);    //Fita LED 3 no pin 24
  FastLED.addLeds<NEOPIXEL, 25>(leds[3], NUM_LEDS_POR_FITA);    //Fita LED 4 no pin 25
  FastLED.addLeds<NEOPIXEL, 26>(leds[4], NUM_LEDS_POR_FITA);    //Fita LED 5 no pin 26

  //Define o detector de água como entrada - funciona como um botão
  pinMode(sensorNivelMaximo1, INPUT);
  pinMode(sensorNivelMaximo2, INPUT);
  pinMode(sensorNivelMaximo3, INPUT);
  pinMode(sensorNivelMaximo4, INPUT);
  pinMode(sensorNivelMaximo5, INPUT);
}
#include <Arduino.h>

/* Funcao que aciona os LEDS da jardineira, de acordo com a cor passada por parametro
 * Cada cor tem uma definicao de acao personalizada 
*/
void ativarLed(char corLed[10], int jardineira){
  int NUM_FITA = 0;

  Serial.println("######## ENTROU NA FUNCAO DE LEDS #########");

  if(jardineira == 1){
    NUM_FITA = 0;
    Serial.println("LED Jardineira: " + String(jardineira));
  } 
  else if(jardineira == 2){
    NUM_FITA = 1;
    Serial.println("LED Jardineira: " + String(jardineira));
  }
  else if(jardineira == 3){
    NUM_FITA = 2;
    Serial.println("LED Jardineira: " + String(jardineira));
  }
  else if(jardineira == 4){
    NUM_FITA = 3;
    Serial.println("LED Jardineira: " + String(jardineira));
  }
  else {
    NUM_FITA = 4;
    Serial.println("LED Jardineira: " + String(jardineira));
  }

  if(corLed == "vermelho"){
    Serial.println("# exibe LED vermelho");
                         
    // Pisca o LED vermelho conforme configuracao desejada
    fill_solid(leds[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Red);
    FastLED.show();
    delay(700);
    fill_solid(leds[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Black);
    FastLED.show();
    delay(700);
    fill_solid(leds[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Red);
    FastLED.show();
    delay(700);
    fill_solid(leds[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Black);
    FastLED.show();
    delay(700);
    fill_solid(leds[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Red);
    FastLED.show();
    delay(2000);
    fill_solid(leds[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Black);
    FastLED.show();
  }

  if(corLed == "verde"){
    Serial.println("# exibe LED verde");

    // Liga LED verde e desliga depois de 5 segundos
    fill_solid(leds[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Green);  // Desliga LED azul
    FastLED.show();
    delay(5000);                    
    fill_solid(leds[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Black);
    FastLED.show();
  }

  if(corLed == "azul"){
    Serial.println("exibe LED azul");

    // Liga LED azul por 2 segundos
    fill_solid(leds[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Blue);
    FastLED.show();  // Desliga LED azul
  }

  if(corLed == "rosa"){
    Serial.println("# exibe LED rosa");

    // Liga LED rosa por 2 segundos
    fill_solid(leds[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Pink);  // Desliga LED azul
    FastLED.show();
    delay(2000);
    fill_solid(leds[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Black);
    FastLED.show();
  } 

  if(corLed == "rainbow"){
    Serial.println("# exibe LED rainbow");

    for (int j = 0; j < 255; j++) {
      for (int i = 0; i < NUM_LEDS_POR_FITA; i++) {
        leds[NUM_FITA][i] = CHSV(i - (j * 2), SATURATION, BRIGHTNESS); /* Quanto maior o valor, menor o fade */ 
      }
      FastLED.show();
      delay(25);
    }
  }
  
  return;
}

// Funcao para desligar LED da jardineira
void desligarTodasFitasLed(){ 
 // This outer loop will go over each strip, one at a time
  for(int x = 0; x < NUM_FITAS_LED; x++) {
    // This inner loop will go over each led in the current strip, one at a time
    for(int i = 0; i < NUM_LEDS_POR_FITA; i++) {
      leds[x][i] = CRGB::Black;
      FastLED.show();
      delay(100);
    }
  }
 return;
}


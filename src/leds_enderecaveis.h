#include <Arduino.h>

/* Funcao que aciona os LEDS da jardineira, de acordo com a cor passada por parametro
 * Cada cor tem uma definicao de acao personalizada 
*/
void ativarLed(char corLed[10], int jardineira)
{
  int NUM_FITA = 0;
  CRGB fitaLED[NUM_FITA][NUM_LEDS_POR_FITA];

  if(jardineira == 1){
    NUM_FITA = 0;
    // fill_solid(teste[x], NUM_LEDS_POR_FITA, CRGB::Red);
    // leds[0][20] = CRGB::Red;
  } 
  else if(jardineira == 2){
    NUM_FITA = 1;
  }
  else if(jardineira == 3){
    NUM_FITA = 2;
  }
  else if(jardineira == 4){
    NUM_FITA = 3;
  }
  else {
    NUM_FITA = 4;
  }
  if(corLed == "vermelho"){
                         
    // Pisca o LED vermelho conforme configuracao desejada
    fill_solid(fitaLED[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Red);
    delay(700);
    fill_solid(fitaLED[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Black);
    delay(700);
    fill_solid(fitaLED[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Red);
    delay(700);
    fill_solid(fitaLED[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Black);
    delay(700);
    fill_solid(fitaLED[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Red);
    delay(2000);
    fill_solid(fitaLED[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Black);
  }
  if(corLed == "verde"){
    // Liga LED verde e desliga depois de 5 segundos
    fill_solid(fitaLED[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Green);  // Desliga LED azul
    delay(5000);                    
    fill_solid(fitaLED[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Black);
  }
  if(corLed == "azul"){
    // Liga LED azul por 2 segundos
    fill_solid(fitaLED[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Blue);  // Desliga LED azul
    delay(2000);
    fill_solid(fitaLED[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Black);
  }
  if(corLed == "rosa"){
    // Liga LED rosa por 2 segundos
    fill_solid(fitaLED[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Pink);  // Desliga LED azul
    delay(2000);
    fill_solid(fitaLED[NUM_FITA], NUM_LEDS_POR_FITA, CRGB::Black);
  } 
  return;
}

// Funcao para desligar LED da jardineira
void desligarLeds(){ 
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
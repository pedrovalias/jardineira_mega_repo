#include <Arduino.h>

/* TODO:
  - utilizar ENUM para as cores LED (tentar tipar)
  - tentar melhorar a chamada das funções
*/

int atribuiFitaJardineira(int jardineira){
  int NUM_FITA = 0;

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

  return NUM_FITA;
}

// Pisca a fita LED na cor vermelha 3 vezes
void ledAlertaVasoCheio(int jardineira) {

  int NUM_FITA_JARDINEIRA = atribuiFitaJardineira(jardineira);

  Serial.println("######## FUNCAO LED_ALERTA_VASO_CHEIO #########");
  Serial.println("# NUM_FITA_JARDINEIRA: " + NUM_FITA_JARDINEIRA);
       
  fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Red);
  FastLED.show();
  delay(700);
  fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Black);
  FastLED.show();
  delay(700);
  fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Red);
  FastLED.show();
  delay(700);
  fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Black);
  FastLED.show();
  delay(700);
  fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Red);
  FastLED.show();
  delay(2000);
  fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Black);
  FastLED.show();
}

 // Liga a fita LED na cor verde e desliga depois de 5 segundos
void ledRegaFinalizada(int jardineira) {

  int NUM_FITA_JARDINEIRA = atribuiFitaJardineira(jardineira);

  Serial.println("######## FUNCAO LED_REGA_FINALIZADA #########");
  Serial.println("# NUM_FITA_JARDINEIRA: " + NUM_FITA_JARDINEIRA);

  fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Green);  // Desliga LED azul
  FastLED.show();
  delay(5000);                    
  fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Black);
  FastLED.show();
}

// Liga fita LED na cor azul por 2 segundos
void ledRegaEmAndamento(int jardineira){

  int NUM_FITA_JARDINEIRA = atribuiFitaJardineira(jardineira);

  Serial.println("######## FUNCAO LED_REGA_EM_ANDAMENTO #########");
  Serial.println("# NUM_FITA_JARDINEIRA: " + NUM_FITA_JARDINEIRA);

  fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Blue);
  FastLED.show();
  delay(2000);
  fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Black);
  FastLED.show();
}

void ledEfeitoArcoIris(int jardineira){
  int NUM_FITA_JARDINEIRA = atribuiFitaJardineira(jardineira);

  Serial.println("######## FUNCAO LED_EFEITO_ARCO_IRIS #########");
  Serial.println("# NUM_FITA_JARDINEIRA: " + NUM_FITA_JARDINEIRA);

  for (int j = 0; j < 255; j++) {
    for (int i = 0; i < NUM_LEDS_POR_FITA; i++) {
      leds[NUM_FITA_JARDINEIRA][i] = CHSV(i - (j * 2), SATURATION, BRIGHTNESS); /* Quanto maior o valor, menor o fade */ 
    }
    FastLED.show();
    delay(25);
  }
}

// Liga fita LED na cor rosa
void ledRosa(int jardineira) {
  int NUM_FITA_JARDINEIRA = atribuiFitaJardineira(jardineira);

  Serial.println("######## FUNCAO LED_ROSA #########");
  Serial.println("# NUM_FITA_JARDINEIRA: " + NUM_FITA_JARDINEIRA);

  fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Pink); 
  FastLED.show();
} 

/* Funcao que aciona os LEDS da jardineira, de acordo com a cor passada por parametro
 * Cada cor tem uma definicao de acao personalizada 
*/
void ativarLed(String corLed, int jardineira){

  int NUM_FITA_JARDINEIRA = atribuiFitaJardineira(jardineira);

  Serial.println("######## ENTROU NA FUNCAO DE LEDS #########");
  Serial.println("# NUM_FITA_JARDINEIRA: " + NUM_FITA_JARDINEIRA);

  if(corLed == "vermelho"){
    Serial.println("# exibe LED vermelho");
                         
    // Pisca o LED vermelho conforme configuracao desejada
    fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Red);
    FastLED.show();
    delay(700);
    fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Black);
    FastLED.show();
    delay(700);
    fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Red);
    FastLED.show();
    delay(700);
    fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Black);
    FastLED.show();
    delay(700);
    fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Red);
    FastLED.show();
    delay(2000);
    fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Black);
    FastLED.show();
  }

  if(corLed == "verde"){
    Serial.println("# exibe LED verde");

    // Liga LED verde e desliga depois de 5 segundos
    fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Green);  // Desliga LED azul
    FastLED.show();
    delay(5000);                    
    fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Black);
    FastLED.show();
  }

  if(corLed == "azul"){
    Serial.println("exibe LED azul");

    // Liga LED azul por 2 segundos
    fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Blue);
    FastLED.show();  // Desliga LED azul
  }

  if(corLed == "rosa"){
    Serial.println("# exibe LED rosa");

    // Liga LED rosa por 2 segundos
    fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Pink);  // Desliga LED azul
    FastLED.show();
    delay(2000);
    fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Black);
    FastLED.show();
  } 

  if(corLed == "rainbow"){
    Serial.println("# exibe LED rainbow");

    for (int j = 0; j < 255; j++) {
      for (int i = 0; i < NUM_LEDS_POR_FITA; i++) {
        leds[NUM_FITA_JARDINEIRA][i] = CHSV(i - (j * 2), SATURATION, BRIGHTNESS); /* Quanto maior o valor, menor o fade */ 
      }
      FastLED.show();
      delay(25);
    }
  }
  
  return;
}

void desligaFitaLed(int jardineira){

  int NUM_FITA_JARDINEIRA = atribuiFitaJardineira(jardineira);

  Serial.println("######## FUNCAO DESLIGA_FITA_LED #########");
  Serial.println("# NUM_FITA_JARDINEIRA: " + NUM_FITA_JARDINEIRA);

  fill_solid(leds[NUM_FITA_JARDINEIRA], NUM_LEDS_POR_FITA, CRGB::Black);
  FastLED.show();
}

// Função que desliga todas as fitas LED de todas as jardineiras
void desligarTodasFitasLed(){

  Serial.println("######## FUNCAO DESLIGAR_TODAS_FITAS_LED #########");

  // Esse loop externo passa por cada fita LED, uma por vez
  for(int x = 0; x < NUM_FITAS_LED; x++) {
    // Esse loop interno passa por cada LED na fita corrente, um por vez
    for(int i = 0; i < NUM_LEDS_POR_FITA; i++) {
      leds[x][i] = CRGB::Black;
      FastLED.show();
      delay(100);
    }
  }
  return;
}


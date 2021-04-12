#include <Arduino.h>

/* Funcao que aciona os LEDS da jardineira, de acordo com a cor passada por parametro
 * Cada cor tem uma definicao de acao personalizada 
*/
void ativarLed(char corLed[10], int jardineira)
{
  byte PINO_LED_R = 0;
  byte PINO_LED_G = 0;
  byte PINO_LED_B = 0;

  if(jardineira == 1){
    PINO_LED_R = PINO_LED_R1;
    PINO_LED_G = PINO_LED_G1;
    PINO_LED_B = PINO_LED_B1;
  }
  else if(jardineira == 2){
    PINO_LED_R = PINO_LED_R2;
    PINO_LED_G = PINO_LED_G2;
    PINO_LED_B = PINO_LED_B2;
  }
  else if(jardineira == 3){
    PINO_LED_R = PINO_LED_R3;
    PINO_LED_G = PINO_LED_G3;
    PINO_LED_B = PINO_LED_B3;
  }
  else if(jardineira == 4){
    PINO_LED_R = PINO_LED_R4;
    PINO_LED_G = PINO_LED_G4;
    PINO_LED_B = PINO_LED_B4;
  }
  else {
    PINO_LED_R = PINO_LED_R5;
    PINO_LED_G = PINO_LED_G5;
    PINO_LED_B = PINO_LED_B5;
  }
  if(corLed == "vermelho"){
    // Liga o LED vermelho e desliga o LED azul e verde
    digitalWrite(PINO_LED_R, HIGH); // Liga LED vermelho
    digitalWrite(PINO_LED_G, LOW);  // Desliga LED verde
    digitalWrite(PINO_LED_B, LOW);  // Desliga LED azul
    delay(700);                      

    // Pisca o LED vermelho conforme configuracao desejada
    digitalWrite(PINO_LED_R, LOW);  
    delay(700);
    digitalWrite(PINO_LED_R, HIGH);
    delay(700);
    digitalWrite(PINO_LED_R, LOW);
    delay(700);
    digitalWrite(PINO_LED_R, HIGH);
    delay(2000);
    digitalWrite(PINO_LED_R, LOW);
  }
  if(corLed == "verde"){
    // Liga LED verde e desliga LED vermelho e verde
    digitalWrite(PINO_LED_R, LOW);  // Desliga LED vermelho
    digitalWrite(PINO_LED_G, HIGH); // Liga LED verde
    digitalWrite(PINO_LED_B, LOW);  // Desliga LED azul
    delay(5000);                    
    digitalWrite(PINO_LED_G, LOW);  
  }
  if(corLed == "azul"){
    // Liga LED azul e desliga LED vermelho e verde
    digitalWrite(PINO_LED_R, LOW);  // Desliga LED vermelho
    digitalWrite(PINO_LED_G, LOW);  // Desliga LED verde
    digitalWrite(PINO_LED_B, HIGH); // Liga LED azul
    delay(2000);                    
  }
  if(corLed == "rosa"){
    // Liga LED vermelho e azul para criar rosa
    digitalWrite(PINO_LED_R, HIGH); // Liga LED vermelho
    digitalWrite(PINO_LED_G, LOW);  // Desliga LED verde
    digitalWrite(PINO_LED_B, HIGH); // Liga LED azul
    delay(2000);                    
    digitalWrite(PINO_LED_R, LOW);  // Desliga LED vermelho
    digitalWrite(PINO_LED_B, LOW);  // Desliga LED azul
  } 
  return;
}

// Funcao para desligar LED da jardineira
//void desligarLed(){ 
//  digitalWrite(PINO_LED_R, LOW); // Liga LED vermelho
//  digitalWrite(PINO_LED_G, LOW);  // Desliga LED verde
//  digitalWrite(PINO_LED_B, LOW); // Liga LED azul
//  return;
//}
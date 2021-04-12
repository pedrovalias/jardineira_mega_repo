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

  // Define os LEDS informativos como saída
  pinMode(PINO_LED_R1, OUTPUT); // LED vermelho
  pinMode(PINO_LED_G1, OUTPUT); // LED verde
  pinMode(PINO_LED_B1, OUTPUT); // LED azul

  pinMode(PINO_LED_R2, OUTPUT); // LED vermelho
  pinMode(PINO_LED_G2, OUTPUT); // LED verde
  pinMode(PINO_LED_B2, OUTPUT); // LED azul

  pinMode(PINO_LED_R3, OUTPUT); // LED vermelho
  pinMode(PINO_LED_G3, OUTPUT); // LED verde
  pinMode(PINO_LED_B3, OUTPUT); // LED azul

  pinMode(PINO_LED_R4, OUTPUT); // LED vermelho
  pinMode(PINO_LED_G4, OUTPUT); // LED verde
  pinMode(PINO_LED_B4, OUTPUT); // LED azul

  pinMode(PINO_LED_R5, OUTPUT); // LED vermelho
  pinMode(PINO_LED_G5, OUTPUT); // LED verde
  pinMode(PINO_LED_B5, OUTPUT); // LED azul

  //Define o detector de água como entrada - funciona como um botão
  pinMode(sensorNivelMaximo1, INPUT);
  pinMode(sensorNivelMaximo2, INPUT);
  pinMode(sensorNivelMaximo3, INPUT);
  pinMode(sensorNivelMaximo4, INPUT);
  pinMode(sensorNivelMaximo5, INPUT);
}
#include <Arduino.h>

// #################################        JARDINEIRA 1        #################################
// Define os pinos dos sensores dos sistema
const int sensorNivelMaximo1 = 2;
const int pinoSensorHumidade1 = A0;
const int pinoValvula1 = 7;

// Inicializa todos os sensores zerados
//int nivelAgua = 0;          // variável que inicializa o nivel como vazio
int nivelMaximo1 = 0;          // inicializador deteccao liquido
int umidadeSolo1 = 0;
//#################################################################################################

// #################################        JARDINEIRA 2        #################################
// Define os pinos dos sensores dos sistema
const int sensorNivelMaximo2 = 3;
const int pinoSensorHumidade2 = A1;
const int pinoValvula2 = 8;

// const int ledNivelAgua2 = 10;

// Inicializa todos os sensores zerados
//int nivelAgua = 0;          // variável que inicializa o nivel como vazio
int nivelMaximo2 = 0;          // inicializador deteccao liquido
int umidadeSolo2 = 0;
//#################################################################################################

// #################################        JARDINEIRA 3        #################################
// Define os pinos dos sensores dos sistema
const int sensorNivelMaximo3 = 4;
const int pinoSensorHumidade3 = A2;
const int pinoValvula3 = 9;

// Inicializa todos os sensores zerados
//int nivelAgua = 0;          // variável que inicializa o nivel como vazio
int nivelMaximo3 = 0;          // inicializador deteccao liquido
int umidadeSolo3 = 0;
//#################################################################################################

// #################################        JARDINEIRA 4        #################################
// Define os pinos dos sensores dos sistema
const int sensorNivelMaximo4 = 5;
const int pinoSensorHumidade4 = A3;
const int pinoValvula4 = 10;

// Inicializa todos os sensores zerados
//int nivelAgua = 0;          // variável que inicializa o nivel como vazio
int nivelMaximo4 = 0;          // inicializador deteccao liquido
int umidadeSolo4 = 0;
//#################################################################################################

// #################################        JARDINEIRA 5        #################################
// Define os pinos dos sensores dos sistema
const int sensorNivelMaximo5 = 6;
const int pinoSensorHumidade5 = A4;
const int pinoValvula5 = 11;

// Inicializa todos os sensores zerados
//int nivelAgua = 0;          // variável que inicializa o nivel como vazio
int nivelMaximo5 = 0;          // inicializador deteccao liquido
int umidadeSolo5 = 0;
//#################################################################################################

// const int iteraSaidasDigitais() {
//     for(int i = 0 ; i < 5 ; i++){
//         const int sensorNivelMaximo[i] = {i + 2}; // itera portas de 2 a 6
//         const int pinoValvula[i] = {i + 7}; // itera portas de 7 a 11
//         const int PINO_LED_R[i] = {i + 22};      // Vermelho  itera portas 22 a 26
//         const int PINO_LED_G[i] = {i + 27};      // Verde     itera portas 27 a 31
//         const int PINO_LED_B[i] = {i + 32};      // Azul      itera portas 32 a 36
//         int nivelMaximo[i] = {0};
//         int umidadeSolo[i] = {0};

//         return pinoValvula[i];
//     }
// }

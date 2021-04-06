#include <Arduino.h>

/* ******************** Rega Automática Pedrorv ********************
   Criado por: Pedro Henrique Ravanelli Valias
   Rev.: 01
   Data: 15.06.2020

   Guia de conexão:
   LCD RS: pino 12
   LCD Enable: pino 11
   LCD D4: pino 5
   LCD D5: pino 4
   LCD D6: pino 3
   LCD D7: pino 2
   LCD R/W: GND
   LCD VSS: GND
   LCD VCC: VCC (5V)
   Potenciômetro de 10K terminal 1: GND
   Potenciômetro de 10K terminal 2: V0 do LCD (Contraste)
   Potenciômetro de 10K terminal 3: VCC (5V)
   Sensor de umidade do solo A0: Pino A0
   Módulo Relé (Válvula): Pino 10
   Sensor indicador de ninvel de agua: Pino A5
   Sensor indicador de nivel máximo de água: Pino 7
   LED indicador de nível máximo de água: Pino 13

   Este código utiliza a biblioteca LiquidCrystal

   Library originally added 18 Apr 2008
   by David A. Mellis
   library modified 5 Jul 2009
   by Limor Fried (http://www.ladyada.net)
   
 ***************************************************************************** */

// Inclui a biblioteca do LCD:
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <jardineiras.h>            // Arquivo externo com as declarações de todas as pinagens das jardineiras
#include <DHT.h>

// Define o pino analógico A5 para o sensor nivel de agua  
// #define nivelAguaPin A5 // DESCOMENTAR SE FOR UTILIZAR O SENSOR DE NIVEL DE LIQUIDOS

// Define a conexão entre o Arduino e o Display LCD utilizando a biblioteca I2C
LiquidCrystal_I2C lcd(0x27,16,2); // Endereco, colunas, linhas

// Constantes sensor Temeperatura/Umidade do ar
#define DHTPIN 0 // Pino D3
#define DHTTYPE DHT11 
DHT dht(DHTPIN,DHTTYPE);
int contadorAltaTemperatura = 0;
int contadorBaixaTemperatura = 0;
boolean autoAjusteLoop = true;

// const int ledNivelAgua = 10;

// Variaveis constantes do programa
int limiarSeco = 0;             // Porcentagem determinada para umidade do solo aceitavel 
int tempoRega = 0;              // Tempo de acao da rega em segundos
int tempoLoop = 0;              // Tempo que vai levar a cada acao de regagem em horas
int tempoLoopControle = 0;
const int delayLoop = 5;
const int quatroHoras = 4;//2880;   // 4*3600/delayLoop = 2880 = 4h

// Inicializa contador de execucoes do programa
int contador = 0;

// Inicializa uma variavel para limpreza do LCD
bool limpaLCD = true;

// Declaracao das funcoes do programa
void inicializaPortasDigitais();
void info_serial();
void escreveLCD(bool limpa, int coluna, int linha, String texto);
void realiza_rega(int tipoRega, int jardineira);
void regar(int jardineira);
int verificaNivel(int jardineira);
void ativarLed(char corLed[10], int jardineira);
void executa_loop();
int obterDadosDHT(int i);

//=======================================================================================================
//                                            INICIO SETUP
//=======================================================================================================
void setup() {

  Serial.begin(115200);   // Inicializa o console serial 
  lcd.init();             // Inicializa o visor LCD
  lcd.backlight();        // Inicializa a iluminacao do LCD
  dht.begin();            // Inicializa o sensor DHT (Temperatura e umidade relativa do ambiente)

  limiarSeco = 75;     // Porcentagem determinada para humidade do solo aceitavel 
  tempoRega = 9;       // Tempo de acao da rega em segundos
  tempoLoop = 2;       // Tempo em horas de intervalo entre as acoes de rega

  // Define os pinos como saída e inicializa as válvulas de agua como desligadas
  inicializaPortasDigitais();

  // pinMode(ledNivelAgua, OUTPUT);

  info_serial();

  delay(500);
  //============================================ FIM SETUP ================================================
}

//=======================================================================================================
//                                            INICIO LOOP
//=======================================================================================================
void loop() {
  
  // Lê o estado do pino destinado ao detector de agua
  //  ######### detecAgua = digitalRead(sensorNivelMaximo);
  
  Serial.println("# SISTEMA INICIADO");

  escreveLCD(limpaLCD,0,0,"Rega Automatica ");
  
  delay(2000);

  // Se for a primeira execucao do programa (contador = 0), realiza a rega
  if(contador < 1){
      realiza_rega(contador,1);
      realiza_rega(contador,2);
      realiza_rega(contador,3);
      realiza_rega(contador,4);
      realiza_rega(contador,5);
  }

  escreveLCD(limpaLCD,0,0,"Rega Automatica ");

  executa_loop();

  realiza_rega(contador,1);
  realiza_rega(contador,2);
  realiza_rega(contador,3);
  realiza_rega(contador,4);
  realiza_rega(contador,5);

  contador ++;

  Serial.print("Execuções do programa: ");
  Serial.println(contador);
  Serial.println("_______________________________");
  Serial.println(" ");
  //============================================ FIM LOOP ================================================
}

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

void info_serial() {
  Serial.println("");
  Serial.println("#### PARÂMETROS DO SISTEMA ####");
  Serial.print("Tempo loop:  "); 
  Serial.println(tempoLoop);
  Serial.print("Tempo rega: ");
  Serial.println(tempoRega);
  Serial.print("Limiar Seco: ");
  Serial.println(limiarSeco);
  Serial.println("-------------------------------");
}

/* Funcao para escrever no LCD
   * Limpa o LCD  
   * Posiciona o cursor do LCD na coluna 0 linha 1
   * (Obs: linha 1 é a segunda linha, a contagem começa em 0
   * Exibe a mensagem no Display LCD
  */
void escreveLCD(bool limpa, int coluna, int linha, String texto) {
  if(limpa == true){
    lcd.clear();
  }
  lcd.setCursor(coluna, linha);
  lcd.print(texto);
}

void realiza_rega(int tipoRega, int jardineira){

  int umidadeSolo = 0;
  byte pinoValvula = 0;

  if(jardineira == 1){
    umidadeSolo = umidadeSolo1;
    pinoValvula = pinoValvula1;
  }
  else if( jardineira == 2){
    umidadeSolo = umidadeSolo2;
    pinoValvula = pinoValvula2;
  }
  else if( jardineira == 3){
    umidadeSolo = umidadeSolo3;
    pinoValvula = pinoValvula3;
  }
  else if( jardineira == 4){
    umidadeSolo = umidadeSolo4;
    pinoValvula = pinoValvula4;
  }
  else {
    umidadeSolo = umidadeSolo5;
    pinoValvula = pinoValvula5;
  } 
  
  if(tipoRega == 0){
    Serial.println("Primeira Rega - inicialização");
    regar(jardineira);
  } else {
    
    /* Verifica condição de humidade do solo
     * Se solo estiver com humidade abaixo do valor estipulado, segue com a rega
    */
    if(umidadeSolo < limiarSeco) {
      regar(jardineira);
    } else {
      // Posiciona o cursor do LCD na coluna 0 linha 1
      digitalWrite(pinoValvula, HIGH);
      escreveLCD(!limpaLCD,0,1,"Solo Encharcado ");
      Serial.println("Solo encharcado");
      ativarLed("vermelho", jardineira);
    }
  }
  return;
}

// Inicializa acao de rega da jardineira   
void regar(int jardineira){
  // Como esta regando, reinicializa o contator de leitura da temperatura
  contadorAltaTemperatura = 0;
  contadorBaixaTemperatura = 0;
  
  byte pinoValvula = 0;

  if(jardineira == 1){
    pinoValvula = pinoValvula1;
  }
  else if(jardineira == 2){
    pinoValvula = pinoValvula2;
  }
  else if(jardineira == 3){
    pinoValvula = pinoValvula3;
  }
  else if(jardineira == 4){
    pinoValvula = pinoValvula4;
  }
  else {
    pinoValvula = pinoValvula5;
  }

  /* Se verificacao do sensor nivel maximo nao detectar contato com a agua
   * (sensor == LOW)
  */
  if(!verificaNivel(jardineira)){
    
    Serial.print("Iniciando Rega da Jardineira: ");
    Serial.println(jardineira);
    escreveLCD(1,0,0,"Jardineira");

    // Variavel de controle para saida do laco de repeticao
    int controle = 1;

    // Enquanto estiver na condição de controle, funciona regagem
    while(controle != 0){
        
      escreveLCD(!limpaLCD,0,1,"    Regando     ");

      // Ativa LED indicativo de processo de rega em andamento
      ativarLed("azul", jardineira);
      
      // Liga a valvula de agua
      digitalWrite(pinoValvula, LOW);
      Serial.print("Regando | estado válvula: ");
      Serial.println(pinoValvula);
      
      // Espera o tempo de rega estipulado na declaracao de constantes
      Serial.print("Tempo funcionamento válvula: ");
      Serial.println(tempoRega);
      for(int j=0; j<tempoRega*1000 ; j+=1000){
        Serial.println("for: j= ");
        Serial.println(j);
  
        /* Valida nivel de agua e atualiza condição de controle
        *  Se vaso ficou cheio, finaliza a regagem
        */
        if(verificaNivel(jardineira)){
          j = tempoRega * 1000;
          Serial.print("Tempo rega de controle: ");
          Serial.println(j);
          // Serial.println(s);
          controle = 0;
        } else {
            /* Vai atualizando a mensagem do LCD conforme andamento da regagem
            *  Divide o tempo determinado em 3 partes, exibindo um ponto de controle a cada parte atingida 
            */
          escreveLCD(!limpaLCD,0,1,"    Regando.    ");
          Serial.println("Regando.");
          
          if(j >= (tempoRega*1000)/3 && j < (tempoRega*1000)/3*2){
            escreveLCD(!limpaLCD,0,1,"    Regando..   ");
            Serial.println("Regando..");
          }
          if(j >= (tempoRega*1000/3)*2){
            escreveLCD(!limpaLCD,0,1,"    Regando...  ");
            Serial.println("Regando...");
          }
          
          delay(1000);  
        }
      }

      // digitalWrite(pinoValvula, LOW);
      lcd.clear();
      controle = 0;
    }
    // Desliga a valvula de agua e ativa LED informativo de conclusão de rega
    digitalWrite(pinoValvula, HIGH);
    Serial.println("Processo de rega finalizado");
    escreveLCD(limpaLCD,0,1,"REGA FINALIZADA!");
    Serial.println("Processo de rega finalizado");
    ativarLed("verde", jardineira);
    delay(3000);
  }
}

// Funcao que verifica se o nivel de agua esta no maximo ou nao 
int verificaNivel(int jardineira){

  byte nivelMaximo = 0;
  byte pinoValvula = 0;
  
  if(jardineira == 1){
    nivelMaximo = digitalRead(sensorNivelMaximo1);
    pinoValvula = pinoValvula1;
  }
  else if(jardineira == 2){
    nivelMaximo = digitalRead(sensorNivelMaximo2);
    pinoValvula = pinoValvula2;
  }
  else if(jardineira == 3){
    nivelMaximo = digitalRead(sensorNivelMaximo3);
    pinoValvula = pinoValvula3;
  }
  else if(jardineira == 4){
    nivelMaximo = digitalRead(sensorNivelMaximo4);
    pinoValvula = pinoValvula4;
  }
  else {
    nivelMaximo = digitalRead(sensorNivelMaximo5);
    pinoValvula = pinoValvula5;
  }

  // Se detectado contato com a agua 
  if(nivelMaximo == HIGH){
    escreveLCD(!limpaLCD,0,1,"Vaso esta cheio!");
    lcd.print("Vaso esta cheio!");

    // Desliga a valvula de agua, caso esteja ligada
    digitalWrite(pinoValvula, HIGH);

    // Liga LEDS informativos tanto da caixa quanto do vaso da jardineira
    // digitalWrite(ledNivelAgua, HIGH);
    ativarLed("vermelho", jardineira);
    delay(3000);
  } else {
    Serial.println("Vaso incompleto, permitir rega");

    // Desliga LED informativo da caixa
    // digitalWrite(ledNivelAgua, LOW);
  }
  Serial.print("Estado sensor nível: ");
  Serial.println(nivelMaximo);

  return nivelMaximo;
}

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

void executa_loop() {
   // Hora = 3600s/delay(5s) = 720s
  tempoLoopControle = tempoLoop;//(tempoLoop*3600)/delayLoop;

  int t = 0;

  obterDadosDHT(t);

  // Mede a umidade do solo a cada 3 segundos. Faz isso durante tempo estipulado (9 horas)
  for(int i=0; i < tempoLoopControle ; i++) { // Hora = 3600s/delay(5s) = 720s
    // t = i;

    i = obterDadosDHT(i);

    escreveLCD(limpaLCD,0,0,"Rega Automatica ");
    escreveLCD(!limpaLCD,0,1,"Umidade: ");           
    
    // Faz a leitura do sensor de umidade do solo
    umidadeSolo1 = analogRead(pinoSensorHumidade1);
    umidadeSolo2 = analogRead(pinoSensorHumidade2);
    umidadeSolo2 = analogRead(pinoSensorHumidade3);
    umidadeSolo2 = analogRead(pinoSensorHumidade4);
    umidadeSolo2 = analogRead(pinoSensorHumidade5);
    
    // Converte a variação do sensor de 0 a 1023 para 0 a 100
    umidadeSolo1 = map(umidadeSolo1, 1023, 0, 0, 100);
    umidadeSolo2 = map(umidadeSolo2, 1023, 0, 0, 100);
    umidadeSolo2 = map(umidadeSolo3, 1023, 0, 0, 100);
    umidadeSolo2 = map(umidadeSolo4, 1023, 0, 0, 100);
    umidadeSolo2 = map(umidadeSolo5, 1023, 0, 0, 100);

    // Exibe a mensagem no Display LCD:

    // TODO: Arrumar exibição da umidade das jardineiras
    lcd.setCursor(0, 0);
    lcd.print("T:");
    lcd.print(umidadeSolo1);
    lcd.print("|");
    lcd.print("2:");
    lcd.print(umidadeSolo2);
    lcd.print("|");
    lcd.print("3:");
    lcd.print(umidadeSolo3);
    lcd.print("|");

    // Exibe tempo espera no console para acompanhamento
    Serial.print(i);
    Serial.print(". ");

    // Espera 5 segundos
    delay(delayLoop*1000);
  }
}

int obterDadosDHT(int i){

  float h=dht.readHumidity(); 
  float t=dht.readTemperature(); 

  // Valida se existe algum erro de leitura dos valores do DHT 
  // Se houver, seta a umidade e temperatura com valor zero
  if (isnan(h) || isnan(t)) { 
    h=0; t=0; 
  }

  // Serial.print("# Temperatura: "); Serial.print(t);
  // Serial.print("| Umidade do Ar: "); Serial.println(h);

  /* 
     Realiza duas verificacoes: 
     Se auto ajuste estiver selecionado, sera alterado o comportamento de rega da jardineira
     Para temperatura registrada acima de 30 graus por um periodo de 4h, tempo rega alterado para acontecer a cada 5h
     Para temperatura abaixo de 28 pelo periodo de 4h, tempo rega alterado para a cada 9h
  */
  if(t > 30 && autoAjusteLoop) {
    contadorAltaTemperatura++;
  
    if(contadorAltaTemperatura >= quatroHoras && tempoLoop >= 7) {
      i = tempoLoopControle;
      tempoLoop = 5;
      Serial.println("Auto ajuste acionado. TempoLoop: "); Serial.println(tempoLoop);  
    }
  }
  if(t < 28 && autoAjusteLoop) {
    contadorBaixaTemperatura++;
  
    if(contadorBaixaTemperatura >= quatroHoras && tempoLoop < 7) {
      i = tempoLoopControle;
      tempoLoop = 9;
      Serial.println("Auto ajuste acionado. TempoLoop: "); Serial.println(tempoLoop);  
    }
  }

  return i;
}

// Funcao para desligar LED da jardineira
//void desligarLed(){ 
//  digitalWrite(PINO_LED_R, LOW); // Liga LED vermelho
//  digitalWrite(PINO_LED_G, LOW);  // Desliga LED verde
//  digitalWrite(PINO_LED_B, LOW); // Liga LED azul
//  return;
//}

// Recebe como parâmetro 3 valores correspondentes a hora|minuto|segundo
// void tempo_espera(double hora, double minuto, double segundo){
//   double h = 0, m = 0, s = 0, tempo = 0;
  
//   h = (hora * 3600)* 1000;  // 1 hora é equivalente a 3600 segundos x 1000 milisegundos da função delay
//   m = (minuto * 60) * 1000; // 1 minutos é equivalente a 60 segundos x 1000 milisegundos da função delay
//   s = segundo * 1000;       // 1 segundo x 1000 milisegundos da função delay 

//   tempo = h + m + s;
//   Serial.println("Tempo de espera estipulado: "); 
//   Serial.println(tempo,0);  // Exibe o tempo estipulado, sem casas decimais
//   delay(tempo);
// }

// Funcao para ler o sensor de nivel de agua | DESCOMENTAR SE FOR UTILIZAR
// ################## Ainda dá para ajustar e explorar mais esse componente ##################
//int lerNivelAgua(){
//  nivelAgua = analogRead(nivelAguaPin);
//  return nivelAgua;
//}

  // Leitura do sensor de nível de líquidos #### TIRAR COMENTARIOS SE FOR UTILIZAR  
//  lcd.clear(); 
//  lcd.setCursor(0, 0);
//  int level = lerNivelAgua();
//  lcd.println("Nivel de Agua:  ");
//  
//  // TO DO: necessario ajustar e validar os parametros do sensor de nivel de agua
//  if(level <= 30){
//    lcd.setCursor(0, 1); 
//    lcd.println("VAZIO  |  ");
//    lcd.println(level);
//  }
//  else if(level > 30 && level <= 400){
//    lcd.setCursor(0, 1); 
//    lcd.println("BAIXO  |  ");
//    lcd.println(level);
//  }
//  else if(level > 200 && level <= 538){
//    lcd.setCursor(0, 1); 
//    lcd.println("MEDIO  |  ");
//    lcd.println(level);
//  }
//  else {
//    lcd.setCursor(0, 1); 
//    lcd.println("CHEIO  |  ");
//    lcd.println(level);
//  }
//  Serial.print("sensor = ");
//  Serial.print(level); 
//  Serial.print("\n"); 
//  delay(5000);

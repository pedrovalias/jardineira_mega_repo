#include <Arduino.h>

// INCLUSÃO DE BIBLIOTECAS
#include <Adafruit_GFX.h>    
#include <Adafruit_TFTLCD.h> 
#include <TouchScreen.h>
#include <Fonts/FreeSans9pt7b.h>
#include <Fonts/FreeSansBold9pt7b.h>

// DEFINIÇÕES DE PINOS
#define LCD_CS A3
#define LCD_CD A2
#define LCD_WR A1
#define LCD_RD A0
#define LCD_RESET A4

#define LIGADO         0x07E0  //VERDE
#define DESLIGADO      0xF800  //VERMELHO

#define MINPRESSURE 10
#define MAXPRESSURE 1000


/*____CALIBRAR TFT LCD_____*/
#define YP A3
#define XM A2
#define YM 9
#define XP 8

#define TS_LEFT 129
#define TS_RT   924
#define TS_TOP  82
#define TS_BOT  896
/*______FIM DA CALIBRAÇÃO______*/

TouchScreen ts = TouchScreen(XP, YP, XM, YM, 300); //300 É A SENSITIVIDADE
Adafruit_TFTLCD tft(LCD_CS, LCD_CD, LCD_WR, LCD_RD, LCD_RESET);

// DEFINIÇÕES DE CORES
#define	BLACK   0x0000
#define	BLUE    0x001F
#define	RED     0xF800
#define	GREEN   0x07E0
#define CYAN    0x07FF
#define MAGENTA 0xF81F
#define YELLOW  0xFFE0
#define WHITE   0xFFFF
#define DARKBLUE 0x0010
#define VIOLET 0x8888
#define GOLD 0xFEA0
#define BROWN 0xA145
#define SILVER 0xC618
uint16_t GREY = tft.color565(64, 64, 64);
uint16_t LIGHTSTEELBLUE = tft.color565(176,196,222);
uint16_t CINZA = tft.color565(128,128,128);
uint16_t VERDE = tft.color565(0,128,0);
uint16_t AMARELO = tft.color565(255,215,0);  //(218,165,32)
uint16_t AZUL = tft.color565(30,144,255);
uint16_t VERMELHO = tft.color565(220,20,60);


int X, Y;
long corBot[5] = {DESLIGADO, DESLIGADO, DESLIGADO, DESLIGADO, DESLIGADO};

TSPoint waitTouch() {
  TSPoint p;
  do {
    p = ts.getPoint();
    pinMode(XM, OUTPUT);
    pinMode(YP, OUTPUT);
  } while ((p.z < MINPRESSURE ) || (p.z > MAXPRESSURE));
  
  p.x = map(p.x, TS_LEFT, TS_RT, 0, 240);
  p.y = map(p.y, TS_BOT, TS_TOP, 0, 320);
  
  return p;
}

void IntroScreen();
void draw_Buttons(int type);
void DetectButtons();
void HeaderScreen();
void DrawHeader();
void DrawSlotSJardineira();
void DrawBotoesJardineira();
void teste();
void DetectarBotoes();
void DrawBotoesRega(int type);

// void setup() {
//   Serial.begin(115200);
  
//   tft.reset();
//   tft.begin(0x9341); // CÓDIGO DO DRIVER DO SEU DISPLAY
//   tft.setRotation(2);
//   tft.fillScreen(BLACK);

//   DrawHeader();
//   teste();
//   DrawBotoesJardineira();

//   // IntroScreen();   // DESENHA A TELA DE INTRO
//   // HeaderScreen();
//   // draw_Buttons(0); // DESENHA TODOS OS BOTOES
// }

// void loop() {
//   TSPoint p = waitTouch();
//   X = p.x; Y = p.y;  

//   // DetectButtons(); // DETECTA OS BOTOES
//   // DrawHeader();
//   // DrawSlotSJardineira();
//   DetectarBotoes();
//   // teste();
//   // DrawBotoesJardineira();

//   delay(300);
// }

// IMPLEMENTO DE FUNÇÕES

void DetectButtons() {

  if (X < 200 && X > 40) {

    if (Y > 220 && Y < 300) { // LOGICA PARA O BOTAO 1
      Serial.println ("Button 1");
      if (corBot[0] == LIGADO) corBot[0] = DESLIGADO;
      else corBot[0] = LIGADO;
      draw_Buttons(1);
    }


    if (Y > 120 && Y < 200) { // LOGICA PARA O BOTAO 2
      Serial.println ("Button 2");
      if (corBot[1] == LIGADO) corBot[1] = DESLIGADO;
      else corBot[1] = LIGADO;
      draw_Buttons(2);
    }

    if (Y > 20 && Y < 100) { // LOGICA PARA O BOTAO 3
      Serial.println ("Button 3");
      if (corBot[2] == LIGADO) corBot[2] = DESLIGADO;
      else corBot[2] = LIGADO;
      draw_Buttons(3);
    }

  }

}

void HeaderScreen() {
  tft.setCursor (10, 10);
  tft.setTextSize (2);
  tft.setTextColor(WHITE);
  tft.println("REGA AUTOMATICA");
}

void IntroScreen() {
  tft.setCursor (55, 80);
  tft.setTextSize (3);
  tft.setTextColor(WHITE);
  tft.println("MENU");
  tft.setCursor (30, 120);
  tft.println("COM ARDUINO");
  tft.setCursor (30, 180);
  tft.setTextSize (2);
  tft.setTextColor(BLUE);
  tft.println("Brincando");
  tft.setCursor (30, 200);
  tft.setTextColor(WHITE);
  tft.println("    com");
  tft.setCursor (30, 220);
  tft.setTextColor(RED);
  tft.println("       Ideias");
  delay(3500);

  tft.fillScreen(BLACK);
}

void draw_Buttons(int type) {
  switch (type) {
    case 1:
      tft.fillRect  (40, 20 , 160, 80, corBot[0]);

      tft.setTextColor(BLACK);
      tft.setTextSize (3);
      tft.setCursor(50, 50);
      tft.println(" QUARTO");
      break;

    case 2:
      tft.fillRect  (40, 120, 160, 80, corBot[1]);

      tft.setTextColor(BLACK);
      tft.setTextSize (3);
      tft.setCursor(50, 150);
      tft.println("  SALA ");
      break;

    case 3:
      tft.fillRect  (40, 220, 160, 80, corBot[2]);

      tft.setTextColor(BLACK);
      tft.setTextSize (3);
      tft.setCursor(60, 250);
      tft.println("COZINHA");
      break;

    default:
      tft.fillRect  (40, 20 , 160, 80, corBot[0]);
      tft.fillRect  (40, 120, 160, 80, corBot[1]);
      tft.fillRect  (40, 220, 160, 80, corBot[2]);

      tft.setTextColor(BLACK);
      tft.setTextSize (3);

      tft.setCursor(50, 50);
      tft.println(" QUARTO");

      tft.setCursor(50, 150);
      tft.println("  SALA ");

      tft.setCursor(60, 250);
      tft.println("COZINHA");
  }
}

void DrawHeader() {
  tft.fillScreen(BLACK);

  tft.setFont();
  tft.setTextSize(2);
  tft.setTextColor(WHITE);

  tft.fillRect(0, 0, 240, 30, SILVER);
  tft.drawLine(0, 30, 240, 30, WHITE);
  // tft.drawRect(0, 0, 240, 30, WHITE);
  // tft.fillRect(0, 40, 240, 280, GREY);    
  // tft.drawRect(0, 40, 240, 280, WHITE); 

  tft.setCursor(4, 7);
  tft.print("REGA AUTOMATICA");

  // MEU TESTE
  // tft.fillRoundRect(0, 0, 240, 40, 8, GREY);
  // tft.drawRoundRect(0, 0, 240, 40, 8, WHITE);
  // tft.fillRoundRect(0, 40, 240, 280, 8, LIGHTSTEELBLUE);    
  // tft.drawRoundRect(0, 40, 240, 280, 8, WHITE);  
}

void DrawSlotSJardineira(){
  tft.fillRoundRect(4, 40, 104, 52, 8, CINZA);
  // tft.drawRoundRect(3, 40, 104, 54, 8, WHITE);
  // tft.drawRect(100, 40, 32, 54, GREY);
  // tft.fillRect(50, 41, 74, 52, BLACK);
  tft.fillRect(100, 40, 34, 52, CINZA);
  tft.drawRoundRect(4, 96, 132, 54, 8, WHITE);
  tft.drawRoundRect(4, 152, 132, 54, 8, WHITE);
  tft.drawRoundRect(4, 208, 132, 54, 8, WHITE);
  tft.drawRoundRect(4, 264, 132, 54, 8, WHITE);

  tft.setTextSize(1);
  tft.setFont(&FreeSans9pt7b);
  tft.setTextColor(WHITE);

  tft.setCursor(8, 56);
  tft.print("Jardineira 1");
  tft.setCursor(8, 84);
  tft.print("Solo: 100%");

  tft.setCursor(8, 114);
  tft.print("Jardineira 2");
  tft.setCursor(8, 140);
  tft.print("Solo: 50%");

  tft.setCursor(8, 170);
  tft.print("Jardineira 3");
  tft.setCursor(8, 196);
  tft.print("Solo: 100%");

  tft.setCursor(8, 226);
  tft.print("Jardineira 4");
  tft.setCursor(8, 252);
  tft.print("Solo: 25%");

  tft.setCursor(8, 282);
  tft.print("Jardineira 5");
  tft.setCursor(8, 308);
  tft.print("Solo: 100%");
}

void DrawBotoesJardineira() {

  // tft.drawRoundRect(191, 46, 44, 44, 8, WHITE);
  // tft.drawRoundRect(191, 102, 44, 44, 8, WHITE);
  // tft.drawRoundRect(191, 158, 44, 44, 8, WHITE);
  // tft.drawRoundRect(191, 214, 44, 44, 8, WHITE);
  // tft.drawRoundRect(191, 270, 44, 44, 8, WHITE);

  // tft.drawCircle(191, 270, 22, WHITE);

  // tft.drawRoundRect(138, 40, 95, 54, 8, WHITE);
  // tft.drawRoundRect(138, 96, 95, 54, 8, WHITE);
  // tft.drawRoundRect(138, 152, 95, 54, 8, WHITE);
  // tft.drawRoundRect(138, 208, 95, 54, 8, WHITE);
  // tft.drawRoundRect(138, 264, 95, 54, 8, WHITE);
  
  // MODELO METADE ARREDONDADO E METADE RETO
  // tft.fillRoundRect(180, 40, 56, 52, 8, VERDE);
  // tft.fillRect(138, 40, 75, 52, VERDE);
  tft.fillRoundRect(138, 40, 95, 52, 8, VERDE);
  tft.fillRoundRect(138, 96, 95, 52, 8, AMARELO);
  tft.fillRoundRect(138, 152, 95, 52, 8, VERDE);
  tft.fillRoundRect(138, 208, 95, 52, 8, VERMELHO);
  tft.fillRoundRect(138, 264, 95, 52, 8, AZUL);

  // tft.setTextSize(1);
  // tft.setFont(&FreeSansBold9pt7b);
  // tft.setTextColor(BLACK);

  // tft.setCursor(156, 70);
  // tft.print("CHEIA");

  // tft.setCursor(153, 128);
  // tft.print("REGAR");

  // tft.setCursor(156, 184);
  // tft.print("CHEIA");

  // tft.setCursor(153, 240);
  // tft.print("REGAR");

  // tft.setCursor(141, 296);
  // tft.print("REGANDO");

  tft.setTextSize(1);
  tft.setFont(&FreeSans9pt7b);
  tft.setTextColor(WHITE);
  
  tft.setCursor(155, 68);
  tft.print("CHEIA");

  tft.setCursor(152, 126);
  tft.print("REGAR");

  tft.setCursor(155, 182);
  tft.print("CHEIA");

  tft.setCursor(152, 238);
  tft.print("REGAR");

  tft.setCursor(140, 294);
  tft.print("REGANDO");
}

// CRIANDO ESTRUTURA EM LAÇO
void teste(){
  tft.setTextSize(1);
  tft.setFont(&FreeSans9pt7b);
  tft.setTextColor(WHITE);

  int y = 40;
  int cy = 60;

  for(int i = 0; i < 5 ; i++) {
    tft.fillRoundRect(4, y, 132, 52, 8, GREY);
    tft.setCursor(8, cy);
    tft.print("Jardineira " + String(i + 1));
    tft.setCursor(8, cy + 24);
    tft.print("Solo: " + String(i + 1));
    y = y + 56;
    cy = cy + 56;
  }
}

void DetectarBotoes() {

  if (X < 236 && X > 138) {

    Serial.print("X: "  + String(X));
    Serial.println(" Y: " + String(Y));

    if (Y > 228 && Y < 280) { // LOGICA PARA O BOTAO 1
      Serial.println ("Button 1");
      if(corBot[0] == LIGADO) corBot[0] = DESLIGADO;        
      else corBot[0] = LIGADO;
      DrawBotoesRega(1);
    }

    if (Y > 172 && Y < 224) { // LOGICA PARA O BOTAO 2
      Serial.println ("Button 2");
      if (corBot[1] == LIGADO) corBot[1] = DESLIGADO;
      else corBot[1] = LIGADO;
      DrawBotoesRega(2);
    }

    if (Y > 116 && Y < 168) { // LOGICA PARA O BOTAO 3
      Serial.println ("Button 3");
      if (corBot[2] == LIGADO) corBot[2] = DESLIGADO;
      else corBot[2] = LIGADO;
      DrawBotoesRega(3);
    }

    if (Y > 60 && Y < 112) { // LOGICA PARA O BOTAO 3
      Serial.println ("Button 4");
      if (corBot[3] == LIGADO) corBot[3] = DESLIGADO;
      else corBot[3] = LIGADO;
      DrawBotoesRega(4);
    }

    if (Y > 2 && Y < 56) { // LOGICA PARA O BOTAO 3
      Serial.println ("Button 5");
      if (corBot[4] == LIGADO) corBot[4] = DESLIGADO;
      else corBot[4] = LIGADO;
      DrawBotoesRega(0);
    }
  }
}

void DrawBotoesRega(int type) {
  tft.setTextSize(1);
  tft.setFont(&FreeSans9pt7b);
  tft.setTextColor(WHITE);

  switch (type) {
    case 1:
      tft.fillRoundRect(138, 40 , 95, 52, 8, corBot[0]);

      tft.setTextColor(WHITE);
      
      if(corBot[0] == LIGADO) {
        //  Serial.println ("CorBot IF: " + String(corBot[0]));
        tft.setCursor(138, 68);
        tft.println("REGANDO");
      }
      else {
        tft.setCursor(155, 68);
        tft.println("REGAR");
      };
      Serial.println ("CorBot: " + String(corBot[0]));
      break;

    case 2:
      tft.fillRoundRect(138, 96, 95, 52, 8,  corBot[1]);

      tft.setCursor(152, 126);
      tft.setTextColor(BLACK);
      tft.println("TESTE 2");
      break;

    case 3:
      tft.fillRoundRect(138, 152, 95, 52, 8, corBot[2]);

      tft.setTextColor(BLACK);
      tft.setCursor(155, 182);
      tft.println("TESTE 3");
      break;

    case 4:
      tft.fillRoundRect(138, 208, 95, 52, 8, corBot[3]);

      tft.setTextColor(BLACK);
      tft.setCursor(152, 238);
      tft.println("TESTE 4");
      break;

    case 5:
      tft.fillRoundRect(138, 264, 95, 52, 8, corBot[4]);

      tft.setTextColor(BLACK);
      tft.setCursor(140, 294);
      tft.println("TESTE 5");
      break;

    default:
      // POSSO USAR O DEFAULT PRA DEIXAR OS BOTOES CURRENT
      tft.fillRoundRect(138, 40, 95, 52, 8, VERDE);
      tft.fillRoundRect(138, 96, 95, 52, 8, AMARELO); 
      tft.fillRoundRect(138, 152, 95, 52, 8, VERDE);
      tft.fillRoundRect(138, 208, 95, 52, 8, VERMELHO);
      tft.fillRoundRect(138, 264, 95, 52, 8, AZUL);

      tft.setCursor(155, 68);
      tft.println("cheio");

      // tft.setCursor(50, 150);
      // tft.println("  SALA ");

      // tft.setCursor(60, 250);
      // tft.println("COZINHA");
  }
}
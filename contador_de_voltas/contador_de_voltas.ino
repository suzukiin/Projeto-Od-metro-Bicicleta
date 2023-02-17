//BIBLIOTECAS
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

// DEFINIÇÕES
#define endereco 0x27 //endereço i2c para reconhecer o display LCD 
#define colunas 16    //número de colunas do display LCD
#define linhas 2      //número de linhas do display LCD
#define sensor 8      //Define pino 8 entrada do sensor

LiquidCrystal_I2C lcd(endereco, colunas, linhas);
unsigned long voltas = 0;     //essa variável pode contar até 4 bilhoes de voltas
bool L_sensor = 1;            //variável para a leitura atual do sensor
bool LA_sensor = 1;           //variável para a leitura anterior do sensor
float diametro = 1.88;        // Diâmetro da roda da bicicleta
float distancia = 0;          // distância percorrida
int cont = 0;
void setup(){
  lcd.init();
  lcd.clear();
  lcd.backlight();
  lcd.print("Distancia:");  
  pinMode(sensor, INPUT);     //configura o pino do sensor como entrada
  
}
void loop(){
  //faz a leitura do sensor e atribui esse valor para a variável L_sensor
  L_sensor = digitalRead(sensor);  
  //SE L_sensor e LA_sensor estiver igual a 1, faça...    
  //obs.: superfície preta,  sensor = 1 (led do sensor apaga) -- superfície branca, sensor = 0 (led do sensor acende)      
  if (L_sensor == 1 && LA_sensor == 1){
    lcd.setCursor(0,1);
    if(voltas < 532){
      distancia = voltas * diametro;
      lcd.print(distancia + String("m"));     
      LA_sensor = 0;                                  
      voltas++; 
    }
    else{
      if(cont == 0){
        lcd.setCursor(0,1);
        lcd.print("                ");
        cont = 1;
      }
      else{
        distancia = voltas * diametro;
        distancia = distancia/1000 ;
        lcd.print((distancia) + String("Km"));
        LA_sensor = 0;                                  
        voltas++;
      }
       
    }
  }

  //SE L_sensor e LA_sensor estiver igual a zero, faça...
  if (L_sensor == 0 && LA_sensor == 0)
  LA_sensor = 1;                                    //retorna a variável LA_sensor para 1
  delay(10);                                        //delay para não travar o arduino
 }

#include "HX711.h" // Incluindo a biblioteca do Módulo HX711
#include "LiquidCrystal_I2C.h" // Incluindo a biblioteca Módulo serial I2C
#include <SoftwareSerial.h> // Incluindo a biblioteca do Módulo Bluetooth
HX711 escala; // Renomeando a biblioteca Módulo HX711
LiquidCrystal_I2C Display_lcd(0x27, 20, 4); // Renomeando a biblioteca Módulo serial I2C e
SoftwareSerial bluetooth(10, 11); // Renomeando a biblioteca do Módulo Bluetooth e
#define DT A1 // Definindo as portas do Módulo HX711
#define SCK A0 // Definindo as portas do Módulo HX711
char b1; // Criação da variação b1 
void calibra(){
  escala.set_scale(-393386.0759); // Substituir o valor encontrado para Escala
  escala.tare(20); // Fixa o peso como tara
}
void setup() {
  escala.begin (DT, SCK); // Iniciando a conexão do Módulo HX711
  Display_lcd.init(); //Inicializando o LCD
  Display_lcd.backlight(); // Ligando o backLight do LCD
  bluetooth.begin(9600); // Iniciando a comunicação do Módulo Bluetooth
  Serial.begin(9600); // Iniciando conexão serial
  Serial.println(escala.read()); // Aguada até o dispositivo estar pronto
  calibra(); //calibra a balança
}
void loop() {
  b1='a'; //colocando um valor em b1 para não trabalhar com lixo
  float Peso = escala.get_units(3); // Criação da variável peso
  Display_lcd.setCursor(4,0); // Linha quatro e coluna zero
  Display_lcd.print("Universidade"); // Mensagem escolhida
  Display_lcd.setCursor(1,1); // Linha um e coluna um
  Display_lcd.print("Catolica Dom Bosco"); // Mensagem escolhida
  Display_lcd.setCursor(0, 2); // Linha zero e coluna dois
  Display_lcd.print("Peso (Kg):");; // Mensagem escolhida
  Display_lcd.print (Peso,3); // Printando o peso no display LCD
  if(bluetooth.available()>0){  //verifica se há dados
    b1=bluetooth.read(); //coloca o valor lido
    if(b1=='c'){ //opção calibragem
      calibra();  //calibragem
    }else if(b1=='p'){//opção de printar
      delay(300);//espera para enviar
      bluetooth.println(Peso,3); // O Arduino envia o peso lido através do modulo bluetooth
    }
  }
}

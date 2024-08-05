#include <Arduino.h>

// Definir os pinos GPIO para o LED RGB
const int redPin = 13;
const int greenPin = 12;
const int bluePin = 16;

// Função para definir a cor do LED RGB
void setColor(int red, int green, int blue) {
  analogWrite(redPin, 255 - red);   // Inverter o valor para anodo comum
  analogWrite(greenPin, 255 - green); // Inverter o valor para anodo comum
  analogWrite(bluePin, 255 - blue); // Inverter o valor para anodo comum
}

// Função para piscar uma cor
void blinkColor(int red, int green, int blue, int delayTime) {
  setColor(red, green, blue); // Definir a cor
  delay(350);           // Esperar
  setColor(0, 0, 0);          // Apagar o LED
  delay(150);           // Esperar
}

void setup() {
  // Inicializar os pinos GPIO como saídas
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);

  // Começar com o LED apagado
  setColor(0, 0, 0);
}

void loop() {
  // Piscar verde
  blinkColor(0, 255, 0, 700);
  // Piscar azul
  blinkColor(0, 0, 255, 700);
  // Piscar amarelo
  blinkColor(255, 255, 0, 700);
}


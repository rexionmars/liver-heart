// Library for displat oled 128x64 pixels
#include "SSD1306.h"

// Configurações do display
SSD1306 display(0x3c, 14, 15);  // SDA, SCL

void setup() {
  // Inicializa o display
  display.init();
  display.flipScreenVertically();

  // Limpa o display
  display.clear();

  // Desenha o logotipo no centro do display
  while (1) {
    drawLogo();
  };
  

  // Atualiza o display
  display.display();
}

void loop() {
  // Seu código principal vai aqui
}

void drawLogo() {
  // Define as coordenadas do centro do display
  int centerX = display.getWidth() / 2;
  int centerY = display.getHeight() / 2;

  // Define o tamanho da fonte para o texto "Neural Engine"
  display.setFont(ArialMT_Plain_16);
  
  // Texto a ser exibido
  String logoText = "Neural Engine";

  // Calcula a largura do texto "Neural Engine"
  int textWidth = display.getStringWidth(logoText);

  // Calcula a posição x para centralizar o texto inicialmente
  int textX = centerX - (textWidth / 2);

  // Loop para exibir caracteres um por um
  for (int i = 0; i <= logoText.length(); i++) {
    // Limpa o display antes de desenhar o próximo caractere
    display.clear();

    // Calcula a nova posição x para centralizar o texto à medida que os caracteres são adicionados
    int newTextX = centerX - (display.getStringWidth(logoText.substring(0, i)) / 2);

    // Desenha os caracteres já processados
    display.drawString(newTextX, centerY - 10, logoText.substring(0, i));

    // Atualiza o display
    display.display();

    // Aguarda um curto período antes de exibir o próximo caractere
    delay(200);
  }

  // Aguarda um pouco antes de exibir o próximo texto
  delay(1000);

  // Define o tamanho da fonte para o texto "AI is the future of medicine"
  display.setFont(ArialMT_Plain_10);

  // Texto a ser exibido
  String infoText = "AI is the future of medicine";

  // Calcula a largura do texto "AI is the future of medicine"
  int textWidth2 = display.getStringWidth(infoText);

  // Calcula a posição x para centralizar o texto inicialmente
  int textX2 = centerX - (textWidth2 / 2);

  // Loop para exibir caracteres um por um
  for (int i = 0; i <= infoText.length(); i++) {
    // Limpa o display antes de desenhar o próximo caractere
    display.clear();

    // Calcula a nova posição x para centralizar o texto à medida que os caracteres são adicionados
    int newTextX2 = centerX - (display.getStringWidth(infoText.substring(0, i)) / 2);

    // Desenha os caracteres já processados
    display.drawString(newTextX2, centerY - 10, infoText.substring(0, i));

    // Atualiza o display
    display.display();

    // Aguarda um curto período antes de exibir o próximo caractere
    delay(100);
  }
}

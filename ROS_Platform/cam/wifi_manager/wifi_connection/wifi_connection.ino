#include <WiFiManager.h> // https://github.com/tzapu/WiFiManager
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_I2C_ADDR 0x3C
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RST_PIN -1

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST_PIN);

// Bitmap para um círculo pequeno preenchido
const unsigned char circle_bitmap [] PROGMEM = {
  0b00111000,
  0b01111100,
  0b11111110,
  0b11111110,
  0b11111110,
  0b01111100,
  0b00111000,
  0b00010000
};

// Função para imprimir texto caractere por caractere com um círculo seguindo o último caractere
void printCharByChar(String text, unsigned int delayTime, int y) {
    int x = 0; // Posição X inicial para o texto

    for (int i = 0; i < text.length(); i++) {
        display.fillRect(x, y, SCREEN_WIDTH - x, 8, BLACK); // Limpa apenas a área necessária
        display.setCursor(x, y);
        display.print(text.substring(0, i + 1)); // Imprime a substring até o caractere atual

        // Desenha o círculo apenas se não for o último caractere
        if (i < text.length() - 1) {
            display.drawBitmap(x + (i + 1) * 6, y, circle_bitmap, 8, 8, WHITE);
        }

        display.display();
        delay(delayTime);
    }
}

void setup() {
    Serial.begin(115200);
    Wire.begin(14, 15, 100000); // Substitua pelos pinos SDA e SCL do seu projeto

    if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_I2C_ADDR)) {
        Serial.println("SSD1306 OLED display failed to initialize.");
        return;
    }

    WiFiManager wm;
    wm.setConfigPortalTimeout(180); // 3 minutos

    // Número de linhas de texto que serão exibidas
    int totalLines = 4; // Ajuste esse número conforme o número de linhas de texto

    int lineHeight = 8; // Altura de uma linha com setTextSize(1)
    int totalTextHeight = lineHeight * totalLines; // Calcula a altura total do texto

    // Calculando a posição vertical inicial para centralizar verticalmente
    int startY = (SCREEN_HEIGHT - totalTextHeight) / 2;

    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(WHITE);

    if (WiFi.SSID() != "") {
        printCharByChar("Conectando a:", 100, startY);
        printCharByChar(WiFi.SSID(), 100, startY + lineHeight);

        if (wm.autoConnect()) {
            printCharByChar("Wifi conectado", 100, startY + 2 * lineHeight);
            Serial.println("Connected to WiFi");
        } else {
            printCharByChar("Conexao falhou", 100, startY + 2 * lineHeight);
            Serial.println("Failed to connect to WiFi");
        }
    } else {
        printCharByChar("Criando AP:", 100, startY);
        printCharByChar("AuRA AI-MED", 100, startY + lineHeight);
        printCharByChar("Pass: auraneural", 100, startY + 2 * lineHeight);

        if (!wm.startConfigPortal("AuRA AI-MED", "auraneural")) {
            printCharByChar("Config AP falhou", 100, startY + 3 * lineHeight);
            Serial.println("Failed to start config portal");
        }
    }
}

void loop() {
    // Código do loop aqui...
}

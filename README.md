# BlueDucky

ESP32-based Bluetooth HID keyboard (BLE Ducky) with button-triggered payload and LED status indicator.

---

## 🛠️ Hardware Required

- **ESP32-WROOM Dev Kit** (tested on NodeMCU-32)  
- **Push button**  
- **Wires / breadboard** (optional for testing)  
- USB cable for programming  

**Button wiring:**  
- One side of the button → GPIO15  
- Other side → GND  

**LED indicator:**  
- Built-in LED → GPIO2 (blinks while not connected, stays ON when connected)  

---

## 📚 Libraries Used

1. **[ESP32-BLE-Keyboard](https://github.com/T-vK/ESP32-BLE-Keyboard)**  
   - Allows ESP32 to act as a Bluetooth keyboard  

---

## ⚙️ Installing Libraries

1. Download the **ESP32-BLE-Keyboard ZIP** from [GitHub](https://github.com/T-vK/ESP32-BLE-Keyboard) → Code → Download ZIP  
2. Open Arduino IDE → **Sketch → Include Library → Add .ZIP Library** → Select the downloaded ZIP  
3. The library is now installed and ready to use.  

---

## ⚙️ Installing the ESP32 Board (WROOM) via Board Manager

1. Open **Arduino IDE**.  
2. Go to **File → Preferences**.  
   - In **“Additional Boards Manager URLs”**, add:  
     ```
     https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
     ```  
   - Click **OK**.  
3. Go to **Tools → Board → Boards Manager**.  
4. Search for **ESP32**.  
5. Install **“esp32 by Espressif Systems”**.  
6. Go to **Tools → Board → ESP32 Arduino** and select:  
   - **Board:** `ESP32 Dev Module`  
   - This board uses the **ESP32-WROOM module** (default for NodeMCU-32).  
7. Set the following options:  
   - **Upload Speed:** 115200  
   - **Partition Scheme:** Default  

✅ Now your Arduino IDE is ready to compile and upload code to your ESP32-WROOM dev kit.

---

## 💻 Code Overview

- **Button Detection:** The payload triggers when GPIO15 is pressed.  
- **Payload Steps:**  
  1. Press **Win+R** to open the Run dialog  
  2. Type `powershell`  
  3. Press **Ctrl+Shift+Enter** to run as administrator  
  4. Confirm UAC with **Alt+Y**  
  5. Type the final command: `(command that you want to run ex: shutdown /s /t 00)`  

- **LED Indicator:**  
  - **Blinking LED** while the ESP32 is not connected to a PC  
  - **LED ON** when the ESP32 successfully connects as a BLE keyboard  

- **Reliable Typing:** Commands are typed **character by character** with small delays to prevent skipped keys.  
- **State Machine Logic:** Ensures each step executes in order, even on slower PCs.  

---

## 🔌 Pin Mapping

| Function          | ESP32 Pin |
|------------------|-----------|
| Button Input     | GPIO15    |
| LED Indicator    | GPIO2     |
| BLE Keyboard     | Built-in BLE (no extra pins needed) |

---

## 💡 Notes

- The code uses **`BleKeyboard.h`** for Bluetooth HID functionality.  
- Delays are tuned for Windows 10/11 — you can adjust them if needed.  
- Works only on PCs that accept Bluetooth keyboards.  

---

## 💻 Usage

1. Connect the ESP32 via USB and upload the code.  
2. The LED will **blink** while waiting to connect.  
3. Once connected via Bluetooth, the LED will **stay ON**.  
4. Press the button → the ESP32 will execute the payload automatically.  
5. To modify the payload, change the string inside `typeCommand()` calls.  

---

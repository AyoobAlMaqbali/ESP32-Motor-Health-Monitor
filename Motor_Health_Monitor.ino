#include <Wire.h>
#include <Adafruit_INA219.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

Adafruit_INA219 ina219;
Adafruit_SSD1306 display(128, 64, &Wire, -1);

unsigned long motorStartTime = 0;
bool motorRunning = false;

void setup() {
  Serial.begin(115200);
  Wire.begin(21, 22);

  if (!ina219.begin()) {
    Serial.println("INA219 not detected!");
    while (1);
  }

  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println("OLED failed!");
    while (1);
  }
}

void loop() {
  float voltage = ina219.getBusVoltage_V();
  float current = ina219.getCurrent_mA();

  const char* status = "NORMAL";

  if (voltage < 4.5) {
    status = "LOW VOLTAGE";
    motorRunning = false;
  }
  else {
    if (!motorRunning) {
      motorStartTime = millis();
      motorRunning = true;
    }

    if (voltage > 5.5) {
      status = "HIGH VOLTAGE";
    }
    else if (current > 65.0 &&                  // Ignore starting current as it usually is one large burst
            millis() - motorStartTime >= 2000) {
      status = "HIGH CURRENT";
    }
  }

  Serial.print("Voltage: ");
  Serial.print(voltage, 2);
  Serial.print(" V | Current: ");
  Serial.print(current, 2);
  Serial.print(" mA | Status: ");
  Serial.println(status);

  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);

  display.setCursor(0, 0);
  display.println("MOTOR MONITOR");

  display.setCursor(0, 18);
  display.print("Voltage: ");
  display.print(voltage, 2);
  display.println(" V");

  display.setCursor(0, 30);
  display.print("Current: ");
  display.print(current, 1);
  display.println(" mA");

  display.setCursor(0, 48);
  display.print("Status: ");
  display.println(status);

  display.display();

  delay(500);
}
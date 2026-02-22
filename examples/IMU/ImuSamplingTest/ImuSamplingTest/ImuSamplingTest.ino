/**
 * Minimal test for sampleImuWindow(): collects 50 samples at 50 Hz,
 * prints first and last sample to Serial.
 */
#include <Dezibot.h>

Dezibot dezibot;
float buffer[50 * 6];

void setup() {
  Serial.begin(115200);
  delay(2000);
  dezibot.begin();

  bool ok = dezibot.motion.detection.sampleImuWindow(buffer, 50, 50);

  if (!ok) {
    Serial.println("sampleImuWindow failed");
    return;
  }

  Serial.println("Sample 0: ax ay az gx gy gz");
  Serial.print(buffer[0]); Serial.print(" ");
  Serial.print(buffer[1]); Serial.print(" ");
  Serial.print(buffer[2]); Serial.print(" ");
  Serial.print(buffer[3]); Serial.print(" ");
  Serial.print(buffer[4]); Serial.print(" ");
  Serial.println(buffer[5]);

  int last = 49 * 6;
  Serial.println("Sample 49: ax ay az gx gy gz");
  Serial.print(buffer[last+0]); Serial.print(" ");
  Serial.print(buffer[last+1]); Serial.print(" ");
  Serial.print(buffer[last+2]); Serial.print(" ");
  Serial.print(buffer[last+3]); Serial.print(" ");
  Serial.print(buffer[last+4]); Serial.print(" ");
  Serial.println(buffer[last+5]);

  Serial.println("Done. Values in m/s^2 and rad/s.");
}

void loop() {}

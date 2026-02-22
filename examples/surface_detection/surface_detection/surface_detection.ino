/****************************************************
 * Surface Detection Example
 * Continuously reads surface reflectivity (IR+DL_BOTTOM).
 * Bright/White surfaces are around ~4000, dark/black surfaces are around ~900. Keep in mind that values change with distance between the sensor and the surface.
 * Value shown on the dezibot's display.
 ****************************************************/

#include <Dezibot.h>

Dezibot dezibot;

void setup() {
  dezibot.begin();
  dezibot.surfaceDetection.beginSurfaceReading();
}

void loop() {
  dezibot.display.clear();
  dezibot.display.print((int)dezibot.surfaceDetection.readSurfaceReflectivity());
  delay(200);
}

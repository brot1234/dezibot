/**
 * @file SurfaceDetection.cpp
 * @brief Implementation of surface reflectivity detection using IR+DL_BOTTOM.
 * @version 0.1
 * @date 2025-02-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "SurfaceDetection.h"
#include "infraredLight/InfraredLight.h"

void SurfaceDetection::begin(InfraredLight& ir) {
    infraredLight = &ir;
}

void SurfaceDetection::beginSurfaceReading(void) {
    infraredLight->bottom.turnOn();
}

void SurfaceDetection::endSurfaceReading(void) {
    infraredLight->bottom.turnOff();
}

uint16_t SurfaceDetection::readSurfaceReflectivity(void) {
    return LightDetection::getValue(DL_BOTTOM);
}

uint16_t SurfaceDetection::readSurfaceWithIr(void) {
    infraredLight->bottom.turnOn();
    uint16_t value = LightDetection::getValue(DL_BOTTOM);
    infraredLight->bottom.turnOff();
    return value;
}

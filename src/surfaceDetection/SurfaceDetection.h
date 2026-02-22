/**
 * @file SurfaceDetection.h
 * @brief Combines bottom IR LED with DL_BOTTOM sensor for ambient-independent surface reflectivity.
 * @version 0.1
 * @date 2025-02-21
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef SurfaceDetection_h
#define SurfaceDetection_h
#include <stdint.h>
#include "lightDetection/LightDetection.h"

class InfraredLight;

class SurfaceDetection {
public:
    /**
     * @brief Initialize with InfraredLight. Call after infraredLight.begin() and lightDetection.begin().
     * @param infraredLight Reference to the robot's InfraredLight component.
     */
    void begin(class InfraredLight& infraredLight);

    /**
     * @brief Turn on bottom IR LED for sustained surface reading (e.g. during movement).
     * Call readSurfaceReflectivity() in a loop, then endSurfaceReading() when done.
     */
    void beginSurfaceReading(void);
    /**
     * @brief Turn off bottom IR LED after surface reading.
     */
    void endSurfaceReading(void);
    /**
     * @brief Read DL_BOTTOM reflectivity (0-4095). IR must be on—call beginSurfaceReading() first.
     * @return uint16_t Reflectivity reading; white ~4000, black ~600.
     */
    uint16_t readSurfaceReflectivity(void);
    /**
     * @brief One-shot: turn on IR, read DL_BOTTOM, turn off IR, return value.
     * @return uint16_t Reflectivity reading (0-4095).
     */
    uint16_t readSurfaceWithIr(void);

protected:
    class InfraredLight* infraredLight;
};

#endif // SurfaceDetection_h

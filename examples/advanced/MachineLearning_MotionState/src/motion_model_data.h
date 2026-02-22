/**
 * @file motion_model_data.h
 * @author Bastian Wecke (bastian.wecke@stud.htwk-leipzig.de)
 * @brief TFLite model flatbuffer for motion state classification.
 *
 * Regenerate from: xxd -i motion_state_model.tflite
 * Then rename array to g_motion_state_model_data, len to g_motion_state_model_data_len.
 *
 * @date 2025-02-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef MOTION_MODEL_DATA_H
#define MOTION_MODEL_DATA_H

#include <stdint.h>

alignas(4) extern const uint8_t g_motion_state_model_data[];
extern const int g_motion_state_model_data_len;

#endif  // MOTION_MODEL_DATA_H

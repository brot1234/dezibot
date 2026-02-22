/**
 * @file motion_state_classifier.cpp
 * @author Bastian Wecke (bastian.wecke@stud.htwk-leipzig.de)
 * @brief TFLite Micro motion state classifier implementation.
 * @date 2025-02-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#include "motion_state_classifier.h"
#include "motion_model_data.h"
#include "motion_normalization_params.h"
#include <Arduino.h>
#include <cmath>

#include <TensorFlowLite_ESP32.h>
#include <tensorflow/lite/micro/micro_interpreter.h>
#include <tensorflow/lite/micro/micro_error_reporter.h>
#include <tensorflow/lite/micro/all_ops_resolver.h>
#include <tensorflow/lite/schema/schema_generated.h>

namespace {
constexpr size_t kTensorArenaSize = 80 * 1024;
static uint8_t tensor_arena[kTensorArenaSize];
static tflite::AllOpsResolver resolver;
static tflite::MicroErrorReporter micro_error_reporter;
static const tflite::Model* model = nullptr;
static tflite::MicroInterpreter* interpreter = nullptr;
static TfLiteTensor* input_tensor = nullptr;
static TfLiteTensor* output_tensor = nullptr;
}  // namespace

const char* const MOTION_STATE_LABELS[MOTION_NUM_CLASSES] = {
    "Idle", "Picked_up", "Shaking",
};

void normalizeMotionData(float* buffer, const int numSamples) {
    constexpr int NUM_FEATURES = 6;
    for (int group = 0; group < 2; group++) {
        const int featureOffset = group * 3;
        float mean[3] = {0.0f, 0.0f, 0.0f};
        for (int i = 0; i < numSamples; i++) {
            const int base = i * NUM_FEATURES + featureOffset;
            mean[0] += buffer[base + 0];
            mean[1] += buffer[base + 1];
            mean[2] += buffer[base + 2];
        }
        mean[0] /= numSamples;
        mean[1] /= numSamples;
        mean[2] /= numSamples;
        float variance[3] = {0.0f, 0.0f, 0.0f};
        for (int i = 0; i < numSamples; i++) {
            const int base = i * NUM_FEATURES + featureOffset;
            for (int j = 0; j < 3; j++) {
                const float diff = buffer[base + j] - mean[j];
                variance[j] += diff * diff;
            }
        }
        float std_dev[3];
        for (int j = 0; j < 3; j++) {
            std_dev[j] = sqrtf(variance[j] / numSamples);
        }
        for (int i = 0; i < numSamples; i++) {
            const int base = i * NUM_FEATURES + featureOffset;
            for (int j = 0; j < 3; j++) {
                buffer[base + j] =
                    (buffer[base + j] - mean[j]) /
                    (std_dev[j] + MOTION_NORM_EPSILON);
            }
        }
    }
}

bool initMotionStateModel(void) {
    model = tflite::GetModel(g_motion_state_model_data);
    if (model->version() != TFLITE_SCHEMA_VERSION) {
        Serial.printf("Motion: model schema version %d, expected %d\n",
                      model->version(), TFLITE_SCHEMA_VERSION);
        return false;
    }
    static tflite::MicroInterpreter static_interpreter(
        model, resolver, tensor_arena, kTensorArenaSize, &micro_error_reporter);
    interpreter = &static_interpreter;
    if (interpreter->AllocateTensors() != kTfLiteOk) {
        Serial.println("Motion: AllocateTensors() failed");
        return false;
    }
    input_tensor = interpreter->input(0);
    output_tensor = interpreter->output(0);
    Serial.printf("Motion model: input [%d,%d,%d], output [%d], arena %u B\n",
                  input_tensor->dims->data[0],
                  input_tensor->dims->data[1],
                  input_tensor->dims->data[2],
                  output_tensor->dims->data[1],
                  static_cast<unsigned>(interpreter->arena_used_bytes()));
    return true;
}

bool runMotionStateClassifier(const float* input, float* scores) {
    constexpr int inputSize = MOTION_NORM_SAMPLES * MOTION_NORM_FEATURES;
    float* inputData = input_tensor->data.f;
    for (int i = 0; i < inputSize; i++) {
        inputData[i] = input[i];
    }
    if (interpreter->Invoke() != kTfLiteOk) {
        Serial.println("Motion: Invoke() failed");
        return false;
    }
    const float* outputData = output_tensor->data.f;
    for (int i = 0; i < MOTION_NUM_CLASSES; i++) {
        scores[i] = outputData[i];
    }
    return true;
}

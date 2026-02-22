/**
 * @file MachineLearning_MotionState.ino
 * @author Bastian Wecke (bastian.wecke@stud.htwk-leipzig.de)
 * @brief TinyML motion state classification on Dezibot.
 *
 * Collects IMU data via sampleImuWindow(), runs motion state classifier,
 * prints predicted state: Idle, Picked_up, Shaking.
 *
 * @date 2025-02-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#include <Arduino.h>
#include <Dezibot.h>
#include "src/motion_state_classifier.h"

Dezibot dezibot;

const int kNumSamples = 50;
const int kSamplesPerSecond = 50;
float imuBuffer[kNumSamples * 6];
float scores[MOTION_NUM_CLASSES];

void setup() {
    Serial.begin(115200);
    delay(2000);
    dezibot.begin();
    dezibot.multiColorLight.turnOffLed(ALL);

    if (!initMotionStateModel()) {
        Serial.println("ERROR: Failed to init motion state model");
        return;
    }
    Serial.println("Motion state classifier ready. Sampling every 1s...");
}

void loop() {
    if (!dezibot.motion.detection.sampleImuWindow(
            imuBuffer, kNumSamples, kSamplesPerSecond)) {
        Serial.println("sampleImuWindow failed");
        delay(500);
        return;
    }

    normalizeMotionData(imuBuffer, kNumSamples);

    if (!runMotionStateClassifier(imuBuffer, scores)) {
        Serial.println("Classifier failed");
        delay(500);
        return;
    }

    int pred = motionStateArgMax(scores);
    const char* label = MOTION_STATE_LABELS[pred];

    Serial.print("State: ");
    Serial.println(label);

    dezibot.display.clear();
    dezibot.display.print(label);
}

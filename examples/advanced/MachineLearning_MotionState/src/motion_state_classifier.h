/**
 * @file motion_state_classifier.h
 * @author Bastian Wecke (bastian.wecke@stud.htwk-leipzig.de)
 * @brief TFLite Micro motion state classifier (Idle, Picked_up, Shaking).
 * @date 2025-02-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef MOTION_STATE_CLASSIFIER_H
#define MOTION_STATE_CLASSIFIER_H

constexpr int MOTION_NUM_CLASSES = 3;

extern const char* const MOTION_STATE_LABELS[MOTION_NUM_CLASSES];

bool initMotionStateModel(void);
bool runMotionStateClassifier(const float* input, float* scores);
void normalizeMotionData(float* buffer, int numSamples);

inline int motionStateArgMax(const float* scores) {
    int best = 0;
    for (int i = 1; i < MOTION_NUM_CLASSES; i++) {
        if (scores[i] > scores[best]) best = i;
    }
    return best;
}

#endif  // MOTION_STATE_CLASSIFIER_H

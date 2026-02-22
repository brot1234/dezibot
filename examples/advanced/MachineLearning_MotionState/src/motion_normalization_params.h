/**
 * @file motion_normalization_params.h
 * @author Bastian Wecke (bastian.wecke@stud.htwk-leipzig.de)
 * @brief Z-score normalization parameters for motion state model (matches training).
 * @date 2025-02-22
 *
 * @copyright Copyright (c) 2025
 *
 */
#ifndef MOTION_NORMALIZATION_PARAMS_H
#define MOTION_NORMALIZATION_PARAMS_H

#define MOTION_NORM_EPSILON 1e-08f
#define MOTION_NORM_SAMPLES 50
#define MOTION_NORM_FEATURES 6
#define MOTION_NORM_SIZE (MOTION_NORM_SAMPLES * MOTION_NORM_FEATURES)

#endif  // MOTION_NORMALIZATION_PARAMS_H

# Machine Learning Motion State Classification

TinyML motion state classification on Dezibot. Classifies IMU windows into **Idle**, **Picked_up**, **Shaking**.

## Prerequisites

- Dezibot library with `sampleImuWindow` API
- TensorFlow Lite Micro for ESP32 (install via Arduino Library Manager or PlatformIO)
- Board: ESP32-S3 with USB support (e.g. ESP32-S3-USB-OTG, ESP32S3 Dev Module)

## Build and Run

### PlatformIO (recommended)

From this directory:

```bash
pio run -t upload
pio device monitor
```

Or from Dezibot library root:

```bash
pio run -d examples/advanced/MachineLearning_MotionState -t upload
```

### Arduino CLI

Install TensorFlow Lite Micro: Arduino IDE → Sketch → Include Library → Manage Libraries → search "TensorFlowLite" → install "TensorFlowLite_ESP32".

From Dezibot library root:

```bash
arduino-cli compile -b esp32:esp32:esp32s3usbotg --library . examples/advanced/MachineLearning_MotionState
arduino-cli upload -b esp32:esp32:esp32s3usbotg -p /dev/ttyUSB0 examples/advanced/MachineLearning_MotionState
```

## Usage

1. Upload the sketch.
2. Open Serial Monitor at 115200.
3. Every second the robot samples IMU (1s window), runs the classifier, prints the state.
4. State is also shown on the Dezibot display.

**Important:** Sample only when the robot is idle. Do not call during `move()` or `rotate()`.

## Updating the Model

To replace with a newly trained model:

1. Export `.tflite` from your training pipeline.
2. Generate C array: `xxd -i motion_state_model.tflite > motion_model_raw.cpp`
3. Edit `motion_model_raw.cpp`: add `#include "motion_model_data.h"`, rename array to `g_motion_state_model_data`, length to `g_motion_state_model_data_len`.
4. Overwrite `src/motion_model_data.cpp` with the result.

Training pipeline: see gestenerkennungscontroller project (data collection, train_motion_state.py, export).

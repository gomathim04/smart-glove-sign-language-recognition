# Smart Glove for Sign Language Recognition

## About the Project

This project presents an ESP32-based smart glove designed to recognize hand gestures and convert them into corresponding alphabet letters.

The system uses flex sensors and an MPU6050 accelerometer to collect hand gesture data. A machine learning model is then used to classify the gestures.

The current prototype recognizes the letters **A, B, C and D**.

## Objectives

- Develop a low-cost smart glove for gesture recognition.
- Collect hand gesture data using wearable sensors.
- Use machine learning for gesture classification.
- Provide real-time letter prediction.
- Include an emergency alert using a push button and buzzer.

## Hardware Used

- ESP32 Development Board
- 4 Flex Sensors
- MPU6050 Accelerometer
- Push Button
- Buzzer
- Smart Glove
- Jumper Wires
- OLED Display

## Software Used

- Arduino IDE
- Python
- Pandas
- Scikit-learn
- Joblib

## Working Principle

The flex sensors measure finger bending, while the MPU6050 measures hand acceleration.

The ESP32 collects the sensor values and sends them to the computer through serial communication.

The collected data contains seven sensor features:

F1, F2, F3, F4, X, Y, Z

Each sample is associated with a gesture label:

A, B, C or D

The collected dataset is used to train a Random Forest machine learning model.

During live testing, the ESP32 continuously sends sensor values to Python. The trained model processes these values and predicts the corresponding letter.

## Machine Learning

A Random Forest Classifier is used for gesture classification.

### Input Features

- F1 - Flex Sensor 1
- F2 - Flex Sensor 2
- F3 - Flex Sensor 3
- F4 - Flex Sensor 4
- X - Accelerometer X-axis
- Y - Accelerometer Y-axis
- Z - Accelerometer Z-axis

### Output

The model predicts one of the trained gesture classes:

A
B
C
D

## Project Structure

Smart_Glove_Project

├── 01_Live_Sign_Prediction
│   ├── Arduino
│   │   └── smart_glove_sensors.ino
│   └── Python
│       ├── train_model.py
│       └── live_prediction.py
│
├── 02_Emergency_Alert
│   └── emergency_button_buzzer.ino
│
├── 03_Dataset
│   └── ABCD_combined.csv
│
└── README.md

## Emergency Alert

A push button and buzzer are included as an emergency alert feature.

When the emergency button is pressed, the ESP32 activates the buzzer to provide an alert.

## Results

The Random Forest model was trained using the collected A, B, C and D gesture data.

The model achieved **99.27% test accuracy** on the collected test dataset.

> Note: This accuracy is based on the collected dataset and test split. Real-world performance may vary when the glove is used by different people or under different hand positions.

## Future Improvements

- Add more alphabet gestures from A-Z.
- Improve recognition for different users.
- Add OLED-based real-time output.
- Add text-to-speech functionality.
- Improve gesture calibration.
- Increase the size and diversity of the dataset.
- Develop a complete communication interface.

## Author

**Gomathi M**

Biomedical Engineering  
Chennai Institute of Technology

## Technologies

`ESP32` `Arduino` `Python` `Machine Learning` `Random Forest` `Flex Sensors` `MPU6050`

import serial
import joblib
import time

# Load trained model
model = joblib.load("smart_glove_model.pkl")

print("Model loaded successfully!")

# Connect ESP32
ser = serial.Serial("COM3", 115200, timeout=1)

time.sleep(2)

# Clear old serial data
ser.reset_input_buffer()

print("ESP32 connected!")
print("Waiting for sensor data...")
print("--------------------------------")

while True:

    try:

        line = ser.readline().decode("utf-8", errors="ignore").strip()

        if not line:
            continue

        print("Received:", line)

        values = line.split(",")

        # We need exactly 7 values
        if len(values) != 7:
            print("Skipping - not 7 values")
            continue

        try:
            sensor_values = [float(x) for x in values]
        except ValueError:
            print("Skipping - invalid data")
            continue

        # Prediction
        prediction = model.predict([sensor_values])[0]

        print("================================")
        print("PREDICTED LETTER:", prediction)
        print("================================")

    except KeyboardInterrupt:

        print("\nProgram stopped.")
        ser.close()
        break

    except Exception as e:

        print("ERROR:", e)
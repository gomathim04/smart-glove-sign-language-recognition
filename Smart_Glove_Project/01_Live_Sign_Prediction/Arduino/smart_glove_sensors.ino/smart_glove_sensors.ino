#include <Wire.h>

// ---------- FLEX ----------
#define FLEX1_PIN 34
#define FLEX2_PIN 35
#define FLEX3_PIN 32
#define FLEX4_PIN 33

// ---------- MPU6050 ----------
#define SDA_PIN 21
#define SCL_PIN 22
#define MPU_ADDR 0x68

bool mpuConnected = false;

// ---------- CHECK MPU ----------
bool checkMPU() {
  Wire.beginTransmission(MPU_ADDR);
  return Wire.endTransmission() == 0;
}

// ---------- WAKE MPU ----------
void wakeMPU() {
  Wire.beginTransmission(MPU_ADDR);
  Wire.write(0x6B);
  Wire.write(0x00);
  Wire.endTransmission();
}

// ---------- READ MPU ----------
int16_t read16(byte reg) {

  Wire.beginTransmission(MPU_ADDR);
  Wire.write(reg);
  Wire.endTransmission(false);

  Wire.requestFrom(MPU_ADDR, (uint8_t)2);

  if (Wire.available() < 2)
    return 0;

  int16_t value = Wire.read() << 8;
  value |= Wire.read();

  return value;
}

void setup() {

  Serial.begin(115200);
  delay(1000);

  Wire.begin(SDA_PIN, SCL_PIN);
  Wire.setClock(100000);

  // Check MPU
  mpuConnected = checkMPU();

  if (mpuConnected) {
    wakeMPU();
    Serial.println("MPU6050 CONNECTED");
  } 
  else {
    Serial.println("MPU6050 ERROR");
  }

  Serial.println("LIVE SENSOR DATA STARTED");
}

void loop() {

  // ---------- FLEX ----------
  int f1 = analogRead(FLEX1_PIN);
  int f2 = analogRead(FLEX2_PIN);
  int f3 = analogRead(FLEX3_PIN);
  int f4 = analogRead(FLEX4_PIN);

  // ---------- ACCELEROMETER ----------
  float ax = 0;
  float ay = 0;
  float az = 0;

  if (mpuConnected) {

    int16_t rawX = read16(0x3B);
    int16_t rawY = read16(0x3D);
    int16_t rawZ = read16(0x3F);

    ax = (rawX / 16384.0) * 9.81;
    ay = (rawY / 16384.0) * 9.81;
    az = (rawZ / 16384.0) * 9.81;
  }

  // ---------- SEND EXACTLY 7 FEATURES ----------
  Serial.print(f1);
  Serial.print(",");

  Serial.print(f2);
  Serial.print(",");

  Serial.print(f3);
  Serial.print(",");

  Serial.print(f4);
  Serial.print(",");

  Serial.print(ax, 2);
  Serial.print(",");

  Serial.print(ay, 2);
  Serial.print(",");

  Serial.println(az, 2);

  delay(200);
}
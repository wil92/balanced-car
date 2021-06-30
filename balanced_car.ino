#include <Arduino.h>
#include <Wire.h>

#define len(x) (*(&x + 1) - x)

int PINS[4] = {14, 12};
int CONFIGURATION[4] = {1, 2};
int direction = 1;
int currentConfiguration = 0;

const int MPU=0x68;
float gx, gy, gz;
float ax, ay, az;
float gravity = 0.98;
float maxValue = 32768;
float aFactor = 2 * gravity / maxValue;
float gFactor = 250 / maxValue;

void setup(){
    Wire.begin();
    Wire.beginTransmission(MPU);
    Wire.write(0x6B);
    Wire.write(0);
    Wire.endTransmission(true);
    Serial.begin(9600);

    int numberOfPins = len(PINS);
    for (int i=0;i<numberOfPins;i++){
        pinMode(PINS[i], OUTPUT);
    }
}

void loop(){
    Wire.beginTransmission(MPU);
    Wire.write(0x3B);
    Wire.endTransmission(false);
    Wire.requestFrom(MPU,12,true);

    // accelerometer data
    ax = (Wire.read()<<8|Wire.read()) * aFactor;
    ay = (Wire.read()<<8|Wire.read()) * aFactor;
    az = (Wire.read()<<8|Wire.read()) * aFactor;

    // temperature data
    int16_t tmp = Wire.read()<<8|Wire.read();

    // gyroscope data
    gx = (Wire.read()<<8|Wire.read()) * gFactor;
    gy = (Wire.read()<<8|Wire.read()) * gFactor;
    gz = (Wire.read()<<8|Wire.read()) * gFactor;

    Serial.print("Accelerometer: ");
    Serial.print("X = "); Serial.print(ax);
    Serial.print(" | Y = "); Serial.print(ay);
    Serial.print(" | Z = "); Serial.println(az);

    Serial.print("Temperature: "); Serial.println(tmp);

    Serial.print("Gyroscope: ");
    Serial.print("X = "); Serial.print(gx);
    Serial.print(" | Y = "); Serial.print(gy);
    Serial.print(" | Z = "); Serial.println(gz);
    Serial.println(" ");

//  nextStep();
//  updatePins();
//  digitalWrite(PINS[0], HIGH);
//  digitalWrite(PINS[1], HIGH);
//  digitalWrite(PINS[2], HIGH);
//  digitalWrite(PINS[3], HIGH);

    delay(1000);
}

void nextStep() {
    int stepsLength = len(CONFIGURATION);
    currentConfiguration = (currentConfiguration + direction) % stepsLength;
}

void updatePins() {
    int currentStep = CONFIGURATION[currentConfiguration];
    int numberOfPins = len(PINS);
//  Serial.print(currentStep);Serial.print(" ");
    for(int i=0;i<numberOfPins;i++){
        digitalWrite(PINS[i], getOutput(currentStep & (1<<i)));
//    Serial.print(getOutput(currentStep & (1<<i)));Serial.print(" ");
    }
//  Serial.println("");
}

int getOutput(int b) {
    return b ? HIGH : LOW;
}

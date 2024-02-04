const int BUTTON_PIN = 2;
const int LED_PIN = 13;
const int BUZZER_PIN = 5;
const int PIR_SENSOR_PIN = 3;
const int PHOTORESISTOR_PIN = A0;

volatile int buttonState = HIGH;
volatile int lightSensorValue = 0;
volatile int pirSensorValue = 0;
volatile bool ledState = LOW;
volatile bool motionDetected = false;

void handleInterrupt() {
  buttonState = digitalRead(BUTTON_PIN);
  lightSensorValue = analogRead(PHOTORESISTOR_PIN);
  pirSensorValue = digitalRead(PIR_SENSOR_PIN);

  if (buttonState == LOW) {
    if (lightSensorValue < 500) {
      ledState = !ledState;
      digitalWrite(LED_PIN, ledState);

      if (ledState == HIGH) {
        Serial.println("LED turned on in low light");
      } else {
        Serial.println("LED turned off in low light");
      }
    } else {
      if (ledState == HIGH) {
        Serial.println("LED turned on in high light");
      } else {
        Serial.println("LED turned off in high light");
      }
    }
  } else {
    if (ledState == HIGH || pirSensorValue == HIGH) {
      digitalWrite(LED_PIN, HIGH);
    }
  }
}

void motionInterrupt() {
  motionDetected = digitalRead(PIR_SENSOR_PIN) == HIGH;

  if (motionDetected) {
    digitalWrite(BUZZER_PIN, HIGH);
    Serial.println("Motion detected!");
    delay(1000);
    digitalWrite(BUZZER_PIN, LOW);
  }
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT_PULLUP);
  pinMode(PHOTORESISTOR_PIN, INPUT);
  pinMode(PIR_SENSOR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  Serial.begin(9600);

  attachInterrupt(digitalPinToInterrupt(BUTTON_PIN), handleInterrupt, CHANGE);
  attachInterrupt(digitalPinToInterrupt(PIR_SENSOR_PIN), motionInterrupt, CHANGE);
}

void loop() {}

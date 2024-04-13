// Temp Libraries
#include <OneWire.h>
#include <DallasTemperature.h>


// Peltier
int base_peltier = 10;


// Voltage Divider for battery
int batteryLevelPin = A0;


// Power indicator pins
int BUZZER = 4;

int rLed = 5;
int gLed = 6;
int bLed = 7;

// Danger light
int dangerLight = 11;


#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);

DallasTemperature sensors(&oneWire);


int startTime;
int currentTime;



void setup() {
  Serial.begin(115200);

  pinMode(base_peltier, OUTPUT);

  pinMode(batteryLevelPin, INPUT);

  pinMode(BUZZER, OUTPUT);

  pinMode(rLed, OUTPUT);
  pinMode(gLed, OUTPUT);
  pinMode(bLed, OUTPUT);

  pinMode(dangerLight, OUTPUT);

  // Temp
  sensors.begin();

  // Device on
  PowerSwitchOnI();
  PowerSwitchOffI();
  delay(5000);

  Serial.println("On");
  Heating();
  HeatOnI();
  Serial.println("Heating on");

  startTime = millis();
}


void Heating() {
  int battery = BatteryLevel();
  // battery = map(battery, 6, 8, 15, 8);
  // analogWrite(base_peltier, battery);
  analogWrite(base_peltier, 20);
  delay(500);
}


float BatteryLevel() {
  float level = analogRead(batteryLevelPin);
  // float realLevel = map(level, 0, 1023, 0, 8);
  float realLevel = level * (5.0/1023) * 1.6;

  Serial.print(level); Serial.print("\t");
  Serial.println (realLevel);
  delay(1000);

  return realLevel;
}


float TempCheck() { 
  // Call sensors.requestTemperatures() to issue a global temperature and Requests to all devices on the bus
  sensors.requestTemperatures(); 
  
  Serial.print("Celsius temperature: ");
  // Why "byIndex"? You can have more than one IC on the same bus. 0 refers to the first IC on the wire
  Serial.print(sensors.getTempCByIndex(0)); 
  Serial.print(" - Fahrenheit temperature: ");
  Serial.println(sensors.getTempFByIndex(0));
  delay(1000);

  return sensors.getTempCByIndex(0);
}


// Power indicators
void PowerSwitchOnI() { // Light indication after device comes on
  digitalWrite(rLed, HIGH);
  digitalWrite(gLed, HIGH);
  digitalWrite(bLed, HIGH);
  delay(2000);
}

void PowerSwitchOffI() {  // Light indication to move to heating mode
  digitalWrite(rLed, LOW);
  analogWrite(gLed, LOW);
  digitalWrite(bLed, LOW);
  delay(1000);
}

/* Heating on */
// Heating mode indicators
void HeatOnI() {  // Light to show that heating coil is actively on
  digitalWrite(rLed, LOW);
  digitalWrite(gLed, HIGH);
  digitalWrite(bLed, LOW);
  delay(100);
}


void Ready() {  // Light to show that heating coil is actively on
  digitalWrite(rLed, LOW);
  digitalWrite(gLed, LOW);
  digitalWrite(bLed, HIGH);
  delay(100);
}


void BatteryLight() {
  digitalWrite(rLed, HIGH);
  digitalWrite(gLed, HIGH);
  digitalWrite(bLed, LOW);
  delay(1000);
}


// Buzzer function
void BuzzerOn(int frequency, int timer, int num, bool urgent) {  // Audio alarm for all functions
  for (int i = num; i > 0; i--) {
    tone(BUZZER, frequency);
    delay(timer);
    noTone(BUZZER);
    delay(timer);
    Serial.println("Buzzer function");
  }
}

void loop() {
  // put your main code here, to run repeatedly:

  int batteryValue = BatteryLevel();
  int temp = TempCheck();

  currentTime = millis();

  Serial.println(temp);
  if (temp >= 35) Ready();
  //Serial.println("Heat attained");

  if (batteryValue < 1) {
    Serial.println("Battery level too low");
    BatteryLight();
    BuzzerOn(1000, 1000, 2, false);
  }
  
  if (currentTime - startTime >= 60000) {
    while (temp > 38.5 || temp < 37) {
      Serial.println("Temp Danger");
      BuzzerOn(1500, 500, 1, true);
      digitalWrite(dangerLight, HIGH);
      delay(500);
      digitalWrite(dangerLight, LOW);
      delay(500);
    }
  }
}


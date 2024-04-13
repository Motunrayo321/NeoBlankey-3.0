// Digital pins
int BUZZER = 2;
int rLed = 4;
int gLed = 5;
int bLed = 6;


void setup() {
  // put your setup code here, to run once:
  pinMode(BUZZER, OUTPUT);
  pinMode(rLed, OUTPUT);
  pinMode(gLed, OUTPUT);
  pinMode(bLed, OUTPUT);
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
  delay(200);
}

/* Heating on */
// Heating mode indicators
void HeatOnI() {  // Light to show that heating coil is actively on
  digitalWrite(rLed, LOW);
  digitalWrite(gLed, HIGH);
  digitalWrite(bLed, LOW);
  delay(100);
}

/* Heating standby */
// Indicator
void HeatStandbyI() { // Light to show that heating coil is temporarily off
  digitalWrite(rLed, LOW);
  digitalWrite(gLed, LOW);
  digitalWrite(bLed, HIGH);
  delay(100);
}

void off() {
  digitalWrite(rLed, LOW);
  digitalWrite(gLed, LOW);
  digitalWrite(bLed, LOW);
  delay(1000);
}

void loop() {
  // put your main code here, to run repeatedly:
  PowerSwitchOnI();
  off();
  PowerSwitchOffI();
  off();
  HeatOnI();
  off();
  HeatStandbyI();
  off();
}

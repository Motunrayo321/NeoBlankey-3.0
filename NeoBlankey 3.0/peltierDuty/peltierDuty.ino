int base_peltier = 10;


void setup() {
  // put your setup code here, to run once:
  pinMode(base_peltier, OUTPUT);

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  analogWrite(base_peltier, 100);
  delay(500);
}

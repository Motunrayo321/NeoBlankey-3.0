int batteryLevel = A0;

void setup() {
  // put your setup code here, to run once:
  pinMode(batteryLevel, INPUT);

  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  float level = analogRead(batteryLevel);
  // level = map(level, 0, 1023.0, 0, 8.0);
 float realLevel = (level*8)/1023;
  Serial.print(level); Serial.print("/t");
  Serial.println (realLevel);
  delay(1000);
}

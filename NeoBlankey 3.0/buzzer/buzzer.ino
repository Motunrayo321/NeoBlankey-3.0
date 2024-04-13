const int BUZZER = 9;

void setup() {
  // put your setup code here, to run once:
  pinMode(BUZZER, OUTPUT);
}


// Buzzer function
void BuzzerOn(int frequency, int timer, int num) {  // Audio alarm for all functions
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
  //BuzzerOn(500, 1, 1);
  tone(BUZZER, 500, 300);
  delay(3000);
}

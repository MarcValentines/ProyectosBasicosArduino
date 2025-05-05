#define PIR_PIN 2
#define BUZZER_PIN 8

void setup() {
  // put your setup code here, to run once:
  pinMode(PIR_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  unsigned int movimiento = digitalRead(PIR_PIN);

  if(movimiento == HIGH){
    Serial.print("Hay movimiento");
    digitalWrite(BUZZER_PIN, HIGH);
    delay(1000);
    digitalWrite(BUZZER_PIN, LOW);
  } else {
    Serial.print("nada");
    digitalWrite(BUZZER_PIN, LOW);
  }

  delay(500); //para evitar ruido
}

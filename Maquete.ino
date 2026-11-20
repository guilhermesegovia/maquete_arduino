const int trig1 = 8;
const int echo1 = 9;
const int ledVermelho = 3;

const int trig2 = 10;
const int echo2 = 11;
const int ledAzul = 7;

const int rele = 2;
const int buzzer = 6;

float medir(int trig, int echo) {
  digitalWrite(trig, LOW);
  delayMicroseconds(2);

  digitalWrite(trig, HIGH);
  delayMicroseconds(10);

  digitalWrite(trig, LOW);

  unsigned long tempo = pulseIn(echo, HIGH, 30000);

  if (tempo == 0) return -1;

  return tempo * 0.0343 / 2;
}

void setup() {
  pinMode(trig1, OUTPUT);
  pinMode(echo1, INPUT);
  pinMode(ledVermelho, OUTPUT);

  pinMode(trig2, OUTPUT);
  pinMode(echo2, INPUT);
  pinMode(ledAzul, OUTPUT);

  pinMode(rele, OUTPUT);
  pinMode(buzzer, OUTPUT);

  digitalWrite(rele, HIGH);
  digitalWrite(buzzer, LOW);

  Serial.begin(9600);
}

void loop() {
  float d1 = medir(trig1, echo1);

  delay(60);

  float d2 = medir(trig2, echo2);

  bool sensor1Ativo = (d1 > 0 && d1 <= 10);
  bool sensor2Ativo = (d2 > 0 && d2 <= 10);

  // Sensor 1 controla o LED azul
  digitalWrite(ledAzul, sensor1Ativo ? HIGH : LOW);

  // Sensor 2 controla o LED vermelho
  digitalWrite(ledVermelho, sensor2Ativo ? HIGH : LOW);

  // Relé acompanha o LED azul
  if (sensor1Ativo) {
    digitalWrite(rele, LOW);
    digitalWrite(buzzer, HIGH);

    Serial.println("BOMBA LIGADA");
  } else {
    digitalWrite(rele, HIGH);
    digitalWrite(buzzer, LOW);

    Serial.println("BOMBA DESLIGADA");
  }

  Serial.print("Sensor 1: ");
  Serial.print(d1);
  Serial.print(" cm | Sensor 2: ");
  Serial.println(d2);

  delay(100);
}
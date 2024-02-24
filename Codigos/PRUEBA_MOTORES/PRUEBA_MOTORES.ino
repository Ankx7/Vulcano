#define M1_PWM  27
#define M2_PWM  26
#define M1_AD   25
#define M1_AT   33
#define M2_AD   14
#define M2_AT   32

void setup() {
  // put your setup code here, to run once:

  pinMode(M1_AD, OUTPUT);
  pinMode(M1_AT, OUTPUT);
  pinMode(M2_AD, OUTPUT);
  pinMode(M2_AT, OUTPUT);
  pinMode(M1_PWM, OUTPUT);
  pinMode(M2_PWM, OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:

  //adelante(255, 255);
  secuencia();
  //analogWrite(M1_PWM, 255);
  //analogWrite(M2_PWM, 255);
  //digitalWrite(26, HIGH);


}

void secuencia() {
  adelante(100, 100);
  Serial.println("adelante");

  delay(500);

  izquierda(20, 100);
  Serial.println("izquierda");

  delay(500);

  derecha(100, 20);
  Serial.println("derecha");

  delay(500);

  atras(255, 100);
  Serial.println("atras");

  delay(500);
}

void adelante(int pwmDerecha, int pwmIzquierda) {

  digitalWrite(M1_PWM, HIGH);
  digitalWrite(M2_PWM, HIGH);

  digitalWrite(M1_AD, HIGH);
  digitalWrite(M1_AT, LOW);
  digitalWrite(M2_AD, HIGH);
  digitalWrite(M2_AT, LOW);

}

void izquierda(int pwmDerecha, int pwmIzquierda) {

  analogWrite(M1_PWM, pwmDerecha);
  analogWrite(M2_PWM, pwmIzquierda);

  digitalWrite(M1_AD, HIGH);
  digitalWrite(M1_AT, LOW);
  digitalWrite(M2_AD, HIGH);
  digitalWrite(M2_AT, HIGH);

}

void derecha(int pwmDerecha, int pwmIzquierda) {

  analogWrite(M1_PWM, pwmDerecha);
  analogWrite(M2_PWM, pwmIzquierda);

  digitalWrite(M1_AD, HIGH);
  digitalWrite(M1_AT, HIGH);
  digitalWrite(M2_AD, HIGH);
  digitalWrite(M2_AT, LOW);

}

void atras(int pwmDerecha, int pwmIzquierda) {

  analogWrite(M1_PWM, pwmDerecha);
  analogWrite(M2_PWM, pwmIzquierda);

  digitalWrite(M1_AD, LOW);
  digitalWrite(M1_AT, HIGH);
  digitalWrite(M2_AD, LOW);
  digitalWrite(M2_AT, HIGH);

}

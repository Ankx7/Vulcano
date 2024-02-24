#include <avr/interrupt.h>

// Constantes
const int IR_PIN = 11;      // Pin para generar la señal IR
const int BUTTON_PIN = 2; // Pin para leer el botón

// Variables
volatile bool buttonState = false;  // Estado del botón (presionado o no)

void setup() {
  pinMode(IR_PIN, OUTPUT);
  pinMode(BUTTON_PIN, INPUT);
  pinMode(13, OUTPUT);

  // Configurar temporizador para generar interrupciones a una frecuencia de 38 kHz
  TCCR2A = 0;                 // Configurar el registro TCCR2A
  TCCR2B = _BV(WGM22) | _BV(CS20); // Modo CTC, sin preescalador
  OCR2A = 210;                // Valor de comparación para generar 38 kHz (16 MHz / (2 * 38 kHz) - 1)
  TIMSK2 = _BV(OCIE2A);       // Habilitar interrupción del comparador A del temporizador 2

  Serial.begin(9600);

  // Habilitar interrupciones
  sei();
}

void loop() {
  
}

// Rutina de interrupción del comparador A del temporizador 2
ISR(TIMER2_COMPA_vect) {
  // Generar señal IR de 38 kHz con un duty cycle del 50%
  static bool irState = false;
  digitalWrite(IR_PIN, irState);
  irState = !irState;

  // Actualizar estado del botón
  buttonState = digitalRead(BUTTON_PIN);
}

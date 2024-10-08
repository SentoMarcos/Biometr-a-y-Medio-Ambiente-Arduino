// -*- mode: c++ -*-

/**
 * @file LED.h
 * @brief Controlador para manejar LEDs.
 * @anchor Sento Marcos Ibarra
 */

#ifndef LED_H_INCLUIDO
#define LED_H_INCLUIDO

/**
 * @function esperar
 * @brief Espera un tiempo dado en milisegundos.
 */

void esperar(long tiempo) {
  delay(tiempo);
}

/**
 * @class LED
 * @brief Clase para manejar LEDs.
 */
class LED {
  /**
   * @var numeroLED
   * @brief Número del pin del LED.
   * @example 13
   * @var encendido
   * @brief Estado del LED.
   * @example false
   */
private:
  int numeroLED;
  bool encendido;
public:

  /**
   * @brief Constructor de la clase LED.
   * @param numero Número del pin del LED.
   */
  LED(int numero)
    : numeroLED(numero), encendido(false) {
    pinMode(numeroLED, OUTPUT);
    apagar();
  }

  /**
   * @function encender
   * @brief Enciende el LED.
   */
  void encender() {
    digitalWrite(numeroLED, HIGH);
    encendido = true;
  }

  /**
   * @function apagar
   * @brief Apaga el LED.
   */
  void apagar() {
    digitalWrite(numeroLED, LOW);
    encendido = false;
  }

  /**
   * @function alternar
   * @brief Alterna el estado del LED.
   */
  void alternar() {
    if (encendido) {
      apagar();
    } else {
      encender();
    }
  }  // ()

  /**
   * @function brillar
   * @brief Enciende el LED durante un tiempo dado.
   * @param tiempo Tiempo en milisegundos.
   */
  void brillar(long tiempo) {
    encender();
    esperar(tiempo);
    apagar();
  }
};  // class

// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
#endif

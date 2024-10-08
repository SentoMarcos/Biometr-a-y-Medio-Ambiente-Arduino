
// -*- mode: c++ -*-

/**
 * @file PuertoSerie.h
 * @brief Controlador para manejar un puerto serie.
 * @author Sento Marcos Ibarra
 */
#ifndef PUERTO_SERIE_H_INCLUIDO
#define PUERTO_SERIE_H_INCLUIDO

/**
 * @class PuertoSerie
 * @brief Clase para manejar un puerto serie.
 */
class PuertoSerie {

public:
  /**
   * @brief Constructor de la clase PuertoSerie.
   * @param baudios Velocidad de transmisión en baudios.
   */
  PuertoSerie(long baudios) {
    Serial.begin(baudios);
    // mejor no poner esto aquí: while ( !Serial ) delay(10);
  }  // ()

  /**
   * @brief Espera a que el puerto serie esté disponible.
   */
  void esperarDisponible() {

    while (!Serial) {
      delay(10);
    }

  }  // ()

  /**
   * @brief Escribe un mensaje en el puerto serie.
   * @param mensaje Mensaje a escribir.
   */
  template<typename T>
  void escribir(T mensaje) {
    Serial.print(mensaje);
  }  // ()

};  // class PuertoSerie

// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
#endif

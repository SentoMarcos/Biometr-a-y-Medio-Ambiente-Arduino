// -*- mode: c++ -*-

/**
 * @file Publicador.h
 * @brief Controlador para publicar mediciones de CO2, temperatura y ruido a través de BLE.
 * @author Sento Marcos Ibarra
 */

#ifndef PUBLICADOR_H_INCLUIDO
#define PUBLICADOR_H_INCLUIDO

/**
 * @brief Clase para publicar mediciones de CO2, temperatura y ruido a través de BLE.
 */
class Publicador {

  /**
   * @var beaconUUID
   * @brief UUID del beacon.
   * @example "EPSG-GTI-PROY-3D"
   */
private:

  uint8_t beaconUUID[16] = {
    'E', 'P', 'S', 'G', '-', 'G', 'T', 'I',
    '-', 'P', 'R', 'O', 'Y', '-', '3', 'D'
  };

  // ............................................................
  // ............................................................
public:

  /**
   * @var laEmisora
   * @brief Emisora BLE.
   */
  EmisoraBLE laEmisora{
    "GTI-3A",  //  nombre emisora
    0x004c,    // fabricanteID (Apple)
    4          // txPower
  };


  const int RSSI = -53;  ///< Valor RSSI (Received Signal Strength Indicator).

  // ............................................................
  // ............................................................
public:

  /**
   * @brief Enumeración para identificar las mediciones.
   * @param CO2 Identificador de la medición de CO2.
   * @param TEMPERATURA Identificador de la medición de temperatura.
   * @param RUIDO Identificador de la medición de ruido.
   */
  enum MedicionesID {
    CO2 = 11,
    TEMPERATURA = 12,
    RUIDO = 13
  };

 /**
  * @brief Constructor de la clase Publicador.
  */
  Publicador() {
    // ATENCION: no hacerlo aquí. (*this).laEmisora.encenderEmisora();
    // Pondremos un método para llamarlo desde el setup() más tarde
  }  // ()

  /** 
   * @function encenderEmisora
   * @brief Inicializa el publicador.
   */
  void encenderEmisora() {
    (*this).laEmisora.encenderEmisora();
  }  // ()

  /**
   * @function publicarCO2
   * @brief Publica una medición de CO2.
   * @param valorCO2 Valor de CO2 en ppm.
   * @param contador Contador de la medición.
   */
  void publicarCO2(int16_t valorCO2, uint8_t contador,
                   long tiempoEspera) {

    /**
     * @var major
     * @brief Valor mayor del beacon.
     * @example 0x0B01
     */
    uint16_t major = (MedicionesID::CO2 << 8) + contador;
    (*this).laEmisora.emitirAnuncioIBeacon((*this).beaconUUID,
                                           major,
                                           valorCO2,     // minor
                                           (*this).RSSI  // rssi
    );

    /*
	Globales::elPuerto.escribir( "   publicarCO2(): valor=" );
	Globales::elPuerto.escribir( valorCO2 );
	Globales::elPuerto.escribir( "   contador=" );
	Globales::elPuerto.escribir( contador );
	Globales::elPuerto.escribir( "   todo="  );
	Globales::elPuerto.escribir( major );
	Globales::elPuerto.escribir( "\n" );
	*/

    //
    // 2. esperamos el tiempo que nos digan
    //
    esperar(tiempoEspera);

    //
    // 3. paramos anuncio
    //
    
    (*this).laEmisora.detenerAnuncio();
  }  // ()

  /**
   * @function publicarTemperatura
   * @brief Publica una medición de temperatura.
   * @param valorTemperatura Valor de temperatura en grados Celsius.
   * @param contador Contador de la medición.
   */
  void publicarTemperatura(int16_t valorTemperatura,
                           uint8_t contador, long tiempoEspera) {

    uint16_t major = (MedicionesID::TEMPERATURA << 8) + contador;
    (*this).laEmisora.emitirAnuncioIBeacon((*this).beaconUUID,
                                           major,
                                           valorTemperatura,  // minor
                                           (*this).RSSI       // rssi
    );
    esperar(tiempoEspera);

    (*this).laEmisora.detenerAnuncio();
  }  // ()

};  // class

// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
// --------------------------------------------------------------
#endif

// -*- mode: c++ -*-

/**
 * @file ServicioEnEmisora.h
 * @brief Controlador para añadir servicios y características a una emisora BLE.
 * @author Sento Marcos Ibarra
 */

#ifndef SERVICIO_EMISORA_H_INCLUIDO
#define SERVICIO_EMISORA_H_INCLUIDO

// ----------------------------------------------------
// ----------------------------------------------------
#include <vector>

// ----------------------------------------------------
// alReves() utilidad
// pone al revés el contenido de una array en el mismo array
// ----------------------------------------------------
template< typename T >
T* alReves(T* p, int n) {
  T aux;

  for (int i = 0; i < n / 2; i++) {
    aux = p[i];
    p[i] = p[n - i - 1];
    p[n - i - 1] = aux;
  }
  return p;
}  // ()

// ----------------------------------------------------
// ----------------------------------------------------
uint8_t* stringAUint8AlReves(const char* pString, uint8_t* pUint, int tamMax) {

  int longitudString = strlen(pString);
  int longitudCopiar = (longitudString > tamMax ? tamMax : longitudString);
  // copio nombreServicio -> uuidServicio pero al revés
  for (int i = 0; i <= longitudCopiar - 1; i++) {
    pUint[tamMax - i - 1] = pString[i];
  }  // for

  return pUint;
}  // ()

/**
 * @class ServicioEnEmisora
 * @brief Clase para añadir servicios y características a una emisora BLE.
 */
class ServicioEnEmisora {

public:


  /**
   * @function CallbackCaracteristicaEscrita
   * @brief Definición de un tipo de función callback para manejar escrituras en una característica BLE.
   * @param conn_handle Identificador de la conexión BLE.
   * @param chr Característica BLE.
   * @param data Datos escritos.
   * @param len Longitud de los datos escritos.
   */
  using CallbackCaracteristicaEscrita = void(uint16_t conn_handle,
                                             BLECharacteristic* chr,
                                             uint8_t* data, uint16_t len);
  
  /**
   * @class Caracteristica
   * @brief Clase para añadir características a un servicio BLE.
   */
  class Caracteristica {
    /**
     * @var uuidCaracteristica
     * @brief UUID de la característica.
     * @example "6E400002-B5A3-F393-E0A9-E50E24DCCA9E"
     * @var laCaracteristica
     * @brief Característica BLE.
     */
  private:
    uint8_t uuidCaracteristica[16] = {  // el uuid se copia aquí (al revés) a partir de un string-c
      // least signficant byte, el primero
      '0', '1', '2', '3',
      '4', '5', '6', '7',
      '8', '9', 'A', 'B',
      'C', 'D', 'E', 'F'
    };

    //
    //
    //
    BLECharacteristic laCaracteristica;

  public:

    /**
     * @brief Constructor de la clase Caracteristica.
     * @param nombreCaracteristica_ Nombre de la característica.
     * @param props Propiedades de la característica.
     * @param permisoRead Permisos de lectura.
     * @param permisoWrite Permisos de escritura.
     * @param tam Tamaño de los datos.
     * @note Este constructor inicializa una característica BLE con los valores dados.
     */
    Caracteristica(const char* nombreCaracteristica_)
      : laCaracteristica(stringAUint8AlReves(nombreCaracteristica_, &uuidCaracteristica[0], 16)) {

    }  // ()

    /**
     * @brief Constructor de la clase Caracteristica.
     * @param nombreCaracteristica_ Nombre de la característica.
     * @param props Propiedades de la característica.
     * @param permisoRead Permisos de lectura.
     * @param permisoWrite Permisos de escritura.
     * @param tam Tamaño de los datos.
     * @note Este constructor inicializa una característica BLE con los valores dados.
     */
    Caracteristica(const char* nombreCaracteristica_,
                   uint8_t props,
                   SecureMode_t permisoRead,
                   SecureMode_t permisoWrite,
                   uint8_t tam)
      : Caracteristica(nombreCaracteristica_)  // llamada al otro constructor
    {
      (*this).asignarPropiedadesPermisosYTamanyoDatos(props, permisoRead, permisoWrite, tam);
    }  // ()

  private:
    // .........................................................
    // CHR_PROPS_WRITE , CHR_PROPS_READ ,  CHR_PROPS_NOTIFY
    // .........................................................

  /**
   * @function asignarPropiedades
   * @brief Asigna propiedades a la característica.
   * @param props Propiedades de la característica.
   */
    void asignarPropiedades(uint8_t props) {
      // no puedo escribir AUN si el constructor llama a esto: Serial.println( " laCaracteristica.setProperties( props ); ");
      (*this).laCaracteristica.setProperties(props);
    }  // ()

    // .........................................................
    // BleSecurityMode::SECMODE_OPEN  , BleSecurityMode::SECMODE_NO_ACCESS
    // .........................................................
    
    void asignarPermisos(SecureMode_t permisoRead, SecureMode_t permisoWrite) {
      // no puedo escribir AUN si el constructor llama a esto: Serial.println( "laCaracteristica.setPermission( permisoRead, permisoWrite ); " );
      (*this).laCaracteristica.setPermission(permisoRead, permisoWrite);
    }  // ()

    // .........................................................
    // .........................................................
    void asignarTamanyoDatos(uint8_t tam) {
      // no puedo escribir AUN si el constructor llama a esto: Serial.print( " (*this).laCaracteristica.setFixedLen( tam = " );
      // no puedo escribir AUN si el constructor llama a esto: Serial.println( tam );
      // (*this).laCaracteristica.setFixedLen( tam );
      (*this).laCaracteristica.setMaxLen(tam);
    }  // ()

  public:
    
    /**
     * @function asignarPropiedadesPermisosYTamanyoDatos
     * @brief Asigna propiedades, permisos y tamaño de datos a la característica.
     * @param props Propiedades de la característica.
     * @param permisoRead Permisos de lectura.
     * @param permisoWrite Permisos de escritura.
     * @param tam Tamaño de los datos.
     * @note Este método asigna propiedades, permisos y tamaño de datos a la característica.
     */
    void asignarPropiedadesPermisosYTamanyoDatos(uint8_t props,
                                                 SecureMode_t permisoRead,
                                                 SecureMode_t permisoWrite,
                                                 uint8_t tam) {
      asignarPropiedades(props);
      asignarPermisos(permisoRead, permisoWrite);
      asignarTamanyoDatos(tam);
    }  // ()


    /**
     * @brief Escribe datos en la característica.
     * @param str Datos a escribir.
     * @return Número de bytes escritos.
     */
    uint16_t escribirDatos(const char* str) {
      // Serial.print( " return (*this).laCaracteristica.write( str  = " );
      // Serial.println( str );
      uint16_t r = (*this).laCaracteristica.write(str);

      // Serial.print( ">>>Escritos " ); Serial.print( r ); Serial.println( " bytes con write() " );

      return r;
    }  // ()

    /**
     * @brief Notifica datos en la característica.
     * @param str Datos a notificar.
     * @return Número de bytes notificados.
     */

    uint16_t notificarDatos(const char* str) {

      uint16_t r = laCaracteristica.notify(&str[0]);

      return r;
    }  //  ()

    /**
     * @function instalarCallbackCaracteristicaEscrita
     * @brief Instala un callback para manejar escrituras en la característica.
     * @param cb Función callback para manejar escrituras.
     */
    void instalarCallbackCaracteristicaEscrita(CallbackCaracteristicaEscrita cb) {
      (*this).laCaracteristica.setWriteCallback(cb);
    }  // ()

    /**
     * @function activar
     * @brief Activa la característica.
     */
    void activar() {
      err_t error = (*this).laCaracteristica.begin();
      Globales::elPuerto.escribir(" (*this).laCaracteristica.begin(); error = ");
      Globales::elPuerto.escribir(error);
    }  // ()

  };  // class Caracteristica

  /**
   * @var uuidServicio
   * @brief UUID del servicio.
   * @example "6E400001-B5A3-F393-E0A9-E50E24DCCA9E"
   * @var elServicio
   * @brief Servicio BLE.
   * @var lasCaracteristicas
   * @brief Vector de características.
   */
private:

  uint8_t uuidServicio[16] = {  // el uuid se copia aquí (al revés) a partir de un string-c
    // least signficant byte, el primero
    '0', '1', '2', '3',
    '4', '5', '6', '7',
    '8', '9', 'A', 'B',
    'C', 'D', 'E', 'F'
  };

  //
  //
  //
  BLEService elServicio;

  //
  //
  //
  std::vector< Caracteristica* > lasCaracteristicas;

public:

  /**
   * @brief Constructor de la clase ServicioEnEmisora.
   * @param nombreServicio_ Nombre del servicio.
   * @note Este constructor inicializa un servicio BLE con el nombre dado.
   */
  ServicioEnEmisora(const char* nombreServicio_)
    : elServicio(stringAUint8AlReves(nombreServicio_, &uuidServicio[0], 16)) {

  }  // ()

  /**
   * @brief Constructor de la clase ServicioEnEmisora.
   * @param nombreServicio_ Nombre del servicio.
   * @param uuidServicio_ UUID del servicio.
   * @note Este constructor inicializa un servicio BLE con el nombre y UUID dados.
   */
  void escribeUUID() {
    Serial.println("**********");
    for (int i = 0; i <= 15; i++) {
      Serial.print((char)uuidServicio[i]);
    }
    Serial.println("\n**********");
  }  // ()

  /**
   * @function anyadirCaracteristica]
   * @brief Añade una característica al servicio.
   * @param car Característica a añadir.
   * @note Este método añade una característica al servicio.
   */
  void anyadirCaracteristica(Caracteristica& car) {
    (*this).lasCaracteristicas.push_back(&car);
  }  // ()

  /**
   * @function activarServicio
   * @brief Activa el servicio.
   * @note Este método activa el servicio.
   */
  void activarServicio() {
    // entiendo que al llegar aquí ya ha sido configurado
    // todo: características y servicio

    err_t error = (*this).elServicio.begin();
    Serial.print(" (*this).elServicio.begin(); error = ");
    Serial.println(error);

    for (auto pCar : (*this).lasCaracteristicas) {
      (*pCar).activar();
    }  // for

  }  // ()
  operator BLEService&() {
    // "conversión de tipo": si pongo esta clase en un sitio donde necesitan un BLEService
    return elServicio;
  }  // ()

};  // class

#endif

// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------
// ----------------------------------------------------------

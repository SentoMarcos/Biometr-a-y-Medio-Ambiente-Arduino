# **Biometría y Medio Ambiente - Arduino**

Este proyecto combina tecnologías biométricas y monitoreo ambiental utilizando dispositivos basados en Arduino. El objetivo es recopilar datos biométricos y ambientales (como la calidad del aire, temperatura, humedad, etc.) y emplearlos para análisis y seguimiento. Este sistema puede ser útil para monitorear entornos en tiempo real y hacer un análisis profundo de las condiciones ambientales.

## **Tecnologías utilizadas**
- **Plataforma:** Arduino
- **Lenguaje de programación:** C++
- **Componentes de hardware:**
  - Placa Arduino: [SparkFun Pro nRF52340 Mini](https://www.sparkfun.com/products/15025 "SparkFun Pro nRF52340 Mini")
  - Batería externa: [Lithium Ion Battery - 850mAh](https://www.sparkfun.com/products/13854 "Lithium Ion Battery - 850mAh")
  - Sensor de Gas: [ULPSM-O3 968-046](https://www.example.com "ULPSM-O3 968-046") (sensor de ozono)
  - Otros sensores opcionales para medición biométrica o ambiental.

## **Instalación y configuración**
### Requisitos previos:
1. **Arduino IDE**: Descarga e instala el [Arduino IDE](https://www.arduino.cc/en/software) si aún no lo tienes.
2. **Librerías necesarias**:
   - **Adafruit nRF52**: Esta librería es necesaria para que la placa SparkFun Pro nRF52340 Mini sea reconocida y funcione correctamente. 
   - Sigue la guía de instalación de SparkFun [aquí](https://learn.sparkfun.com/tutorials/nrf52840-development-with-arduino-and-circuitpython "nRF52840 Development") para agregar el soporte en Arduino IDE.
   
### Instrucciones:
1. Clona el repositorio del proyecto:
   ```bash
   git clone https://github.com/SentoMarcos/Biometr-a-y-Medio-Ambiente-Arduino.git
   ```

2. Abre el archivo `.ino` principal en el Arduino IDE.

3. Conecta tu placa **SparkFun Pro nRF52340 Mini** a tu ordenador mediante un cable USB.

4. En el **Arduino IDE**, selecciona la placa y el puerto correspondientes. Esto se hace en el menú `Herramientas > Placa` y `Herramientas > Puerto`.

5. Asegúrate de que todas las librerías necesarias estén instaladas y sincronizadas, luego carga el código a la placa.

6. Conecta los sensores (como el **ULPSM-O3 968-046**) a los pines adecuados según el diagrama de conexión proporcionado en la documentación del proyecto.

7. Conecta la batería **Lithium Ion Battery - 850mAh** para asegurar la alimentación cuando el sistema no esté conectado por USB.

## **Uso**
Una vez que el sistema esté configurado y cargado con el código, la placa comenzará a recopilar datos ambientales (como niveles de ozono) a través del sensor de gas **ULPSM-O3 968-046**. Los datos se pueden visualizar en tiempo real a través del Monitor Serie del Arduino IDE, o se pueden transmitir a una plataforma externa para su análisis.

Es posible adaptar el código para agregar otros sensores biométricos o ambientales, según las necesidades del proyecto.

### Ejemplo de salida:
```
Niveles de Ozono: 0.04 ppm
Temperatura: 25.5 °C
```

## **Autores**
- [SentoMarcos](https://github.com/SentoMarcos)

## **Proyectos Relacionados**
- [Biometría y Medio Ambiente - Android](https://github.com/SentoMarcos/Biometr-a-y-Medio-Ambiente-Android)
- [Biometría y Medio Ambiente - Web](https://github.com/SentoMarcos/Biometr-a-y-Medio-Ambiente-Docker-Web-DB)

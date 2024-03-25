/**
 * @file   pu_sensor.ino
 * @brief  Prueba unitaria del sensor SHT31 con Arduino.
 *
 * Este programa realiza la prueba unitaria del sensor SHT31, midiendo la temperatura
 * y la humedad y mostrando los resultados en el monitor serie. Se utiliza la biblioteca
 * Adafruit_SHT31 para la comunicación con el sensor a través de I2C.
 *
 * @author Juan David Carvajal Cucuñame, María Paula Cabezas Charry
 * @date   Fecha de Creación
 */

#include <Arduino.h>
#include <Wire.h>
#include "Adafruit_SHT31.h"

Adafruit_SHT31 sht31 = Adafruit_SHT31(); /**< Objeto para interactuar con el sensor SHT31 */

/**
 * @brief Inicialización del programa y configuración del sensor.
 *
 * Se establece la comunicación serial y se intenta inicializar el sensor SHT31.
 * Si no se puede encontrar el sensor, se imprime un mensaje de error y el programa
 * entra en un bucle infinito.
 */
void setup() {
  Serial.begin(115200);

  if (!sht31.begin(0x44)) {   
    Serial.println("Sensor no conectado");
    while (1) delay(1);
  }
}

/**
 * @brief Bucle principal del programa.
 *
 * En cada iteración del bucle, se lee la temperatura y la humedad del sensor SHT31.
 * Si los valores son válidos, se imprimen en el monitor serie. En caso de que haya un
 * valor nulo, se imprime un mensaje de error correspondiente. Luego, el programa espera
 * 60 segundos antes de realizar la siguiente lectura.
 */
void loop() {
  float temp = sht31.readTemperature(); /**< Variable para almacenar la temperatura leída del sensor */
  float hum = sht31.readHumidity();    /**< Variable para almacenar la humedad leída del sensor */

  if (!isnan(temp)) { 
    Serial.print("Temperatura(°C): "); 
    Serial.print(temp); 
    Serial.print("\t\t");
  } else { 
    Serial.println("Valor nulo de temperatura"); /**< Mensaje de error si la temperatura es nula */
  }
  
  if (!isnan(hum)) {  
    Serial.print("Humedad(%): "); 
    Serial.println(hum);
  } else { 
    Serial.println("Valor nulo de humedad"); /**< Mensaje de error si la humedad es nula */
  }

  delay(60000); /**< Espera 60 segundos antes de realizar la siguiente lectura */
}

/**
 * @file   main.cpp
 * @brief  Prueba unitaria del sensor SHT31 con ESP32.
 *
 * Este programa realiza la prueba unitaria del sensor SHT31, midiendo la temperatura
 * y la humedad y mostrando los resultados en el monitor serie. Se utiliza la biblioteca
 * Adafruit_SHT31 para la comunicación con el sensor a través de I2C.
 *
 * @author Juan David Carvajal Cucuñame, María Paula Cabezas Charry
 */

#include <Arduino.h>
#include <Wire.h>
#include <SPI.h>
#include "Adafruit_SHT31.h"

// Objeto para interactuar con el sensor SHT31
Adafruit_SHT31 sht31 = Adafruit_SHT31();

/**
 * @brief Inicialización del programa y configuración del sensor.
 *
 * Establece la comunicación serial e intenta inicializar el sensor SHT31.
 * Si no se puede encontrar el sensor, imprime un mensaje de error y el programa
 * entra en un bucle infinito.
 */
void setup()
{
  Serial.begin(115200); // velocidad para ESP32

  if (!sht31.begin(0x44))
  {
    Serial.println("Sensor no conectado");
    while (1)
      delay(1);
  }
  Serial.println("Sensor inicializado correctamente");
}

/**
 * @brief Bucle principal del programa.
 *
 * En cada iteración del bucle, se lee la temperatura y la humedad del sensor SHT31.
 * Si los valores son válidos, se imprimen en el monitor serie. En caso de que haya un
 * valor nulo, se imprime un mensaje de error correspondiente. Luego, el programa espera
 * 60 segundos antes de realizar la siguiente lectura.
 */
void loop()
{
  float temp = sht31.readTemperature();
  float hum = sht31.readHumidity();

  if (!isnan(temp))
  {
    Serial.print("Temperatura(°C): ");
    Serial.print(temp);
    Serial.print("\t\t");
  }
  else
  {
    Serial.println("Valor nulo de temperatura");
  }

  if (!isnan(hum))
  {
    Serial.print("Humedad(%): ");
    Serial.println(hum);
  }
  else
  {
    Serial.println("Valor nulo de humedad");
  }

  delay(60000);
}

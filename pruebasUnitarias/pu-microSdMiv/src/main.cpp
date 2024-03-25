/**
* @file   main.cpp
* @brief  Prueba unitaria del módulo MicroSD con la ESP32.
*
* Este programa realiza una prueba unitaria del módulo MicroSD, escribiendo la frase
* "Funciona bien" en un archivo llamado "prueba.txt". Se utiliza la biblioteca SD
* para la gestión de la tarjeta.
*
* @author Juan David Carvajal Cucuñame, Maria Paula Cabezas Charry
*/

#include <Arduino.h>
#include <Wire.h>
#include <SD.h>

// Pin de selección del módulo MicroSD
const int chipSelect = 5;

/**
* @brief Inicialización del programa y configuración del módulo MicroSD.
*
* Se establece la comunicación serial y se intenta inicializar la tarjeta MicroSD.
* Si no se puede inicializar, se imprime un mensaje de error y el programa se detiene.
*/
void setup() {
  Serial.begin(115200);

  // Inicialización del módulo MicroSD
  if (!SD.begin(chipSelect)) {
    Serial.println("Error al inicializar la tarjeta MicroSD");
    while (1);
  }

  Serial.println("Tarjeta MicroSD inicializada correctamente");
  
}

/**
* @brief Bucle principal del programa.
*
* Abre el archivo "prueba.txt" en modo de escritura, escribe la frase "Funciona bien"
* y luego cierra el archivo. El programa espera 5 segundos antes de realizar la
* siguiente escritura.
*/
void loop() {
  // Abre el archivo en modo de escritura
  File dataFile = SD.open("/prueba.txt", FILE_WRITE);

  // Verifica si se pudo abrir el archivo correctamente
  if (dataFile) {
    Serial.println("Escribiendo en el archivo: prueba.txt");
    
    // Escribe la frase en el archivo
    dataFile.println("Funciona bien");

    // Cierra el archivo
    dataFile.close();
    Serial.println("Escritura completada");
  } else {
    Serial.println("Error al abrir el archivo");
  }

  delay(5000);
}
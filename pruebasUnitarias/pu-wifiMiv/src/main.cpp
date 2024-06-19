/**
 * @file   main.cpp
 * @brief  Prueba unitaria del componente de conexión WiFi del ESP32.
 *
 * Este programa realiza una prueba unitaria del componente de conexión WiFi de la ESP32.
 * Se conecta a una red WiFi especificada por el SSID y la contraseña, y luego imprime la
 * dirección IP local de la ESP32 en el monitor serie.
 *
 * @author Juan David Carvajal Cucuñame, María Paula Cabezas Charry
 */

#include <Arduino.h>
#include <WiFi.h>

// SSID y contraseña de la red WiFi
const char *SSID = "NombreDeTuRed";
const char *PASSWORD = "TuContrasena";

void setup()
{
  Serial.begin(115200);
  while (!Serial)
    ;

  Serial.println("Conectando a WiFi...");
  WiFi.begin(SSID, PASSWORD);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("¡WiFi conectado!");
  Serial.print("Dirección IP: ");
  Serial.println(WiFi.localIP().toString());
}

void loop() {}
/**
 * @file   main.cpp
 * @brief  Prueba unitaria de transmisión de datos con ESP32.
 *
 * Este programa envía datos a una base de datos en MySQL utilizando Xampp como bundle de desarrollo.
 *
 * @author Juan David Carvajal Cucuñame, María Paula Cabezas Charry
 */

#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>

const char *SSID = "NombreDeTuRed";
const char *PASSWORD = "TuContrasena";

/**
 * @brief Configuración inicial de la ESP32.
 */
void setup()
{
  // Inicializar la comunicación serial
  Serial.begin(115200);

  // Conectar a la red Wi-Fi
  WiFi.begin(SSID, PASSWORD);

  // Esperar a que se establezca la conexión
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Conectando a WiFi...");
  }

  // Mostrar mensaje de conexión exitosa
  Serial.println("Conectado a WiFi");
}

/**
 * @brief Ciclo principal de la ESP32.
 */
void loop()
{
  // Dato a enviar a la base de datos
  String data = "dato=Funciona";

  // Verificar la conexión a la red Wi-Fi
  if (WiFi.status() == WL_CONNECTED)
  {
    Serial.println("Mandando datos");
    // Instancia de cliente HTTP
    HTTPClient http;

    // Establecer comunicación con el servidor
    http.begin("http://192.168.3.192/pruebaEnvioDatos/pruebaEnvioDatos.php");

    // Agregar cabecera de la petición
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Enviar petición HTTPS de tipo POST
    int httpResponseCode = http.POST(data);

    // Verificar el código de respuesta HTTP
    if (httpResponseCode != 200)
    {
      Serial.println("Falló el envío");
    }
    Serial.println("Datos enviados correctamente");
    // Liberar recursos
    http.end();
  }
  else
  {
    Serial.println("No hay conexión a WiFi");
  }

  // Esperar 10 segundos antes de enviar los datos nuevamente
  delay(10000);
}
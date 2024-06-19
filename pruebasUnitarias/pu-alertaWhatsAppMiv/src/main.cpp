/**
 * @file   main.cpp
 * @brief  Prueba unitaria del componente de generación de alertas con CallMeBot.
 *
 * @author Juan David Carvajal Cucuñame, María Paula Cabezas Charry
 */
#include <Arduino.h>
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <UrlEncode.h>
#include <HTTPClient.h>

const char *SSID = "NombreDeTuRed";
const char *PASSWORD = "TuContrasena";
String P_NUMBER = "TuNumeroDeCelular";
String API_KEY_BOT = "TuLlave";

void setup()
{
  // Inicializa la comunicación serial para imprimir en el monitor
  Serial.begin(115200);

  // Conecta a la red Wi-Fi
  WiFi.begin(SSID, PASSWORD);

  // Espera a que se establezca la conexión Wi-Fi
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }

  Serial.println("Conectado a Wi-Fi");
}

void loop()
{
  // URL de la API de CallMeBot para enviar mensajes de WhatsApp
  String url = "https://api.callmebot.com/whatsapp.php?phone=" + P_NUMBER + "&apikey=" + API_KEY_BOT + "&text=" + urlEncode("Funciona el bot de WhatsApp");

  // Verifica si hay conexión Wi-Fi activa
  if (WiFi.status() == WL_CONNECTED)
  {
    // Crea una instancia de HTTPClient para realizar la petición HTTP
    HTTPClient http;

    // Establece la URL de destino para la petición
    http.begin(url);

    // Agrega el encabezado "Content-Type" para indicar el tipo de datos
    http.addHeader("Content-Type", "application/x-www-form-urlencoded");

    // Envía una petición HTTP POST a la API para enviar el mensaje
    int httpResponseCode = http.POST(url);

    // Imprime el código de respuesta HTTP
    Serial.print("Código de respuesta HTTP: ");
    Serial.println(httpResponseCode);

    // Evalúa el código de respuesta
    if (httpResponseCode != 200)
    {
      Serial.println("Error al enviar el mensaje de WhatsApp");
    }
    else
    {
      Serial.println("Mensaje de WhatsApp enviado correctamente");
    }

    // Libera los recursos utilizados por la petición HTTP
    http.end();
  }
  else
  {
    // Si no hay conexión Wi-Fi, imprime un mensaje de error
    Serial.println("Error de conexión Wi-Fi, no se puede enviar el mensaje");
  }

  // Agrega un retraso para evitar saturar la comunicación serial
  delay(1000);
}

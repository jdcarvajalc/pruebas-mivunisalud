/**
 * @file   main.cpp
 * @brief  Prueba unitaria del componente de gestión del tiempo con ESP32.
 *
 * @author Juan David Carvajal Cucuñame, María Paula Cabezas Charry
 */
#include <Arduino.h>
#include <WiFi.h>
#include <ESP32Time.h>

const char *SSID = "NombreDeTuRed";
const char *PASSWORD = "TuContrasena";

// Define el servidor NTP y las compensaciones horarias (ajusta para tu ubicación)
const char *NTP_SERVER = "pool.ntp.org";
const long GMT_OFFSET_SEC = -5 * 3600; // Reemplaza con tu diferencia horaria GMT en horas
const int DAYLIGHT_OFFSET_SEC = 0;

// Declarar variables para fecha y marca de tiempo
String fecha, marca_de_tiempo;

// Crea una instancia del objeto ESP32Time
ESP32Time rtc;

/**
 * @brief Actualiza el reloj en tiempo real (RTC) con la hora del servidor NTP.
 *
 * Esta función configura el RTC utilizando el servidor NTP y las compensaciones horarias especificadas.
 * Luego, recupera la hora actual del servidor y configura el RTC en consecuencia.
 */
void actualizarRTC()
{
  configTime(GMT_OFFSET_SEC, DAYLIGHT_OFFSET_SEC, NTP_SERVER);
  struct tm timeinfo;
  if (getLocalTime(&timeinfo))
  {
    rtc.setTimeStruct(timeinfo);
  }
  else
  {
    Serial.println("Fallo al obtener la hora del servidor NTP");
  }
}

void setup()
{
  // Inicializa la comunicación serial para imprimir en el monitor
  Serial.begin(115200);

  // Conectar a la red Wi-Fi
  WiFi.begin(SSID, PASSWORD);

  // Esperar a que se establezca la conexión
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
  }

  // Comienza actualizando el RTC con la hora del servidor NTP
  actualizarRTC();
}

void loop()
{
  fecha = rtc.getTime("%Y-%m-%d");           // Formatea la fecha como AAAA-MM-DD
  marca_de_tiempo = rtc.getTime("%H:%M:%S"); // Formatea la hora como HH:MM:SS

  // Imprime la fecha y la marca de tiempo formateadas en el monitor serial
  Serial.print("Fecha actual: ");
  Serial.println(fecha);
  Serial.print("Hora actual: ");
  Serial.println(marca_de_tiempo);

  // Agrega un retraso para evitar saturar el monitor serial (opcional)
  delay(1000);
}

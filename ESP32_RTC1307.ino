#include <Wire.h>
#include "RTClib.h"

RTC_DS1307 rtc;  // Crea un objeto de la clase RTC_DS1307 llamado "rtc" que se utilizará para interactuar con el RTC.

void setup () {
  Serial.begin(9600);  // Inicia la comunicación serie a una velocidad de 9600 baudios.

  Wire.begin(32, 33);  // Inicia la comunicación I2C en los pines SDA = 32 y SCL = 33.

  if (! rtc.begin()) {  // Verifica si se puede inicializar correctamente el RTC.
    Serial.println("No se pudo encontrar RTC");  // Imprime un mensaje de error si no se encuentra el RTC.
    Serial.flush();
    abort();
  }

  if (! rtc.isrunning()) {  // Verifica si el RTC no está en funcionamiento.
    Serial.println("RTC NO se está ejecutando, ¡configuremos la hora!");  // Imprime un mensaje indicando que el RTC no está en ejecución.
    rtc.adjust(DateTime(F(__DATE__), F(__TIME__)));  // Ajusta la fecha y hora del RTC utilizando la fecha y hora en que se compiló el código.
  }
}

void loop () {
  DateTime now = rtc.now();  // Obtiene la fecha y hora actual del RTC y la guarda en la variable "now" de tipo DateTime.

  // Imprime en el puerto serie la hora, los minutos, los segundos, el día, el mes y el año utilizando las funciones de la clase DateTime.
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.print(' ');
  Serial.print(now.day(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.year(), DEC);
  Serial.println();

  delay(3000);  // Espera 3 segundos antes de repetir el bucle para mostrar la fecha y hora actualizada cada 3 segundos.
}

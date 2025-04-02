/* Introducción a Microcontroladores, Ejercicio 2:
 * Configurar un pin TOUCH para que funcione como un “pulsador”. Mostrar 
 *   en pantalla (terminal serie) cada vez que se pulsa.
 * José Luis Muñiz Traviesas, 01-04-25
 * Ejemplo modificado de: https://docs.espressif.com/projects/arduino-esp32/en/latest/api/touch.html 
 */

// ESP32 Touch Test
// Test del pin de TOUCH - T0 está en el GPIO 4.


void setup() {
  Serial.begin(115200);
  delay(1000);  // Esperamos al monitor serie
  Serial.println("ESP32 Touch Test");
}

void loop() {
  Serial.println(String("Medida: ") + touchRead(T0));  // Imprimimos en pantalla la medida del sensor touch del pin 4
  delay(1000);  // Esperamos 1 segundo
}
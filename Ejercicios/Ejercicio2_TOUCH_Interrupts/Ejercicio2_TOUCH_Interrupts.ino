/* Introducción a Microcontroladores, Ejercicio 2 (Versión Interrupciones):
 * Configurar un pin TOUCH para que funcione como un “pulsador”. Mostrar 
 *   en pantalla (terminal serie) cada vez que se pulsa.
 * José Luis Muñiz Traviesas, 01-04-25
 * Ejemplo modificado de: https://docs.espressif.com/projects/arduino-esp32/en/latest/api/touch.html 
 */

/*
This is an example how to use Touch Intrrerupts
The bigger the threshold, the more sensible is the touch
*/

const int THRESHOLD = 40;

bool touch1detected = false;
bool touch2detected = false;

void gotTouch1() {
    touch1detected = true;
}

void gotTouch2() {
    touch2detected = true;
}

void setup(){
    Serial.begin(115200);
    delay(1000);  // give me time to bring up serial monitor
    Serial.println("ESP32 Touch Interrupt Test");
    touchAttachInterrupt(T2, gotTouch1, THRESHOLD);
    touchAttachInterrupt(T3, gotTouch2, THRESHOLD);
}

void loop(){
    if(touch1detected){
        touch1detected = false;
        Serial.println("Touch 1 detected");
    }
    if(touch2detected){
        touch2detected = false;
        Serial.println("Touch 2 detected");
    }
}
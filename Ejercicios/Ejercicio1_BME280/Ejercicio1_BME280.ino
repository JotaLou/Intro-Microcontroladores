/* Introducción a Microcontroladores, Ejercicio 1:
 * Programar la lectura de la temperatura y presión cada 10 segundos con 
 *  un sensor BME280 (I2C).
 * José Luis Muñiz Traviesas, 01-04-25
 * Ejemplo modificado de: https://github.com/finitespace/BME280/blob/master/examples/BME_280_I2C_Test/BME_280_I2C_Test.ino
 */

#include <BME280I2C.h>      // https://github.com/finitespace/BME280
#include <Wire.h>           // Librería de I2C de Arduino; https://docs.arduino.cc/language-reference/en/functions/communication/wire/

// Terminal Serie
const int HARDWARE_BAUDRATE = 115200;   // Tasa de baudios del terminal serie hardware
// BME280 
#define WIRE Wire    // Se suele hacer esto para poder cambiar entre Wire, Wire1, ...
const int SDA_PIN = 21; // Conectar al pin SDA del BME280 
const int SCL_PIN = 22; // Conectar al pin SCL del BME280
const int MEASURE_T_MS = 5000;  // Tiempo de medida en milisegundos (ms)

BME280I2C BME;  // Default : forced mode, standby time = 1000 ms; Oversampling = pressure ×1, temperature ×1, humidity ×1, filter off
bool humidity_available = false; // Flag para saber si es BME280 o BMP280 (El BMP no puede medir humedad)

void setup(){
    Serial.begin(HARDWARE_BAUDRATE);  // Tratamos de iniciar el terminal serie
    while(!Serial){} // Esperamos a que esté disponible el terminal serie
    Serial.println(String("Terminal Serie Iniciado, Baudios: ") + HARDWARE_BAUDRATE);

    WIRE.setPins(SDA_PIN, SCL_PIN);  // Configuramos los pines de I2C
    WIRE.begin(); // Iniciamos el bus de I2C
    Serial.println("Bus de I2C Iniciado, PIN SDA: " + String(PIN_SDA) + "; PIN SCL: " + String(PIN_SCL));
    // Comunicación inicial con el sensor
    while(!BME.begin()){
        Serial.println("No pudo encontrarse el sensor BME280 ");
        // Esperamos un segundo, imprimiendo un punto cada 200ms
        for(int i=0; i<5; i++){
            delay(200);
            Serial.print(".");
        }
    }
    // Discernir tipo de sensor
    switch(BME.chipModel()){
        case BME280::ChipModel_BME280:
            Serial.println("BME280 encontrado. Humedad disponible.");
            humidity_available = true;
            break;
        case BME280::ChipModel_BMP280:
            Serial.println("Sensor de tipo BMP280. Humedad no disponible");
            humidity_available = false;
            break;
        default:
        Serial.println("Tipo de sensor no reconocido. ERROR");
        delay(2000);    // Esperamos 2 segundos
        exit(1);        // Reiniciamos
    }
}

void loop(){
    // Variables para almacenar las medidas
    float temp(NAN), hum(NAN), pres(NAN);
    // Elegimos unidades para las medidas del sensor
    BME280::TempUnit tempUnit(BME280::TempUnit_Celsius); // grados centígrados
    BME280::PresUnit presUnit(BME280::PresUnit_hPa);    // hectoPascales

    BME.read(pres, temp, hum, tempUnit, presUnit);

    Serial.print("Temperatura: ");
    Serial.print(temp);
    Serial.print("°C");
    if(humidity_available){
        Serial.print("\t\tHumedad: ");
        Serial.print(hum);
        Serial.print("% RH");
    }
    Serial.print("\t\tPresion: ");
    Serial.print(pres);
    Serial.println("hPa");
    delay(MEASURE_T_MS);
}

/*
 
  Connection light intensity sensor:

    VCC -> 3V3 or 5V
    GND -> GND
    SCL -> D3
    SDA -> D4
    ADD -> (not connected) or GND

   Connection UV light sensor:

    VCC -> 3V3 or 5V
    GND -> GND
    Analog -> A0

   Connection temp humi altitude and pressure sensor:

   
    VCC -> 3V3 or 5V
    GND -> GND
    SCL -> D1
    SDA -> D2
    
*/
#include <Wire.h>
#include <BH1750.h>
#include <DHT.h>        // including the library of DHT11 temperature and humidity sensor
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BME280.h>
#define SEALEVELPRESSURE_HPA (1013.25)
#define DHTTYPE DHT11   // DHT 11
#define dht_dpin D5

Adafruit_BME280 bme;

DHT dht(dht_dpin, DHTTYPE); 
BH1750 lightMeter(0x23);
const int UV=A0;

void setup() {
dht.begin();
Serial.begin(115200);
Serial.println("Humidity and temperature\n\n");

}


void light(){
Wire.begin(D4, D3);  //SDA = D4  SCL = D3
if (lightMeter.begin(BH1750::CONTINUOUS_HIGH_RES_MODE)) {
    float lux = lightMeter.readLightLevel();
         
    Serial.print("Light intensity: ");
    Serial.println(lux);
  }
 
} 


void pressure(){
Wire.begin(D2, D1);
if (!bme.begin(0x76)) {
    Serial.println("Could not find a valid BME280 sensor, check wiring!");
    while (1);
  } 
  Serial.print("Temperature = ");
  Serial.print(bme.readTemperature());
  Serial.println("*C");

  Serial.print("Pressure = ");
  Serial.print(bme.readPressure() / 100.0F);
  Serial.println("hPa");

  Serial.print("Approx. Altitude = ");
  Serial.print(bme.readAltitude(SEALEVELPRESSURE_HPA));
  Serial.println("m");

  Serial.print("Humidity = ");
  Serial.print(bme.readHumidity());
  Serial.println("%");
  
}

void loop() {
int valeur_UV=analogRead(UV);
light();
float h = dht.readHumidity();
float t = dht.readTemperature();   
Serial.print("Current humidity = ");
Serial.print(h);
Serial.print("%  ");
Serial.print("temperature = ");
Serial.print(t); 
Serial.println("C  ");
Serial.print("uv light: ");
Serial.println(valeur_UV);
pressure();
Serial.println();
delay(7000);
}

#include "DHT.h"

#define DHTPIN 2     // what digital pin we're connected to

// Uncomment whatever type you're using!
#define DHTTYPE DHT11   // DHT 11
//#define DHTTYPE DHT22   // DHT 22  (AM2302), AM2321
//#define DHTTYPE DHT21   // DHT 21 (AM2301)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  dht.begin();
}

void loop() {

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float h = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float t = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(h) || isnan(t) || isnan(f)) {
    Serial.println("Failed to read from DHT sensor!");
    return;
  }

  // Calcul de la temperature ressentie en Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(t, h, false);

  //Envoi de la temperature (type 6)
  Serial.print("1;1;1;0;7;"+String(hic)+"\n");

  //Envoi du taux d'humidite (type 7)
  Serial.print("1;2;1;0;8;"+String(h)+"\n");


  // Wait a few seconds between measurements.
  delay(3600000); //toutes les heures
  //delay(2000); // 2 secondes

}

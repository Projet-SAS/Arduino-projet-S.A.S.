#include <XBee.h>
// shield Arduino
#define RXPIN 0
#define TXPIN 1
#define BAUDRATE 9600

// library :  https://www.arduino.cc/en/Reference/SoftwareSerial
SoftwareSerial xbee =  SoftwareSerial(RXPIN, TXPIN);
// luminosity
int photocellPin = 7; // the cell and 10K pulldown are connected to a0
int photocellReading; // the analog reading from the analog resistor divider
<<<<<<< HEAD
// temperature
int chaleurIntPin = 10;
=======
//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
int calibrationTime = 10;

int ledPin = 13;                // choose the pin for the LED
int inputPin = 15;               // choose the input pin (for PIR sensor)
int pirState = LOW;             // we start, assuming no motion detected
int val = 0;                    // variable for reading the pin status
>>>>>>> refs/remotes/origin/master

 
void setup()
{
  pinMode(ledPin, OUTPUT);      // declare LED as output
  pinMode(inputPin, INPUT);     // declare sensor as input

  Serial.print("calibrating sensor ");
  for(int i = 0; i < calibrationTime; i++){
    Serial.print(".");
    delay(1000);
  }
    pinMode(13, OUTPUT);
    // bauderate + print
    Serial.begin(BAUDRATE);
    Serial.println("[INFOS] Arduino 1 ok.");
 
    // Envois un message aux modules xbee
    xbee.begin(BAUDRATE);
    xbee.println("[INFOS] Arduino 1 ok.");
}
 
void loop()
{
<<<<<<< HEAD
  // read tmp36 value
  int inTmp36 = analogRead(chaleurIntPin);
  //Serial.println(inTmp36);
  //float voltage = inTmp36 * 0.5;
  //voltage /= 1024.0;
  
  //Serial.println(voltage);
  
  // 5/1023 calcul pour °C
  float temperatureC = ((inTmp36*0.004882) - 0.50) * 100 ;
  
  Serial.print(temperatureC);
=======

    val = digitalRead(inputPin);  // read input value
  Serial.println(val);
  if (val == HIGH) { // check if the input is HIGH
    digitalWrite(ledPin, HIGH);  // turn LED ON
    delay(150);

    if (pirState == LOW) {
      // we have just turned on
      Serial.println("Motion detected!");
      // We only want to print on the output change, not state
      pirState = HIGH;
    }
  } else {
    digitalWrite(ledPin, LOW); // turn LED OFF
    delay(300);
    if (pirState == HIGH){
      // we have just turned of
      Serial.println("Motion ended!");
      // We only want to print on the output change, not state
      pirState = LOW;
    }
  }
    int chaleurIntPin = 10;
    char c[256];
    char dfcon;
    
    int inTmp36 = analogRead(chaleurIntPin);
    //Serial.println(inTmp36);
    //float voltage = inTmp36 * 0.5;
    //voltage /= 1024.0;
    
    //Serial.println(voltage);
 
    // 5/1023
    float temperatureC = ((inTmp36*0.004882) - 0.50) * 100 ;
    
    Serial.print(temperatureC);
    //dfcon = Serial.print(temperatureC);
    
    
    
    // Affiche les informations qu'il reçois
    if (XBeeSerial.available()) {
        Serial.println(XBeeSerial.read());
    }
 
    //if (Serial.available() > 0) {
     // XBeeSerial.print(dfcon);
    //}
 
    delay(2000);


>>>>>>> refs/remotes/origin/master

  photocellReading = analogRead(photocellPin);
  Serial.print("   Analog reading = ");
  Serial.print(photocellReading); // the raw analog reading
  // We'll have a few threshholds, qualitatively determined
  if (photocellReading < 10) {
    Serial.println(" - Noir");
  } else if (photocellReading < 200) {
    Serial.println(" - Sombre");
  } else if (photocellReading < 500) {
    Serial.println(" - Lumiere");
  } else if (photocellReading < 800) {
    Serial.println(" - Lumineux");
  } else {
    Serial.println(" - Tres lumineux");
  }
  delay(2000);
<<<<<<< HEAD

  xbee.readPacket();

=======
>>>>>>> refs/remotes/origin/master

}


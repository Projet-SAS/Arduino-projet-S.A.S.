// Ajouts des librairies
  //DS18B20 libs
  #include <OneWire.h>
  #include <DallasTemperature.h>
  //Xbee lib
  #include <SoftwareSerial.h>

// Xbee PIN
  #define RXPIN 0
  #define TXPIN 1
// Xbee Init
  SoftwareSerial XBeeSerial =  SoftwareSerial(RXPIN, TXPIN);

// fréquence
  #define BAUDRATE 9600

// Data wire is plugged into port 2 on the Arduino
  #define ONE_WIRE_BUS 2
// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
  OneWire oneWire(ONE_WIRE_BUS);
// Pass our oneWire reference to Dallas Temperature. 
  DallasTemperature sensors(&oneWire);


// Détecteur de présence
  int ledPin = 13;                // Pin de la LED
  int inputPin = 15;               // Pin d'entrée du PIR
  int pirState = LOW;             // we start, assuming no motion detected
  int val = 0;                    // variable for reading the pin status

// Photorésistance
  int photocellPin = 7; // the cell and 10K pulldown are connected to a0
  int photocellReading; // the analog reading from the analog resistor divider
//the time we give the sensor to calibrate (10-60 secs according to the datasheet)
  int calibrationTime = 10;

/*
 * The setup function.
 */
void setup(void)
{
  pinMode(ledPin, OUTPUT);      // LED as output
  pinMode(inputPin, INPUT);     // PIR sensor as input
  
  // Calibrate sensor for detect movement.
    //Serial.print("calibrating sensor ");
    for(int i = 0; i < calibrationTime; i++){ // see CalibrationTime var.
      delay(1000);
    }
  
  // start serial port
    Serial.begin(BAUDRATE);
    Serial.println("[INFOS] Arduino 1 ok.");
 
    // Envois un message aux modules xbee
    XBeeSerial.begin(BAUDRATE);
    XBeeSerial.println("[INFOS] Arduino 1 ok.");

  // Start up the library
    sensors.begin();
}

/*
 * Main function.
 */
void loop(void)
{ 
  /*----------------------------------------------------
   *                 PIR MOVEMENT SENSOR
   ---------------------------------------------------*/
    val = digitalRead(inputPin);  // There is someone?
    Serial.print("PIR(True/False) : ");Serial.println(val); // print result
    
    if (val == HIGH) { // check if the input is HIGH
      digitalWrite(ledPin, HIGH);  // turn LED ON
      delay(150);

      if (pirState == LOW) {
        // we have just turned on
        Serial.println("PIR - INFOS : Motion detected!");
        // We only want to print on the output change, not state
        pirState = HIGH;
      }
    } else {
      digitalWrite(ledPin, LOW); // turn LED OFF
      delay(300);
      
      if (pirState == HIGH){
        // we have just turned of
        Serial.println("PIR - INFOS : Motion ended!");
        // We only want to print on the output change, not state
        pirState = LOW;
      }
    }


  /*----------------------------------------------------
   *                 D18B20 SENSOR
   ---------------------------------------------------*/
    // call sensors.requestTemperatures() to issue a global temperature 
    // request to all devices on the bus
    //Serial.print("Requesting temperatures...");
    sensors.requestTemperatures(); // Send the command to get temperatures
    //Serial.println("DONE");
    // After we got the temperatures, we can print them here.
    // We use the function ByIndex, and as an example get the temperature from the first sensor only.
    Serial.print("DS18B20 : ");
    Serial.println(sensors.getTempCByIndex(0));  


  /*----------------------------------------------------
   *                 TMP36 SENSOR
   ---------------------------------------------------*/  
    int chaleurIntPin = 10;
    int inTmp36 = analogRead(chaleurIntPin);
    // 5/1023
      float temperatureC = ((inTmp36*0.004882) - 0.50) * 100 ;
    Serial.print("TMP36 : ");Serial.println(temperatureC);
  
  /*----------------------------------------------------
   *                 PHOTOCELL SENSOR
   ---------------------------------------------------*/
    photocellReading = analogRead(photocellPin);
    Serial.print("Analog reading = ");
    Serial.print(photocellReading); // the raw analog reading
    // We'll have a few threshholds, qualitatively determined
    if (photocellReading < 10) { Serial.println(" - Noir"); }
    else if (photocellReading < 200) { Serial.println(" - Sombre"); }
    else if (photocellReading < 500) { Serial.println(" - Lumiere"); }
    else if (photocellReading < 800) { Serial.println(" - Lumineux"); }
    else { Serial.println(" - Tres lumineux"); }
  
  /*----------------------------------------------------
   *                 XBEE SENSOR
   ---------------------------------------------------*/
    if (XBeeSerial.available()) {
      Serial.println(XBeeSerial.read());
    }
}


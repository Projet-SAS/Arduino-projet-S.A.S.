#include <OneWire.h>
#include <DallasTemperature.h>
#include <SoftwareSerial.h>

int calibrationTime = 10;
int ONE_WIRE_BUS = 2;
int ds18b20Pin = 2; // interrupt 0
int tmpPin[] = { 8 , 9 }; // analog in
int lumPin[] = { 12, 13, 14, 15 }; // analog in
int movementPin[] = { 31, 33, 35 }; // digital
int lightning;
int heating;
int stagePin;
int ballastPin;

// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire); // Pass our oneWire reference to Dallas Temperature. 

void setup(void)
{
	Serial.begin(9600);
	Serial.println("load arduino");

	while (! Serial);
	Serial.println("[INFOS] Arduino 1 ok.");

	//the time we give the sensor to calibrate (10-60 secs according to the datasheet) PIR Sensor
	Serial.print("calibrating sensor ");
	for(int i = 0; i < calibrationTime; i++)
		{
			Serial.print('.');
			delay(1000);
		}
	Serial.print('\n');
	sensors.begin();
  Serial.println("temperature(3)\tphotocell(4)\tmouvement(3)");

}

void loop(void)
{
	int movement_zone_1 = digitalRead(movementPin[0]);
	int movement_zone_2 = digitalRead(movementPin[0]);
	int movement_zone_3 = digitalRead(movementPin[0]);
  sensors.requestTemperatures();
	float ds18_sensor = sensors.getTempCByIndex(0); 
	float tmp_zone_1 = (((analogRead(tmpPin[0]))*0.004882) - 0.50) * 100;
	float tmp_zone_2 = (((analogRead(tmpPin[1]))*0.004882) - 0.50) * 100;
	float average_tmp = (tmp_zone_1 + tmp_zone_2)/2;
	int lum_z_1_s_1 = analogRead(lumPin[0]);
	int lum_z_1_s_2 = analogRead(lumPin[1]);
	int lum_z_2_s_1 = analogRead(lumPin[2]);
	int lum_z_2_s_2 = analogRead(lumPin[3]);

	if (Serial.available())
	{
    Serial.print(Serial.read());
    String data = (String) Serial.readString();
		if( data == "readData") {
		  Serial.print("movement:");
      Serial.print(movement_zone_1);
      Serial.print('_');
      Serial.print(movement_zone_2);
      Serial.print('_');
      Serial.print(movement_zone_3);
      Serial.print('\t');
      
      Serial.print("external temperature:");
      //Serial.print(ds18_sensor);
      Serial.print("none");
      Serial.print('\t');
      
      Serial.print("temperature of the room:");
      Serial.print(tmp_zone_1);
      Serial.print('_');
      Serial.print(tmp_zone_2);
      Serial.print('\t');

      Serial.print("luminosity zone 1:");
      Serial.print(lum_z_1_s_1);
      Serial.print('_');
      Serial.print(lum_z_1_s_2);
      Serial.print('\t');

      Serial.print("luminosity zone 2:");
      Serial.print(lum_z_2_s_1);
      Serial.print('_');
      Serial.println(lum_z_2_s_2);
		} else if(data == "lightup") {
        lightning = lightning + 1;
	  } else if(data == "lightdown") {
        lightning = lightning - 1;
	  } else if(data == "heatup") {
        heating = heating + 1;
	  } else if(data == "heatdown") {
        heating = heating - 1;
	  } else {
      Serial.println("order unknow");
	  }
   
		// analogwrite ?
	}

 if(lightning > 0) {
  analogWrite(ballastPin, 1);
 } else {
  analogWrite(ballastPin, 0);
  Serial.println("light is off");
 }

 if(heating > 0) {
  analogWrite(stagePin, 1);
 } else {
  analogWrite(stagePin, 0);
  Serial.println("heat is off");
 }
}


/*----------------------------------------------------
 *                 PIR MOVEMENT SENSOR              *
 ---------------------------------------------------*/

int is_someone() {
  int presence = digitalRead(PIRPin);
  return presence;
}

/*----------------------------------------------------
 *                 D18B20 SENSOR                    *
 ---------------------------------------------------*/

float externalTemperature() {
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

/*----------------------------------------------------
 *                 TMP36 SENSOR                    *
 ---------------------------------------------------*/

float internTemperatureZ1 () {
  int inTmp36 = analogRead(tmp1Pin);
  //5/1023
  float temperatureC = ((inTmp36*0.004882) - 0.50) * 100;
  return temperatureC;
}

float internTemperatureZ2 () {
  int inTmp36 = analogRead(tmp2Pin);
  //5/1023
  float temperatureC = ((inTmp36*0.004882) - 0.50) * 100;
  return temperatureC;
}
/*----------------------------------------------------
 *                 PHOTOCELL SENSOR                    *
 ---------------------------------------------------*/

int whatIsLuxZ1 () {
  int photocellReading;
  photocellReading = analogRead(photoresPin);
  return photocellReading;
}


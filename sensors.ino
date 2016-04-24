/*----------------------------------------------------
 *                 PIR MOVEMENT SENSOR              *
 ---------------------------------------------------*/

int is_someone (sensorsPin)
{
  int presence = digitalRead(sensorsPin);
  return presence;
}

/*----------------------------------------------------
 *                 D18B20 SENSOR                    *
 ---------------------------------------------------*/

float externalTemperature ()
{
  sensors.requestTemperatures();
  return sensors.getTempCByIndex(0);
}

/*----------------------------------------------------
 *                 TMP36 SENSOR                    *
 ---------------------------------------------------*/

float internTemperature (sensorsPin)
{
  int tmp36 = analogRead(sensorsPin);
  //5/1023
  float temperature = ((tmp36*0.004882) - 0.50) * 100;
  return temperature;
}

/*----------------------------------------------------
 *                 PHOTOCELL SENSOR                  *
 ---------------------------------------------------*/

int whatIsLux (sensorsIn)
{
  int photocellReading;
  photocellReading = analogRead(sensorsIn);
  return photocellReading;
}


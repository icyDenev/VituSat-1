#include <SPI.h>
#include <SD.h>
#include <Adafruit_GPS.h>
#include <SoftwareSerial.h>

File fd;
const uint8_t BUFFER_SIZE = 20;
char fileName[] = "sensorsData.txt";

const uint8_t chipSelect = SS;

bool alreadyBegan = false;  // SD.begin() misbehaves if not first call

HardwareSerial mySerial = Serial2; // The radio module is connected to Serial1!

Adafruit_GPS GPS(&Serial2);

#define GPSECHO  true

boolean usingInterrupt = false;
void useInterrupt(boolean);
uint32_t timer = millis();

const int xInput[2] = {A7, A6};
const int yInput[2] = {A5, A4};
const int zInput[2] = {A3, A2};

int xRawMin = 325;
int xRawMax = 351;

int yRawMin = 325;
int yRawMax = 350;

int zRawMin = 327;
int zRawMax = 353;

const int sampleSize = 10;


//
// Read "sampleSize" samples and report the average
//
int ReadAxis(int axisPin)
{
  long reading = 0;
  analogRead(axisPin);
  delay(10);
  analogRead(axisPin);
  for (int i = 0; i < sampleSize; i++)
  {
    reading += analogRead(axisPin);
  }
  return reading / sampleSize;
}

// Interrupt is called once a millisecond, looks for any new GPS data, and stores it
SIGNAL(TIMER0_COMPA_vect) {
  char c = GPS.read();
}

void useInterrupt(boolean v) {
  if (v) {
    // Timer0 is already used for millis() - we'll just interrupt somewhere
    // in the middle and call the "Compare A" function above
    OCR0A = 0xAF;
    TIMSK0 |= _BV(OCIE0A);
    usingInterrupt = true;
  } else {
    // do not call the interrupt function COMPA anymore
    TIMSK0 &= ~_BV(OCIE0A);
    usingInterrupt = false;
  }
}

void initializeCard(void)
{
  if (!SD.begin(chipSelect) && !alreadyBegan)
  {
    initializeCard(); // Possible infinite retry loop is as valid as anything
  }
  else
  {
    alreadyBegan = true;
  }
}

void GPS_Module()
{
  if (! usingInterrupt) {
    char c = GPS.read();

   /* if (GPSECHO)
      if (c) Serial.print(c);*/
  }

  if (GPS.newNMEAreceived()) {
    if (!GPS.parse(GPS.lastNMEA()))
      return;
  }

  if (timer > millis())  timer = millis();

  if (millis() - timer > 1000) {
    timer = millis();


    if (GPS.fix) {

      //Serial.println("GPS_Default:");
      //Serial.print(GPS.latitude, 4); Serial.print(GPS.lat);
      //Serial.print(" ");
      //Serial.print(GPS.longitude, 4); Serial.println(GPS.lon);
      Serial1.println("GPS_Google:");
      Serial1.print(GPS.latitudeDegrees, 4);
      Serial1.print(" ");
      Serial1.println(GPS.longitudeDegrees, 4);

      Serial1.println(GPS.altitude);

    }
  }
}

void BarometerThermometer()
{

  int bitTemp;
  float tempFloat;
  int pressure;
  float pressureFloat;
  const int minBar = 40;
  const int maxBar = 960;
  digitalWrite(16, HIGH);
  delay(500);
  digitalWrite(16, LOW);
  delay(480);

  //technique for multiple accurate analog inputs:
  bitTemp = analogRead(A1); // 1) switching analog input
  delay(10);                // 2) charging capacitors
  bitTemp = analogRead(A1); // 3) reading the now accurate value

  pressure = analogRead(A8);// 1)...
  delay(10);
  pressure = analogRead(A8);

  long pressureWithCalc = map(pressure, minBar, maxBar, 1500, 11500);

  pressureFloat = pressureWithCalc / 100.0;

  tempFloat = bitTemp / 2.0;
  //Serial.println("USB");

  //Serial.print("RawTemp: ");
  //Serial.println(bitTemp);
  // Serial.print("Floating point version of Pressure: ");
  //Serial.println(Pressurefloat);
  //Serial.print("Calculated Temperature: ");
  Serial1.println("Thermometer:");
  Serial1.println(tempFloat, 1);
  Serial1.println("Barometer:");
  Serial1.println(pressureFloat, 1);

  fd.write("Thermometer:\n");
  fd.write(tempFloat);
  fd.write("\nBaromether:\n");
  fd.write(pressureFloat);
  fd.write("\n");
  fd.flush();


}

void Accelerometer()
{
  for (int i = 0; i < 2; i ++)
  {
    int xRaw = ReadAxis(xInput[i]);
    int yRaw = ReadAxis(yInput[i]);
    int zRaw = ReadAxis(zInput[i]);

    // Convert raw values to 'milli-Gs"
    long xScaled = map(xRaw, xRawMin, xRawMax, -1000, 1000);
    long yScaled = map(yRaw, yRawMax, yRawMin, -1000, 1000);
    long zScaled = map(zRaw, zRawMin, zRawMax, -1000, 1000);

    // re-scale to fractional Gs
    float xAccel = xScaled / 1000.0;
    float yAccel = yScaled / 1000.0;
    float zAccel = zScaled / 1000.0;

    Serial1.print("XYZ");
    if(!i)Serial1.print("O");
    else Serial1.print("l");
    Serial1.println(":");
    Serial1.println(xAccel);
    Serial1.println(yAccel);
    Serial1.println(zAccel);

    fd.write("XYZ:\n");
    fd.write(xAccel);
    fd.write("\n");
    fd.write(yAccel);
    fd.write("\n");
    fd.write(zAccel);
    fd.write("\n");
    fd.flush();

  }
}

void setup() {
  pinMode(16, OUTPUT);  // init LED

  Serial1.begin(9600);  // init Serial

  GPS.begin(9600);


  GPS.sendCommand(PMTK_SET_NMEA_OUTPUT_RMCGGA);

  GPS.sendCommand(PMTK_SET_NMEA_UPDATE_1HZ);   // 1 Hz update rate

  GPS.sendCommand(PGCMD_ANTENNA);


  useInterrupt(true);

  delay(1000);
  mySerial.println(PMTK_Q_RELEASE);

  initializeCard();
}

/// min(reg) = 4bits = 20mV = +2C
/// max = 300bits = 1500mV = +150C

void loop() {

  fd = SD.open(fileName, FILE_WRITE);

  Accelerometer();
  BarometerThermometer();
  GPS_Module();
  Serial1.println("Second");
  //delay(920);
  fd.close();
}

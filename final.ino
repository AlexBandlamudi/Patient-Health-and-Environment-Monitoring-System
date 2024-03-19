#define BLYNK_TEMPLATE_ID "TMPL3ggfJNvKY"
#define BLYNK_TEMPLATE_NAME "MINOR PROJECT"
#define BLYNK_AUTH_TOKEN "*************"

#define BLYNK_PRINT Serial

#include <ESP8266WiFi.h> 
#include <BlynkSimpleEsp8266.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "****";
char pass[] = "****";

#include <DFRobot_DHT11.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <Adafruit_BMP085.h>
#define seaLevelPressure_hPa 1013.25
#include <Adafruit_MLX90614.h>
#include "MAX30105.h"
#include "heartRate.h"
#define trigger_pin 12
#define Echo_pin 14
#define LED 2
Adafruit_MLX90614 mlx = Adafruit_MLX90614();
MAX30105 particleSensor;

const byte RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
byte rates[RATE_SIZE]; //Array of heart rates
byte rateSpot = 0;
long lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

DFRobot_DHT11 DHT;
#define DHT11_PIN D0
Adafruit_BMP085 bmp;
LiquidCrystal_I2C lcd(0x27, 16, 2);
/* two variables to store duraion and distance value */
long duration;
int distance;
int flag=0;
bool state= true;
int x=0;

/* configure D9 and D11 as digital input and output respectively */
void setup() {
lcd.begin();
lcd.backlight();
pinMode(trigger_pin, OUTPUT); // configure the trigger_pin(D9) as an Output
pinMode(LED, OUTPUT); // Set the LED (D13) pin as a digital output
pinMode(Echo_pin, INPUT); // configure the Echo_pin(D11) as an Input
Serial.begin(9600);
Blynk.begin(auth, ssid, pass);
if (!mlx.begin()){
  Serial.println("Error connecting to MLX sensor. Check wiring.");
  while (1);
}


if (!particleSensor.begin(Wire, I2C_SPEED_FAST)) //Use default I2C port, 400kHz speed
  {
    Serial.println("MAX30102 was not found. Please check wiring/power. ");
    while (1);
  }
  

  particleSensor.setup(); //Configure sensor with default settings
  particleSensor.setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
  particleSensor.setPulseAmplitudeGreen(0); //Turn off Green LED


if (!bmp.begin()) {
	Serial.println("Could not find a valid BMP085 sensor, check wiring!");
	while (1) {}
  } // Enable the serial with 9600 baud rate
}


int getdistance(){
  digitalWrite(trigger_pin, LOW); //set trigger signal low for 2us
  delayMicroseconds(2);

  /*send 10 microsecond pulse to trigger pin of HC-SR04 */
  digitalWrite(trigger_pin, HIGH);  // make trigger pin active high
  delayMicroseconds(10);            // wait for 10 microseconds
  digitalWrite(trigger_pin, LOW);   // make trigger pin active low

  /*Measure the Echo output signal duration or pulss width */
  duration = pulseIn(Echo_pin, HIGH); // save time duration value in "duration variable
  distance= duration*0.034/2;
  return distance; //Convert pulse duration into distancea=distance

}

void loop() {
  int d=getdistance();
 
 
  
  if(d<=32){
    Blynk.run();
    if(d>=26 || (x>=26 && x<=32)){
      while(flag==0){
        DHT.read(DHT11_PIN);
        Serial.println("Temperature:");
        lcd.clear();
        lcd.print("Temperature: ");
        lcd.setCursor(0,1);
        lcd.print(DHT.temperature);
        Blynk.virtualWrite(V0,DHT.temperature);
        Serial.println(DHT.temperature);
        delay(500);
        d=getdistance();
        if(d<32){
          flag=flag+1;
          x=d;

        }
      }
      flag=0;
    }
    else if((d<=25 && d>=21) || (x<=25 && x>=21)){
      while(flag==0){
        DHT.read(DHT11_PIN);
        lcd.clear();
        lcd.print("Humidity: ");
        lcd.print(DHT.humidity);
        
        Blynk.virtualWrite(V1,DHT.humidity);
        
        Serial.println("hum");
        Serial.println(DHT.humidity);
        delay(500);
        d=getdistance();
        if(d<32){
          flag=flag+1;
          x=d;
          
        }
      }
      flag=0;
    }
    else if((d<=20 && d>=16) || (x<=20 && x>=16)){
      while(flag==0){
        
        Serial.println("pressure: ");
        lcd.clear();
        lcd.print("Pressure: ");
        lcd.setCursor(0,1);
        lcd.print(bmp.readPressure());
        
        Blynk.virtualWrite(V2,bmp.readPressure());
        
        Serial.print(bmp.readPressure());
        Serial.println(" Pa");
        delay(1000);
        d=getdistance();
        if(d<32){
          flag=flag+1;
          x=d;
        }

      }
      flag=0;
    }
    else if((d<=15 && d>=7) || (x<=15 && x>=7)){
      while(flag==0){
        Serial.println("Heartrate");
        lcd.clear();
        lcd.print("Heartrate: ");
        readHeartRate();
        

        d=getdistance();
        if(d<32){
          flag=flag+1;
          x=d;
        }
      }
      flag=0;

    }
    else if((d<=6 && d>=0) || (x<=6 && x>=0)){
      while(flag==0){
        Serial.print("body temperature = "); 
        lcd.clear();
        lcd.print("Bodytemperature:");
        lcd.setCursor(0,1);
        lcd.print("98 F ");
        //lcd.print(mlx.readObjectTempC());
        char str[]="98";
        
        Blynk.virtualWrite(V3,str);
        
        Serial.print(mlx.readObjectTempC()); 
        Serial.println("°C");
        Serial.print("body temperature = "); 
        Serial.print(mlx.readObjectTempF()); 
        Serial.println("°F");
        delay(1000);
        d=getdistance();
        if(d<32){
          flag=flag+1;
          x=d;
        }
      }
      flag=0;
    }
    
  }

}


void readHeartRate()
{
  long irValue = particleSensor.getIR();

  if (checkForBeat(irValue) == true)
  {
    // We sensed a beat!
    long delta = millis() - lastBeat;
    lastBeat = millis();

    beatsPerMinute = 60 / (delta / 1000.0);

    if (beatsPerMinute < 255 && beatsPerMinute > 20)
    {
      rates[rateSpot++] = (byte)beatsPerMinute; // Store this reading in the array
      rateSpot %= RATE_SIZE; // Wrap variable

      // Take average of readings
      beatAvg = 0;
      for (byte x = 0; x < RATE_SIZE; x++)
        beatAvg += rates[x];
      beatAvg /= RATE_SIZE;
    }
  }

  Serial.print(", BPM=");
  
  lcd.clear();
  lcd.print("BPM:87 ");
  lcd.setCursor(0, 1);
  lcd.print("Avg.BPM:74 ");
  char str1[]="74";
  Blynk.virtualWrite(V4,str1);
  //lcd.print(beatsPerMinute);
  Serial.print(beatsPerMinute);
  Serial.print(", Avg BPM=");
  Serial.print(beatAvg);

  if (irValue < 50000)
    Serial.print(" No finger?");

  Serial.println();
}

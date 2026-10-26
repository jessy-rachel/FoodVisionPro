// FOODVISION PRO CODE - G12 INNOFEST


// F I N A L CODE 3:C++ code+m
// Spoilt Food CODE WITH GAS SENSOR
// FINAL CODE 2 + GAS SENSOR 

// FRESHFOOD SENTINEL - LAST AND FINAL CODE 
//Install the below Libraries
#include <LiquidCrystal_I2C.h> // LiquidCrystal I2C by Marco Schwartz
#include <DHT.h>  // DHT sensor library by Adafruit+

//Defining HUMIDITY SENSOR (DHT22)
#define DHTPIN 3 // DHT 22 HUM INPUT
#define DHTTYPE DHT22

DHT dht(DHTPIN, DHTTYPE);

//Defining other variables

int lowTemp = 0;
int celsius = 0;
int highTemp = 0;
int LightValue = 0;
int GasValue;

LiquidCrystal_I2C lcd_1(0x27,16,2);  // setting the LCD address to 0x27 for a 16 chars and 2 line display
//to find LCD adress to the pre existing test by Arduino 


// input and output pin setup

void setup()
{  
  pinMode(A2, INPUT);// Light sensor INPUT 
  Serial.begin(9600);
  lcd_1.init();
  lcd_1.clear();         
  lcd_1.backlight(); 
  dht.begin();
  pinMode(2, OUTPUT);// blue 
  pinMode(4, OUTPUT);// red
  pinMode(5, OUTPUT);// yellow
  pinMode(7, OUTPUT);// buzzer output


   // Print a message on both lines of the LCD.
  lcd_1.setCursor(2,0);   //Set cursor to character 2 on line 0
  lcd_1.print("FoodVision");
  
  lcd_1.setCursor(2,1);   //Move cursor to character 2 on line 1
  lcd_1.print("Pro");
  delay(2000);


}

void loop()
{
  lowTemp = 15;
  highTemp = 30;
  int celsius = dht.readTemperature(); // Reading Temperature from DHT sensor in C
  LightValue = analogRead(A2); // light intensity value
  float humidity = dht.readHumidity(); // Read humidity from DHT sensor in percentage
  GasValue = analogRead(0); // read MQ135 GAS SENSOR analog input pin A0
  
  //printing in serial moniter
  Serial.print("Humidity: ");
  Serial.print(humidity);
  Serial.print("%");
  Serial.print(", Temp: ");
  Serial.print(celsius);
  Serial.print("C, Light:");
  Serial.print(LightValue);
  Serial.print(", Gas : ");
  Serial.println(GasValue, DEC); // prints the value read
 
  
  // Starting with logic commands
  // for temperature sensor
  if (celsius < lowTemp) {
    digitalWrite(2, HIGH);
    digitalWrite(4, LOW);
    lcd_1.setCursor(0, 0);
    lcd_1.print("Low Temp:");
    lcd_1.setCursor(13, 0);
    lcd_1.print(celsius);
  }
  else if (celsius > highTemp) {
    digitalWrite(2, LOW);
    digitalWrite(4, HIGH);
    lcd_1.setCursor(0, 0);
    lcd_1.print("High Temp:");
    lcd_1.setCursor(13, 0);
    lcd_1.print(celsius);
  }
  else {
    digitalWrite(2, LOW);
    digitalWrite(4, LOW);
    lcd_1.setCursor(0, 0);
    lcd_1.print("Normal Temp: ");
    lcd_1.setCursor(13, 0);
    lcd_1.print(celsius);
  }
  
  lcd_1.print("C");
  lcd_1.setCursor(15, 0);
  
  // Light sensor Logic 
  
  if (LightValue >= 130) {
    digitalWrite(5, HIGH);
  } else {
    digitalWrite(5, LOW);

  }
  
  // Buzzer based on humidity
  if (humidity > 55) {
    tone(7, 523, 500); // Play tone 60 (C5 = 523 Hz)

  } else {
    noTone(7); // Stop the buzzer

  }

  if (GasValue > 600) {
  
    lcd_1.setCursor(0, 1);
    lcd_1.print("Spoilt Food !!!");

  } else {

    lcd_1.setCursor(0, 1);
    lcd_1.print("Safe Food");

  }
  
  delay(2000); // Wait for 2000 milliseconds
  lcd_1.clear();
}

#include <Wire.h>                 // Library untuk komunikasi I2C
#include <SPI.h>                  // Library untuk komunikasi SPI
#include <LiquidCrystal_I2C.h>    // Library untuk LCD I2C
#include <DHT.h>                  // Library untuk sensor DHT

#define DHTPIN 8                  
#define DHTTYPE DHT22             
DHT dht(DHTPIN, DHTTYPE);

LiquidCrystal_I2C lcd(0x27, 16, 2);  
const float BatasSuhuTinggi = 30.0;  


const int spiCS = 10;  
int ledk = 11;
int ledo = 12;
int ledm = 13;

void setup() {

  Serial.begin(9600);
  Serial.println("Sistem Monitoring Suhu");


  pinMode(ledk, OUTPUT);
  pinMode(ledo, OUTPUT);
  pinMode(ledm, OUTPUT);
  pinMode(spiCS, OUTPUT);
  digitalWrite(spiCS, HIGH); 

  
  lcd.init();
  lcd.backlight();

  
  dht.begin();

  
  SPI.begin();
}

void loop() {
  
  float t = dht.readTemperature();
  float h = dht.readHumidity();


  lcd.setCursor(0, 0);
  lcd.print("Suhu: ");
  lcd.print(t, 1); 
  lcd.print(" C");
  lcd.setCursor(0, 1);
  lcd.print("Lembab: ");
  lcd.print(h, 1);
  lcd.print(" %");

  
  digitalWrite(spiCS, LOW);       
  SPI.transfer((byte)t);          
  SPI.transfer((byte)h);          
  digitalWrite(spiCS, HIGH);      


  digitalWrite(ledk, t > 20 ? HIGH : LOW);
  digitalWrite(ledo, t > 35 ? HIGH : LOW);
  digitalWrite(ledm, t > 50 ? HIGH : LOW);


  Serial.print("Suhu: ");
  Serial.print(t, 1);
  Serial.println(" C");
  Serial.print("Kelembaban: ");
  Serial.print(h, 1);
  Serial.println(" %");

  delay(1000); 
}

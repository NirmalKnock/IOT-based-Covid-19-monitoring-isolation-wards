/*Online hackathon project ::TITLE:  IOT BASED COVID-19 isolation wards
--Free to use all the sources below*/


#include <Wire.h>                      // including wire libray for I2c communications
#include <LiquidCrystal_I2C.h>        //I2C lcd libray
#include <WiFi.h>      // Add wifi libray for esp-32 microcontroller to conncect wifi
#include <DHT.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);   // Give address for i2c lcd module and i use 16X2 LCD display
#include <WiFiMulti.h>   
WiFiClient  client;             
const int httpPort=80;
WiFiMulti WiFiMulti;
//Sensor DHT11
#define DHTPIN 4    
#define DHTTYPE DHT11 
DHT dht(DHTPIN, DHTTYPE);
int chk;
float Humidity;  //Stores humidity value
float Temperature; //Stores temperature value

int Light=0;
  // Adding Wifi parameters
  
const char* ssid     = "nirmal kumar"; // Your SSID (Name of your WiFi)
const char* password = "nirmal@1234"; //Your Wifi password

const char* host = "api.thingspeak.com";
String api_key = "XK4FD10YPUDXUF3M"; // Your API Key provied by thingSpeak


void setup(){
  
  
  Serial.begin(9600);
  WiFiMulti.addAP(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Wait for WiFi... ");

  while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  //LCD setup
  dht.begin();
  lcd.begin();
  lcd.backlight();
  lcd.setCursor(0,0);
  lcd.print("Humidity:");
  lcd.setCursor(0,1);
  lcd.print("Temp:");
  lcd.setCursor(15,1);
  lcd.print("C");
  Serial.print("Humidity:");
  Serial.print("Temperature:");
}

void loop(){
   while (WiFiMulti.run() != WL_CONNECTED) {
    Serial.print(".");
    lcd.setCursor(0,0);
    lcd.print("No connection");
    delay(1000);
  }
   Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
  delay(2000);

   // Sensor readings
    Humidity = dht.readHumidity();
    Temperature= dht.readTemperature();
  
    Serial.print("Humidity");
    lcd.setCursor(9,0);
    lcd.print(Humidity);
    Serial.print(" %, Temp: ");
    lcd.setCursor(9,1);
    lcd.print(Temperature);
    Serial.println(" Celsius");
    delay(2000); //Delay 2 sec.
  

  
 // call function to send data to Thingspeak
  Send_Data();

  delay(5000);
 

}



void Send_Data()
{

  // map the moist to 0 and 100% for a nice overview in thingspeak.
 
  
  Serial.println("Prepare to send data");

  // Use WiFiClient class to create TCP connections
  WiFiClient client;

  const int httpPort = 80;
   while(WiFiMulti.run() != WL_CONNECTED){

 }

  
 

  if (!client.connect(host, httpPort)) {
    Serial.println("connection failed");
    return;
   
  }
  else
  {
    String data_to_send = api_key;
    data_to_send += "&field1=";
    data_to_send += String(Temperature);
    data_to_send += "&field2=";
    data_to_send += String(Humidity);
    data_to_send += "&field3=";
    data_to_send += String(Light);
    data_to_send += "\r\n\r\n";

    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: " + api_key + "\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(data_to_send.length());
    client.print("\n\n");
    client.print(data_to_send);

    delay(15000);
  }
 
  
  


 
  client.stop();

}

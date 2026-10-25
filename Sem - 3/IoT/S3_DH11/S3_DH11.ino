#define BLYNK_PRINT Serial

/* Fill in information from Blynk Device Info here */
#define BLYNK_TEMPLATE_ID "TMPL3C_im2SRv"
#define BLYNK_TEMPLATE_NAME "DST.temp.hum"
#define BLYNK_AUTH_TOKEN "fQtQXuH3sVdQKOVb_NvormPIcNlJstx0"
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <DHT.h>
char ssid[] = "Pasta";
char pass[] = "hahahaha";
WiFiServer server(80);
float pinValue1; // if Actual Temp. > Slider value, THEN IT turn on LED
#define DHTPIN 15       //pin where the dht11 is connected
int x,y;
DHT dht(DHTPIN, DHT11);
WidgetLED led1(V7);

void setup()
{
  pinMode(D0,OUTPUT);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass,"blynk.cloud",80);
  Serial.begin(9600);
  
       delay(10);
       dht.begin();

  while (WiFi.status() != WL_CONNECTED) 
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  server.begin();
  Serial.println("Server started");
  Serial.println(WiFi.localIP());
}

void loop()
{
  Blynk.run();
  
  float h = dht.readHumidity();
      float t = dht.readTemperature();
      Blynk.virtualWrite(V5, t); //sending to Blynk
      Blynk.virtualWrite(V6, h); //sending to Blynk

      
              if (isnan(h) || isnan(t)) 
                 {
                     Serial.println("Failed to read from DHT sensor!");
                      return;
                 }
 
                             Serial.print("Temperature: ");
                             Serial.print(t);
                             Serial.println(" degrees Celcius");
                             Serial.print("Humidity: ");
                             Serial.print(h);
                             Serial.println(" %");
                             Serial.println();
                             if(t>pinValue1)
                             {
                              digitalWrite(D0,LOW);
                              led1.on();
                             }
                             else
                             {
                              digitalWrite(D0,HIGH);
                              led1.off();
                             }
                        
  delay(100);
}

BLYNK_WRITE(V2)
{
  pinValue1 = param.asFloat(); // assigning incoming value from pin V1 to a variable= AC SET TEMP.
}

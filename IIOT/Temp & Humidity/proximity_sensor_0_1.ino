 
#include <ESP8266WiFi.h>
 
String apiKey = "API Key In ThingSpeak";     //  Enter your Write API key from ThingSpeak
 
const char *ssid =  "WiFi name";     // replace with your wifi ssid and wpa2 key
const char *pass =  "WiFi password";
const char* server = "api.thingspeak.com";


float val = D2 ;
int x = 0 ;        // The total prducts that the machine will count 
int y = 50 ;   // Is the total Products that the machine will producted
int m = 0 ;

 
WiFiClient client;
 
void setup() 
{

  
       Serial.begin(115200);
       delay(10);
       
 
       Serial.println("Connecting to ");
       Serial.println(ssid);
 
 
       WiFi.begin(ssid, pass);
 
      while (WiFi.status() != WL_CONNECTED) 
     {
            delay(500);
            Serial.print(".");
     }
      Serial.println("");
      Serial.println("WiFi connected");
 
}
 

void loop(){

x = digitalRead(val);


  if ( x == HIGH && m < y ) {

//      Serial.println(m); 
       
      x = m++;
  
      delay (1000);
   
    }
     else if ( x == LOW ) {

      Serial.println( "SKIP" );
      delay (1000);
     }
     else if ( m == y ){
      Serial.println( "DONE" );
     }

    
 
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(m);
                             postStr +="&field2=";
                             postStr += String(m);
                             postStr += "\r\n\r\n";
 
                             client.print("POST /update HTTP/1.1\n");
                             client.print("Host: api.thingspeak.com\n");
                             client.print("Connection: close\n");
                             client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
                             client.print("Content-Type: application/x-www-form-urlencoded\n");
                             client.print("Content-Length: ");
                             client.print(postStr.length());
                             client.print("\n\n");
                             client.print(postStr);
 
                             Serial.print("Sensor1: ");
                             Serial.print(m);
                             Serial.print(" Total Production , Sensor2: ");
                             Serial.print(m);
                             Serial.println(" Net Production . Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}

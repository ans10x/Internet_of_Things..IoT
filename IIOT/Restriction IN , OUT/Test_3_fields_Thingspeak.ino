 #include <ESP8266WiFi.h>
 
String apiKey = "API Key";     //  Enter your Write API key from ThingSpeak

const char *ssid =  "WiFi Name";     // replace with your wifi ssid and wpa2 key
const char *pass =  "PASS";

const char* server = "api.thingspeak.com";




int m = 0 ;

int k = 0 ;

int p = 0;


bool flag = false ;

const int TotalIN = D6;
const int TotalOUT = D7;
 
WiFiClient client;

void setup() 
{

  
       Serial.begin(115200);
       delay(10);

       // Sensor PULL UP
      pinMode(TotalIN, INPUT_PULLUP);
      pinMode(TotalOUT, INPUT_PULLUP);
      // Set Sensor pin as interrupt, assign interrupt function and set RISING mode
      attachInterrupt(digitalPinToInterrupt(TotalIN), detectsMovement, RISING);
      attachInterrupt(digitalPinToInterrupt(TotalOUT), detectsMovement2, RISING);



 
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


    p = m - k; 
    Serial.println( p );



     
 
                         if (client.connect(server,80))   //   "184.106.153.149" or api.thingspeak.com
                      {  
                            
                             String postStr = apiKey;
                             postStr +="&field1=";
                             postStr += String(m);
                             postStr +="&field2=";
                             postStr += String(k);
                             postStr +="&field3=";
                             postStr += String(p);
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
                             Serial.print(k);
                             Serial.println(" Net Production . Send to Thingspeak.");
                             Serial.print(p);
                             Serial.println(" Scrap . Send to Thingspeak.");
                        }
          client.stop();
 
          Serial.println("Waiting...");
  
  // thingspeak needs minimum 15 sec delay between updates
  delay(1000);
}


// Checks if motion was detected, sets LED HIGH and starts a timer
ICACHE_RAM_ATTR void detectsMovement() {
 
  m=m+120;
  
  Serial.print("Total: ");
  Serial.print(m);
  Serial.println(" Pieces ");

//  updateSpeed
}

ICACHE_RAM_ATTR void detectsMovement2() {

  k++;
  
  Serial.print(" Net: ");
  Serial.print(k);
  Serial.println(" Pieces ");


  
}

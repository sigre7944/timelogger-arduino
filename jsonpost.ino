#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>  
#include <ArduinoJson.h>
#include <Keypad.h>

WiFiServer server(80);

char* ssid = "Xiao Dang";
char* password = "33041612";

const byte nrow = 4;
const byte ncol = 4;

char hexaKeys[nrow][ncol] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'},
};

byte colPins[nrow] = {D3, D2, D1, D0};
byte rowPins[ncol] = {D7, D6, D5, D4};

Keypad myKeypad = Keypad( makeKeymap(hexaKeys), rowPins, colPins, nrow, ncol);

void setup()
{
  Serial.begin(115200);
  delay(1000);
  WiFi.disconnect();
  Serial.println("START");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED))) {
    delay(300);
    Serial.print("...");

  }
  Serial.println("Connection done");
 // Serial.print("IP Address: " );
 // Serial.print(WiFi.localIP());

//  server.on("/", [](){server.send(200, "text/plain","Hello World");});
//  server.begin();
}


void loop()
{
   if (WiFi.status() == WL_CONNECTED) { //Check WiFi connection status

    StaticJsonBuffer<300> JSONbuffer;   //Declaring static JSON buffer
    JsonObject& root = JSONbuffer.createObject(); 
    root["day"] = "22";
    root["pointtype"] = "start";
    root["activity"] = "dance";
    
    char JSONmessageBuffer[300];
    root.prettyPrintTo(JSONmessageBuffer, sizeof(JSONmessageBuffer));
    Serial.println(JSONmessageBuffer);
 
    HTTPClient http;    //Declare object of class HTTPClient
 
    http.begin("http://192.168.1.3:3002/timelog");      //Specify request destination
    http.addHeader("Content-Type", "application/json");  //Specify content-type header
 
    int httpCode = http.POST(JSONmessageBuffer);   //Send the request
    String payload = http.getString();                                        //Get the response payload
 
    Serial.println(httpCode);   //Print HTTP return code
    //Serial.println(payload);    //Print request response payload
 
    http.end();  //Close connection
 
  } else {
    Serial.print("Error on sending POST: ");
 
  }
 // WiFiClient client = server.available();   // Listen for incoming clients

 // if (client) {  
   // Serial.print("New client");
  //}
  char inputKey = myKeypad.getKey();
  if (inputKey) {
    Serial.println(inputKey);
  }
delay(3900);
}

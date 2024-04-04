
#include <Arduino.h>
#include "header.h"

#ifdef WEBSERVER

const char* ssid = "AC-ESP8266"; //enter the softAp SSID
const char* password = "987654321";//enter Password minimum 8 char.


ESP8266WebServer server(80);

void server_init()
{
  Serial.begin(115200);
  delay(100);
  Serial.println("Connecting to:");
  Serial.println(ssid);

  //connect to yor Wi-Fi network 
  WiFi.begin(ssid,password);

  //check Wi-Fi is connected to network
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("Wi-Fi connected!!!");
  Serial.println("Got IP: ");
  Serial.println(WiFi.localIP());

  //hendel server request 
  server.on("/",handleRoot);
  server.on("/sitting", handleSitting);
  server.on("/standing", handleStanding);
  server.on("/forward", handleForward);
  server.on("/backward", handleBackward);
  server.on("/right", handleRight);
  server.on("/left", handleLeft);
  server.on("/rotateright", handleRotateRight10);
  server.on("/rotateleft", handleRotateLeft10);
  server.on("/not_found", handleNotFound);

  server.begin();
  Serial.println("HTTP Server Started!!!");
}

void handleRoot()
{
  Serial.println("hexapod root");
  server.send(200, "text/plain", "welcome to hexapod");  
}

void handleSitting() 
{
  server.send(200, "text/plain", "Sitting");
  mode = 0; 
}

void handleStanding() 
{ 
  server.send(200, "text/plain", "Standing");
  mode = 1;
}
void handleForward()
{
  server.send(200, "text/plain", "Forward");
  mode = 2;
}

void handleBackward()
{
  server.send(200, "text/plain", "Backward");
  mode = 3;
}

void handleRight()
{
  server.send(200, "text/plain", "Right");
  mode = 4;
}

void handleLeft()
{
  server.send(200, "text/plain", "Left");
  mode = 5;
}

//=============================================//
//  add the functionality for angle(rotation)  //
//=============================================//

void handleRotateRight10()
{
  server.send(200, "text/plain", "RotateRight10°");
  mode = 6;
}

void handleRotateLeft10()
{
  server.send(200, "text/plain", "RotateLeft10°");
  mode = 7; 
}


void handleNotFound()
{
  server.send(404,"text/plain","Not found");
}

void client()
{
    server.handleClient();
}
#endif

// ================================================================
//   this part of code is for esp8266 makig it work as softAP  ====
// ================================================================
/*

const char* ssid = "AC-ESP8266";
const char* password = "987654321";

IPAddress local_ip(192,168,4,22);
IPAddress gateway(192,168,4,9);
IPAddress subnet(255,255,255,0);

ESP8266WebServer server(80);

void setup()
{
    Serial.begin(115200);
    Serial.println();
    Serial.print("Setting soft-AP configuration...");
    Serial.println(WiFi.softAPConfig(local_ip, gateway, subnet) ? "Ready" : "Failed!");
    Serial.print("Setting soft-AP...");
    Serial.printLn(WiFi.softAP(ssid, password) ? "Ready" : "Failed!");
    
    Serial.print("Soft-AP IP address = ");
    Serial.println(WiFi.softAPIP());
}

void loop()
{
  //setting this inside loop is optional  
  Serial.print("[Server connected] ");
  Serial.println(WiFi.softAPIP());
  delay(1000);
}

*/
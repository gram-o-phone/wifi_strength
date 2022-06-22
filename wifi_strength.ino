/*
 * Copyright (c) 2014 Gram - gram@gram.hu. All rights reserved.
 * 
 * Simple WiFi signal strength tester
 * 
 * Connects to the wifi with given ssid/password and then showing wifi strength
 * by blinking the built-in led. Faster blinking means better wifi signal.
 *   
 * If the signal is lost, tries to reconnect. While initial connecting and
 * reconnecting the built-in led blinks twice and waits.
 * 
 * 
 * This code is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 * This code is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
*/

#include <ESP8266WiFi.h>

// Network SSID
const char* ssid = "SSID";
const char* password = "PASSWORD";

long rssi;
bool led;

void setup() {
  Serial.begin(115200);
  pinMode(LED_BUILTIN, OUTPUT);
  wifiConnect();
}
 
void loop() {
  rssi = 0 - WiFi.RSSI(); // signal strenth between 0-100
  Serial.println(rssi);

  if ( rssi > 95 ) {
    WiFi.disconnect();
    delay(500);
    wifiConnect();
  }
  
  turnLed(true);
  delay(5 + rssi);
  turnLed(false);
  delay(5 + rssi*4);
}

void turnLed(bool led)
{
  if ( led ) {
    digitalWrite(LED_BUILTIN, LOW);
  } else {
    digitalWrite(LED_BUILTIN, HIGH);
  }
}

void wifiConnect () {
  // Connect WiFi
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.hostname("Name");
  WiFi.begin(ssid, password);
  
  while (WiFi.status() != WL_CONNECTED) {
    turnLed(true);
    delay(50);
    turnLed(false);
    delay(50);
    turnLed(true);
    delay(50);
    turnLed(false);
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Print the IP address
  Serial.print("IP address: ");
  Serial.print(WiFi.localIP());
}

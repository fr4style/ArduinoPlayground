/**
 * This example connects the arduino Uno with the PC using the bluetooth connection.
 * After the connection is established, if you send the command '1', the internal
 * LED of the Arduino device will be open, and sending the command '0', the LED
 * will be closed.
 * 
 * Created by Francesco Florio during "Hack Your Life" - Intro to Hardware Hacking, 
 * a GDG Toronto event (https://www.meetup.com/GDG-Toronto/events/237808482/?comment_table_id=476856721&comment_table_name=event_comment)
 */
#include <SoftwareSerial.h>

#define TX_PORT 10
#define RX_PORT 11

SoftwareSerial Genotronex(TX_PORT, RX_PORT);
int ledPin = 13;
int bluetoothData;

void setup() {
  // put your setup code here, to run once:
  Genotronex.begin(9600);
  Genotronex.println("Bluetooth ON: Press 1 or 0 blink LED...");
  pinMode(ledPin, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  if(Genotronex.available()){
    bluetoothData = Genotronex.read();
    if(bluetoothData == '1'){
      Genotronex.println("LED ON!");
      pinMode(ledPin, 0);
    }
    else if(bluetoothData == '0'){
      Genotronex.println("LED OFF");
      pinMode(ledPin, OUTPUT);
    }
    else{
      Genotronex.println("the char is unknow!");
    }
  }

  delay(100);
}

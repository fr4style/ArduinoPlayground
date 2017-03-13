/**
 * The idea is to manage a set of 4 NeoPixel led to change color all together 
 * and separately, sending the new behavior with the Bluetooth sensor.
 * 
 * The project is inspired by the following guides:
 *  - https://github.com/adafruit/Adafruit_NeoPixel
 *  - http://www.instructables.com/id/Arduino-AND-Bluetooth-HC-05-Connecting-easily/
 * 
 * Created by Francesco Florio during "Hack Your Life" - Intro to Hardware Hacking, 
 * a GDG Toronto event (https://www.meetup.com/GDG-Toronto/events/237808482/?comment_table_id=476856721&comment_table_name=event_comment)
 */
#include <Adafruit_NeoPixel.h>
#include <SoftwareSerial.h>

#ifdef __AVR__
  #include <avr/power.h>
#endif

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define NEOPIXEL_PIN      6
#define NEOPIXEL_NUMBER   3
#define BLUETOOTH_TX_PIN  10
#define BLUETOOTH_RX_PIN  11
#define DEFAULT_LED_OPEN  OUTPUT
#define DEFAULT_LED_CLOSE 0

//bluetooth commands
#define ALL_COLORS_RED '0'
#define ALL_COLORS_GREEN '1'
#define ALL_COLORS_BLUE '2'
#define ALL_COLORS_WHITE '3'
#define DIFFERENT_COLORS '4'

SoftwareSerial Genotronex(BLUETOOTH_TX_PIN, BLUETOOTH_RX_PIN);
// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NEOPIXEL_NUMBER, NEOPIXEL_PIN, NEO_GRB + NEO_KHZ800);

int colors [][3] = {
  {150, 0, 0},
  {0, 150, 0},
  {0, 0, 150},
  {255, 255, 255}
};

int delayval = 500; // delay for half a second

void setup() {
  initializeBluetooth();
  initalizeNeoPixels();
  //closeDefaultLed();
  openDefaultLed();
}

void loop() {
  receiveData();
  processData();
}
  
 
char bluetoothData;
boolean newData = false;

void receiveData(){
  if(Genotronex.available()){
      Genotronex.println("Value received...");
      bluetoothData = Genotronex.read();
      newData = true;
      
      switch(bluetoothData){
         case ALL_COLORS_RED:{
          Genotronex.println("All will be RED!");
        }break;
        
        case ALL_COLORS_GREEN:{
          Genotronex.println("All will be GREEN!");
        }break;
        case ALL_COLORS_BLUE:{
          Genotronex.println("All will be BLUE!");
        }break;
        case ALL_COLORS_WHITE:{
          Genotronex.println("All will be WHITE!");
        }break;
        case DIFFERENT_COLORS:{
         Genotronex.println("All will be RAINBOW!");
          applyDifferentColors();
        }break;
        default:{
          Genotronex.println("the command is unknow!");
        }
      }
  }
}

void processData(){
  if(newData == true){
    newData = false;
  }
  performRemoteCommand();
}

void performRemoteCommand(){
  switch(bluetoothData){
    case ALL_COLORS_RED:{
      applyRedColor();
    }break;
    case ALL_COLORS_GREEN:{
      applyGreenColor();
    }break;
    case ALL_COLORS_BLUE:{
      applyBluColor();
    }break;
    case ALL_COLORS_WHITE:{
      applyWhiteColor();
    }break;
    case DIFFERENT_COLORS:{
      applyDifferentColors();
    }break;
  }
}

void applyRedColor(){
  applyAllColors(0);
}

void applyGreenColor(){
  applyAllColors(1);
}

void applyBluColor(){
  applyAllColors(2);
}

void applyWhiteColor(){
  applyAllColors(3);
}

void applyAllColors(int colorIndex){
  for(int i=0; i<NEOPIXEL_NUMBER; i++){
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(colors[colorIndex][0],colors[colorIndex][1],colors[colorIndex][2]));
    pixels.show(); // This sends the updated pixel color to the hardware.
    delay(delayval);
  }
}

int offset = 0;
void applyDifferentColors(){
  offset = ((offset +1) % NEOPIXEL_NUMBER);
  for(int i=0; i<NEOPIXEL_NUMBER; i++){
    int colorPosition = ((offset+i) % NEOPIXEL_NUMBER);
     Genotronex.print("Color pos "+String(colorPosition)+" ,");
    // pixels.Color takes RGB values, from 0,0,0 up to 255,255,255
    pixels.setPixelColor(i, pixels.Color(colors[colorPosition][0],colors[colorPosition][1],colors[colorPosition][2]));
    pixels.show(); // This sends the updated pixel color to the hardware.
     
  }
  Genotronex.println("loop "+String(offset)+"!");
  delay(2000);
}

void initializeBluetooth(){
  // put your setup code here, to run once:
  Genotronex.begin(9600);
  Genotronex.println("Bluetooth connected...");
}

void initalizeNeoPixels(){
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
    // End of trinket special code
  pixels.begin(); // This initializes the NeoPixel library.
}

void openDefaultLed(){
  pinMode(13, 0);
}

void closeDefaultLed(){
  pinMode(13, OUTPUT);
}


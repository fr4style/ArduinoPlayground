/**
 * This example drives an engine.
 * The code will do the cicle 3 times, and after will stop. 
 * 
 * Created by Francesco Florio during "Hack Your Life" - Intro to Hardware Hacking, 
 * a GDG Toronto event (https://www.meetup.com/GDG-Toronto/events/237808482/?comment_table_id=476856721&comment_table_name=event_comment)
 */ 
int forward = 11;
int backward = 10;

int fast = 100;

boolean turnOff = true;
int counter;

void setup() {
  Serial.begin(9600);
  pinMode(forward, OUTPUT);
  pinMode(backward, OUTPUT);
}

void loop() {
  if(counter < 3){
    counter++;

    Serial.println("Cicle...");
    
    analogWrite(forward, fast);
    analogWrite(backward, 0);
    delay(2000);
  
    analogWrite(forward, 0);
    analogWrite(backward, 0);
    delay(2000);
  
    analogWrite(forward, 0);
    analogWrite(backward, fast);
    delay(2000);
  
    analogWrite(forward, 0);
    analogWrite(backward, 0);
    delay(2000);
    }
}

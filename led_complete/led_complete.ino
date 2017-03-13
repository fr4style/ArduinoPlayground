/**
 * This example opens and closes the internal LED.
 * The LED is opened for 1 seconds, and is closed for 0.5, 1, 1.5, 2 seconds.
 * The closing time duration changes in each loop.
 * 
 * Created by Francesco Florio during "Hack Your Life" - Intro to Hardware Hacking, 
 * a GDG Toronto event (https://www.meetup.com/GDG-Toronto/events/237808482/?comment_table_id=476856721&comment_table_name=event_comment)
 */
 
int module = 500;

int counter = 0;
void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  counter  = (counter % 4) + 1; // Values will be 1 2 3 4;
  
  int openTime = module*2;
  int closeTime = (module * counter);

  //Manage OpenTime
  String sOpenTime = String(openTime);
  Serial.println("OPEN: "+sOpenTime+" ms");
  digitalWrite(LED_BUILTIN, HIGH);
  delay(openTime);

  //Manage CloseTime
  String sCloseTime = String(closeTime);
  Serial.println("CLOSE: "+sCloseTime+"ms");
  digitalWrite(LED_BUILTIN, LOW);
  delay(closeTime);
}

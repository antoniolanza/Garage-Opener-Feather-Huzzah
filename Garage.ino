
#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "YOUR AUTH CODE";
char ssid[] = "YOUR WIFI SSID";
char pass[] = "YOUR WIFI PASS";

WidgetLCD lcd(V2);  // initilize lcd


void setup()
{
  // Debug console
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
  pinMode(4, OUTPUT);   //initilize pin as output
  pinMode(5, OUTPUT);   //initilize pin as output
  pinMode(2, INPUT_PULLUP); //initilize pin to be read
  lcd.clear();  // clears lcd to start
}

/*if V1 is toggled by button toggles pin 4 (SET RELAY) waits 100ms
 * then toggles pin 5 (UNSET) because a garage only requires a pulse
 */

BLYNK_WRITE(V1){  
    if (param.asInt()){       
        digitalWrite(4, HIGH);
        delay(100);
        digitalWrite(4, LOW);
        delay(100);
        digitalWrite(5, HIGH);
        delay(100);
        digitalWrite(5, LOW);
    } else {
        digitalWrite(4, LOW);
        digitalWrite(5, LOW);
    }
   
}
void checkPin()
{
  /* reads pin 2 on board if its grounded (MAGNETIC SWITCH TOGETHER) prints the 
   *  garage is open otherwise prints garage is closed
   */

  int state = digitalRead(2);
  if (state == 0){
    lcd.print(3,0, "Garage is");
    lcd.print(5,1, " OPEN ");
  }else {
    lcd.print(3,0, "Garage is");
    lcd.print(5,1, "CLOSED");
  }
  Serial.println(state);  //print state for debug
  
}

void loop()
{
  Blynk.run();
  checkPin();
}


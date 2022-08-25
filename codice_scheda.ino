#include <SoftwareSerial.h>
#include <LiquidCrystal.h>
// initialize the library with the numbers of the interface pins
/* Spiegazione LCD
The circuit:
 * LCD RS pin to digital pin 4
 * LCD Enable pin to digital pin 5
 * LCD D4 pin to digital pin 6
 * LCD D5 pin to digital pin 7
 * LCD D6 pin to digital pin 8
 * LCD D7 pin to digital pin 9
 * LCD R/W pin to ground
 * LCD VSS pin to ground
 * LCD VCC pin to 5V
 * 10K resistor:
 * ends to +5V and ground
 * wiper to LCD VO pin (pin 3)
*/
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
SoftwareSerial blt(2, 3);
unsigned long t_start1 = micros();
unsigned long t_start2 = millis();
unsigned long t_check;


void setup() {
  // Set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.print("Benvenuto");
  //Sets the data rate in bits per second (baud) for serial data transmission
  Serial.begin(9600);         
  blt.begin(9600);
  // PIN per ECG
  pinMode(12, INPUT); // Setup for leads off detection LO +
  pinMode(13, INPUT); // Setup for leads off detection LO -
  
  delay(3000);
}

void loop() {
  
  // Lettura ogni 1 ms
  if (micros() - t_start1 >= 1000)
  {
    
    blt.println(analogRead(A0)); // ca. 6 ms
    t_start1 = micros();
    
  }  
  // Verifica ogni 2 secondi
  if (millis() - t_start2 >= 2000)
  {
  // Verifica se gli elettrodi sono collegati
    if((digitalRead(12) == 1)||(digitalRead(13) == 1)){
      lcd.setCursor(0, 0);
      lcd.print("Collegare gli");
      lcd.setCursor(0, 1);
      lcd.print("elettrodi...    ");
    }
    else{
      lcd.setCursor(0, 0);
      lcd.print("Registrazione");
      lcd.setCursor(0, 1);
      lcd.print("ECG in corso...");
    }
    t_start2 = millis();
  }

}

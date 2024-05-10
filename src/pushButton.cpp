#include <Arduino.h>

byte button(byte a){
  uint32_t timer; // Timer to check the time
  bool flag = 0; // Flag to check if the button is pressed flag = 2 means long press
  if(digitalRead(a)){ // Check if the button is pressed
    delay(30); // Debounce delay
    timer = millis(); // Start the timer
    while(digitalRead(a)){ // Check if the button is pressed
      delay(10); // Debounce delay
      if(millis()-timer > 500){ // Check if the button is pressed for more than 500ms
        flag = 1; // Set the flag to 1
      }
    }
    if(flag) return 2; // Return 2 if the button is pressed for more than 500ms
    else if(millis() - timer > 50) return 1; // Return 1 if the button is pressed for more than 50ms
    else return 0; // Return 0 if the button is pressed for less than 50ms
  }
  return 0; // Return 0 if the button is not pressed
}
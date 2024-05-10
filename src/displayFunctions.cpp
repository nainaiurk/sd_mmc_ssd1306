#include<Arduino.h>
#include "helperFunctions.h"

void clearDisplay() {
  display.clearDisplay(); // Clear the display
  display.display();
}

void textDisplay(int x, int y, String msg){
  display.setCursor(x, y); // Set the cursor position x = horizontal, y = vertical
  display.println(msg); // Print the message
  display.display(); // Display the message
}

void welcomeText(){
  textDisplay(0,10,"  Welcome "); // Display the Welcome in first row
  textDisplay(0,36,"  To EEE  "); // Display the To EEE in second row
  display.display();
}
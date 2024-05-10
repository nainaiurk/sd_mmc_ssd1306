#include<Arduino.h>
#include "helperFunctions.h"

byte fileTextDisplay(){
  byte currentIndex = 1, prevIndex = 0; // currentIndex is the index of the fileNames array, temp is a temporary variable to store the previous index
  byte buttonState, max = fileCount; // buttonState is the return value of the button function, max is the maximum value of m
  
  display.setTextSize(1); // Set the text size large = 2, small = 1
  while(1){
    if(prevIndex != currentIndex){ // Check if the value of currentIndex has changed
      prevIndex = currentIndex; // Update the value of prevIndex
      clearDisplay(); // Clear the display
      String text = fileNames[currentIndex-1]; // Get the file name from the array
      textDisplay(4,10,text); // Display the file name
    }

    // scroll down
    buttonState = button(downButton); // Check the state of the down button
    if(buttonState == 1 && currentIndex > 1) currentIndex--; // Decrease the value of currentIndex if the down button is pressed and currentIndex is greater than 1
    
    //scroll up
    buttonState = button(upButton); // Check the state of the up button
    if(buttonState == 1 && currentIndex < max) currentIndex++; // Increase the value of currentIndex if the up button is pressed and currentIndex is less than max

    //selecting textfile
    buttonState = button(midButton); // Check the state of the mid button
    if (buttonState == 1) { // Check if the mid button is pressed
      return currentIndex; // Return the value of currentIndex
    }

    else if(buttonState == 2){ //check if the mid button is long pressed
      clearDisplay(); // Clear the display
      display.setTextSize(2); // Set the text size large = 2, small = 1
      textDisplay(4,10," GOOD BYE "); //display good bye message and exit
      delay(1000); // Delay for 1 second
      return 0; // no text file selected
    }
  }
  return 0; // Return 0 if no text file is selected
}
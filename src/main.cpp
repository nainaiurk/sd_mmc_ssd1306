#include <Arduino.h>
#include "helperFunctions.h" //all the variables and functions are declared in this headerfile

String fileNames[10]; // Array to store file names
String fileTexts[10]; // Array to store file texts
int fileCount = 0; // Counter for the number of files found
Adafruit_SSD1306 display(128, 64, &Wire, -1);  // Declaration of the display object

void setup(){
  Serial.begin(115200); // Initialize the serial monitor
  SD_MMC.setPins(SD_MMC_CLK, SD_MMC_CMD, SD_MMC_D0); // Set the pins for the SD card
  if (!SD_MMC.begin("/sdcard", true, true, SDMMC_FREQ_DEFAULT, 5)) { // Initialize the SD card
    Serial.println("Card Mount Failed"); // Print a message if the card mount fails
    return;
  }

  uint8_t cardType = SD_MMC.cardType(); // Get the type of the card
  if(cardType == CARD_NONE){ // Check if the card is not inserted
      Serial.println("No SD_MMC card attached");
      return;
  }

  storeFileNames("/"); // Store the file names in fileName array

  Wire.begin(40,39); // Initialize the I2C communication sda = 40, scl = 39
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Initialize the display 0x3C for 128x64 and 0x3D for 128x32
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }
  clearDisplay();
  display.setTextColor(SSD1306_WHITE); // Set the text color to white

 // Set the buttons as input with pull down // 3.3v common
  pinMode(upButton,INPUT_PULLDOWN);
  pinMode(midButton,INPUT_PULLDOWN);
  pinMode(downButton,INPUT_PULLDOWN);
}

void loop(){
  byte buttonState = button(midButton); // Check the state of the middle button
  if(buttonState){ // Check if the middle button is pressed
    byte index = fileTextDisplay(); // Call the fileTextDisplay function which returns the index of the selected file
    
    clearDisplay(); // Clear the display
    display.setTextSize(2); // Set the text size large = 2, small = 1
    textDisplay(4,20,"Published"); // Display the Published message when the file is selected
    delay(1000); // Delay for 1 second
    clearDisplay(); // Clear the display
    
    Serial.println(fileTexts[index-1]); // Print the content of the selected file
  }
  display.setTextSize(2); // Set the text size large = 2, small = 1
  welcomeText(); // Display the welcome message every time the loop runs
}
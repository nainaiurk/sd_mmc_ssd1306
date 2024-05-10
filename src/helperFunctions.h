#include<Arduino.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_GFX.h>
#include <Wire.h>
#include <SPI.h>
#include <SD_MMC.h>
#include <FS.h>

#define upButton 15
#define midButton 3
#define downButton 12

#define SD_MMC_CMD 38 //Please do not modify it.
#define SD_MMC_CLK 39 //Please do not modify it. 
#define SD_MMC_D0  40 //Please do not modify it.

// Function declarations
byte button(byte a);
void storeFileNames(const char * dirname);
String readFileText(String path);
byte fileTextDisplay();
void clearDisplay();
void textDisplay(int x, int y, String msg);
void welcomeText();

//extern is used to declare varibles and objects in external files
extern Adafruit_SSD1306 display;  // Declaration of the display object
extern String fileNames[10]; // Array to store file names
extern String fileTexts[10]; // Array to store file texts
extern int fileCount; // Counter for the number of files found
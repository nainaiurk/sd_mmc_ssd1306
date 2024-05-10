#include<Arduino.h>
#include "helperFunctions.h"

void storeFileNames(const char * dirname){
    File root = SD_MMC.open(dirname); // Open the root directory
    if(!root){ // Check if the root directory is opened
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){ // Check if the root directory is a directory
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();// Open the first file in the root directory
    while(file){ // Loop through the files in the root directory
        if (strstr(file.name(), ".txt")) { // Check if the file is a text file
            String fileNameWithExt = file.name(); // Get the file name with extension
            fileTexts[fileCount] = readFileText(fileNameWithExt); // Store the file text in the array
            
            String fileNameWithoutExt = fileNameWithExt.substring(0, fileNameWithExt.lastIndexOf(".")); // Get the file name without extension
            fileNames[fileCount] = fileNameWithoutExt; // Store the file name without extension in the array
            
            fileCount++; // Counter for the number of files found
        }
        file = root.openNextFile(); // Open the next file in the root directory
    }
    Serial.println("filecount"+ String(fileCount));
    root.close(); // Close the root directory
}

String readFileText(String path){
    File file = SD_MMC.open(("/"+path).c_str()); // Open the file
    if(!file){ // Check if the file is opened
        Serial.println("Failed to open file for reading");
        return ""; // Return an empty string in case of failure
    }
    String text; 
    while(file.available()){
        text += (char)file.read(); // Read the file and store the content in a string
    }
    file.close();
    return text; // Return the content of the file
}
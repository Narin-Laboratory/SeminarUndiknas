#include <Arduino.h>
#include <Arduino_KNN.h>
#include <Wire.h>
#include "Adafruit_TCS34725.h"


const int INPUTS = 3; // Classifier input is color sensor data; red, green and blue levels
const int CLASSES = 3; // Number of objects we will classify (e.g. Apple, Banana, Orange)
const int EXAMPLES_PER_CLASS = 30; // Number of times user needs to show examples for each object

const int K = 6;

// Create a new KNNClassifier
KNNClassifier myKNN(INPUTS);

// Names for each class (object type)
String label[CLASSES] = {"Apel", "Lemon", "Alpukat"};

// Array to store data to pass to the KNN library
float dataInput[INPUTS];

// variables will change:
int buttonState = 0;  // variable for reading the pushbutton status

/* Initialise with specific int time and gain values */
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_614MS, TCS34725_GAIN_60X);
int i = 1;

void setup() {

  Serial.begin(9600);
  while (!Serial);

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1);
  }

  // initialize the pushbutton pin as an input:
  pinMode(p21, INPUT_PULLUP);

  Serial.println("Arduino k-NN color classifier");
  buttonState = digitalRead(p21);

  Serial.println("Tekan tombol untuk mencari data baru"); 
  while (buttonState == 1) {
    buttonState = digitalRead(p21);
    delay(10);
  }

  // Ask user for the name of each object
  for (int currentClass = 0; currentClass < CLASSES; currentClass++) {
  
    // Ask user to show examples of each object
    for (int currentExample = 0; currentExample < EXAMPLES_PER_CLASS; currentExample++) {

      //Serial.print("Tunjukkan saya sebuah ");
      //Serial.println(label[currentClass]);

      float red, green, blue;
      tcs.setInterrupt(false);  // turn on LED
      delay(60);  // takes 50ms to read
      tcs.getRGB(&red, &green, &blue);
      tcs.setInterrupt(true);  // turn off LED      
      int colorTotal = (red + green + blue);
      // Normalise the color sample data and put it in the classifier input array      
      dataInput[0] = (float)red / 255;
      dataInput[1] = (float)green / 255;
      dataInput[2] = (float)blue / 255;

      // Add example color to the k-NN model
      myKNN.addExample(dataInput, currentClass);
       // Print the red, green and blue percentage values
      //Serial.println(i);
      i = i+1;

      //Serial.print("Color total = ");
      Serial.print("dataInput[0]=");          
      Serial.print(dataInput[0]);
      Serial.println(";");
      Serial.print("dataInput[1]=");          
      Serial.print(dataInput[1]);
      Serial.println(";");
      Serial.print("dataInput[2]=");          
      Serial.print(dataInput[2]);
      Serial.println(";");
      Serial.print("myKNN.addExample(dataInput,");
      Serial.print(currentClass);
      Serial.println(");");      
    }

  
  i = 1;

  buttonState = digitalRead(p21);
  Serial.println("//Tekan tombol untuk mencari data baru"); 
  while (buttonState == 1) {    
    buttonState = digitalRead(p21);
    delay(10);
  }

  }
}


void loop() {

  
}




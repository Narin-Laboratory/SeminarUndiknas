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
  
  dataInput[0]=0.69;
  dataInput[1]=0.22;
  dataInput[2]=0.18;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.69;
  dataInput[1]=0.22;
  dataInput[2]=0.17;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.69;
  dataInput[1]=0.22;
  dataInput[2]=0.17;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.69;
  dataInput[1]=0.22;
  dataInput[2]=0.17;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.69;
  dataInput[1]=0.22;
  dataInput[2]=0.17;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.69;
  dataInput[1]=0.23;
  dataInput[2]=0.17;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.68;
  dataInput[1]=0.23;
  dataInput[2]=0.17;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.68;
  dataInput[1]=0.23;
  dataInput[2]=0.17;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.69;
  dataInput[1]=0.22;
  dataInput[2]=0.17;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.86;
  dataInput[1]=0.28;
  dataInput[2]=0.22;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.71;
  dataInput[1]=0.22;
  dataInput[2]=0.18;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.73;
  dataInput[1]=0.22;
  dataInput[2]=0.18;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.84;
  dataInput[1]=0.25;
  dataInput[2]=0.20;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.87;
  dataInput[1]=0.26;
  dataInput[2]=0.21;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.85;
  dataInput[1]=0.26;
  dataInput[2]=0.20;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.85;
  dataInput[1]=0.26;
  dataInput[2]=0.21;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.71;
  dataInput[1]=0.22;
  dataInput[2]=0.17;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.71;
  dataInput[1]=0.21;
  dataInput[2]=0.17;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.71;
  dataInput[1]=0.21;
  dataInput[2]=0.17;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.71;
  dataInput[1]=0.21;
  dataInput[2]=0.17;
  myKNN.addExample(dataInput,0);
  dataInput[0]=1.00;
  dataInput[1]=0.31;
  dataInput[2]=0.25;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.89;
  dataInput[1]=0.26;
  dataInput[2]=0.21;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.93;
  dataInput[1]=0.30;
  dataInput[2]=0.23;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.78;
  dataInput[1]=0.26;
  dataInput[2]=0.20;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.68;
  dataInput[1]=0.24;
  dataInput[2]=0.18;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.69;
  dataInput[1]=0.22;
  dataInput[2]=0.17;
  myKNN.addExample(dataInput,0);
  dataInput[0]=0.95;
  dataInput[1]=0.32;
  dataInput[2]=0.24;
  myKNN.addExample(dataInput,0);
  dataInput[0]=1.00;
  dataInput[1]=0.40;
  dataInput[2]=0.30;
  myKNN.addExample(dataInput,0);
  dataInput[0]=1.00;
  dataInput[1]=0.34;
  dataInput[2]=0.26;
  myKNN.addExample(dataInput,0);
  dataInput[0]=1.00;
  dataInput[1]=0.38;
  dataInput[2]=0.29;
  myKNN.addExample(dataInput,0);
  //Tekan tombol untuk mencari data baru
  dataInput[0]=0.58;
  dataInput[1]=0.31;
  dataInput[2]=0.14;
  myKNN.addExample(dataInput,1);
  dataInput[0]=1.00;
  dataInput[1]=0.57;
  dataInput[2]=0.25;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.95;
  dataInput[1]=0.51;
  dataInput[2]=0.22;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.80;
  dataInput[1]=0.43;
  dataInput[2]=0.18;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.85;
  dataInput[1]=0.44;
  dataInput[2]=0.19;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.60;
  dataInput[1]=0.31;
  dataInput[2]=0.14;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.58;
  dataInput[1]=0.31;
  dataInput[2]=0.14;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.58;
  dataInput[1]=0.31;
  dataInput[2]=0.14;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.63;
  dataInput[1]=0.33;
  dataInput[2]=0.15;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.65;
  dataInput[1]=0.33;
  dataInput[2]=0.15;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.86;
  dataInput[1]=0.42;
  dataInput[2]=0.19;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.80;
  dataInput[1]=0.41;
  dataInput[2]=0.18;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.67;
  dataInput[1]=0.36;
  dataInput[2]=0.16;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.92;
  dataInput[1]=0.48;
  dataInput[2]=0.21;
  myKNN.addExample(dataInput,1);
  dataInput[0]=1.00;
  dataInput[1]=0.51;
  dataInput[2]=0.23;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.83;
  dataInput[1]=0.44;
  dataInput[2]=0.19;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.74;
  dataInput[1]=0.39;
  dataInput[2]=0.17;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.85;
  dataInput[1]=0.46;
  dataInput[2]=0.20;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.81;
  dataInput[1]=0.43;
  dataInput[2]=0.19;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.83;
  dataInput[1]=0.45;
  dataInput[2]=0.19;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.83;
  dataInput[1]=0.44;
  dataInput[2]=0.19;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.82;
  dataInput[1]=0.44;
  dataInput[2]=0.19;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.81;
  dataInput[1]=0.43;
  dataInput[2]=0.19;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.80;
  dataInput[1]=0.43;
  dataInput[2]=0.19;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.80;
  dataInput[1]=0.43;
  dataInput[2]=0.19;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.79;
  dataInput[1]=0.42;
  dataInput[2]=0.18;
  myKNN.addExample(dataInput,1);
  dataInput[0]=0.81;
  dataInput[1]=0.43;
  dataInput[2]=0.18;
  myKNN.addExample(dataInput,1);
  dataInput[0]=1.00;
  dataInput[1]=0.54;
  dataInput[2]=0.23;
  myKNN.addExample(dataInput,1);
  dataInput[0]=1.00;
  dataInput[1]=0.76;
  dataInput[2]=0.33;
  myKNN.addExample(dataInput,1);
  dataInput[0]=1.00;
  dataInput[1]=0.83;
  dataInput[2]=0.36;
  myKNN.addExample(dataInput,1);
  //Tekan tombol untuk mencari data baru
  dataInput[0]=0.52;
  dataInput[1]=0.34;
  dataInput[2]=0.25;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.53;
  dataInput[1]=0.34;
  dataInput[2]=0.24;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.53;
  dataInput[1]=0.34;
  dataInput[2]=0.24;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.52;
  dataInput[1]=0.34;
  dataInput[2]=0.25;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.53;
  dataInput[1]=0.34;
  dataInput[2]=0.25;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.54;
  dataInput[1]=0.34;
  dataInput[2]=0.24;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.55;
  dataInput[1]=0.33;
  dataInput[2]=0.24;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.55;
  dataInput[1]=0.33;
  dataInput[2]=0.24;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.54;
  dataInput[1]=0.33;
  dataInput[2]=0.24;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.53;
  dataInput[1]=0.33;
  dataInput[2]=0.25;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.54;
  dataInput[1]=0.33;
  dataInput[2]=0.24;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.54;
  dataInput[1]=0.33;
  dataInput[2]=0.23;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.55;
  dataInput[1]=0.33;
  dataInput[2]=0.23;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.55;
  dataInput[1]=0.33;
  dataInput[2]=0.23;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.54;
  dataInput[1]=0.34;
  dataInput[2]=0.23;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.55;
  dataInput[1]=0.33;
  dataInput[2]=0.23;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.55;
  dataInput[1]=0.33;
  dataInput[2]=0.23;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.55;
  dataInput[1]=0.33;
  dataInput[2]=0.23;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.55;
  dataInput[1]=0.33;
  dataInput[2]=0.23;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.56;
  dataInput[1]=0.33;
  dataInput[2]=0.23;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.55;
  dataInput[1]=0.33;
  dataInput[2]=0.23;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.55;
  dataInput[1]=0.33;
  dataInput[2]=0.23;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.55;
  dataInput[1]=0.33;
  dataInput[2]=0.24;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.54;
  dataInput[1]=0.33;
  dataInput[2]=0.24;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.55;
  dataInput[1]=0.33;
  dataInput[2]=0.24;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.56;
  dataInput[1]=0.33;
  dataInput[2]=0.23;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.56;
  dataInput[1]=0.33;
  dataInput[2]=0.23;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.54;
  dataInput[1]=0.33;
  dataInput[2]=0.24;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.53;
  dataInput[1]=0.34;
  dataInput[2]=0.25;
  myKNN.addExample(dataInput,2);
  dataInput[0]=0.53;
  dataInput[1]=0.35;
  dataInput[2]=0.24;
  myKNN.addExample(dataInput,2);

}


void loop() {

  int classification;
  buttonState = digitalRead(p21);
  Serial.println("Tekan tombol dan tunjukkan saya sebuah objek");
  // Wait for the object to move away again
  while (buttonState == 1) {
    buttonState = digitalRead(p21);
    delay(10);
  }
  

  // Wait for an object then read its color
  //read colour
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

  // Classify the object
  classification = myKNN.classify(dataInput, K);

  // Print the classification
  Serial.print("Kamu menunjukkan: ");
  Serial.println(label[classification]);
 
}




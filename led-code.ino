// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// Released under the GPLv3 license to match the rest of the
// Adafruit NeoPixel library

#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
 #include <avr/power.h> // Required for 16 MHz Adafruit Trinket
#endif

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 // On Trinket or Gemma, suggest changing this to 1

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 120

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 0 // Time (in milliseconds) to pause between pixels

const int dataPin1 = 8;
const int dataPin2 = 9;
const int dataPin3 = 10;

void setup() {
  // These lines are specifically to support the Adafruit Trinket 5V 16 MHz.
  // Any other board, you can remove this part (but no harm leaving it):
#if defined(__AVR_ATtiny85__) && (F_CPU == 16000000)
  clock_prescale_set(clock_div_1);
#endif
  // END of Trinket-specific code.
  Serial.begin(9600); //initiate debug serial

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)

  pinMode(dataPin1, INPUT);
  pinMode(dataPin2, INPUT);
  pinMode(dataPin3, INPUT);
}

void loop() {
  int input1 = digitalRead(dataPin1);
  int input2 = digitalRead(dataPin2);
  int input3 = digitalRead(dataPin3);
  //inputs from PINs are read as input1 in the 1s place, input2 in the 2s place, input3 in the 4s place
  int inputAsNumber = input1 + (2*input2) + (4*input3);
  Serial.println(inputAsNumber);
  
  //convert the numbers into actual colors


  //pixels.clear(); // Set all pixel colors to 'off'
  numberToColor(inputAsNumber);
  pixels.show();   // Send the updated pixel colors to the hardware.
}

void displayColor(String color){
int R, G, B;
  if(color == "red"){
    R = 120;
    G = 0;
    B = 0;
  } else if(color == "orange"){
    R = 102;
    G = 66;
    B = 0;
  } else if(color == "yellow"){
    R = 90;
    G = 90;
    B = 0;
  } else if(color == "green"){
    R = 0;
    G = 120;
    B = 0;
  } else if(color == "blue"){
    R = 0;
    G = 0;
    B = 120;
  } else if(color == "purple"){
    R = 80;
    G = 16;
    B = 140;
  } else if(color == "white"){
    R = 70;
    G = 70;
    B = 70;
  } else if(color == "off"){
    R = 0;
    G = 0;
    B = 0;
  }
  //now show the color
  for(int i=0; i<NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(R, G, B));
  }
}

void numberToColor(int number){
  switch(number){
    case 1:
      displayColor("red");
      break;
    case 2:
      displayColor("orange");
      break;
    case 3:
      displayColor("yellow");
      break;
    case 4:
      displayColor("green");
      break;
    case 5:
      displayColor("blue");
      break;
    case 6:
      displayColor("purple");
      break;
    default:
      displayColor("off");
  }
}

void schoolColors(){
for(int i=0; i<NUMPIXELS; i++) { // For each pixel...
    if(i % 2){
      pixels.setPixelColor(i, pixels.Color(80, 16, 140));
    } else {
    pixels.setPixelColor(i, pixels.Color(70, 70, 70));
    }
  }
}

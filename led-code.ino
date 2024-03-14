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
#define NUMPIXELS 61 

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 0 // Time (in milliseconds) to pause between pixels

const int dataPin1 = 10;
const int dataPin2 = 11;
const int dataPin3 = 12;
int startPixel = 0;
int endPixel = 50;
bool flash = false;
int timer = 0;
int defaultBrightness = 50;
int brightness = defaultBrightness;

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
  //Serial.println(inputAsNumber);

  numberToLights(inputAsNumber); //convert the numbers into actual colors

  pixels.setBrightness(brightness);
  
  if(flash==true){
    if (timer < 50){
      pixels.show();
      Serial.write("A");
    } else if(timer < 100){
      clearPixels();
      Serial.write("B");
    } else {
      timer = 0;
    }
  } else {
    pixels.show();
    timer = 0;
  }
  ++timer;
  Serial.println(timer);
  Serial.write("\n");
}

void displayColor(String color){
int R, G, B;
  if(color == "red"){
    R = 120;
    G = 0;
    B = 0;
  } else if(color == "orange"){
    R = 140;
    G = 70;
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

void numberToLights(int number){
  switch(number){
    case 1:
      pixels.clear();
      displayColor("purple");
      flash = false;
      brightness = (0.5*defaultBrightness);
      break;
    case 2:
      pixels.clear();
      displayColor("purple");
      flash = true;
      brightness = (1.5*defaultBrightness);
      break;
    case 3:
      pixels.clear();
      partialLights("left");
      flash = false;
      brightness = (1.5*defaultBrightness);
      break;
    case 4:
    pixels.clear();
      partialLights("right");
      flash = false;
      brightness = defaultBrightness;
      break;
    case 5: 
      pixels.clear();
      partialLights("center");
      flash = true;
      brightness = defaultBrightness;
      break;
    case 6:
      pixels.clear();
      displayColor("green");
      flash = true;
      brightness = defaultBrightness;
      break;
    default:
      displayColor("off");
  }
}

void partialLights(String side){
int R, G, B;  
  if(side=="center"){
    startPixel = 0;
    endPixel = NUMPIXELS;
    R = 255;
    G = 166;
    B = 0;
  } else if(side=="left"){
    startPixel = 0;
    endPixel = 10;
    R = 0;
    G = 63;
    B = 92;
  } else if(side=="right"){
    startPixel = 15;
    endPixel = 25;
    R = 188;
    G = 80;
    B = 144;
  }
  for(int i=startPixel; i<endPixel; i++){
    pixels.setPixelColor(i, pixels.Color(R, G, B));
  }
}

void clearPixels(){
  for (int i=0; i<NUMPIXELS; i++){
    pixels.setPixelColor(i, pixels.Color(0, 0, 0));
  }
  pixels.show();
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

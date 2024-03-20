#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
#define PIN        6 

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS 61
#define NUMPIXELSUNDERGLOW 75
#define NUMPIXELSTOTAL NUMPIXELS + NUMPIXELSUNDERGLOW

// When setting up the NeoPixel library, we tell it how many pixels,
// and which pin to use to send signals. Note that for older NeoPixel
// strips you might need to change the third parameter -- see the
// strandtest example for more information on possible values.
Adafruit_NeoPixel pixels(NUMPIXELSTOTAL, PIN, NEO_GRB + NEO_KHZ800);

#define DELAYVAL 0 // Time (in milliseconds) to pause between pixels

//pins for data
const int dataPin1 = 10;
const int dataPin2 = 11;
const int dataPin3 = 12;

bool flash = false; //do you want the lights to flash

//timers
int timer = 0; // timer for the normal lights
int underglowTimer = 0; //timer for the underglow

//brightness for informative lights
int defaultBrightness = 255; //the default brightness of the lights
int brightness = defaultBrightness; //how bright the lights will be at this moment

//stuff used later in the code
int startPixel = 0;
int endPixel = 50;

//undergl ow stuff
const bool underglowEnabled = true; //do you want the under glow on?
const int underglowBrightness = 255; //brightness of the underglow, max 255

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

  pixels.setBrightness(brightness);

  numberToLights(inputAsNumber); //convert the numbers into actual colors
  
  if(flash==true){
    if (timer < 3){
      pixels.show();
      Serial.write("Flashing...\n");
    } else if(timer < 6){
      clearPixels();
      Serial.write("Un-Flashing...\n");
    } else {
      Serial.write("Flash timer over...\n");
      timer = 0;
    }
  } else {
    Serial.println("Default show without flash...");
    pixels.show();
    timer = 0;
  }
  if(underglowEnabled == true){
    underglow();
  }
  ++timer;
  //Serial.println(timer);
  //delay(10000);
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
    R = 255;
    G = 166;
    B = 0;
  } else if(color == "green"){
    R = 0;
    G = 120;
    B = 0;
  } else if(color == "blue"){
    R = 0;
    G = 63;
    B = 92;
  } else if(color == "purple"){
    R = 80;
    G = 16;
    B = 140;
  } else if(color = "dark-purple"){
    R = 30;
    G = 6;
    B = 53;
  } else if(color == "white"){
    R = 70;
    G = 70;
    B = 70;
  } else if(color == "pink"){
    R = 255;
    G = 99;
    B = 97;
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
  Serial.write("numberToLights(");
  Serial.print(number);
  Serial.write(")...\n");
  switch(number){
    case 1:
      Serial.println("State: default");
      displayColor("dark-purple");
      flash = false;
      brightness = (0.5*defaultBrightness);
      break;
    case 2:
      Serial.println("State: note has been intaked");
      displayColor("purple");
      flash = true;
      brightness = defaultBrightness;
      break;
    case 3:
      Serial.println("State: note detected to the right");
      displayColor("blue");
      flash = false;
      brightness = (0.5*defaultBrightness);
      break;
    case 4:
      Serial.println("State: note detected to the left");
      displayColor("pink");
      flash = false;
      brightness = (defaultBrightness);
      break;
    case 5: 
      Serial.println("State: note detected in the center");
      displayColor("yellow");
      flash = true;
      brightness = defaultBrightness;
      break;
    case 6:
      Serial.println("State: Speaker AprilTag detected");
      displayColor("green");
      flash = true;
      brightness = defaultBrightness;
      break;
    default:
      Serial.println("State: LED off");
      displayColor("off");
      flash = false;
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
  } else if(side=="right"){
    startPixel = 0;
    endPixel = floor(0.5 * NUMPIXELS);
    R = 0;
    G = 63;
    B = 92;
  } else if(side=="left"){
    startPixel = ceil(0.5 * NUMPIXELS);
    endPixel = NUMPIXELS;
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

void underglow(){
  const int underglowFirstTime = NUMPIXELSUNDERGLOW * 3;
  const int underglowSecondTime = underglowFirstTime + (NUMPIXELSUNDERGLOW * 2);
  const int underglowThirdTime = underglowSecondTime + (NUMPIXELSUNDERGLOW * 2);

  //pixels.setBrightness(underglowBrightness);

  if(underglowTimer < underglowFirstTime){
    if(underglowTimer % 3 == 0){
      pixels.setPixelColor(((underglowTimer/5)+NUMPIXELS), pixels.Color(180, 50, 255));
    }
  } else if (underglowTimer < underglowSecondTime){
      if ((underglowTimer - underglowFirstTime) % 2 == 0){
        pixels.setPixelColor((((underglowTimer - underglowFirstTime)/3)+NUMPIXELS), pixels.Color(255, 255, 255));
      }
  } else if (underglowTimer < underglowThirdTime){
      if ((underglowTimer - underglowSecondTime) % 4 == 0){
        pixels.setPixelColor(((2 * (underglowTimer - underglowSecondTime)/4)+NUMPIXELS), pixels.Color(180, 50, 255));
      }
  } else {
    underglowTimer = 0;
  }
  pixels.show();
  ++underglowTimer;
  //Serial.println(underglowTimer);
}

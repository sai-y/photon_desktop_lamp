/*
 * Particle Desktop Lamp
 *Enables sending a trigger from a rollbar webhook
 */
#include "neopixel/neopixel.h"



// IMPORTANT: Set pixel COUNT, PIN and TYPE
#define PIXEL_PIN D6
#define PIXEL_COUNT 24
#define PIXEL_TYPE WS2812B

Adafruit_NeoPixel strip = Adafruit_NeoPixel(PIXEL_COUNT, PIXEL_PIN, PIXEL_TYPE);

bool triggerReceived = false;

void setup() 
{
    //register trigger function with the cloud
    bool success = Particle.function("trigger", triggerAlert);
    strip.begin();
    strip.show(); // Initialize all pixels to 'off'
}
void loop() 
{
    
    if(triggerReceived){
        for(int i=0;i<25;i++){
            colorWipe(strip.Color(255, 0, 0), 50); // Red
            colorWipe(strip.Color(0, 0, 0), 50); // Off
        }
        triggerReceived = false;
    }else{
        for(int i=0;i<2;i++){
            colorWipe(strip.Color(255, 255, 255), 50); // White
            colorWipe(strip.Color(0, 0, 0), 50); // Off
        }
    }
}

// Fill the dots one after the other with a color, wait (ms) after each one
void colorWipe(uint32_t c, uint8_t wait) {
  for(uint16_t i=0; i<strip.numPixels(); i++) {
    strip.setPixelColor(i, c);
    strip.show();
    delay(wait);
  }
}

// this is the function that is called when a trigger is received 
int triggerAlert(String command){
    if(command == "triggered"){
        if(true){
            triggerReceived = true;
            return 1;
        }
    }
    return -1;
}
/*
 * This Example shows the allcolor, allrgb, and clear commands
 * 
 * allcolor(color[3]) or allcolor(color[3],delay)
 * allrgb(R,G,B) or allrgb(R,G,B,delay)
 * clear() or clear(delay)
 * 
 * Library based off the one created by Adafruit for the PCA9685
 */

#include <i2cRGB.h> // include the library

RGBDriver rgb1 = RGBDriver(0x40); // create the instance, and specify the i2c address. default is 0x40 - address can be found / confirmed with i2c scanner File >> Examples >> Wire >> i2c_scanner
// RGBDriver rgb2 = RGBDriver(0x41); // multiple instanaces can be made and name rgb can be changed to suit one's need

/*
 * Built in colors in the library:
 * 
 * black
 * white
 * green
 * cyan
 * blue
 * purple
 * magenta
 * red
 * orange
 * yellow
 * 
 * using a library color will show up in green text
 * 
 * custom colors can be made within a sketch:
 * 
 * give your color a name - set the RGB values 0 - 255
 * custom_color[3] = {0,0,0};
 * 
 */


void setup() {
  // put your setup code here, to run once:

  rgb1.begin(); // start the instance - starts teh i2c communication and runs teh clear(); command ensuring all outputs are off

  // rgb1.clear(); this command can be used with an with or without a delay in the brackets.

}

void loop() {
  // put your main code here, to run repeatedly:

  rgb1.allcolor(red);         // operate the same as allcrgb but you can use an array color - either custom or from the 10 colors in the library
                              // the 4th number is a delay value (for possible animations) with use delay and can block code
                              // can be done with or without a delay
  delay(1000);
  rgb1.allcolor(green);
  delay(1000);
  rgb1.allcolor(blue);
  delay(1000);
  rgb1.clear();               // turns off all RGB channels - can be done with or without a delay
  rgb1.allrgb(255,0,0,500);   // operate the same as allcolor but you can specify rgb value vs using an array color,
                              //the 4th number is a delay value (for possible animations) with use delay and can block code
                              // can be done with or without a delay
  delay(1000);
  rgb1.allrgb(0,255,0,500);
  delay(1000);
  rgb1.allrgb(0,0,255,500);
  delay(1000);
  rgb1.clear(500);

}

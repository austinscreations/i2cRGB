/*
 * This Example shows the rgb, color, and off commands
 * 
 * rgb(channel #,R,G,B)
 * color(channel #, color[3])
 * off(channel #
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
 * a library color will show up in green text
 * 
 * custom colors can be made within a sketch:
 * 
 * give your color a name - set the RGB values 0 - 255
 * int custom_color[3] = {0,0,0};
 * 
 */

int custom_color[3] = {5,250,100}; // lets make a custom green color

void setup() {
  // put your setup code here, to run once:

  rgb1.begin(); // start the instance - starts teh i2c communication and runs teh clear(); command ensuring all outputs are off

  // rgb1.clear(); this command can be used with an with or without a delay in the brackets.

}

void loop() {
  // put your main code here, to run repeatedly:

  rgb1.rgb(0,255,0,0); // setting channel 0 to red using RGB values
  delay(1000);
  rgb1.rgb(1,0,255,0); // setting channel 1 to green using RGB values
  delay(1000);
  rgb1.color(2,blue); // setting channel 2 to blue using color array built into library
  delay(1000);
  rgb1.color(3,magenta);  // setting channel 3 to cyan using color array built into library
  delay(1000);
  rgb1.color(4,custom_color); // setting channel 4 to a custom color array specifyed by user in the sketch
  delay(1000);
  
  // lets turn each channel off in reverse order
  
  rgb1.off(4); // specify channel number - each module can support 5 channels but channel number starts from 0 (0-4 acceptable)
  delay(500);
  rgb1.off(3);
  delay(500);
  rgb1.off(2);
  delay(500);
  rgb1.off(1);
  delay(500);
  rgb1.off(0);
  delay(1000);
  
  
  
 

}

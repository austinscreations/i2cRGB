/*
 * This Example shows the crossfadeCOLOR and crossfadeRGB commands
 * 
 * This is a basic example of fade one led to a color
 * 
 * crossfadeCOLOR(channel #, color[3])
 * crossfadeRGB(channel #, R,G,B)
 * 
 * variable "complete[channel #]" - used to check if a loop of fade has finished (has traget fade color been reached)
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

int light1[3] = {black[3]}; // variable to store the current color to fade to for the first LED channel

unsigned long previousMillis1 = 0; // previous update of fading for led color strip 1

int colorselect = 1; // current color being selected menu


void setup() {
  // put your setup code here, to run once:

  rgb1.begin(); // start the instance - starts teh i2c communication and runs teh clear(); command ensuring all outputs are off

  // rgb1.clear(); this command can be used with an with or without a delay in the brackets.

}

void loop() {
  // put your main code here, to run repeatedly:

 // updates the color with the new fade step every 10 milli seconds
 // fade can be sped up or slowed down wit hchanging the variable "10"
 // fading must be done with a millis counter as the library doesn't use delay to avoid blocking and distrupting other aspects of a project.

unsigned long currentMillis = millis();

if (currentMillis - previousMillis1 >= 10) {
  previousMillis1 = currentMillis;
  rgb1.crossfadeCOLOR(0,light1);   // fade channel 0 to our selected color
}

  if (rgb1.complete[0] == true){  // have we reached the targeted color?
  delay(5000);                 // wait a moment before starting the next color crossfade
  colorselect ++;              // advances to the next color to fade to
  if (colorselect >= 10){      // have we reached our last color in teh menu, then reset
    colorselect = 1;
  }
  rgb1.complete[0] = {false};       // reset out loop finish variable
}


if (colorselect == 1){
 light1[0] = {red[0]}; // set led color
 light1[1] = {red[1]}; // set led color
 light1[2] = {red[2]}; // set led color
 colorselect++;
}
if (colorselect == 3){
 light1[0] = {green[0]}; // set led color
 light1[1] = {green[1]}; // set led color
 light1[2] = {green[2]}; // set led color
 colorselect++;
}
if (colorselect == 5){
 light1[0] = {blue[0]}; // set led color
 light1[1] = {blue[1]}; // set led color
 light1[2] = {blue[2]}; // set led color
 colorselect++;
}
if (colorselect == 7){  // color array could even be set with RGB values
 light1[0] = {5}; // set led color
 light1[1] = {250}; // set led color
 light1[2] = {100}; // set led color
 colorselect++;
}
if (colorselect == 9){
 light1[0] = {magenta[0]}; // set led color
 light1[1] = {magenta[1]}; // set led color
 light1[2] = {magenta[2]}; // set led color
 colorselect++;
}




}

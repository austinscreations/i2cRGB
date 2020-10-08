/*
 * This Example shows the crossfadeCOLOR commands with button control
 * 
 * This is a basic example of fading between colors with buttons
 * 
 * crossfadeBUTTON(channel #, color[3]) // use this one for seemless button control, fade can have unexpeted results with other fade functions
 * fadereset(channel #) used to reset a fade, say changing color based on button press
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

// declare your push buttons (wired to ground)

#define L1_button1 4
#define L1_button2 6
#define L2_button1 2
#define L2_button2 5
#define L3_button1 3
#define L3_button2 7
 
int light1[3] = {black[3]}; // variable to store the current color to fade to for the first LED channel
int light2[3] = {black[3]}; // variable to store the current color to fade to for the first LED channel
int light3[3] = {black[3]}; // variable to store the current color to fade to for the first LED channel

unsigned long previousMillis1 = 0; // previous update of fading for led color strip 1
unsigned long previousMillis2 = 0; // previous update of fading for led color strip 1
unsigned long previousMillis3 = 0; // previous update of fading for led color strip 1

int state1 = 0;      // state of buttons
int state2 = 0;      // state of button
int state3 = 0;      // state of button

int reading1;           // the current reading from the input pin
int reading2;           // the current reading from the input pin
int reading3;           // the current reading from the input pin
int reading4;           // the current reading from the input pin
int reading5;           // the current reading from the input pin
int reading6;           // the current reading from the input pin

int previous1 = LOW;    // the previous reading from the input pin
int previous2 = LOW;    // the previous reading from the input pin
int previous3 = LOW;    // the previous reading from the input pin
int previous4 = LOW;    // the previous reading from the input pin
int previous5 = LOW;    // the previous reading from the input pin
int previous6 = LOW;    // the previous reading from the input pin

long buttonprev1 = 0;         // the last time the output pin was toggled
long buttonprev2 = 0;         // the last time the output pin was toggled
long buttonprev3 = 0;         // the last time the output pin was toggled
long buttonprev4 = 0;         // the last time the output pin was toggled
long buttonprev5 = 0;         // the last time the output pin was toggled
long buttonprev6 = 0;         // the last time the output pin was toggled

long debounce = 300;   // the debounce time, increase if the output flickers


void setup() {
  // put your setup code here, to run once:

  rgb1.begin(); // start the instance - starts teh i2c communication and runs teh clear(); command ensuring all outputs are off

  // rgb1.clear(); this command can be used with an with or without a delay in the brackets.

  pinMode(L1_button1, INPUT_PULLUP);
  pinMode(L1_button2, INPUT_PULLUP);
  
  pinMode(L2_button1, INPUT_PULLUP);
  pinMode(L2_button2, INPUT_PULLUP);
  
  pinMode(L3_button1, INPUT_PULLUP);
  pinMode(L3_button2, INPUT_PULLUP);


}

void loop() {
  // put your main code here, to run repeatedly:

reading1 = digitalRead(L1_button1);
reading2 = digitalRead(L1_button2);

reading3 = digitalRead(L2_button1);
reading4 = digitalRead(L2_button2);

reading5 = digitalRead(L3_button1);
reading6 = digitalRead(L3_button2);

//// light 1 buttons

if (reading1 == HIGH && previous1 == LOW && millis() - buttonprev1 > debounce) {
  rgb1.fadereset(0); // resets the when button pressed - if not added the fade would stop and not fade to the second color
 if (state1 == 1){ // I was the last pressed
  state1 = 0;
 light1[0] = {black[0]}; // set led color//turn off
 light1[1] = {black[1]}; // set led color//turn off
 light1[2] = {black[2]}; // set led color//turn off
 }else{ // not the most recent button 
  state1 = 1;
 light1[0] = {red[0]}; // set led color//turn off
 light1[1] = {red[1]}; // set led color//turn off
 light1[2] = {red[2]}; // set led color//turn off
 }
 buttonprev1 = millis();
}

if (reading2 == HIGH && previous2 == LOW && millis() - buttonprev2 > debounce) {
  rgb1.fadereset(0); // resets the when button pressed - if not added the fade would stop and not fade to the second color
 if (state1 == 2){ // I was the last pressed
  state1 = 0;
 light1[0] = {black[0]}; // set led color//turn off
 light1[1] = {black[1]}; // set led color//turn off
 light1[2] = {black[2]}; // set led color//turn off
 }else{ // not the most recent button 
  state1 = 2;
 light1[0] = {white[0]}; // set led color//turn off
 light1[1] = {white[1]}; // set led color//turn off
 light1[2] = {white[2]}; // set led color//turn off
 }
   buttonprev2 = millis();
}


//// light 2 buttons

if (reading3 == HIGH && previous3 == LOW && millis() - buttonprev3 > debounce) {
  rgb1.fadereset(1); // resets the when button pressed - if not added the fade would stop and not fade to the second color
 if (state2 == 1){ // I was the last pressed
  state2 = 0;
 light2[0] = {black[0]}; // set led color//turn off
 light2[1] = {black[1]}; // set led color//turn off
 light2[2] = {black[2]}; // set led color//turn off
 }else{ // not the most recent button 
  state2 = 1;
 light2[0] = {red[0]}; // set led color//turn off
 light2[1] = {red[1]}; // set led color//turn off
 light2[2] = {red[2]}; // set led color//turn off
 }
 buttonprev3 = millis();
}

if (reading4 == HIGH && previous4 == LOW && millis() - buttonprev4 > debounce) {
  rgb1.fadereset(1); // resets the when button pressed - if not added the fade would stop and not fade to the second color
 if (state2 == 2){ // I was the last pressed
  state2 = 0;
 light2[0] = {black[0]}; // set led color//turn off
 light2[1] = {black[1]}; // set led color//turn off
 light2[2] = {black[2]}; // set led color//turn off
 }else{ // not the most recent button 
  state2 = 2;
 light2[0] = {white[0]}; // set led color//turn off
 light2[1] = {white[1]}; // set led color//turn off
 light2[2] = {white[2]}; // set led color//turn off
 }
 buttonprev4 = millis();
}


//// light 3 buttons

if (reading5 == HIGH && previous5 == LOW && millis() - buttonprev5 > debounce) {
  rgb1.fadereset(2); // resets the when button pressed - if not added the fade would stop and not fade to the second color
 if (state3 == 1){ // I was the last pressed
  state3 = 0;
 light3[0] = {black[0]}; // set led color//turn off
 light3[1] = {black[1]}; // set led color//turn off
 light3[2] = {black[2]}; // set led color//turn off
 }else{ // not the most recent button 
  state3 = 1;
 light3[0] = {purple[0]}; // set led color//turn off
 light3[1] = {purple[1]}; // set led color//turn off
 light3[2] = {purple[2]}; // set led color//turn off
 }
   buttonprev5 = millis();
}

if (reading6 == HIGH && previous6 == LOW && millis() - buttonprev6 > debounce) {
  rgb1.fadereset(2); // resets the when button pressed - if not added the fade would stop and not fade to the second color
 if (state3 == 2){ // I was the last pressed
  state3 = 0;
 light3[0] = {black[0]}; // set led color//turn off
 light3[1] = {black[1]}; // set led color//turn off
 light3[2] = {black[2]}; // set led color//turn off
 }else{ // not the most recent button 
  state3 = 2;
 light3[0] = {white[0]}; // set led color//turn off
 light3[1] = {white[1]}; // set led color//turn off
 light3[2] = {white[2]}; // set led color//turn off
// color(0,white);
 }
 buttonprev6 = millis();
}

previous1 = reading1;
previous2 = reading2;
previous3 = reading3;
previous4 = reading4;
previous5 = reading5;
previous6 = reading6;

 // updates the color with the new fade step every 10 milli seconds
 // fade can be sped up or slowed down wit hchanging the variable "10"
 // fading must be done with a millis counter as the library doesn't use delay to avoid blocking and distrupting other aspects of a project.

unsigned long currentMillis = millis();

if (currentMillis - previousMillis1 >= 10) {
  previousMillis1 = currentMillis;
  rgb1.crossfadeBUTTON(0,light1);   // fade channel 0 to our selected color
}


if (currentMillis - previousMillis2 >= 10) { // light 2 will fade quickly
  previousMillis2 = currentMillis;
  rgb1.crossfadeBUTTON(1,light2);   // fade channel 0 to our selected color
}


if (currentMillis - previousMillis3 >= 10) { // light 3 wil lfade the slowest
  previousMillis3 = currentMillis;
  rgb1.crossfadeBUTTON(2,light3);   // fade channel 0 to our selected color
}





}

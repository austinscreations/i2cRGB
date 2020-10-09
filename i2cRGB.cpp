// cpp file

/*!
 *
 * This library is based of one created by Adafruit for the PCA9685,
 * it has been modified for easy control of RGB led strips via mosfets
 *
 *  @file Adafruit_PWMServoDriver.cpp
 *
 *  @mainpage Adafruit 16-channel PWM & Servo driver
 *
 *  @section intro_sec Introduction
 *
 *  This is a library for the 16-channel PWM & Servo driver.
 *
 *  Designed specifically to work with the Adafruit PWM & Servo driver.
 *
 *  Pick one up today in the adafruit shop!
 *  ------> https://www.adafruit.com/product/815
 *
 *  These displays use I2C to communicate, 2 pins are required to interface.
 *
 *  Adafruit invests time and resources providing this open source code,
 *  please support Adafruit andopen-source hardware by purchasing products
 *  from Adafruit!
 *
 *  @section author Author
 *
 *  Limor Fried/Ladyada (Adafruit Industries).
 *
 *  @section license License
 *
 *  BSD license, all text above must be included in any redistribution
 */





#include "i2cRGB.h"
#include <Wire.h>


/*!
 *  @brief  Instantiates a new PCA9685 PWM driver chip with the I2C address on a
 * TwoWire interface
 *  @param  addr The 7-bit I2C address to locate this chip, default is 0x40
 */
RGBDriver::RGBDriver(const uint8_t addr)
    : _i2caddr(addr), _i2c(&Wire) {}


/*!
 *  @brief  Setups the I2C interface and hardware
 */
void RGBDriver::begin() {
  _i2c->begin();
  reset();
    setPWMFreq(1000);
  // set the default internal frequency
  setOscillatorFrequency(FREQUENCY_OSCILLATOR);
clear();
}

/*!
 *  @brief  Sends a reset command to the PCA9685 chip over I2C
 */
void RGBDriver::reset() {
  write8(PCA9685_MODE1, MODE1_RESTART);
  delay(10);
}

/*!
 *  @brief  Sets the PWM frequency for the entire chip, up to ~1.6 KHz
 *  @param  freq Floating point frequency that we will attempt to match
 */
void RGBDriver::setPWMFreq(float freq) {
  // Range output modulation frequency is dependant on oscillator
  if (freq < 1)
    freq = 1;
  if (freq > 3500)
    freq = 3500; // Datasheet limit is 3052=50MHz/(4*4096)

  float prescaleval = ((_oscillator_freq / (freq * 4096.0)) + 0.5) - 1;
  if (prescaleval < PCA9685_PRESCALE_MIN)
    prescaleval = PCA9685_PRESCALE_MIN;
  if (prescaleval > PCA9685_PRESCALE_MAX)
    prescaleval = PCA9685_PRESCALE_MAX;
  uint8_t prescale = (uint8_t)prescaleval;

  uint8_t oldmode = read8(PCA9685_MODE1);
  uint8_t newmode = (oldmode & ~MODE1_RESTART) | MODE1_SLEEP; // sleep
  write8(PCA9685_MODE1, newmode);                             // go to sleep
  write8(PCA9685_PRESCALE, prescale); // set the prescaler
  write8(PCA9685_MODE1, oldmode);
  delay(5);
  // This sets the MODE1 register to turn on auto increment.
  write8(PCA9685_MODE1, oldmode | MODE1_RESTART | MODE1_AI);

}

/*!
 *  @brief  Sets the output mode of the PCA9685 to either
 *  open drain or push pull / totempole.
 *  Warning: LEDs with integrated zener diodes should
 *  only be driven in open drain mode.
 *  @param  totempole Totempole if true, open drain if false.
 */
void RGBDriver::setOutputMode(bool totempole) {
  uint8_t oldmode = read8(PCA9685_MODE2);
  uint8_t newmode;
  if (totempole) {
    newmode = oldmode | MODE2_OUTDRV;
  } else {
    newmode = oldmode & ~MODE2_OUTDRV;
  }
  write8(PCA9685_MODE2, newmode);
}



/*!
 *  @brief  Gets the PWM output of one of the PCA9685 pins
 *  @param  num One of the PWM output pins, from 0 to 15
 *  @return requested PWM output value
 */
uint8_t RGBDriver::getPWM(uint8_t num) {
  _i2c->requestFrom((int)_i2caddr, PCA9685_LED0_ON_L + 4 * num, (int)4);
  return _i2c->read();
}

/*!
 *  @brief  Sets the PWM output of one of the PCA9685 pins
 *  @param  num One of the PWM output pins, from 0 to 15
 *  @param  on At what point in the 4096-part cycle to turn the PWM output ON
 *  @param  off At what point in the 4096-part cycle to turn the PWM output OFF
 */
void RGBDriver::setPWM(uint8_t num, uint16_t on, uint16_t off) {
  _i2c->beginTransmission(_i2caddr);
  _i2c->write(PCA9685_LED0_ON_L + 4 * num);
  _i2c->write(on);
  _i2c->write(on >> 8);
  _i2c->write(off);
  _i2c->write(off >> 8);
  _i2c->endTransmission();
}

void RGBDriver::off(int c){
setPWM(0+(3*c),0,0); // off
setPWM(1+(3*c),0,0); // off
setPWM(2+(3*c),0,0); // off
prevR[c] = 0;
prevG[c] = 0;
prevB[c] = 0;
redVal[c] = 0;
grnVal[c] = 0; 
bluVal[c] = 0;
}


void RGBDriver::rgb(int c,uint8_t r,uint8_t g,uint8_t b){
 R = map(r,0,255,0,4095); // changes from a 255 value to a 16 bit value as the PWM driver outputs a 16bit pulse
 G = map(g,0,255,0,4095);
 B = map(b,0,255,0,4095);
setPWM(0+(3*c),0,R); //red
setPWM(1+(3*c),0,G); //green
setPWM(2+(3*c),0,B); //blue

prevR[c] = r;
prevG[c] = g;
prevB[c] = b;
redVal[c] = r;
grnVal[c] = g;
bluVal[c] = b;
}

void RGBDriver::rgb16(int c,uint16_t r,uint16_t g,uint16_t b){
setPWM(0+(3*c),0,r); //red
setPWM(1+(3*c),0,g); //green
setPWM(2+(3*c),0,b); //blue

 R = map(r,0,4095,0,255); // changes from a 16 bit value to an 8 bit value for color fade variables
 G = map(g,0,4095,0,255);
 B = map(b,0,4095,0,255);

prevR[c] = R;
prevG[c] = G;
prevB[c] = B;
redVal[c] = R;
grnVal[c] = G;
bluVal[c] = B;
}

void RGBDriver::color(int c, int color[3]) {
  int r = color[0]; // more varibles to extract the array numbers
  int g = color[1];
  int b = color[2];
 R = map(r,0,255,0,4095);
 G = map(g,0,255,0,4095);
 B = map(b,0,255,0,4095);
 setPWM(0+(3*c),0,R); //red
 setPWM(1+(3*c),0,G); //green
 setPWM(2+(3*c),0,B); //blue
prevR[c] = r;
prevG[c] = g;
prevB[c] = b;
redVal[c] = r;
grnVal[c] = g;
bluVal[c] = b;
}

void RGBDriver::chan(int c, int value){
 int  v = map(value,0,255,0,4095);
  setPWM(c,0,v);
}

void RGBDriver::clear(int d){
for (int x = 0; x <= 5; x++) {
    off(x);
   delay(d);
}}

void RGBDriver::allcolor(int color[3],int d){
int r = color[0];
int g = color[1];
int b = color[2];
for (int x = 0; x <= 5; x++) {
    rgb(x,r,g,b);
  delay(d);
}}

void RGBDriver::allrgb(uint8_t r,uint8_t g,uint8_t b,int d){
for (int x = 0; x <= 5; x++) {
    rgb(x,r,g,b);
   delay(d);
}}

void RGBDriver::clear(){
for (int x = 0; x <= 5; x++) {
    off(x);
}}

void RGBDriver::allcolor(int color[3]){
int r = color[0];
int g = color[1];
int b = color[2];
for (int x = 0; x <= 5; x++) {
    rgb(x,r,g,b);
}}

void RGBDriver::allrgb(uint8_t r,uint8_t g,uint8_t b){
for (int x = 0; x <= 5; x++) {
    rgb(x,r,g,b);
}}

void RGBDriver::fadereset(int c){
    i = 0;
  prevR[c] = redVal[c]; 
  prevG[c] = grnVal[c]; 
  prevB[c] = bluVal[c];
}

RGBDriver::calculateStep(int prevValue, int endValue) {
  int step = endValue - prevValue; // What's the overall gap?
  if (step) {                      // If its non-zero, 
    step = 1020/step;              //   divide by 1020
  } 
  return step;
}

/* The next function is calculateVal. When the loop value, i,
*  reaches the step size appropriate for one of the
*  colors, it increases or decreases the value of that color by 1. 
*  (R, G, and B are each calculated separately.)
*/

RGBDriver::calculateVal(int step, int val, int i) {

  if ((step) && i % step == 0) { // If step is non-zero and its time to change a     value,
    if (step > 0) {              //   increment the value if step is positive...
      val += 1;           
    } 
    else if (step < 0) {         //   ...or decrement it if step is negative
      val -= 1;
    } 
  }
  // Defensive driving: make sure val stays in the range 0-255
  if (val > 255) {
    val = 255;
  } 
  else if (val < 0) {
    val = 0;
  }
  return val;
}


void RGBDriver::crossfadeCOLOR(int c,int color[3]) {

  int stepR = calculateStep(prevR[c], color[0]);
  int stepG = calculateStep(prevG[c], color[1]); 
  int stepB = calculateStep(prevB[c], color[2]);

    redVal[c] = calculateVal(stepR, redVal[c], i);
    grnVal[c] = calculateVal(stepG, grnVal[c], i);
    bluVal[c] = calculateVal(stepB, bluVal[c], i);

 R = map(redVal[c],0,255,0,4095); // changes from a 255 value to a 16 bit value as the PWM driver outputs a 16bit pulse
 G = map(grnVal[c],0,255,0,4095);
 B = map(bluVal[c],0,255,0,4095);
    
 setPWM(0+(3*c),0,R); //red
 setPWM(1+(3*c),0,G); //green
 setPWM(2+(3*c),0,B); //blue

if (i >= 1020){
complete[c] = {true};
fadereset(c);
}else{
  i++;
}
}

void RGBDriver::crossfadeBUTTON(int c,int color[3]) {

  int stepR = calculateStep(prevR[c], color[0]);
  int stepG = calculateStep(prevG[c], color[1]); 
  int stepB = calculateStep(prevB[c], color[2]);

    redVal[c] = calculateVal(stepR, redVal[c], i);
    grnVal[c] = calculateVal(stepG, grnVal[c], i);
    bluVal[c] = calculateVal(stepB, bluVal[c], i);

 R = map(redVal[c],0,255,0,4095); // changes from a 255 value to a 16 bit value as the PWM driver outputs a 16bit pulse
 G = map(grnVal[c],0,255,0,4095);
 B = map(bluVal[c],0,255,0,4095);
    
 setPWM(0+(3*c),0,R); //red
 setPWM(1+(3*c),0,G); //green
 setPWM(2+(3*c),0,B); //blue

if (i <= 1020){
complete[c] = {true};
fadereset(c);
}else{
  i++;
}
}

void RGBDriver::crossfadeRGB(int c,uint8_t r,uint8_t g,uint8_t b) {

  int stepR = calculateStep(prevR[c], r);
  int stepG = calculateStep(prevG[c], g); 
  int stepB = calculateStep(prevB[c], b);

    redVal[c] = calculateVal(stepR, redVal[c], i);
    grnVal[c] = calculateVal(stepG, grnVal[c], i);
    bluVal[c] = calculateVal(stepB, bluVal[c], i);

 R = map(redVal[c],0,255,0,4095); // changes from a 255 value to a 16 bit value as the PWM driver outputs a 16bit pulse
 G = map(grnVal[c],0,255,0,4095);
 B = map(bluVal[c],0,255,0,4095);
    
 setPWM(0+(3*c),0,R); //red
 setPWM(1+(3*c),0,G); //green
 setPWM(2+(3*c),0,B); //blue


if (i >= 1020){
complete[c] = {true};
fadereset(c);
}else{
  i++;
}
}


/*!
 *  @brief Setter for the internally tracked oscillator used for freq
 * calculations
 *  @param freq The frequency the PCA9685 should use for frequency calculations
 */
void RGBDriver::setOscillatorFrequency(uint32_t freq) {
  _oscillator_freq = freq;
}

/******************* Low level I2C interface */
uint8_t RGBDriver::read8(uint8_t addr) {
  _i2c->beginTransmission(_i2caddr);
  _i2c->write(addr);
  _i2c->endTransmission();

  _i2c->requestFrom((uint8_t)_i2caddr, (uint8_t)1);
  return _i2c->read();
}

void RGBDriver::write8(uint8_t addr, uint8_t d) {
  _i2c->beginTransmission(_i2caddr);
  _i2c->write(addr);
  _i2c->write(d);
  _i2c->endTransmission();
}

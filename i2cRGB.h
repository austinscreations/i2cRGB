// h file

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



#ifndef i2cRGB_H
#define i2cRGB_H

#include <Arduino.h>
#include <Wire.h>


// REGISTER ADDRESSES
#define PCA9685_MODE1 0x00      /**< Mode Register 1 */
#define PCA9685_MODE2 0x01      /**< Mode Register 2 */
#define PCA9685_SUBADR1 0x02    /**< I2C-bus subaddress 1 */
#define PCA9685_SUBADR2 0x03    /**< I2C-bus subaddress 2 */
#define PCA9685_SUBADR3 0x04    /**< I2C-bus subaddress 3 */
#define PCA9685_ALLCALLADR 0x05 /**< LED All Call I2C-bus address */
#define PCA9685_LED0_ON_L 0x06  /**< LED0 on tick, low byte*/
#define PCA9685_LED0_ON_H 0x07  /**< LED0 on tick, high byte*/
#define PCA9685_LED0_OFF_L 0x08 /**< LED0 off tick, low byte */
#define PCA9685_LED0_OFF_H 0x09 /**< LED0 off tick, high byte */
// etc all 16:  LED15_OFF_H 0x45
#define PCA9685_ALLLED_ON_L 0xFA  /**< load all the LEDn_ON registers, low */
#define PCA9685_ALLLED_ON_H 0xFB  /**< load all the LEDn_ON registers, high */
#define PCA9685_ALLLED_OFF_L 0xFC /**< load all the LEDn_OFF registers, low */
#define PCA9685_ALLLED_OFF_H 0xFD /**< load all the LEDn_OFF registers,high */
#define PCA9685_PRESCALE 0xFE     /**< Prescaler for PWM output frequency */
#define PCA9685_TESTMODE 0xFF     /**< defines the test mode to be entered */

// MODE1 bits
#define MODE1_ALLCAL 0x01  /**< respond to LED All Call I2C-bus address */
#define MODE1_SUB3 0x02    /**< respond to I2C-bus subaddress 3 */
#define MODE1_SUB2 0x04    /**< respond to I2C-bus subaddress 2 */
#define MODE1_SUB1 0x08    /**< respond to I2C-bus subaddress 1 */
#define MODE1_SLEEP 0x10   /**< Low power mode. Oscillator off */
#define MODE1_AI 0x20      /**< Auto-Increment enabled */
#define MODE1_EXTCLK 0x40  /**< Use EXTCLK pin clock */
#define MODE1_RESTART 0x80 /**< Restart enabled */
// MODE2 bits
#define MODE2_OUTNE_0 0x01 /**< Active LOW output enable input */
#define MODE2_OUTNE_1                                                          \
  0x02 /**< Active LOW output enable input - high impedience */
#define MODE2_OUTDRV 0x04 /**< totem pole structure vs open-drain */
#define MODE2_OCH 0x08    /**< Outputs change on ACK vs STOP */
#define MODE2_INVRT 0x10  /**< Output logic state inverted */

#define PCA9685_I2C_ADDRESS 0x40      /**< Default PCA9685 I2C Slave Address */
#define FREQUENCY_OSCILLATOR 25000000 /**< Int. osc. frequency in datasheet */

#define PCA9685_PRESCALE_MIN 3   /**< minimum prescale value */
#define PCA9685_PRESCALE_MAX 255 /**< maximum prescale value */

const int black[3]  = {0,0,0};
const int white[3]  = {255,255,255};
const int green[3]  = {0,255,0};
const int cyan[3] = {0,100,255};
const int blue[3]   = {0,0,255};
const int purple[3]   = {150,0,255};
const int magenta[3] = {255,0,255};
const int red[3]    = {255,0,0};
const int orange[3] = {255,20,0};
const int yellow[3] = {150,255,0};




/*!
 *  @brief  Class that stores state and functions for interacting with PCA9685
 * PWM chip
 */
class RGBDriver {
public:
  RGBDriver(const uint8_t addr);
  void begin();
  void setPWMFreq(float freq);
  uint8_t getPWM(uint8_t num);
  void off(int c);
  void fadereset(int c);
  void rgb(int c,uint8_t r,uint8_t g,uint8_t b);
  void color(int c, int color[3]);
  void allrgb(uint8_t r,uint8_t g,uint8_t b,int d);
  void allcolor(int color[3],int d);
  void allrgb(uint8_t r,uint8_t g,uint8_t b);
  void allcolor(int color[3]);
  void chan(int c, int value);
  void clear(int d);
  void clear();
  void crossfadeCOLOR(int c,int color[3]);
  void crossfadeBUTTON(int c,int color[3]);
  void crossfadeRGB(int c,uint8_t r,uint8_t g,uint8_t b);
  int complete[5] = {false,false,false,false,false};



private:
  void setOscillatorFrequency(uint32_t freq);
  void setPWM(uint8_t num, uint16_t on, uint16_t off);
  void reset();
  uint8_t _i2caddr;
  TwoWire *_i2c;
  void setOutputMode(bool totempole);

  int calculateVal(int step, int val, int i);
  int calculateStep(int prevValue, int endValue);

  uint32_t _oscillator_freq;
  uint8_t read8(uint8_t addr);
  void write8(uint8_t addr, uint8_t d);

  int r = 0;
  int g = 0;
  int b = 0;
  int c = 0;
  int R = 0;
  int G = 0;
  int B = 0;
  int i = 0;
  int prevR[5] = {};
  int prevG[5] = {};
  int prevB[5] = {};
  int redVal[5] = {};
  int grnVal[5] = {}; 
  int bluVal[5] = {};
  int stepR;
  int stepG; 
  int stepB;
};

#endif


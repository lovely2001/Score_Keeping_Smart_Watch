//TRANSMITTER

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // OLED display width,  in pixels
#define SCREEN_HEIGHT 32 // OLED display height, in pixels

// declare an SSD1306 display object connected to I2C
Adafruit_SSD1306 oled(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>

RF24 radio(8, 9); //CE, CSN
const byte address[6] = "00001"; //Byte of array representing the address.
//This is the address where we will send the data. This should be same on the receiving side.

// constants won't change. They're used here to set pin numbers:
const int inc = 6;  // the number of the pushbutton pin
const int rst = 5;  // the number of the pushbutton pin
const int dec = 4;  // the number of the pushbutton pin

// variables will change:
uint8_t incButtonState;
uint8_t rstButtonState;
uint8_t decButtonState;

void setup()
{
  Serial.begin(9600);
  radio.begin(); //Starting the Wireless communication
  radio.openWritingPipe(address); //Setting the address where we will send the data
  radio.setPALevel(RF24_PA_MAX); //You can set it as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.stopListening(); //This sets the module as transmitter

  // the pull-up input pin will be HIGH when the switch is open and LOW when the switch is closed.
  pinMode(inc, INPUT_PULLUP);
  pinMode(rst, INPUT_PULLUP);
  pinMode(dec, INPUT_PULLUP);
}

uint8_t state;

void loop()
{

  // initialize OLED display with address 0x3C for 128x32
  if (!oled.begin(SSD1306_SWITCHCAPVCC, 0x3C)) {
    Serial.println(F("SSD1306 allocation failed"));
    while (true);
  }

  delay(1000);         // wait for initializing
  oled.clearDisplay(); // clear display

  oled.setTextSize(1);          // text size
  oled.setTextColor(WHITE);     // text color
  oled.setCursor(0, 16);        // position to display
  oled.print("SCORE CONTROL WATCH"); // text to display
  oled.display();               // show on OLED

  //Read the state of the pushbutton value:
  incButtonState = digitalRead(inc);
  rstButtonState = digitalRead(rst);
  decButtonState = digitalRead(dec);

  if (incButtonState == LOW)
  {
    state = 1;
    radio.write(&state, sizeof(state));
    Serial.println("Increment");
    delay(1000);
  }

  if (rstButtonState == LOW)
  {
    state = 2;
    radio.write(&state, sizeof(state));
    Serial.println("Reset");
    delay(1000);
  }

  if (decButtonState == LOW)
  {
    state = 3;
    radio.write(&state, sizeof(state));
    Serial.println("Decrement");
    delay(1000);
  }
}

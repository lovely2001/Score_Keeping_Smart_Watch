//RECEIVER

#include <SPI.h>
#include <nRF24L01.h>
#include <RF24.h>
#include <LedControl.h>

// the number at which LED pin is connected
//const int LED_1 =  PC10;
//const int LED_2 =  PC11;
//const int LED_3 =  PC12;


int DIN = 2;
int CS =  3;
int CLK = 4;

RF24 radio(8, 9); // (CE, CSN)
const byte address[6] = "00001";  //Byte of array representing the address.
//This is the address where we will send the data. This should be same on the receiving side.

// variables will change:
uint8_t recState = 0;

byte zero[8] = {0x00, 0xEE, 0xAA, 0xAA, 0xAA, 0xAA, 0xAA, 0xEE};
byte one[8] = {0x00, 0xE4, 0xAC, 0xA4, 0xA4, 0xA4, 0xA4, 0xEE};
byte two[8] = {0x00, 0xEE, 0xA2, 0xA2, 0xAE, 0xA8, 0xA8, 0xEE};
byte three[8] = {0x00, 0xEE, 0xA2, 0xA2, 0xAE, 0xA2, 0xA2, 0xEE};
byte four[8] = {0x00, 0xE2, 0xA6, 0xAA, 0xAF, 0xA2, 0xA2, 0xE2};
byte five[8] = {0x00, 0xEE, 0xA8, 0xA8, 0xAE, 0xA2, 0xA2, 0xEE};
byte six[8] = {0x00, 0xEE, 0xA8, 0xA8, 0xAE, 0xAA, 0xAA, 0xEE};
byte seven[8] = {0x00, 0xEE, 0xA2, 0xA2, 0xA2, 0xA2, 0xA2, 0xE2};
byte eight[8] = {0x00, 0xEE, 0xAA, 0xAA, 0xAE, 0xAA, 0xAA, 0xEE};
byte nine[8] = {0x00, 0xEE, 0xAA, 0xAA, 0xAE, 0xA2, 0xA2, 0xEE};
byte ten[8] = {0x00, 0x4E, 0xCA, 0x4A, 0x4A, 0x4A, 0x4A, 0xEE};
byte eleven[8] = {0x00, 0x44, 0xCC, 0x44, 0x44, 0x44, 0x44, 0xEE};
byte twelve[8] = {0x00, 0x4E, 0xC2, 0x42, 0x4E, 0x48, 0x48, 0xEE};
byte thirteen[8] = {0x00, 0x4E, 0xC2, 0x42, 0x4E, 0x42, 0x42, 0xEE};
byte fourteen[8] = {0x00, 0x42, 0xC6, 0x4A, 0x4F, 0x42, 0x42, 0xE2};
byte fifteen[8] = {0x00, 0x4E, 0xC8, 0x48, 0x4E, 0x42, 0x42, 0xEE};
byte sixteen[8] = {0x00, 0x4E, 0xC8, 0x48, 0x4E, 0x4A, 0x4A, 0xEE};
byte seventeen[8] = {0x00, 0x4E, 0xC2, 0x42, 0x42, 0x42, 0x42, 0xE2};
byte eighteen[8] = {0x00, 0x4E, 0xCA, 0x4A, 0x4E, 0x4A, 0x4A, 0xEE};
byte nineteen[8] = {0x00, 0x4E, 0xCA, 0x4A, 0x4E, 0x42, 0x42, 0xEE};
byte twenty[8] = {0x00, 0xEE, 0x2A, 0x2A, 0xEA, 0x8A, 0x8A, 0xEE};
byte twentyone[8] = {0x00, 0xE4, 0x2C, 0x24, 0xE4, 0x84, 0x84, 0xEE};

LedControl lc = LedControl(DIN, CLK, CS, 0);

void setup()
{

  lc.shutdown(0, false);      //The MAX72XX is in power-saving mode on startup
  lc.setIntensity(0, 1);     // Set the brightness to maximum value i.e 15
  lc.clearDisplay(0);         // and clear the display
  pinMode(DIN, OUTPUT);

  // initialize the LED pin as an output:
  //  pinMode(LED_1, OUTPUT);
  //  pinMode(LED_2, OUTPUT);
  //  pinMode(LED_3, OUTPUT);

  Serial.begin(9600);
  radio.begin();
  radio.openReadingPipe(0, address); //Setting the address at which we will receive the data same as on transmitter side.
  radio.setPALevel(RF24_PA_MAX); //You can set this as minimum or maximum depending on the distance between the transmitter and receiver.
  radio.startListening(); //This sets the module as receiver
  printByte(zero);
}


int count = 0;
void loop()
{
  if (radio.available()) //Looking for the data.
  {
    //Reading the data
    radio.read(&recState, sizeof(recState));
    Serial.println(recState);

    if (recState == 1 )
    {
      count = count + 1;
      printDigits();
      //   digitalWrite(LED_1, HIGH);
      Serial.println("INC");
    }

    if (recState == 2 ) {
      printByte(zero);
      count = 0;
      // digitalWrite(LED_2, HIGH);
      Serial.println("RST");
    }

    if (recState == 3 ) {
      count = count - 1;
      printDigits();
      //   digitalWrite(LED_3, HIGH);
      Serial.println("DEC");
    }
  }

  if (count == 22) {
    count = 0;
  }
}

void printDigits() {

  switch (count) {

    case 1:
      printByte(one);
      delay(100);
      break;

    case 2:
      printByte(two);
      delay(100);
      break;

    case 3:
      printByte(three);
      delay(100);
      break;

    case 4:
      printByte(four);
      delay(100);
      break;

    case 5:
      printByte(five);
      delay(100);
      break;

    case 6:
      printByte(six);
      delay(100);
      break;

    case 7:
      printByte(seven);
      delay(100);
      break;

    case 8:
      printByte(eight);
      delay(100);
      break;

    case 9:
      printByte(nine);
      delay(100);
      break;

    case 10:
      printByte(ten);
      delay(100);
      break;

    case 11:
      printByte(eleven);
      delay(100);
      break;

    case 12:
      printByte(twelve);
      delay(100);
      break;

    case 13:
      printByte(thirteen);
      delay(100);
      break;

    case 14:
      printByte(fourteen);
      delay(100);
      break;

    case 15:
      printByte(fifteen);
      delay(100);
      break;

    case 16:
      printByte(sixteen);
      delay(100);
      break;

    case 17:
      printByte(seventeen);
      delay(100);
      break;

    case 18:
      printByte(eighteen);
      delay(100);
      break;

    case 19:
      printByte(nineteen);
      delay(100);
      break;

    case 20:
      printByte(twenty);
      delay(100);
      break;

    case 21:
      printByte(twentyone);
      delay(100);
      break;

    default:
      printByte(zero);
      break;
  }

}

void printByte(byte character [])

{

  int i = 0;

  for (i = 0; i < 8; i++)

  {

    lc.setRow(0, i, character[i]);

  }

}

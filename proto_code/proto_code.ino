/***************************************************
  This is a library for the Adafruit 1.8" SPI display.

This library works with the Adafruit 1.8" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/358
The 1.8" TFT shield
  ----> https://www.adafruit.com/product/802
The 1.44" TFT breakout
  ----> https://www.adafruit.com/product/2088
as well as Adafruit raw 1.8" TFT display
  ----> http://www.adafruit.com/products/618

  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include <Adafruit_GFX.h>    // Core graphics library
#include <Adafruit_ST7735.h> // Hardware-specific library
#include <SPI.h>
#include <SD.h>
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"
#include <WiFi101.h>
char ssid[] = "CarinaWiFi";
char pass[] = "testtest";
int status = WL_IDLE_STATUS;
#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883
#define AIO_USERNAME    "caycay"
#define AIO_KEY         "80009f64496041f79d5f440181eeb727"
WiFiClient client;
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);
#define halt(s) { Serial.println(F( s )); while(1);  }
Adafruit_MQTT_Publish meetuser = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME "/feeds/meetuser");
Adafruit_MQTT_Subscribe interest = Adafruit_MQTT_Subscribe(&mqtt, AIO_USERNAME "/feeds/interest");
#define TFT_CS     6
#define TFT_RST    10
#define TFT_DC     9
#define SD_CS    11
const int detailButtonPin = A1;     // the number of the pushbutton pin
const int modeButtonPin = 13;     // the number of the pushbutton pin
int mode = 0;
int count = 0;
int countBusiness = 0;
int countProto = 0;
int buttonState = 0;
int modebuttonState = 0;             // the current reading from the input pin
int lastButtonState = LOW;   // the previous reading from the input pin

Adafruit_ST7735 tft = Adafruit_ST7735(TFT_CS, TFT_DC, TFT_RST);

void setup(void) {
//  WiFi.setPins(12,5,13);
  while (!Serial);
  Serial.begin(115200);
  Serial.println(F("Welcome to your Smart Name Tag!"));
  Serial.print(F("\nInit the WiFi module..."));
//  if (WiFi.status() == WL_NO_SHIELD) {
//    Serial.println("WINC1500 not present");
//    while (true);
//  }
  Serial.println("ATWINC OK!");
  Serial.print("Initializing SD card...");
  if (!SD.begin(SD_CS)) {
    Serial.println("failed!");
    return;
  }
  mqtt.subscribe(&interest);
  uint32_t x=0;
  pinMode(modeButtonPin, INPUT);
  pinMode(detailButtonPin, INPUT);

  // Use this initializer if you're using a 1.8" TFT
  tft.initR(INITR_BLACKTAB);
  
  Serial.print("Initializing SD card...");
  
  Serial.println("OK!");
  tft.setRotation(tft.getRotation()+1);
  bmpDraw("social.bmp", 0, 0);
}

uint8_t txFailures = 0;  // Count of how many publish failures have occured in a row.

void loop() {
//  MQTT_connect();
//  Adafruit_MQTT_Subscribe *subscription;
//  while ((subscription = mqtt.readSubscription(3000))) {
//    if (subscription == &interest) {
//      Serial.println("let's display common interest!");
//    }
//    if (subscription == &locationRequest) {
//      Serial.println("oh never mind, works!");
//    }
//  }
  buttonState = digitalRead(detailButtonPin);
  int reading = digitalRead(modeButtonPin);

 if (reading == HIGH && lastButtonState == LOW) {
  Serial.println("mode button pressed");
  mode += 1;
  if (mode == 2) {
    mode = 0;
  }
  if (mode == 0) {
     bmpDraw("social.bmp", 0, 0);
  }
  if (mode == 1) {
     bmpDraw("business.bmp", 0, 0);
  }
  lastButtonState = HIGH;
  }
  if (reading == LOW) {
    lastButtonState = LOW;
  }

  if (mode == 0 && buttonState == HIGH) { //social mode
    Serial.println("detail button pressed");
    Serial.println(count);
    if (count == 3) {
      count = 0;
    }
    if (count == 0) {
      bmpDraw("carina.bmp", 0, 0); 
    }
    if (count == 1) {
      bmpDraw("venmo.bmp", 0,0);
    }
    if (count == 2) {
      bmpDraw("wechat.bmp", 0,0);
    }
    count += 1;
  }
  if (mode == 1 && buttonState == HIGH) { //business mode
    Serial.println("we are in business mode right now");

    if (countBusiness == 4) {
      countBusiness = 0;
    }
    if (countBusiness == 0) {
      bmpDraw("sally.bmp", 0, 0);
    }
    if (countBusiness == 1) {
      bmpDraw("recr.bmp", 0, 0);
    }
    if (countBusiness == 2) {
      bmpDraw("facebook.bmp", 0, 0);
    }
    if (countBusiness == 3) {
      bmpDraw("elon.bmp", 0, 0);
    }
    countBusiness += 1;
  }
  
  if (mode == 2 && buttonState == HIGH) { //proto mode
    Serial.println("we are in proto mode right now");

    if (countProto == 5) {
      countProto = 0;
    }
    if (countProto == 0) {
      bmpDraw("anxiety.bmp", 0, 0);
    }
    if (countProto == 1) {
      bmpDraw("designer.bmp", 0, 0);
    }
    if (countProto == 2) {
      bmpDraw("drinks.bmp", 0, 0);
    }
    if (countProto == 3) {
      bmpDraw("jacobs.bmp", 0, 0);
    }
    if (countProto == 4) {
      bmpDraw("ndist.bmp", 0, 0);
    }
    if (countProto == 4) {
      bmpDraw("bad.bmp", 0, 0);
    }
    countProto += 1;
  }
  
}

// This function opens a Windows Bitmap (BMP) file and
// displays it at the given coordinates.  It's sped up
// by reading many pixels worth of data at a time
// (rather than pixel by pixel).  Increasing the buffer
// size takes more of the Arduino's precious RAM but
// makes loading a little faster.  20 pixels seems a
// good balance.

#define BUFFPIXEL 20

void bmpDraw(char *filename, uint8_t x, uint8_t y) {

  File     bmpFile;
  int      bmpWidth, bmpHeight;   // W+H in pixels
  uint8_t  bmpDepth;              // Bit depth (currently must be 24)
  uint32_t bmpImageoffset;        // Start of image data in file
  uint32_t rowSize;               // Not always = bmpWidth; may have padding
  uint8_t  sdbuffer[3*BUFFPIXEL]; // pixel buffer (R+G+B per pixel)
  uint8_t  buffidx = sizeof(sdbuffer); // Current position in sdbuffer
  boolean  goodBmp = false;       // Set to true on valid header parse
  boolean  flip    = true;        // BMP is stored bottom-to-top
  int      w, h, row, col;
  uint8_t  r, g, b;
  uint32_t pos = 0, startTime = millis();

  if((x >= tft.width()) || (y >= tft.height())) return;

  Serial.println();
  Serial.print("Loading image '");
  Serial.print(filename);
  Serial.println('\'');

  // Open requested file on SD card
  if ((bmpFile = SD.open(filename)) == NULL) {
    Serial.print("File not found");
    return;
  }

  // Parse BMP header
  if(read16(bmpFile) == 0x4D42) { // BMP signature
    Serial.print("File size: "); Serial.println(read32(bmpFile));
    (void)read32(bmpFile); // Read & ignore creator bytes
    bmpImageoffset = read32(bmpFile); // Start of image data
    Serial.print("Image Offset: "); Serial.println(bmpImageoffset, DEC);
    // Read DIB header
    Serial.print("Header size: "); Serial.println(read32(bmpFile));
    bmpWidth  = read32(bmpFile);
    bmpHeight = read32(bmpFile);
    if(read16(bmpFile) == 1) { // # planes -- must be '1'
      bmpDepth = read16(bmpFile); // bits per pixel
      Serial.print("Bit Depth: "); Serial.println(bmpDepth);
      if((bmpDepth == 24) && (read32(bmpFile) == 0)) { // 0 = uncompressed

        goodBmp = true; // Supported BMP format -- proceed!
        Serial.print("Image size: ");
        Serial.print(bmpWidth);
        Serial.print('x');
        Serial.println(bmpHeight);

        // BMP rows are padded (if needed) to 4-byte boundary
        rowSize = (bmpWidth * 3 + 3) & ~3;

        // If bmpHeight is negative, image is in top-down order.
        // This is not canon but has been observed in the wild.
        if(bmpHeight < 0) {
          bmpHeight = -bmpHeight;
          flip      = false;
        }

        // Crop area to be loaded
        w = bmpWidth;
        h = bmpHeight;
        if((x+w-1) >= tft.width())  w = tft.width()  - x;
        if((y+h-1) >= tft.height()) h = tft.height() - y;

        // Set TFT address window to clipped image bounds
        tft.setAddrWindow(x, y, x+w-1, y+h-1);

        for (row=0; row<h; row++) { // For each scanline...

          // Seek to start of scan line.  It might seem labor-
          // intensive to be doing this on every line, but this
          // method covers a lot of gritty details like cropping
          // and scanline padding.  Also, the seek only takes
          // place if the file position actually needs to change
          // (avoids a lot of cluster math in SD library).
          if(flip) // Bitmap is stored bottom-to-top order (normal BMP)
            pos = bmpImageoffset + (bmpHeight - 1 - row) * rowSize;
          else     // Bitmap is stored top-to-bottom
            pos = bmpImageoffset + row * rowSize;
          if(bmpFile.position() != pos) { // Need seek?
            bmpFile.seek(pos);
            buffidx = sizeof(sdbuffer); // Force buffer reload
          }

          for (col=0; col<w; col++) { // For each pixel...
            // Time to read more pixel data?
            if (buffidx >= sizeof(sdbuffer)) { // Indeed
              bmpFile.read(sdbuffer, sizeof(sdbuffer));
              buffidx = 0; // Set index to beginning
            }

            // Convert pixel from BMP to TFT format, push to display
            b = sdbuffer[buffidx++];
            g = sdbuffer[buffidx++];
            r = sdbuffer[buffidx++];
            tft.pushColor(tft.Color565(r,g,b));
          } // end pixel
        } // end scanline
        Serial.print("Loaded in ");
        Serial.print(millis() - startTime);
        Serial.println(" ms");
      } // end goodBmp
    }
  }

  bmpFile.close();
  if(!goodBmp) Serial.println("BMP format not recognized.");
}

// These read 16- and 32-bit types from the SD card file.
// BMP data is stored little-endian, Arduino is little-endian too.
// May need to reverse subscript order if porting elsewhere.

uint16_t read16(File f) {
  uint16_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read(); // MSB
  return result;
}

uint32_t read32(File f) {
  uint32_t result;
  ((uint8_t *)&result)[0] = f.read(); // LSB
  ((uint8_t *)&result)[1] = f.read();
  ((uint8_t *)&result)[2] = f.read();
  ((uint8_t *)&result)[3] = f.read(); // MSB
  return result;
}


void MQTT_connect() {
  int8_t ret;
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    status = WiFi.begin(ssid, pass);
    uint8_t timeout = 10;
    while (timeout && (WiFi.status() != WL_CONNECTED)) {
      timeout--;
      delay(1000);
    }
  }
  if (mqtt.connected()) {
    return;
  }
  Serial.print("Connecting to MQTT... ");
  while ((ret = mqtt.connect()) != 0) {
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);
  }
  Serial.println("MQTT Connected!");
}


void tftPrintTest() {
  tft.setTextWrap(true);
  tft.fillScreen(ST7735_BLACK);
  tft.setCursor(10, 40);
  tft.setTextColor(ST7735_BLUE);
  tft.setTextSize(4.5);
  tft.println("Carina");
}

void logMetUser(uint32_t number, Adafruit_MQTT_Publish& publishFeed) {

  // Publish
  Serial.print(F("Publishing that I met someone: "));
  if (!publishFeed.publish(number)) {
    Serial.println(F("Publish failed!"));
    txFailures++;
  }
  else {
    Serial.println(F("Publish succeeded!"));
    txFailures = 0;
  }
}

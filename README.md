# Introduction
This project implements a darts scoring system using an ESP32 development board with a 2.4" TFT touch display (CYD - Cheap Yellow Display). The system uses the TFT_eSPI library for display handling and TFT_eTouch for touch input processing. The hardware setup includes a 320x240 ILI9341 display with touch capabilities, making it perfect for interactive dart score tracking.

![Display Image](darts.png)


# Hardware
https://www.amazon.de/dp/B0CQK88RBD?psc=1&ref=ppx_yo2ov_dt_b_product_details

# Arduino IDE
* Board: ESP32 Dev Module
* Upload Speed: 460800

# Setup
* Installed TFT_eSPI (2.5.43)
* Copied https://github.com/achillhasler/TFT_eTouch files into project dir
* I had to change the content of the ```User_Setup.h``` file in the ```TFT_eSPI``` library folder to make the display work.
/Users/<user name>/Documents/Arduino/libraries/TFT_eSPI/User_Setup.h

Thanks to https://cool-web.de/esp8266-esp32/esp32-2432s028-cheap-yellow-display-touchscreen-programmierung-platformio-library-tft-espi.htm for the setup info.

```cpp
#define USER_SETUP_INFO "User_Setup"

#define ILI9341_2_DRIVER     

#define TFT_MISO  12
#define TFT_MOSI  13
#define TFT_SCLK  14
#define TFT_CS    15
#define TFT_DC    2 
#define TFT_RST   -1

#define TFT_BL    21
#define TFT_BACKLIGHT_ON HIGH 

//#define TOUCH_CS  33     

#define LOAD_GLCD   // Font 1. Original Adafruit 8 pixel font needs ~1820 bytes in FLASH
#define LOAD_FONT2  // Font 2. Small 16 pixel high font, needs ~3534 bytes in FLASH, 96 characters
#define LOAD_FONT4  // Font 4. Medium 26 pixel high font, needs ~5848 bytes in FLASH, 96 characters
#define LOAD_FONT6  // Font 6. Large 48 pixel font, needs ~2666 bytes in FLASH, only characters 1234567890:-.apm
#define LOAD_FONT7  // Font 7. 7 segment 48 pixel font, needs ~2438 bytes in FLASH, only characters 1234567890:-.
#define LOAD_FONT8  // Font 8. Large 75 pixel font needs ~3256 bytes in FLASH, only characters 1234567890:-.
#define LOAD_GFXFF  // FreeFonts. Include access to the 48 Adafruit_GFX free fonts FF1 to FF48 and custom fonts

#define SMOOTH_FONT


#define SPI_FREQUENCY  27000000
#define SPI_READ_FREQUENCY  20000000
#define SPI_TOUCH_FREQUENCY  2500000
```


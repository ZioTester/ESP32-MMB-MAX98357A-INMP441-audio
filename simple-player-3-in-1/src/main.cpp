////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
//////
////// Info, guides and tutorials on:
////// https://ziotester.github.io
//////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
////////////////////////////////////////////////////////
#include "Arduino.h"
#include "Audio.h"

#ifdef STREAMING_EXAMPLE
  #include "WiFi.h"
#endif
#ifdef SPIFFS_EXAMPLE
  #include <SPIFFS.h>
#endif
#ifdef SDCARD_EXAMPLE
  #include "SD.h"
#endif

Audio audio;
SPIClass spiSD(VSPI);

void setup() {
  Serial.begin(115200);
  audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
  audio.setVolume(VOLUME);

  /*

  streaming

  */
  #ifdef STREAMING_EXAMPLE
    String ssid = SID;
    String password = PASSWORD;
    Serial.print("Connecting");
    WiFi.disconnect();
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid.c_str(), password.c_str());
    while (WiFi.status() != WL_CONNECTED) {
      Serial.print(".");
      delay(500);
    }
    Serial.println();
    Serial.println("Connected!");
    Serial.print("Playing streaming from: ");
    Serial.println(STREAMING_URL);
    audio.connecttohost(STREAMING_URL);
  #endif

  /*

  file MP3 on SPIFFS

  */
  #ifdef SPIFFS_EXAMPLE
   if (!SPIFFS.begin()) {
     Serial.println("File system Failed");
     for (;;) {
     }
   } else {
     Serial.println("File system Successful");
   }
   Serial.print("Playing mp3 form SPIFFS: ");
   Serial.println(MP3_FILE);
   audio.connecttoFS(SPIFFS, MP3_FILE);   
  #endif

  /*

  file MP3 on SD card

 */
  #ifdef SDCARD_EXAMPLE
    spiSD.begin(SD_CLK, SD_MISO, SD_MOSI, SD_CS);
    if(!SD.begin(SD_CS, spiSD)){
      Serial.println("File system Failed");
      for (;;) {
      }
    } else {
      Serial.println("File system Successful");
    }
    Serial.print("Playing mp3 form SD Card: ");
    Serial.println(MP3_FILE);
    audio.connecttoFS(SD, MP3_FILE);
  #endif
  

  // audio.connecttospeech("Hello my freind!", "en");
}
void loop() { audio.loop(); }
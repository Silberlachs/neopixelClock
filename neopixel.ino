#include <Adafruit_NeoPixel.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

const char *ssid =  "AP_NAME";                    
const char *pass =  "AP_PASS";    

Adafruit_NeoPixel pixels(24, 12, NEO_GRB + NEO_KHZ800);

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 3600);
double hourTime = 0;
double minuteTime = 0;
double secondTime = 0;

void setup() {
    
    pixels.begin();
    pixels.clear();
    
    WiFi.begin(ssid, pass); 
    int pixNum_init = 0;
    
    while (WiFi.status() != WL_CONNECTED || pixNum_init < 24) 
    {
        pixels.setPixelColor(pixNum_init++, pixels.Color(0, 0, 255));
        pixels.show();
        delay(300);
    }

    if(WiFi.status() != WL_CONNECTED)
    {
      setAllPixelsTo(255,0,0);
      for(;;){delay(100000);}   //ERROR STATE: NO WIFI CONNECTION
    }

    //########################### OKAY STATE SHOW  ###########################
    delay(300);
    setAllPixelsTo(0,0,0);
    delay(300);
    setAllPixelsTo(0,255,0);
    delay(300);
    setAllPixelsTo(0,0,0);
    delay(300);
    setAllPixelsTo(0,255,0);
    delay(300);
    setAllPixelsTo(0,0,0);
    delay(300);
    setAllPixelsTo(0,255,0);
    delay(300);
    setAllPixelsTo(0,0,0);
    //########################################################################
    timeClient.begin();
    timeClient.update();
}

void setAllPixelsTo(int red, int green, int blue)
{
    for(int i=0; i<24; i++) 
    { 
        pixels.setPixelColor(i, pixels.Color(red, green, blue));
    }
    pixels.show();  
}

void loop() {

        timeClient.update();

        secondTime = timeClient.getSeconds();
        minuteTime = timeClient.getMinutes();
        hourTime = timeClient.getHours() +1; //cet +1 kekw
        if(hourTime > 24) hourTime = 24;

        if(secondTime == 0)
          setAllPixelsTo(0,0,0);

        int secondPixColor = 0;
        secondPixColor = secondTime / 5 *2;

        int minutePixVal = 0;
        minutePixVal = minuteTime / 5 *2;

       int hourPixVal = 0;
       if(hourTime<12)
          hourPixVal = hourTime*2;
       else
          hourPixVal = (hourTime -12) *2;

        if(minuteTime >= 30)
          hourPixVal++;

        pixels.setPixelColor(secondPixColor, pixels.Color(0,10,10));
        pixels.setPixelColor(minutePixVal, pixels.Color(25,25,0));
        pixels.setPixelColor(hourPixVal , pixels.Color(50, 0, 0));
        pixels.show();
}

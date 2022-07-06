#define TINY_GSM_MODEM_SIM800 //Tells program the type of GSM module we're using

#define SerialMon Serial //Renames Serial SerialMon
#include <SoftwareSerial.h> //Brings in library for software serial
SoftwareSerial SerialAT(10,11); // Tx and Rx of SIM800l connected to 10(RX), TX

#define DUMP_AT_COMMANDS //to dump the AT commands
#define TINY_GSM_DEBUG SerialMon

#define SMS_TARGET  "+2349079809103" //The number to send SMS to
#define CALL_TARGET "+2348104342470" //The number to call

#include <TinyGsmClient.h> //to include the library.
#ifdef DUMP_AT_COMMANDS
#include <StreamDebugger.h> //debug codes that concern the gsm module
StreamDebugger debugger(SerialAT, SerialMon); //object of streamdebugger
TinyGsm modem(debugger);
#else
TinyGsm modem(SerialAT); //AT is for the gsm module
#endif

uint8_t index;
bool error;

char* charLocation;
String text;
String location;



void setup() 
{
  SerialAT.begin(9600);
  SerialMon.begin(115200);
 // pinMode(8,INPUT_PULLUP);
}

void loop() 
{
  
    //getLocation();
    sendSMS();
    //call();
  
}

void sendSMS()
{
  #if defined(SMS_TARGET)  
  // This is only supported on SIMxxx series
  boolean res11 = modem.sendSMS_UTF16(SMS_TARGET, u"EMERGENCY! Your ward is in danger. Click this link to find his/her location: https://www.google.com/maps/place/6.54179,3.39287", 127);
  #endif 
  
}

void call()
{
  boolean res1 = modem.callNumber(CALL_TARGET);
  
  if (res1) 
  {
    delay(1000L); 
    // Play DTMF A, duration 1000ms
    modem.dtmfSend('A', 1000); //dualtonemodulationfrequency.

    // Play DTMF 0...4, default duration (100ms)
    for (char tone='0'; tone<='4'; tone++) 
    {
      modem.dtmfSend(tone);
    }
    
    //delay(30000);
    delay(9000);
    res1 = modem.callHangup();
  }  
}

void getLocation()
{
  
} 

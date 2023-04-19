//NodeMCU-32S
///LIBRARIES
//EEPROM LIBRARY
#include <EEPROM.h>
//ESP BLEUTOUTH LIBRARY
#include "BluetoothSerial.h"
BluetoothSerial SerialBT;
//***uRTC LIBRARIES
#include "Arduino.h"
#include "uRTCLib.h"
//***uRTC LIBRARIES finish
//***DFplayer LIBRARIES
#include "DFRobotDFPlayerMini.h"
//SoftwareSerial mySoftwareSerial(16, 17); // RX, TX
//AltSoftSerial mySoftwareSerial(16, 17); // RX, TX
HardwareSerial mySoftwareSerial(1);
DFRobotDFPlayerMini myDFPlayer;
#define RX_PIN 16  // RX, TX ,esp32
#define TX_PIN 17
///SOUND VARIABLES
byte sound_volumeM=25;
/////
///LED STATING 
int LED=2;
int ledp=18;
int ledstate=LOW;
bool flag=false;
///
//df player delay and millis
//unsigned long previousMillis=0*60000*1;//Set starting point to the largest period
long dfplayer_on = 1000;   //3*60000*1;// setting on time for main pump (first mult is minutes)
long dfplayer_off =1000;  //0.5*60000*1;// setting off time for main pump
int df_p_state = 0;
/////
unsigned long previousMillis = 4 * 60000;  //Set starting point to the largest period
long irrigaation_on = 60000;               //
long azan_calling_on = 3.5 * 60000;

/////
//***DFplayer LIBRARIES finish
//*************time variables
uRTCLib rtc(0x68);
int rtc_years;
int rtc_month;
String rtc_date;
String dayof = "day";
String new_rtc_date;
String daynum;
int int_day_num;
int t_hours;
int t_minutes;
int c_t_hours;
int c_t_minutes;
int time_accuracy_up = 3;
int time_accuracy_d = 0;
////
int F_accuracy_up = 3;
int F_accuracy_d = 0;
int S_accuracy_up = 3;
int S_accuracy_d = 0;
int D_accuracy_up = 3;
int D_accuracy_d = 0;
int A_accuracy_up = 3;
int A_accuracy_d = 0;
int M_accuracy_up = 3;
int M_accuracy_d = 0;
int I_accuracy_up = 3;
int I_accuracy_d = 0;
////
int c_t_hours_eqp;
int c_t_minutes_up_eqp;
int c_t_minutes_bel_eqp;
///PRAYER EQUI BELOW
int F_minutes_bel_eqp;
int S_minutes_bel_eqp;
int D_minutes_bel_eqp;
int A_minutes_bel_eqp;
int M_minutes_bel_eqp;
int I_minutes_bel_eqp;
///
///PRAYER EQUI ABOVE
int F_minutes_up_eqp;
int S_minutes_up_eqp;
int D_minutes_up_eqp;
int A_minutes_up_eqp;
int M_minutes_up_eqp;
int I_minutes_up_eqp;
///
bool fajr_equil_point;
bool sunrise_equil_point;
bool zuhr_equil_point;
bool asr_equil_point;
bool maghrib_equil_point;
bool isha_equil_point;
//variables for time
unsigned long year;
unsigned long n_year;
double month;
double daegy;
///VARIABLES FOR PRAYER TIMES MINUTES AND HOURS
int fajr_hour;
int fajr_min;
int sunrise_hour;
int sunrise_min;
int zuhr_hour;
int zuhr_min;
int asr_hour;
int asr_min;
int maghrib_hour;
int maghrib_min;
int isha_hour;
int isha_min;
double fajr = 0, sunRise = 0, zuhr = 0, asr = 0, maghrib = 0, isha = 0;
///preparing monitoring data start
///************FAJR
String Fajr_praying, Sunrise_praying, Duhr_praying, Asr_praying, Maghrib_praying, Isha_praying;
String fajr_hour1_s, fajr_min1_s;
int fajr_h_length;
int fajr_m_length;
int fajr_p_length;
///************SUNRISE
String sunrise_hour1_s, sunrise_min1_s;
int sunrise_h_length;
int sunrise_m_length;
int sunrise_p_length;
///************DUHR
String duhr_hour1_s, duhr_min1_s;
int duhr_h_length;
int duhr_m_length;
int duhr_p_length;
///************ASR
String asr_hour1_s, asr_min1_s;
int asr_h_length;
int asr_m_length;
int asr_p_length;
///************MAGHRIB
String maghrib_hour1_s, maghrib_min1_s;
int maghrib_h_length;
int maghrib_m_length;
int maghrib_p_length;
///************ISHA
String isha_hour1_s, isha_min1_s;
int isha_h_length;
int isha_m_length;
int isha_p_length;
///preparing monitoring data finish
///bluetouth texting start
#define maxChar 32
char message[maxChar];  // stores the message
char Incoming_data;     // reads each character
byte posi = 0;          // defines the position into your array
int ii;
String bluetooth_pr_d, bluetooth_sv_d, bluetooth_rtc_d;
///bluetouth texting finish

//variables for calculations
double longitude = 0;
double latitude = 0;
double timeZone = 0;
double fajrTwilight = 0;
double ishaTwilight = 0;
////definitions for ouputs and inputs
#define led_pin 23
unsigned long led_previous_millis = 0;
long led_to_on = 1.5 * 60000;
long led_to_off = 1.5 * 60000;
int mobile_delay=25;
int serial_delay=25;
int led_state = 0;
///EEPROM VARIABLES START
//const char* texto = ""; //MAX 32
String texto_read = "";
String texto_read1 = "";
char rx_byte = 0;
String rx_str = "";
///EEPROM VARIABLES FINISH
void setup() {

  //*******************************URTC SETTINGS START
  delay(1000);
  Serial.begin(115200);
  Serial.println("Serial OK");

#ifdef ARDUINO_ARCH_ESP32
  URTCLIB_WIRE.begin(21, 22);  // D21 and D22 on ESP32
#else
  URTCLIB_WIRE.begin();
#endif
  //rtc.set(30,22, 17, 5, 5, 8,22);
  //  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
  //*********************************URTC SETTINGS FINISH
  //********************BLEUTOUTH SETTING STARTS
  //BluetoothSerial SerialBT;
  SerialBT.begin("Nida App.v4");  //Name of your Bluetooth interface -> will show up on your phone
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif

  // Parameters for Bluetooth interface
  //********************BLEUTOUTH SETTING FINISH

  //**********************DFPLAYER SETTING START
  mySoftwareSerial.begin(9600, SERIAL_8N1, RX_PIN, TX_PIN);  // speed, type, RX, TX
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(mySoftwareSerial)) {  //Use softwareSerial to communicate with mp3.

    Serial.println(myDFPlayer.readType(), HEX);
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true)
      ;
  }
  Serial.println(F("DFPlayer Mini online."));
  myDFPlayer.setTimeOut(500);  //Set serial communictaion time out 500ms
  //----Set volume----
  myDFPlayer.volume(15);    //Set volume value (0~30).
  myDFPlayer.volumeUp();    //Volume Up
  myDFPlayer.volumeDown();  //Volume Down
  //----Set different EQ----
  myDFPlayer.EQ(DFPLAYER_EQ_NORMAL);
  //----Set device we use SD as default----
  //  myDFPlayer.outputDevice(DFPLAYER_DEVICE_U_DISK);
  myDFPlayer.outputDevice(DFPLAYER_DEVICE_SD);
  int delayms = 100;
  //----Read imformation----
  Serial.println(F("readState--------------------"));
  Serial.println(myDFPlayer.readState());  //read mp3 state
  Serial.println(F("readVolume--------------------"));
  Serial.println(myDFPlayer.readVolume());  //read current volume
  //Serial.println(F("readEQ--------------------"));
  //Serial.println(myDFPlayer.readEQ()); //read EQ setting
  Serial.println(F("readFileCounts--------------------"));
  Serial.println(myDFPlayer.readFileCounts());  //read all file counts in SD card
  Serial.println(F("readCurrentFileNumber--------------------"));
  Serial.println(myDFPlayer.readCurrentFileNumber());  //read current play file number
  Serial.println(F("readFileCountsInFolder--------------------"));
  Serial.println(myDFPlayer.readFileCountsInFolder(3));  //read fill counts in folder SD:/03
  Serial.println(F("--------------------"));
  Serial.println(F("myDFPlayer.play(1)"));
  //myDFPlayer.play(1);  //Play the first mp3

  //**********************DFPLAYER SETTING FINISH
  ///OUTPUT INPUT SETTING
pinMode(LED,OUTPUT);
pinMode(ledp,INPUT_PULLUP);
}

void loop() {
  //bleutooth setting function
  //trials();
  //sound_volume_f();
  led_stating();
  Prayer_time_control();
  DataToMobileApp();
  bluetooth_setting();
}
///CODE FUNCTIONS***************************
//DS3231 FUNCTIONS START
///DS3231 Calibration function start
void rtc_calibration() {
  //rtc.set(30,22, 17, 5, 5, 8,22);
  //  RTCLib::set(byte second, byte minute, byte hour, byte dayOfWeek, byte dayOfMonth, byte month, byte year)
}
///DS3231 Calibration function finish
int years_function() {
  rtc.refresh();
  rtc_years = int((20 * 100) + (rtc.year() % 100));  //OBTAINING YEARS
  //rtc_years = (t.year);  //OBTAINING YEARS
  /*Serial.print("year is :");
  Serial.println(rtc_years);*/

  return rtc_years;
}
//function for month
int months_function() {
  rtc.refresh();
  rtc_month = int(rtc.month());  //OBTAINING MONTHS
  /*Serial.print("month of year is :");
  Serial.println(rtc_month);*/
  return rtc_month;
}
//function for day
int days_function() {
  rtc.refresh();
  /*rtc_date = (rtc.getDateStr());  //OBTAINING DATES
  new_rtc_date = dayof + rtc_date;
  daynum = new_rtc_date.substring(new_rtc_date.indexOf(dayof) + 3, new_rtc_date.indexOf("."));*/
  int_day_num = int(rtc.day());
  /*Serial.print("date is :");
  Serial.println(rtc_date);
  Serial.print("day of month is :");
  Serial.println(int_day_num);*/
  return int_day_num;
}
//function for hours
int hours_function() {
  rtc.refresh();
  t_hours = int(rtc.hour());
  Serial.print(t_hours);
  Serial.println(" hour(s), ");
  return t_hours;
}
//function for minutes
int minutes_function() {
  rtc.refresh();
  t_minutes = int(rtc.minute());
  Serial.print(t_minutes);
  Serial.println(" minute(s)");
  return t_minutes;
}
//DS3231 FUNCTIONS FINISH
///PRAYER TIME CALCULATION FUNCTION STARTS
//convert Degree to Radian
double degToRad(double degree) {
  return ((3.1415926 / 180) * degree);
}
//convert Radian to Degree
double radToDeg(double radian) {
  return (radian * (180 / 3.1415926));
}
//make sure a value is between 0 and 360
double moreLess360(double value) {
  while (value > 360 || value < 0) {
    if (value > 360)
      value -= 360;

    else if (value < 0)
      value += 360;
  }

  return value;
}

//make sure a value is between 0 and 24
double moreLess24(double value) {
  while (value > 24 || value < 0) {
    if (value > 24)
      value -= 24;

    else if (value < 0)
      value += 24;
  }

  return value;
}

//convert the double number to Hours and Minutes
void doubleToHrMin(double number, int &hours, int &minutes) {
  hours = floor(moreLess24(number));
  minutes = floor(moreLess24(number - hours) * 60);
}
///*************************BLUETOUTH FUNCTION START(GETTING SERIAL DATA)
///to call function for bluetooth setting
void bluetooth_setting() {
  //BluetoothSerial SerialBT;
  SerialBT.begin("Nida App.v4");  //Name of your Bluetooth interface -> will show up on your phone
#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
}
///*************************BLUETOUTH FUNCTION FINISH (GETTING SERIAL DATA)
///*************************BLUETOUTH with EEPROM FUNCTION START(GETTING SERIAL DATA)
String bluetooth_function() {
  if (SerialBT.available()) {
    for (ii = 0; ii < 32; ii++) {
      message[ii] = '\0';
    }
    posi = 0;
  }
  byte index = 0;                     //make the index equal to zerO
  while (SerialBT.available() > 0) {  // ¿Hay algún caracter?
                                      ///
    if (index < (maxChar)) {
      Incoming_data = SerialBT.read();  // Reads a character
      Serial.print("character value \n");
      Serial.println(Incoming_data);
      message[index] = Incoming_data;  // Stores the character in message array
      index++;                         // Increment position
      message[index] = '\0';           // Delete the last position
    }
    ////
    String bluetooth_data = message;
    Serial.print("NEW DATAaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa");
    Serial.println(bluetooth_data);
    ///
  String test_data_s1 = bluetooth_data.substring(bluetooth_data.indexOf("n") + 1, bluetooth_data.indexOf("m"));  //to be sure from start data come
  String test_data_f1 = bluetooth_data.substring(bluetooth_data.indexOf("f") + 1, bluetooth_data.indexOf("w"));  //to be sure from finish data come
  if (test_data_s1 == "z" && test_data_f1 == "h")
  {
    ///
    EEPROM_ESP32_WRITE(bluetooth_data, 0);  // Save in address 0...32
    Serial.print("texto Written to EEPROM: ");
    Serial.println(bluetooth_data);
    bluetooth_data = "";
    delayMicroseconds(100);
  }
  ///HERE WE CAN PUT OUR CHANGES 18.10.2022
  else
  {
   digitalWrite(LED, HIGH);
  }
  }
  texto_read = (String)EEPROM_ESP32_READ(0, 32);  // Read 0...32 address
  Serial.print("texto Read from EEPROM: ");
  Serial.println(texto_read);
  Serial.println(".....................");
  delay(100);
  return texto_read;
}

//// Function WRITE EEPROM
void EEPROM_ESP32_WRITE(String buffer, int N) {
  EEPROM.begin(512);
  delay(10);
  for (int L = 0; L < 32; ++L) {
    EEPROM.write(N + L, buffer[L]);
  }
  EEPROM.commit();
}

//// Function READ EEPROM
String EEPROM_ESP32_READ(int min, int max) {
  EEPROM.begin(512);
  delay(10);
  String buffer;
  for (int L = min; L < max; ++L)
    // if (isAlphaNumeric(EEPROM.read(L)))
    buffer += char(EEPROM.read(L));
  return buffer;
}
////01.09.2022


////
///*************************BLUETOUTH with EEPROM FUNCTION FINISH(GETTING SERIAL DATA)
/////*********************************************************CALCULATION OF TIME START
void calcPrayerTimes(double longitude, double latitude, double timeZone,
                     double fajrTwilight, double ishaTwilight,
                     double &fajrTime, double &sunRiseTime, double &zuhrTime,
                     double &asrTime, double &maghribTime, double &ishaTime) {
  //storing prepared collected string into new variable
  //retrieving data for EEPROM
  String data_to_use = bluetooth_function();
  //Incoming_data = "nzma34b36c43d23e32fhw" must be between these letters,numbers are variable and in can be changed; //Read what we receive
  //"a(long)b(lat)c(time_zone)d(fajr_inc)e(isha_inc)f"
  String test_data_s = data_to_use.substring(data_to_use.indexOf("n") + 1, data_to_use.indexOf("m"));  //to be sure from start data come
  String test_data_f = data_to_use.substring(data_to_use.indexOf("f") + 1, data_to_use.indexOf("w"));  //to be sure from finish data come
  if (test_data_s == "z" && test_data_f == "h") {
    Serial.println("data from bleutooth flowting start.....");
    ///coming data slicing start
    //"a(long)b(lat)c(time_zone)d(fajr_inc)e(isha_inc)f"
    //long start
    String longitude_s = data_to_use.substring(data_to_use.indexOf("a") + 1, data_to_use.indexOf("b"));  //obtain longitude string
    double longitude = longitude_s.toDouble();
    //long finish
    //latit start
    String latitude_s = data_to_use.substring(data_to_use.indexOf("b") + 1, data_to_use.indexOf("c"));  //obtain latitude string
    double latitude = latitude_s.toDouble();
    //latit finish
    //timezone start
    String timeZone_s = data_to_use.substring(data_to_use.indexOf("c") + 1, data_to_use.indexOf("d"));  //obtain timezone string
    double timeZone = timeZone_s.toDouble();
    //timezone finish
    //fajrTwilight start
    String fajrTwilight_s = data_to_use.substring(data_to_use.indexOf("d") + 1, data_to_use.indexOf("e"));  //obtain fajrTwilight string
    double fajrTwilight = fajrTwilight_s.toDouble();
    //fajrTwilight finish
    //ishaTwilight start
    String ishaTwilight_s = data_to_use.substring(data_to_use.indexOf("e") + 1, data_to_use.indexOf("f"));  //obtain ishaTwilight string
    double ishaTwilight = ishaTwilight_s.toDouble();
    //ishaTwilight finish

    ///coming data slicing finish
   /* Serial.println(data_to_use);
    Serial.println("data from bleutooth flowting finish");
    delay(serial_delay);
    Serial.print("longitude is :");
    Serial.println(longitude);
    delay(serial_delay);
    Serial.print("latitude is :");
    Serial.println(latitude);
    delay(serial_delay);
    Serial.print("timeZone is :");
    Serial.println(timeZone);
    delay(serial_delay);
    Serial.print("fajrTwilight is :");
    Serial.println(fajrTwilight);
    delay(serial_delay);
    Serial.print("ishaTwilight is :");
    Serial.println(ishaTwilight);
    delay(serial_delay);*/
    /////*********************************************************CALCULATION OF TIME FINISH
    year = years_function();
    n_year = 367 * year;
    month = months_function();
    int day = days_function();
    //

    double D = (n_year) - ((year + (int)((month + 9) / 12)) * 7 / 4) + (((int)(275 * month / 9)) + day - 730531.5);
    //Serial.println(D);
    double L = 280.461 + 0.9856474 * D;
    L = moreLess360(L);

    double M = 357.528 + (0.9856003) * D;
    M = moreLess360(M);

    double Lambda = L + 1.915 * sin(degToRad(M)) + 0.02 * sin(degToRad(2 * M));
    Lambda = moreLess360(Lambda);


    double Obliquity = 23.439 - 0.0000004 * D;
    double Alpha = radToDeg(atan((cos(degToRad(Obliquity)) * tan(degToRad(Lambda)))));
    Alpha = moreLess360(Alpha);

    Alpha = Alpha - (360 * (int)(Alpha / 360));
    Alpha = Alpha + 90 * (floor(Lambda / 90) - floor(Alpha / 90));

    double ST = 100.46 + 0.985647352 * D;
    double Dec = radToDeg(asin(sin(degToRad(Obliquity)) * sin(degToRad(Lambda))));
    double Durinal_Arc = radToDeg(acos((sin(degToRad(-0.8333)) - sin(degToRad(Dec)) * sin(degToRad(latitude))) / (cos(degToRad(Dec)) * cos(degToRad(latitude)))));


    double Noon = Alpha - ST;
    Noon = moreLess360(Noon);

    double UT_Noon = Noon - longitude;

    ////////////////////////////////////////////
    // Calculating Prayer Times Arcs & Times //
    //////////////////////////////////////////

    // 2) Zuhr Time [Local noon]
    zuhrTime = UT_Noon / 15 + timeZone;

    // Asr Hanafi
    //double Asr_Alt =radToDeg(atan(2+tan(degToRad(latitude - Dec))));
    double Asr_Alt = radToDeg(atan(1.0 + tan(degToRad(latitude - Dec))));
    // Asr Shafii
    //double Asr_Alt = radToDeg(atan(1 + tan(degToRad(latitude - Dec))));
    double Asr_Arc = radToDeg(acos((sin(degToRad(90 - Asr_Alt)) - sin(degToRad(Dec)) * sin(degToRad(latitude))) / (cos(degToRad(Dec)) * cos(degToRad(latitude)))));
    Asr_Arc = Asr_Arc / 15;
    // 3) Asr Time
    asrTime = zuhrTime + Asr_Arc;
    /*Serial.println("Asr_Alt");
   Serial.println(radToDeg(atan(1 + tan(degToRad(abs(latitude - Dec))))));
   Serial.println(Asr_Alt);*/
    // 1) Shorouq Time
    sunRiseTime = zuhrTime - (Durinal_Arc / 15);

    // 4) Maghrib Time
    maghribTime = zuhrTime + (Durinal_Arc / 15);

    double Esha_Arc = radToDeg(acos((sin(degToRad(ishaTwilight)) - sin(degToRad(Dec)) * sin(degToRad(latitude))) / (cos(degToRad(Dec)) * cos(degToRad(latitude)))));
    // 5) Isha Time
    ishaTime = zuhrTime + (Esha_Arc / 15);

    // 0) Fajr Time
    double Fajr_Arc = radToDeg(acos((sin(degToRad(fajrTwilight)) - sin(degToRad(Dec)) * sin(degToRad(latitude))) / (cos(degToRad(Dec)) * cos(degToRad(latitude)))));
    fajrTime = zuhrTime - (Fajr_Arc / 15);



  } else {
    fajrTime = fajrTime;
    sunRiseTime = sunRiseTime;
    zuhrTime = zuhrTime;
    asrTime = asrTime;
    maghribTime = maghribTime;
    ishaTime = ishaTime;
  }
  return;
}

///*************************BLUETOUTH FUNCTION FINISH(GETTING SERIAL DATA)
////////////*********sound volume control function start

////////////*********sound volume control function finish


///****************************************CONTROL FUNCTION START
void Prayer_time_control() {

  calcPrayerTimes(longitude, latitude, timeZone, fajrTwilight, ishaTwilight,
                  fajr, sunRise, zuhr, asr, maghrib, isha);
  int hours, minutes;
  ////calling potontiometer sound volume arrangement
  ///modified 09/08/2022
  char pr_time;
  ///for azan timing time
  unsigned long currentMillis = millis();
  ///////////////
  if (fajr != 0 && zuhr != 0 && asr != 0 && maghrib != 0 && isha != 0) {
    //calling RTC functions ,store them into another variables
    Serial.println("DONNNNNNNNNNNNNNNNNNNNNNNNNNE");
    c_t_hours = hours_function();
    c_t_minutes = minutes_function();
    /* c_t_minutes_up_eqp = c_t_minutes + time_accuracy_up;
    c_t_minutes_bel_eqp = c_t_minutes - time_accuracy_d; */
    //****Fajr Time
    //Serial.print( fajr);
    doubleToHrMin(fajr, hours, minutes);
    fajr_hour = int(hours);
    fajr_min = int(minutes);
    F_minutes_up_eqp=fajr_min+F_accuracy_up; 
    F_minutes_bel_eqp=fajr_min-F_accuracy_d;
    fajr_equil_point = ((c_t_hours == fajr_hour) && ( c_t_minutes>=F_minutes_bel_eqp&&c_t_minutes<F_minutes_up_eqp ));
    ///just testing switch
    //if()
    ///
    if (fajr_equil_point == true) {
      pr_time = 'p';
      Serial.println("  it is in fajr mood");
      //////
      /////
      Serial.println("fajr time azanNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN");
      Serial.print("Fajr time is : ");
      Serial.print(fajr_hour);
      Serial.print(":");
      Serial.println(fajr_min);
      ///
      //sound_volume_r = pot_fun();
      myDFPlayer.play(1);
      myDFPlayer.volume(sound_volumeM);
      Serial.print("sound_volume_2nd : ");
      digitalWrite(LED, HIGH);      
     delay(azan_calling_on);
    }

    //****Sunrise Time
    //Serial.print( sunRise);
    doubleToHrMin(sunRise, hours, minutes);
    sunrise_hour = int(hours);
    sunrise_min = int(minutes);
    S_minutes_up_eqp=sunrise_min+S_accuracy_up; 
    S_minutes_bel_eqp=sunrise_min-S_accuracy_d;
    sunrise_equil_point  = ((c_t_hours == sunrise_hour) && ( c_t_minutes>=S_minutes_bel_eqp&&c_t_minutes<S_minutes_up_eqp ));    
    
    if (sunrise_equil_point == true) {
      pr_time = 's';
      Serial.println("  : set df player to ON");
      ///LED
     
      //////
      ////
      Serial.println("sunrise time azanNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN");
      Serial.print("sunRise time is ");
      Serial.print(sunrise_hour);
      Serial.print(":");
      Serial.println(sunrise_min);
      ///
      //sound_volume_r = pot_fun();
      myDFPlayer.play(2);
      myDFPlayer.volume(sound_volumeM);
      Serial.print("sound_volume_2nd : ");
      ////
      digitalWrite(LED, HIGH);      
      delay(azan_calling_on);
    }
    ///////////
    //Serial.print( zuhr);
    doubleToHrMin(zuhr, hours, minutes);
    zuhr_hour = int(hours);
    zuhr_min = int(minutes);
    D_minutes_up_eqp=zuhr_min+D_accuracy_up; 
    D_minutes_bel_eqp=zuhr_min-D_accuracy_d;
    zuhr_equil_point  = ((c_t_hours == zuhr_hour) && ( c_t_minutes>=D_minutes_bel_eqp&&c_t_minutes<D_minutes_up_eqp ));
    if (zuhr_equil_point == true) {
      pr_time = 'd';
      Serial.println("  : set df player to ON");
      ///LED
     
      //////
      ////
      Serial.println("zuhr time azanNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN");
      Serial.print("zuhr time is ");
      Serial.print(zuhr_hour);
      Serial.print(":");
      Serial.println(zuhr_min);
      ///
      //sound_volume_r = pot_fun();
      myDFPlayer.play(2);
      myDFPlayer.volume(sound_volumeM);
      Serial.print("sound_volume_2nd : ");
     digitalWrite(LED, HIGH);      
      delay(azan_calling_on);
    }
    //****Asr Time
    doubleToHrMin(asr, hours, minutes);
    asr_hour = int(hours);
    asr_min = int(minutes);
    A_minutes_up_eqp=asr_min+A_accuracy_up; 
    A_minutes_bel_eqp=asr_min-A_accuracy_d;
    asr_equil_point  = ((c_t_hours == asr_hour) && ( c_t_minutes>=A_minutes_bel_eqp&&c_t_minutes<A_minutes_up_eqp ));
    if (asr_equil_point == true) {
      pr_time = 'a';
      Serial.println("  : set df player to ON");
      ///LED
   
      //////

      Serial.println("asr time azanNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN");
      Serial.print("asr time is ");
      Serial.print(asr_hour);
      Serial.print(":");
      Serial.println(asr_min);
      ///
      //sound_volume_r = pot_fun();

      myDFPlayer.play(3);
      myDFPlayer.volume(sound_volumeM);
      Serial.print("sound_volume_2nd : ");  ///
      digitalWrite(LED, HIGH);      
      delay(azan_calling_on);
    }
    //****Maghrib Time
    doubleToHrMin(maghrib, hours, minutes);
    maghrib_hour = int(hours);
    maghrib_min = int(minutes);
    M_minutes_up_eqp=maghrib_min+M_accuracy_up; 
    M_minutes_bel_eqp=maghrib_min-M_accuracy_d;
    maghrib_equil_point  = ((c_t_hours == maghrib_hour) && ( c_t_minutes>=M_minutes_bel_eqp&&c_t_minutes<M_minutes_up_eqp ));
    if (maghrib_equil_point == true) {
      pr_time = 'm';
      Serial.println("  : set df player to ON");
      ///LED

      //////
      ////
      Serial.println("maghrib time azanNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN");
      Serial.print("maghrib time is ");
      Serial.print(maghrib_hour);
      Serial.print(":");
      Serial.println(maghrib_min);
      ///
      //sound_volume_r = pot_fun();
      myDFPlayer.play(4);
      myDFPlayer.volume(sound_volumeM);
      Serial.print("sound_volume_2nd : ");
      ////
     digitalWrite(LED, HIGH);      
      delay(azan_calling_on);
    }

    //****Isha Time
    doubleToHrMin(isha, hours, minutes);
    isha_hour = int(hours);
    isha_min = int(minutes);
    I_minutes_up_eqp=isha_min+I_accuracy_up; 
    I_minutes_bel_eqp=isha_min-I_accuracy_d;
    isha_equil_point  = ((c_t_hours == isha_hour) && ( c_t_minutes>=I_minutes_bel_eqp&&c_t_minutes<I_minutes_up_eqp ));
    if (isha_equil_point == true) {
      pr_time = 'i';
      Serial.println("  : set df player to ON");
      ///LED
     
      //////
      ///
      Serial.println("isha time azanNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNNN");
      Serial.print("isha time is ");
      Serial.print(isha_hour);
      Serial.print(":");
      Serial.println(isha_min);
      ///
      //sound_volume_r = pot_fun();
      myDFPlayer.play(5);
      myDFPlayer.volume(sound_volumeM);
      Serial.print("sound_volume_2nd : ");
      ///
      digitalWrite(LED, HIGH);      
      delay(azan_calling_on);
    }
  }
}
////////////////////******************DFPLAYER FUNCTION START
///main function for dfplayer
/*void Dfplayer_fun() {
  if (Serial.available()) {
    String inData = "";
    //sound_volume_r = pot_fun();
    inData = Serial.readStringUntil('\n');
    if (inData.startsWith("1")) {
      myDFPlayer.volume(25);
      Serial.print("sound_volume_r : ");
      Serial.println(22);
      myDFPlayer.play(1);
      Serial.println("playing track is ....: ");
      delay(3 * 60000);
    } else if (inData.startsWith("2")) {
      myDFPlayer.volume(22);
      myDFPlayer.play(2);
      Serial.print("playing track is ....: ");
    } else if (inData.startsWith("3")) {
      myDFPlayer.volume(25);
      myDFPlayer.play(3);
      Serial.print("playing track is ....: ");
    } else if (inData.startsWith("4")) {
      myDFPlayer.volume(25);
      myDFPlayer.play(4);
      Serial.print("playing track is ....: ");
    } else if (inData.startsWith("5")) {
      myDFPlayer.volume(22);
      myDFPlayer.play(5);
      Serial.print("playing track is ....: ");

    } else if (inData.startsWith("6")) {
      myDFPlayer.volume(22);
      myDFPlayer.play(6);
      Serial.print("playing track is ....: ");
    } else if (inData.startsWith("+")) {
      Serial.println(F("up--------------------"));
      myDFPlayer.volumeUp();
      Serial.println(myDFPlayer.readVolume());  //read current volume
    } else if (inData.startsWith("-")) {
      Serial.println(F("down--------------------"));
      myDFPlayer.volumeDown();
      Serial.println(myDFPlayer.readVolume());  //read current volume
    } else if (inData.startsWith("*")) {
      Serial.println(F("pause--------------------"));
      myDFPlayer.pause();
    } else if (inData.startsWith(">")) {
      Serial.println(F("start--------------------"));
      myDFPlayer.start();
    }
  }
}*/

///////////////////////////**************************DFPLAYER FUNCTION FINISH


///SEND TO SERIAL PLOTTER FUNCTION
void DataToMobileApp() {

  DataToBeMonitored(Fajr_praying, Sunrise_praying, Duhr_praying, Asr_praying, Maghrib_praying, Isha_praying);
  String DataToMobile = Fajr_praying + Sunrise_praying + Duhr_praying + Asr_praying + Maghrib_praying + Isha_praying;  // Join T,H,D
  //String DataToMobile ="1234567890";  // Join T,H,D
  Serial.println(DataToMobile);
  SerialBT.print(DataToMobile);  // Send to Android
  delay(250);
}
//************************PRINTING TO SERIAL PLOTTER FINISH
////PREPARING DATA THAT WILL BE MONITORED START
void DataToBeMonitored(String &Fajr_praying, String &Sunrise_praying, String &Duhr_praying, String &Asr_praying, String &Maghrib_praying, String &Isha_praying) {
  calcPrayerTimes(longitude, latitude, timeZone, fajrTwilight, ishaTwilight, fajr, sunRise, zuhr, asr, maghrib, isha);
  /////
  int hours, minutes;
  ///FAJR TIME START
  doubleToHrMin(fajr, hours, minutes);
  int fajr_hour1 = int(hours);
  int fajr_min1 = int(minutes);
  fajr_hour1_s = "0" + String(fajr_hour1);
  fajr_min1_s = "0" + String(fajr_min1);
  Fajr_praying = fajr_hour1_s + ":" + fajr_min1_s;
  fajr_h_length = fajr_hour1_s.length();
  fajr_m_length = fajr_min1_s.length();
  fajr_p_length = Fajr_praying.length();
  if (fajr != 0 && zuhr != 0 && asr != 0 && maghrib != 0 && isha != 0) {
    if (fajr_h_length > 2 && fajr_m_length > 2) {
      fajr_hour1_s.remove(0, 1);
      fajr_min1_s.remove(0, 1);
      Fajr_praying = fajr_hour1_s + ":" + fajr_min1_s;
      Serial.print("FAJR TIME IS 1  :");
      Serial.println(Fajr_praying);
      ///To go to mobile app
      //SerialBT.print(Fajr_praying);  // Send to Android
      delay(mobile_delay);
    }
    if (fajr_h_length > 2 && fajr_m_length <= 2) {
      fajr_hour1_s.remove(0, 1);
      Fajr_praying = fajr_hour1_s + ":" + fajr_min1_s;
      Serial.print("FAJR TIME IS 2 :");
      Serial.println(Fajr_praying);
      ///To go to mobile app
      // SerialBT.print(Fajr_praying);  // Send to Android
      delay(mobile_delay);
    }
    if (fajr_h_length <= 2 && fajr_m_length > 2) {
      fajr_min1_s.remove(0, 1);
      Fajr_praying = fajr_hour1_s + ":" + fajr_min1_s;
      Serial.print("FAJR TIME IS 3 :");
      Serial.println(Fajr_praying);
      ///To go to mobile app
      //SerialBT.print(Fajr_praying);  // Send to Android
      delay(mobile_delay);
    }
    if (fajr_h_length <= 2 && fajr_m_length <= 2) {
      Fajr_praying = fajr_hour1_s + ":" + fajr_min1_s;
      Serial.print("FAJR TIME IS 4 :");
      Serial.println(Fajr_praying);
      ///To go to mobile app
      //SerialBT.print(Fajr_praying);  // Send to Android
      delay(mobile_delay);
    }
    //////FAJR TIME FINISH
    ///SUNRISE TIME START
    doubleToHrMin(sunRise, hours, minutes);
    int sunrise_hour1 = int(hours);
    int sunrise_min1 = int(minutes);
    sunrise_hour1_s = "0" + String(sunrise_hour1);
    sunrise_min1_s = "0" + String(sunrise_min1);
    Sunrise_praying = sunrise_hour1_s + ":" + sunrise_min1_s;
    sunrise_h_length = sunrise_hour1_s.length();
    sunrise_m_length = sunrise_min1_s.length();
    sunrise_p_length = Sunrise_praying.length();
    if (sunrise_h_length > 2 && sunrise_m_length > 2) {
      sunrise_hour1_s.remove(0, 1);
      sunrise_min1_s.remove(0, 1);
      Sunrise_praying = sunrise_hour1_s + ":" + sunrise_min1_s;
      Serial.print("SUNRISE TIME IS 1  :");
      Serial.println(Sunrise_praying);
      ///To go to mobile app
      //SerialBT.print(Sunrise_praying);  // Send to Android
      delay(mobile_delay);
    }
    if (sunrise_h_length > 2 && sunrise_m_length <= 2) {
      sunrise_hour1_s.remove(0, 1);
      Sunrise_praying = sunrise_hour1_s + ":" + sunrise_min1_s;
      Serial.print("SUNRISE TIME IS 2 :");
      Serial.println(Sunrise_praying);
      ///To go to mobile app
      // SerialBT.print(Sunrise_praying);  // Send to Android
      delay(mobile_delay);
    }
    if (sunrise_h_length <= 2 && sunrise_m_length > 2) {
      sunrise_min1_s.remove(0, 1);
      Sunrise_praying = sunrise_hour1_s + ":" + sunrise_min1_s;
      Serial.print("SUNRISE TIME IS 3 :");
      Serial.println(Sunrise_praying);
      ///To go to mobile app
      //SerialBT.print(Sunrise_praying);  // Send to Android
      delay(mobile_delay);
    }
    if (sunrise_h_length <= 2 && sunrise_m_length <= 2) {
      Sunrise_praying = sunrise_hour1_s + ":" + sunrise_min1_s;
      Serial.print("SUNRISE TIME IS 4 :");
      Serial.println(Sunrise_praying);
      ///To go to mobile app
      //SerialBT.print(Sunrise_praying);  // Send to Android
      delay(mobile_delay);
    }
    //////SUNRISE TIME FINISH


    ///
    ///ZUHR TIME START
    doubleToHrMin(zuhr, hours, minutes);
    int duhr_hour1 = int(hours);
    int duhr_min1 = int(minutes);
    duhr_hour1_s = "0" + String(duhr_hour1);
    duhr_min1_s = "0" + String(duhr_min1);
    Duhr_praying = duhr_hour1_s + ":" + duhr_min1_s;
    duhr_h_length = duhr_hour1_s.length();
    duhr_m_length = duhr_min1_s.length();
    duhr_p_length = Duhr_praying.length();
    if (duhr_h_length > 2 && duhr_m_length > 2) {
      duhr_hour1_s.remove(0, 1);
      duhr_min1_s.remove(0, 1);
      Duhr_praying = duhr_hour1_s + ":" + duhr_min1_s;
      Serial.print("DUHR TIME IS 1  :");
      Serial.println(Duhr_praying);
      ///To go to mobile app
      //SerialBT.print(Duhr_praying);  // Send to Android
      delay(mobile_delay);
    }
    if (duhr_h_length > 2 && duhr_m_length <= 2) {
      duhr_hour1_s.remove(0, 1);
      Duhr_praying = duhr_hour1_s + ":" + duhr_min1_s;
      Serial.print("DUHR TIME IS 2 :");
      Serial.println(Duhr_praying);
      ///To go to mobile app
      //SerialBT.print(Duhr_praying);  // Send to Android
      delay(mobile_delay);
    }
    if (duhr_h_length <= 2 && duhr_m_length > 2) {
      duhr_min1_s.remove(0, 1);
      Duhr_praying = duhr_hour1_s + ":" + duhr_min1_s;
      Serial.print("DUHR TIME IS 3 :");
      Serial.println(Duhr_praying);
      ///To go to mobile app
      //SerialBT.print(Duhr_praying);  // Send to Android
      delay(mobile_delay);
    }
    if (duhr_h_length <= 2 && duhr_m_length <= 2) {
      Duhr_praying = duhr_hour1_s + ":" + duhr_min1_s;
      Serial.print("DUHR TIME IS 4 :");
      Serial.println(Duhr_praying);
      ///To go to mobile app
      //SerialBT.print(Duhr_praying);  // Send to Android
      delay(mobile_delay);
    }
    ///ZUHR TIME FINISH
    ///ASR TIME START
    doubleToHrMin(asr, hours, minutes);
    int asr_hour1 = int(hours);
    int asr_min1 = int(minutes);
    asr_hour1_s = "0" + String(asr_hour1);
    asr_min1_s = "0" + String(asr_min1);
    Asr_praying = asr_hour1_s + ":" + asr_min1_s;
    asr_h_length = asr_hour1_s.length();
    asr_m_length = asr_min1_s.length();
    asr_p_length = Asr_praying.length();
    if (asr_h_length > 2 && asr_m_length > 2) {
      asr_hour1_s.remove(0, 1);
      asr_min1_s.remove(0, 1);
      Asr_praying = asr_hour1_s + ":" + asr_min1_s;
      Serial.print("ASR TIME IS 1  :");
      Serial.println(Asr_praying);
      ///To go to mobile app
      //SerialBT.print(Asr_praying);  // Send to Android
      delay(mobile_delay);
    }
    if (asr_h_length > 2 && asr_m_length <= 2) {
      asr_hour1_s.remove(0, 1);
      Asr_praying = asr_hour1_s + ":" + asr_min1_s;
      Serial.print("ASR TIME IS 2 :");
      Serial.println(Asr_praying);
      ///To go to mobile app
      //SerialBT.print(Asr_praying);  // Send to Android
      delay(mobile_delay);
    }
    if (asr_h_length <= 2 && asr_m_length > 2) {
      asr_min1_s.remove(0, 1);
      Asr_praying = asr_hour1_s + ":" + asr_min1_s;
      Serial.print("ASR TIME IS 3 :");
      Serial.println(Asr_praying);
      ///To go to mobile app
      //SerialBT.print(Asr_praying);  // Send to Android
      delay(mobile_delay);
    }
    if (asr_h_length <= 2 && asr_m_length <= 2) {
      Asr_praying = asr_hour1_s + ":" + asr_min1_s;
      Serial.print("ASR TIME IS 4 :");
      Serial.println(Asr_praying);
      ///To go to mobile app
      //SerialBT.print(Asr_praying);  // Send to Android
      delay(mobile_delay);
    }

    ///ASR TIME FINISH
    ///MAGHRIB TIME START
    doubleToHrMin(maghrib, hours, minutes);
    int maghrib_hour1 = int(hours);
    int maghrib_min1 = int(minutes);
    maghrib_hour1_s = "0" + String(maghrib_hour1);
    maghrib_min1_s = "0" + String(maghrib_min1);
    Maghrib_praying = maghrib_hour1_s + ":" + maghrib_min1_s;
    maghrib_h_length = maghrib_hour1_s.length();
    maghrib_m_length = maghrib_min1_s.length();
    maghrib_p_length = Maghrib_praying.length();
    if (maghrib_h_length > 2 && maghrib_m_length > 2) {
      maghrib_hour1_s.remove(0, 1);
      maghrib_min1_s.remove(0, 1);
      Maghrib_praying = maghrib_hour1_s + ":" + maghrib_min1_s;
      Serial.print("MAGHRIB TIME IS 1  :");
      Serial.println(Maghrib_praying);
      ///To go to mobile app
      //SerialBT.print(Maghrib_praying);  // Send to Android
      delay(mobile_delay);
    }
    if (maghrib_h_length > 2 && maghrib_m_length <= 2) {
      maghrib_hour1_s.remove(0, 1);
      //maghrib_min1_s.remove(0, 1);
      Maghrib_praying = maghrib_hour1_s + ":" + maghrib_min1_s;
      Serial.print("MAGHRIB TIME IS 2 :");
      Serial.println(Maghrib_praying);
      ///To go to mobile app
      // SerialBT.print(Maghrib_praying);  // Send to Android
      delay(mobile_delay);
    }
    if (maghrib_h_length <= 2 && maghrib_m_length > 2) {
      maghrib_min1_s.remove(0, 1);
      Maghrib_praying = maghrib_hour1_s + ":" + maghrib_min1_s;
      Serial.print("MAGHRIB TIME IS 3 :");
      Serial.println(Maghrib_praying);
      ///To go to mobile app
      //SerialBT.print(Maghrib_praying);  // Send to Android
      delay(mobile_delay);
    }
    if (maghrib_h_length <= 2 && maghrib_m_length <= 2) {
      Maghrib_praying = maghrib_hour1_s + ":" + maghrib_min1_s;
      Serial.print("MAGHRIB TIME IS 4 :");
      Serial.println(Maghrib_praying);
      ///To go to mobile app
      //SerialBT.print(Maghrib_praying);  // Send to Android
      delay(mobile_delay);
    }

    ///MAGHRIB TIME FINISH
    ///ISHA TIME START
    doubleToHrMin(isha, hours, minutes);
    int isha_hour1 = int(hours);
    int isha_min1 = int(minutes);
    isha_hour1_s = "0" + String(isha_hour1);
    isha_min1_s = "0" + String(isha_min1);
    Isha_praying = isha_hour1_s + ":" + isha_min1_s;
    isha_h_length = isha_hour1_s.length();
    isha_m_length = isha_min1_s.length();
    isha_p_length = Isha_praying.length();
    if (isha_h_length > 2 && isha_m_length > 2) {
      isha_hour1_s.remove(0, 1);
      isha_min1_s.remove(0, 1);
      Isha_praying = isha_hour1_s + ":" + isha_min1_s;
      Serial.print("ISHA TIME IS 1 :");
      Serial.println(Isha_praying);
      ///To go to mobile app
      //SerialBT.print(Isha_praying);  // Send to Android
      delay(mobile_delay);
    }
    if (isha_h_length > 2 && isha_m_length <= 2) {
      isha_hour1_s.remove(0, 1);
      Isha_praying = isha_hour1_s + ":" + isha_min1_s;
      Serial.print("ISHA TIME IS 2 :");
      Serial.println(Isha_praying);
      ///To go to mobile app
      // SerialBT.print(Isha_praying);  // Send to Android
      delay(mobile_delay);
    }
    if (isha_h_length <= 2 && isha_m_length > 2) {
      isha_min1_s.remove(0, 1);
      Isha_praying = isha_hour1_s + ":" + isha_min1_s;
      Serial.print("ISHA TIME IS 3 :");
      Serial.println(Isha_praying);
      ///To go to mobile app
      //SerialBT.print(Isha_praying);  // Send to Android
      delay(mobile_delay);
    }
    if (isha_h_length <= 2 && isha_m_length <= 2) {
      Isha_praying = isha_hour1_s + ":" + isha_min1_s;
      Serial.print("ISHA TIME IS 4 :");
      Serial.println(Isha_praying);
      ///To go to mobile app
      //SerialBT.print(Isha_praying);  // Send to Android
      delay(mobile_delay);
    }
    ///ISHA TIME FINISH
    //************************SENTD TO SERIAL PLOTTER FINISH
  }
  ///
}
////////PREPARING DATA THAT WILL BE MONITORED  FINISH

////LED STATTING START
void led_stating()
{
ledstate=digitalRead(ledp);
 if (ledstate == HIGH/* &&flag==false*/) {
    digitalWrite(LED, HIGH);
    Serial.println(ledstate);
    //flag=true;
  } 
  if(ledstate == LOW /*&&flag==true*/) {
    digitalWrite(LED, LOW);
    Serial.println(ledstate);
    //flag=false;
  }  
}
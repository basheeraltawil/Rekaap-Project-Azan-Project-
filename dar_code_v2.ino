//df player start
#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"
// Use pins 10 and 11 to communicate with DFPlayer Mini/ARDUINO MEGA
static const uint8_t PIN_MP3_TX = 11;  // Connects to module's RX
static const uint8_t PIN_MP3_RX = 10;  // Connects to module's TX
int sound_volume = 20;
SoftwareSerial softwareSerial(PIN_MP3_RX, PIN_MP3_TX);
// Create the Player object
DFRobotDFPlayerMini myDFPlayer;
/////
long EXE_INTERVAL = 2 * 60000;
unsigned long lastExecutedMillis = 2 * 60000;  // vairable to save the last executed time
//df player finish
///INPUTS DEFINITION START
////level selection
const int level_s = 8;
///surat selection
const int nas_s = 53;  ///surat alnas
const int falaq_s = 52;
const int ikhlas_s = 51;
const int masad_s = 50;
//////control bottuns
const int start_b = 49;
const int next_b = 48;
const int previous_b = 47;
const int repeat_b = 46;
const int pause_b = 45;
/////digital readings
int level_s_Value = 0;
int nas_s_Value = 0;
int falaq_s_Value = 0;
int ikhlas_s_Value = 0;
int masad_s_Value = 0;
int start_b_Value = 0;
int next_b_Value = 0;
int previous_b_Value = 0;
int repeat_b_Value = 0;
int pause_b_Value = 0;
///INPUTS DEFINITION FINISH
////**************************
///OUTPUTS DEFINITION START
const int YELLOWLED = 2;
const int BLUELED = 3;
const int GREENLED = 4;
const int REDLED = 5;

///OUTPUTS DEFINITION FINISH
////**************************
//////GLOBAL VARIABLE START
int state = 0, LEDstate = 0;
//////GLOBAL VARIABLE FINISH
void setup() {
  // Dfplayer start
  Serial.begin(9600);
  // Init serial port for DFPlayer Mini
  softwareSerial.begin(9600);

  // Start communication with DFPlayer Mini
  ///
  Serial.println();
  Serial.println(F("DFRobot DFPlayer Mini Demo"));
  Serial.println(F("Initializing DFPlayer ... (May take 3~5 seconds)"));

  if (!myDFPlayer.begin(softwareSerial)) {  //Use softwareSerial to communicate with mp3.

    //Serial.println(myDFPlayer.readType(),HEX);
    Serial.println(F("Unable to begin:"));
    Serial.println(F("1.Please recheck the connection!"));
    Serial.println(F("2.Please insert the SD card!"));
    while (true)
      ;
      
  }
  Serial.println(F("DFPlayer Mini online."));

  myDFPlayer.setTimeOut(500);  //Set serial communictaion time out 500ms
  Serial.println(F("myDFPlayer.play(1)"));
myDFPlayer.playFolder(3,6);
    Serial.println(myDFPlayer.readCurrentFileNumber());
      Serial.println(myDFPlayer.readCurrentFileNumber());   
  // Dfplayer finish
  ///I/O SETUP
  pinMode(level_s, INPUT);
  pinMode(nas_s, INPUT);
  pinMode(falaq_s, INPUT);
  pinMode(ikhlas_s, INPUT);
  pinMode(masad_s, INPUT);
  pinMode(start_b, INPUT);
  pinMode(next_b, INPUT);
  pinMode(previous_b, INPUT);
  pinMode(repeat_b, INPUT);
  pinMode(pause_b, INPUT);
  pinMode(YELLOWLED, OUTPUT);
  pinMode(BLUELED, OUTPUT);
  pinMode(GREENLED, OUTPUT);
  pinMode(REDLED, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
sura_controlfunctions();
ayat_controlling_function();
//digitalWrite(YELLOWLED, HIGH);
 
}


///controlTRAILS
void sura_controlfunctions() {

  INPUTS_FUNCTION(level_s_Value, nas_s_Value, falaq_s_Value, ikhlas_s_Value, masad_s_Value, start_b_Value, next_b_Value, previous_b_Value, repeat_b_Value, pause_b_Value);
  /*  Serial.println("level_s_Value");
  Serial.println(level_s_Value);
  delay(500);
  Serial.println("nas_s_Value");
  Serial.println(nas_s_Value);
  delay(500);
  Serial.println("falaq_s_Value");
  Serial.println(falaq_s_Value);
  delay(500);
  Serial.println("ikhlas_s_Value");
  Serial.println(ikhlas_s_Value);
  delay(500); 
  Serial.println("masad_s_Value");
  Serial.println(masad_s_Value);
  delay(500); 
  Serial.println("start_b_Value");
  Serial.println(start_b_Value);
  delay(500);
  Serial.println("next_b_Value");
  Serial.println(next_b_Value);  
  delay(500);
  Serial.println("previous_b_Value");
  Serial.println(previous_b_Value);  
  delay(500);
  Serial.println("repeat_b_Value");
  Serial.println(repeat_b_Value);  
  delay(500); 
  Serial.println("pause_b_Value");
  Serial.println(pause_b_Value);  
  delay(500); */
  if (level_s_Value == HIGH)
{
   
  if (/* level_s_Value == HIGH && */  nas_s_Value == HIGH &&falaq_s_Value == LOW && ikhlas_s_Value == LOW &&masad_s_Value == LOW) {
    digitalWrite(YELLOWLED, HIGH);
    Serial.println("HIGHHHH");
    if (start_b_Value == HIGH) {
      myDFPlayer.playFolder(1, 1);
      myDFPlayer.volume(20);
    }
    else if (repeat_b_Value == HIGH) {
      file_looping();
    } else if (pause_b_Value == HIGH) {
      file_pause();
    }
  }
  if (/* level_s_Value == HIGH && */nas_s_Value == LOW &&falaq_s_Value == HIGH && ikhlas_s_Value == LOW &&masad_s_Value == LOW) {
    digitalWrite(BLUELED, HIGH);
    Serial.println("HIGHHHH");
    if (start_b_Value == HIGH) {
      myDFPlayer.playFolder(1, 2);
      myDFPlayer.volume(20);
    }
    else if (repeat_b_Value == HIGH) {
      file_looping();
    } else if (pause_b_Value == HIGH) {
      file_pause();
    }
  }
  if (/* level_s_Value == HIGH &&  */ nas_s_Value == LOW &&falaq_s_Value == LOW && ikhlas_s_Value == HIGH &&masad_s_Value == LOW) {
    digitalWrite(GREENLED, HIGH);
    Serial.println("HIGHHHH");
    if (start_b_Value == HIGH) {
      myDFPlayer.playFolder(1, 3);
      myDFPlayer.volume(20);
    }
    else if (repeat_b_Value == HIGH) {
      file_looping();
    } else if (pause_b_Value == HIGH) {
      file_pause();
    }
  }
  if (/* level_s_Value == HIGH && */  nas_s_Value == LOW &&falaq_s_Value == LOW && ikhlas_s_Value == LOW &&masad_s_Value == HIGH) {
    digitalWrite(REDLED, HIGH);
    Serial.println("HIGHHHH");
    if (start_b_Value == HIGH) {
      myDFPlayer.playFolder(1, 4);
      myDFPlayer.volume(20);
    }
    //dfpassing_bottuns();

    else if (repeat_b_Value == HIGH) {
     file_looping();
    } else if (pause_b_Value == HIGH) {
      file_pause();
    }
  }
}

  ////TO CLOSE LEDS
  if(nas_s_Value == LOW &&falaq_s_Value == LOW && ikhlas_s_Value == LOW &&masad_s_Value == LOW)
  {
    led_locking();
  }

  
}
////ayat controlling
void ayat_controlling_function()
{
  INPUTS_FUNCTION(level_s_Value, nas_s_Value, falaq_s_Value, ikhlas_s_Value, masad_s_Value, start_b_Value, next_b_Value, previous_b_Value, repeat_b_Value, pause_b_Value);
  /*  Serial.println("level_s_Value");
  Serial.println(level_s_Value);
  delay(500);
  Serial.println("nas_s_Value");
  Serial.println(nas_s_Value);
  delay(500);
  Serial.println("falaq_s_Value");
  Serial.println(falaq_s_Value);
  delay(500);
  Serial.println("ikhlas_s_Value");
  Serial.println(ikhlas_s_Value);
  delay(500); 
  Serial.println("masad_s_Value");
  Serial.println(masad_s_Value);
  delay(500); 
  Serial.println("start_b_Value");
  Serial.println(start_b_Value);
  delay(500);
Serial.println("next_b_Value");
  Serial.println(next_b_Value);  
  delay(500);
  Serial.println("previous_b_Value");
  Serial.println(previous_b_Value);  
  delay(500);
  Serial.println("repeat_b_Value");
  Serial.println(repeat_b_Value);  
  delay(500); 
  Serial.println("pause_b_Value");
  Serial.println(pause_b_Value);  
  delay(500); */

  if (level_s_Value == LOW)
{
   //NAS
  if (/* level_s_Value == HIGH && */ nas_s_Value == HIGH &&falaq_s_Value == LOW && ikhlas_s_Value == LOW &&masad_s_Value == LOW) {
    digitalWrite(YELLOWLED, HIGH);
    //Serial.println("HIGHHHH");
    if (start_b_Value == HIGH) 
    {
      delay(150);
      myDFPlayer.playFolder(2, 1);
      Serial.println(myDFPlayer.readCurrentFileNumber());
      Serial.println(myDFPlayer.readCurrentFileNumber());      
      myDFPlayer.volume(20);
    }
    
    else if (repeat_b_Value == HIGH) {
      delay(150); 
      file_looping();
    } else if (pause_b_Value == HIGH) {
      delay(150); 
      file_pause();
    }
    ////
    if (previous_b_Value == HIGH) {
      delay(150);
    int filetoloop = myDFPlayer.readCurrentFileNumber();
    if (filetoloop > 5 &&filetoloop<=10) {
      myDFPlayer.previous();  //Play previous mp3
      Serial.print("playing track is ....: ");
      Serial.println(myDFPlayer.readCurrentFileNumber());
      Serial.println(myDFPlayer.readCurrentFileNumber());
    }
    if (filetoloop == 5) {
      myDFPlayer.playFolder(2, 1);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)           Serial.println("1"); //read current volume
      myDFPlayer.volume(20);
      Serial.println(myDFPlayer.readCurrentFileNumber());
      Serial.println(myDFPlayer.readCurrentFileNumber());
    }
  } else if (next_b_Value == HIGH) {
    delay(150);
    int filetoloop = myDFPlayer.readCurrentFileNumber();
    //nt filetoloop = myDFPlayer.readCurrentFileNumber();
    if (filetoloop >= 5 &&filetoloop<10) {
    
      myDFPlayer.next();  //Play next mp3
      Serial.print("playing track is ....: ");
      Serial.println(myDFPlayer.readCurrentFileNumber());
      Serial.println(myDFPlayer.readCurrentFileNumber());
    }
    if (filetoloop ==10) {
      myDFPlayer.playFolder(2, 6);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)           Serial.println("1"); //read current volume
      myDFPlayer.volume(20);
      Serial.println(myDFPlayer.readCurrentFileNumber());
      Serial.println(myDFPlayer.readCurrentFileNumber());
    }
  }    
    ////
  }
  //FALAQ
  if (/* level_s_Value == HIGH && */ nas_s_Value == LOW &&falaq_s_Value == HIGH && ikhlas_s_Value == LOW &&masad_s_Value == LOW) {
delay(150);  
    digitalWrite(BLUELED, HIGH);
    //Serial.println("HIGHHHH");
    if (start_b_Value == HIGH) {
      delay(150); 
      myDFPlayer.playFolder(3, 1);
      myDFPlayer.volume(20);
    }
    else if (repeat_b_Value == HIGH) {
delay(150);       
      file_looping();
    } else if (pause_b_Value == HIGH) {
      delay(150); 
      file_pause();
    }
  ////
    if (previous_b_Value == HIGH) {
      delay(150);
    int filetoloop = myDFPlayer.readCurrentFileNumber();
    if (filetoloop > 11 &&filetoloop<=15) {
      myDFPlayer.previous();  //Play previous mp3
      Serial.print("playing track is ....: ");
      Serial.println(myDFPlayer.readCurrentFileNumber());
      Serial.println(myDFPlayer.readCurrentFileNumber());
    }
    if (filetoloop == 11) {
      myDFPlayer.playFolder(3, 1);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)           Serial.println("1"); //read current volume
      myDFPlayer.volume(20);
      Serial.println(myDFPlayer.readCurrentFileNumber());
      Serial.println(myDFPlayer.readCurrentFileNumber());
    }
  } else if (next_b_Value == HIGH) {
    delay(150);
    int filetoloop = myDFPlayer.readCurrentFileNumber();
    //nt filetoloop = myDFPlayer.readCurrentFileNumber();
    if (filetoloop >= 11 &&filetoloop<15) {
    
      myDFPlayer.next();  //Play next mp3
      Serial.print("playing track is ....: ");
      Serial.println(myDFPlayer.readCurrentFileNumber());
      Serial.println(myDFPlayer.readCurrentFileNumber());
    }
    if (filetoloop ==15) {
      myDFPlayer.playFolder(3, 5);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)           Serial.println("1"); //read current volume
      myDFPlayer.volume(20);
      Serial.println(myDFPlayer.readCurrentFileNumber());
      Serial.println(myDFPlayer.readCurrentFileNumber());
    }
  }    
    ////
    
  }
  //IKHLAS
  if (/* level_s_Value == HIGH &&  */nas_s_Value == LOW &&falaq_s_Value == LOW && ikhlas_s_Value == HIGH &&masad_s_Value == LOW) {
    digitalWrite(GREENLED, HIGH);
    Serial.println("HIGHHHH");
    if (start_b_Value == HIGH) {
      myDFPlayer.playFolder(4, 1);
      myDFPlayer.volume(20);
    }
    else if (repeat_b_Value == HIGH) {
      file_looping();
    } else if (pause_b_Value == HIGH) {
      file_pause();
    }
  }
  //MASAD
  if (/* level_s_Value == HIGH && */ nas_s_Value == LOW &&falaq_s_Value == LOW && ikhlas_s_Value == LOW &&masad_s_Value == HIGH) {
    digitalWrite(REDLED, HIGH);
    Serial.println("HIGHHHH");
    if (start_b_Value == HIGH) {
      myDFPlayer.playFolder(5, 1);
      myDFPlayer.volume(20);
    }
    //dfpassing_bottuns();

    else if (repeat_b_Value == HIGH) {
      file_looping();
    } else if (pause_b_Value == HIGH) {
      file_pause();
    }
      
  }
}

  ////TO CLOSE LEDS
  if(nas_s_Value == LOW &&falaq_s_Value == LOW && ikhlas_s_Value == LOW &&masad_s_Value == LOW)
  {
    led_locking();
  }
  

}
////LOOPING SURA FUNCTION
void file_looping() {
  int filetoloop_n = myDFPlayer.readCurrentFileNumber();
  myDFPlayer.loop(filetoloop_n);  //Loop the first mp3
}
//////PAUSING SURA FUNCTION
void file_pause() {
  Serial.println(F("pause--------------------"));
  myDFPlayer.pause();
}
/////STARTING SURA FUNCTION
void sura_start()
{
/*else if (inData.startsWith(">")) {
      Serial.println(F("start--------------------"));
      myDFPlayer.start();
    }  */
}

//////PASSING BETWEEN DFPLAYER WORK
void dfpassing_bottuns() {
  ///s

  if (previous_b_Value == HIGH) {
    int filetoloop = myDFPlayer.readCurrentFileNumber();
    if (filetoloop != 1) {
      myDFPlayer.previous();  //Play previous mp3
      Serial.print("playing track is ....: ");
      Serial.println(myDFPlayer.readCurrentFileNumber());
      Serial.println(myDFPlayer.readCurrentFileNumber());
    }
    if (filetoloop == 1) {
      myDFPlayer.playFolder(1, 1);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)           Serial.println("1"); //read current volume
      myDFPlayer.volume(20);
      Serial.println(myDFPlayer.readCurrentFileNumber());
      Serial.println(myDFPlayer.readCurrentFileNumber());
    }
  } else if (next_b_Value == HIGH) {
    int filetoloop = myDFPlayer.readCurrentFileNumber();
    //nt filetoloop = myDFPlayer.readCurrentFileNumber();
    if (filetoloop != 4) {
      myDFPlayer.next();  //Play next mp3
      Serial.print("playing track is ....: ");
      Serial.println(myDFPlayer.readCurrentFileNumber());
      Serial.println(myDFPlayer.readCurrentFileNumber());
    }
    if (filetoloop == 4) {
      myDFPlayer.playFolder(1, 4);  //play specific mp3 in SD:/15/004.mp3; Folder Name(1~99); File Name(1~255)           Serial.println("1"); //read current volume
      myDFPlayer.volume(20);
      Serial.println(myDFPlayer.readCurrentFileNumber());
      Serial.println(myDFPlayer.readCurrentFileNumber());
    }
  } else if (repeat_b_Value == HIGH) {
    int filetoloop = myDFPlayer.readCurrentFileNumber();
    //int filetoloop = myDFPlayer.readCurrentFileNumber();
    myDFPlayer.loop(filetoloop);  //Loop the first mp3
  }

  else if (pause_b_Value == HIGH) {
    Serial.println(F("pause--------------------"));
    myDFPlayer.pause();
  }
  ////f
}
/////LEDS LOCKING FUNCTION
void led_locking()
{
////TO CLOSE LEDS
  if (nas_s_Value == LOW) {
    digitalWrite(YELLOWLED, LOW);
    //Serial.println("LOW");
  }
  if (falaq_s_Value == LOW) {
    digitalWrite(BLUELED, LOW);
    //Serial.println("LOW");
  }
  if (ikhlas_s_Value == LOW) {
    digitalWrite(GREENLED, LOW);
   // Serial.println("LOW");
  }
  if (masad_s_Value == LOW) {
    digitalWrite(REDLED, LOW);
    //Serial.println("LOW");
  }
  
}

//////INPUTS FUNCTION
void INPUTS_FUNCTION(int &level_s_Value, int &nas_s_Value, int &falaq_s_Value, int &ikhlas_s_Value, int &masad_s_Value, int &start_b_Value, int &next_b_Value, int &previous_b_Value, int &repeat_b_Value, int &pause_b_Value) {

  level_s_Value = digitalRead(level_s);
  nas_s_Value = digitalRead(nas_s);
  falaq_s_Value = digitalRead(falaq_s);
  ikhlas_s_Value = digitalRead(ikhlas_s);
  masad_s_Value = digitalRead(masad_s);
  start_b_Value = digitalRead(start_b);
  next_b_Value = digitalRead(next_b);
  previous_b_Value = digitalRead(previous_b);
  repeat_b_Value = digitalRead(repeat_b);
  pause_b_Value = digitalRead(pause_b);
  /////
  //////
}
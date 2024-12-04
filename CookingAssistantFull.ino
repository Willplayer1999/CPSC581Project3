#include <LiquidCrystal.h>
#include <IRremote.hpp>
#include <dht.h>

// THE FOLLOWING CODE IS FROM:
/* 
  Super Mario Bros - Overworld theme 
  Connect a piezo buzzer or speaker to pin 11 or select a new pin.
  More songs available at https://github.com/robsoncouto/arduino-songs                                            
                                              
                                              Robson Couto, 2019
*/
#define NOTE_B0  31
#define NOTE_C1  33
#define NOTE_CS1 35
#define NOTE_D1  37
#define NOTE_DS1 39
#define NOTE_E1  41
#define NOTE_F1  44
#define NOTE_FS1 46
#define NOTE_G1  49
#define NOTE_GS1 52
#define NOTE_A1  55
#define NOTE_AS1 58
#define NOTE_B1  62
#define NOTE_C2  65
#define NOTE_CS2 69
#define NOTE_D2  73
#define NOTE_DS2 78
#define NOTE_E2  82
#define NOTE_F2  87
#define NOTE_FS2 93
#define NOTE_G2  98
#define NOTE_GS2 104
#define NOTE_A2  110
#define NOTE_AS2 117
#define NOTE_B2  123
#define NOTE_C3  131
#define NOTE_CS3 139
#define NOTE_D3  147
#define NOTE_DS3 156
#define NOTE_E3  165
#define NOTE_F3  175
#define NOTE_FS3 185
#define NOTE_G3  196
#define NOTE_GS3 208
#define NOTE_A3  220
#define NOTE_AS3 233
#define NOTE_B3  247
#define NOTE_C4  262
#define NOTE_CS4 277
#define NOTE_D4  294
#define NOTE_DS4 311
#define NOTE_E4  330
#define NOTE_F4  349
#define NOTE_FS4 370
#define NOTE_G4  392
#define NOTE_GS4 415
#define NOTE_A4  440
#define NOTE_AS4 466
#define NOTE_B4  494
#define NOTE_C5  523
#define NOTE_CS5 554
#define NOTE_D5  587
#define NOTE_DS5 622
#define NOTE_E5  659
#define NOTE_F5  698
#define NOTE_FS5 740
#define NOTE_G5  784
#define NOTE_GS5 831
#define NOTE_A5  880
#define NOTE_AS5 932
#define NOTE_B5  988
#define NOTE_C6  1047
#define NOTE_CS6 1109
#define NOTE_D6  1175
#define NOTE_DS6 1245
#define NOTE_E6  1319
#define NOTE_F6  1397
#define NOTE_FS6 1480
#define NOTE_G6  1568
#define NOTE_GS6 1661
#define NOTE_A6  1760
#define NOTE_AS6 1865
#define NOTE_B6  1976
#define NOTE_C7  2093
#define NOTE_CS7 2217
#define NOTE_D7  2349
#define NOTE_DS7 2489
#define NOTE_E7  2637
#define NOTE_F7  2794
#define NOTE_FS7 2960
#define NOTE_G7  3136
#define NOTE_GS7 3322
#define NOTE_A7  3520
#define NOTE_AS7 3729
#define NOTE_B7  3951
#define NOTE_C8  4186
#define NOTE_CS8 4435
#define NOTE_D8  4699
#define NOTE_DS8 4978
#define REST      0


// change this to make the song slower or faster
int tempo = 200;

// change this to whichever pin you want to use
int buzzer = 9;

// notes of the moledy followed by the duration.
// a 4 means a quarter note, 8 an eighteenth , 16 sixteenth, so on
// !!negative numbers are used to represent dotted notes,
// so -4 means a dotted quarter note, that is, a quarter plus an eighteenth!!
int melody[] = {

  // Super Mario Bros theme
  // Score available at https://musescore.com/user/2123/scores/2145
  // Theme by Koji Kondo
  
  
  NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,8, //1
  NOTE_G5,4, REST,4, NOTE_G4,8, REST,4, 
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 3
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,
  NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 3
  NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  REST,8, NOTE_E5,4,NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

  // cut short due to dynamic memory limit

  // REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//7
  // REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
  // REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
  // NOTE_C5,2, REST,2,

  // REST,4, NOTE_G5,8, NOTE_FS5,8, NOTE_F5,8, NOTE_DS5,4, NOTE_E5,8,//repeats from 7
  // REST,8, NOTE_GS4,8, NOTE_A4,8, NOTE_C4,8, REST,8, NOTE_A4,8, NOTE_C5,8, NOTE_D5,8,
  // REST,4, NOTE_DS5,4, REST,8, NOTE_D5,-4,
  // NOTE_C5,2, REST,2,

  // NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,//11
  // NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,

  // NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,//13
  // REST,1, 
  // NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4,
  // NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
  // NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
  // NOTE_G5,4, REST,4, NOTE_G4,4, REST,4, 
  // NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // 19
  
  // NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  // NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  // REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

  // NOTE_C5,-4, NOTE_G4,8, REST,4, NOTE_E4,-4, // repeats from 19
  // NOTE_A4,4, NOTE_B4,4, NOTE_AS4,8, NOTE_A4,4,
  // NOTE_G4,-8, NOTE_E5,-8, NOTE_G5,-8, NOTE_A5,4, NOTE_F5,8, NOTE_G5,8,
  // REST,8, NOTE_E5,4, NOTE_C5,8, NOTE_D5,8, NOTE_B4,-4,

  // NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//23
  // NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  // NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
  
  // NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
  // NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  // NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  // NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
  // NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,

  // NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,//repeats from 23
  // NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  // NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
  
  // NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //26
  // NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  // NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  // NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
  // NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
  // NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,8, NOTE_E5,8,
  // REST,1,

  // NOTE_C5,8, NOTE_C5,4, NOTE_C5,8, REST,8, NOTE_C5,8, NOTE_D5,4, //33
  // NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2,
  // NOTE_E5,8, NOTE_E5,8, REST,8, NOTE_E5,8, REST,8, NOTE_C5,8, NOTE_E5,4,
  // NOTE_G5,4, REST,4, NOTE_G4,4, REST,4, 
  // NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  // NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  // NOTE_D5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_A5,-8, NOTE_G5,-8, NOTE_F5,-8,
  
  // NOTE_E5,8, NOTE_C5,4, NOTE_A4,8, NOTE_G4,2, //40
  // NOTE_E5,8, NOTE_C5,4, NOTE_G4,8, REST,4, NOTE_GS4,4,
  // NOTE_A4,8, NOTE_F5,4, NOTE_F5,8, NOTE_A4,2,
  // NOTE_B4,8, NOTE_F5,4, NOTE_F5,8, NOTE_F5,-8, NOTE_E5,-8, NOTE_D5,-8,
  // NOTE_C5,8, NOTE_E4,4, NOTE_E4,8, NOTE_C4,2,
  
  // //game over sound
  NOTE_C5,-4, NOTE_G4,-4, NOTE_E4,4, //45
  NOTE_A4,-8, NOTE_B4,-8, NOTE_A4,-8, NOTE_GS4,-8, NOTE_AS4,-8, NOTE_GS4,-8,
  NOTE_G4,8, NOTE_D4,8, NOTE_E4,-2,  
};

// sizeof gives the number of bytes, each int value is composed of two bytes (16 bits)
// there are two values per note (pitch and duration), so for each note there are four bytes
int notes = sizeof(melody) / sizeof(melody[0]) / 2;

// this calculates the duration of a whole note in ms
int wholenote = (60000 * 4) / tempo;

int currentNote = 0;  // Start at the first note
int divider = 0, noteDuration = 0;

// END OF THE MARIO CODE


// IR REMOTE BUTTONS
#define BUTTON_0 22 // Command for button 0
#define BUTTON_1 12 // Command for button 1
#define BUTTON_2 24
#define BUTTON_3 94
#define BUTTON_4 8
#define BUTTON_5 28
#define BUTTON_6 90
#define BUTTON_7 66
#define BUTTON_8 82
#define BUTTON_9 74

#define REWIND 68
#define POWER 69

// Recipe Structure
struct Recipe {
  const char* name;
  int temperature;
  int humidity;
  unsigned long time;//changed
};

// Time is stored in milliseconds
Recipe recipes[] = {
  // Name, temperature (°C), humidity (%), duration
  {"Boil Eggs", 100, 20, 600000}, // 10 minutes
  {"Oatmeal", 100, 25, 900000}, // 15 minutes
  {"Boil Potatoes", 100, 25, 1200000}, // 20 minutes
  {"Cook Rice", 100, 30, 900000}, // 15 minutes
  {"Boil Pasta", 100, 30, 420000}, // 7 minutes
  {"Boil Shrimp", 100, 50, 300000}, // 5 minutes
  {"Tomato Soup", 100, 45, 1500000}, // 25 minutes
  {"Hot Chocolate", 88, 40, 300000}, // 5 minutes
  {"Jello", 100, 15, 300000}, // 5 minutes
  {"Demo", 25, 40, 10000} // 10 seconds
};

// IR Receiver
#define IR_RECEIVE_PIN 6

// LCD Screen
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Initial start message and marquee variables
String message = "1. Boil Eggs, 2. Oatmeal, 3. Boil Potatoes, 4. Cook Rice, 5. Boil Pasta, 6. Boil Shrimp, 7. Tomato Soup, 8. Hot Chocolate, 9. Jello";//, 0. Demo";
int startMessageIndex = 0;
bool startMessage = true;

// Variables to track selected recipe and temperatures
Recipe selectedRecipe;

bool repeatMenu = false;
int repeatMenuStep = 0;

bool readConditions = false;

// Temperature and humidity sensor
#define DHT11_PIN 7
dht DHT;

// Timer logic: https://forum.arduino.cc/t/making-a-timer/313423
unsigned long previousMillis = 0;
bool startTimer = true;

void setup()
{
  Serial.begin(9600);
  
  // LCD screen is 16 columns by 2 rows
  lcd.begin(16, 2); 

  // For the buzzer output to pin 9
  pinMode(buzzer, OUTPUT);

  IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK); // Start the receiver
}

void loop()
{
  IrReceiver.resume();
  if(startMessage)
  {
    lcd.setCursor(0, 0);
    lcd.print("Select Recipe");
    lcd.setCursor(0, 1);
    lcd.print(message.substring(startMessageIndex, startMessageIndex + 16));
    startMessageIndex++;
    
    // End of string restart
    if (startMessageIndex + 16 > message.length())
    {
      startMessageIndex = 0;
    }
    delay(300); // scrolling speed
  } 
  
  if (IrReceiver.decode() && startMessage)
  {
    switch (IrReceiver.decodedIRData.command)
    {
      case BUTTON_1:
      	selectedRecipe = recipes[0];
        break;
      case BUTTON_2:
       	selectedRecipe = recipes[1];
       	break;
      case BUTTON_3:
       	selectedRecipe = recipes[2];
       	break;
      case BUTTON_4:
       	selectedRecipe = recipes[3];
       	break;
      case BUTTON_5:
       	selectedRecipe = recipes[4];
       	break;
      case BUTTON_6:
       	selectedRecipe = recipes[5];
       	break;
      case BUTTON_7:
       	selectedRecipe = recipes[6];
       	break;
      case BUTTON_8:
       	selectedRecipe = recipes[7];
       	break;
      case BUTTON_9:
       	selectedRecipe = recipes[8];
       	break;
      case BUTTON_0: // this is the demo
       	selectedRecipe = recipes[9];
       	break;
      default:
      	selectedRecipe = {nullptr, 0, 0, 0};
      	break;
    }
    
    if(selectedRecipe.name != nullptr)
    {
      startMessage = false;
      repeatMenu = true;  
    }   
    IrReceiver.resume();
  }
  
  if(repeatMenu)
  {
    // Display the instructions
    repeatMenuStep++;
    lcd.clear();
    char* timeUnit = ""; // this stores the unit seconds, minutes
    unsigned long time = 0; // this stores the time
    
    if(selectedRecipe.time >= 60000)
    {
      timeUnit = "minutes";
      time = selectedRecipe.time / 1000 / 60; // convert milliseconds to minutes
    } else
    {
      timeUnit = "seconds";
      time = selectedRecipe.time / 1000; // convert milliseconds to seconds
    }

    switch(repeatMenuStep)
    {
      case 1:
        lcd.setCursor(0, 0);
        lcd.print("Recipe:");
        lcd.setCursor(0, 1);
        lcd.print(selectedRecipe.name);
      	break;
      case 2:
        lcd.setCursor(0, 0);
        lcd.print("Set Temperature:");
        lcd.setCursor(0, 1);
        lcd.print(selectedRecipe.temperature);
        lcd.print((char)223); // Degree symbol
    	lcd.print("C");
      	break;
      case 3:
        lcd.setCursor(0, 0);
        lcd.print("Set Humidity:");
        lcd.setCursor(0, 1);
        lcd.print(selectedRecipe.humidity);
      	lcd.print("%");
      	break;
      case 4:
        lcd.setCursor(0, 0);
        lcd.print("Total Time:");
        lcd.setCursor(0, 1);
        lcd.print(String(time) + " " + timeUnit);
      	break;
      case 5:
        lcd.setCursor(0, 0);
        lcd.print("Press power");
        lcd.setCursor(0, 1);
        lcd.print("to start!");
      	break;
      case 6:  
        lcd.setCursor(0, 0);
        lcd.print("Press Rewind to");
        lcd.setCursor(0, 1);
        lcd.print("go back!");
      	break;
      case 7:
      	repeatMenuStep = 0;
      	break;
    }
    
    delay(1200); // might need to change how fast
  }
  
  // Checks the conditions
  if (readConditions)
  {
    // Humidity and temperature sensor
    int chk = DHT.read11(DHT11_PIN);
    int temperature = DHT.temperature;
    int humidity = DHT.humidity;

    // Write to LCD Screen
    lcd.setCursor(0, 0); 
    lcd.print("Temp: ");
    lcd.print(temperature);
    lcd.print((char)223); // Degree symbol
    lcd.print("C");
    lcd.setCursor(0, 1);
    lcd.print("Humidity: ");
    lcd.print(humidity);
    lcd.print("%");
    // delay(1000); // Slow down the screen updates

    // Determine if the timer should be started
    if (temperature >= selectedRecipe.temperature && humidity >= selectedRecipe.humidity && startTimer)
    {
      previousMillis = millis(); // update the previous time
      startTimer = false; // only start timer once
      readConditions = false; // Time to run the timer
    }
  }

  // IrReceiver.resume();

  // Timer is started (go ahead and count down)
  if(!startTimer)
  { // No longer need to start time we can check how long the timer has been on
    unsigned long currentMillis = millis();

    // Buzz if over interval
    if (currentMillis - previousMillis >= selectedRecipe.time)
    {
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Done! You");
      lcd.setCursor(0, 1);
      lcd.print("win at cooking");
      // THE FOLLOWING CODE IS FROM:
      /* 
        Super Mario Bros - Overworld theme 
        Connect a piezo buzzer or speaker to pin 11 or select a new pin.
        More songs available at https://github.com/robsoncouto/arduino-songs                                            
                                                    
                                                    Robson Couto, 2019
      */
      for (int thisNote = 0; thisNote < notes; thisNote++)
      {

        // calculates the duration of each note
        divider = melody[thisNote * 2  + 1];
        if (divider > 0) {
          // regular note, just proceed
          noteDuration = (wholenote) / divider;
        } else if (divider < 0) {
          // dotted notes are represented with negative durations!!
          noteDuration = (wholenote) / abs(divider);
          noteDuration *= 1.5; // increases the duration in half for dotted notes
        }

        // we only play the note for 90% of the duration, leaving 10% as a pause
        tone(buzzer, melody[thisNote * 2], noteDuration * 0.9);

        // Wait for the specief duration before playing the next note.
        delay(noteDuration);

        // stop the waveform generation before the next note.
        noTone(buzzer);
      }

      delay(500);

      previousMillis = 0;
      startTimer = true;  // we can start the timer again
      startMessage = true; // restart the loop
      repeatMenu = false;
      readConditions = false;
      selectedRecipe = {nullptr, 0, 0, 0};
      repeatMenuStep = 0; // so the repeat menu will start at the first instruction
      startMessageIndex = 0; // So the start message begins at the start
      lcd.clear();
      IrReceiver.stop();
      delay(10); // Give it a moment to reset
      IrReceiver.begin(IR_RECEIVE_PIN, ENABLE_LED_FEEDBACK);
    }      
  }

  
  // Restart everything and go back to the start menu
  if(!startMessage && IrReceiver.decode())
  {
    // This is the power button
    if(IrReceiver.decodedIRData.command == POWER && repeatMenu && !startMessage)
    {
      readConditions = true;
      repeatMenu = false;
      lcd.clear();
    }
    if(IrReceiver.decodedIRData.command == REWIND && !startMessage)
    {
      Serial.print("Go Back");
      previousMillis = 0;
      startTimer = true;  // we can start the timer again
      startMessage = true; // restart the loop
      repeatMenu = false;
      readConditions = false;
      selectedRecipe = {nullptr, 0, 0, 0};
      repeatMenuStep = 0; // so the repeat menu will start at the first instruction
      startMessageIndex = 0; // So the start message begins at the start
      lcd.clear();
  	}
  }
}

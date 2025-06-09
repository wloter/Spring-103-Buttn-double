#include <Adafruit_CircuitPlayground.h>
#include <AsyncDelay.h>


AsyncDelay delay_1ms;

  const byte lgtbuttn = 4;
  const byte rgtbuttn = 5;
  const byte intPin = 7;
  volatile bool intFlag = false;
  volatile bool imtFlag = false;
  volatile bool switchState = false;
  volatile bool printcondition = true;

  int count = 0;
  int averagescore = 0;
  int taveragescore = 0;
  int tcount = 0;
  int dstore = 0;
  int r = 0;
  int g = 0;
  int b = 0;

  //varaibles identifed for buttons and value storage

void setup() {
  Serial.begin(9600);
  while(!Serial);
  CircuitPlayground.begin();

  pinMode(rgtbuttn, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(rgtbuttn), snap, RISING);
  pinMode(lgtbuttn, INPUT_PULLDOWN);
  attachInterrupt(digitalPinToInterrupt(lgtbuttn), bnap, RISING);

  delay_1ms.start(1, AsyncDelay::MILLIS);
  pinMode(intPin , INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(intPin), wait, CHANGE);

  randomSeed(analogRead(1)); // Seed random with garbage unknown analog reading

  //button parameter setting
}

void loop() {
  

  
  if(switchState == 1){
    printcondition = true;
    Serial.println("STARTING");
    Serial.println("  ");
    Serial.println("  ");
    Serial.println("  ");
    //game starting sequence
    for(int i = 0; i < 5; i++){
      CircuitPlayground.clearPixels();
      int randLED = random(10);
      int randdelay = random(2000);
      //indicates 5 rounds within each play
      if(randLED <= 4){
        delay (randdelay);
        CircuitPlayground.setPixelColor(randLED, 0xFFFFFF);
        CircuitPlayground.playTone(200, 10);
        imtFlag = false;
        while(true) {
          delay_1ms.start(1, AsyncDelay::MILLIS);
          if(delay_1ms.isExpired())  {
            count++;
            //Serial.println(count);
          }
          if(imtFlag) {
            delay(150);
            imtFlag = false;
            break;
            //one button reaction time and cache of speed
          }
        }
      }
      if(randLED > 4 ){
        delay (randdelay);
        CircuitPlayground.setPixelColor(randLED, 0xFFFFFF);
        CircuitPlayground.playTone(200, 10);
        intFlag = false;
        while(true) {
          delay_1ms.start(1, AsyncDelay::MILLIS);
          if(delay_1ms.isExpired())  {
            count++;
            //Serial.println(count);
          }
          if(intFlag) {
            delay(150);
            intFlag = false;
            break;
            //one button reaction time and cache of speed
          }
        }
      }
      intFlag = false;
      imtFlag = false;
      //debounce debug
      }
      while(true) {
        if(imtFlag || intFlag) {
          delay(300);
          count = 0;
          imtFlag = false;
          intFlag = false;
          break;
        }
        for(int i=0; i<10; i++) {
          CircuitPlayground.setPixelColor(i, 255, 255, 255);
          //indicate change with lights all on to show 
        }
        if(printcondition) {
          averagescore = (count)/5;
          Serial.print("Average Score:  ");
          Serial.println(averagescore);
          tcount ++;
          taveragescore = taveragescore + averagescore;
          if (averagescore >= 300){
            r = 235;
            g = 52;
            b = 107;
          }
          if (averagescore <= 200){
            r = 207;
            g = 235;
            b = 52;
          }
          if (averagescore < 300 && averagescore > 200){
            r = 52;
            g = 235;
            b = 180;
          }
          //map values for lights do to reaction time to show if player is fast

          for(int i=0; i<10; i++) {
            CircuitPlayground.setPixelColor(i, r, g, b);
            delay(500);
          }
          printcondition = false;
        }
      }
    }

  else if (switchState == 0){
    CircuitPlayground.clearPixels();
    count = 0;
    intFlag = false;
    imtFlag = false;
    dstore = (taveragescore)/(tcount);
          if (dstore >= 300){
            r = 235;
            g = 52;
            b = 107;
          }
          if (dstore <= 200){
            r = 207;
            g = 235;
            b = 52;
          }
          if (dstore < 300 && dstore > 200){
            r = 52;
            g = 235;
            b = 180;
          }
        if(printcondition == false) {
          Serial.print("Total Average Score:  ");
          Serial.println(dstore);

          printcondition = true;
        }
      for(int i = 0; i < 10; i++){ //makes the choice of the pixel continuous one after the other giving the loading effect
      int randlight = random(10);
      CircuitPlayground.setPixelColor(i, r, g, b);
      delay(50);
      CircuitPlayground.setPixelColor(i, 0x000000);
        }
        //load effect to show total average speed of all plays


    
  }
}


void wait() {
  switchState = digitalRead(intPin);
}

void snap() {
  intFlag = true;
  //Serial.println("INTFLAG CALLED");
}

void bnap() {
  imtFlag = true;
  //Serial.println("IMTFLAG CALLED");
}

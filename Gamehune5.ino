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
}

void loop() {
  

  
  if(switchState == 1){
    printcondition = true;
    Serial.println("STARTING");
    Serial.println("  ");
    Serial.println("  ");
    Serial.println("  ");
    for(int i = 0; i < 5; i++){
      CircuitPlayground.clearPixels();
      int randLED = random(10);
      int randdelay = random(2000);
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
          }
        }
      }
      intFlag = false;
      imtFlag = false;
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
        }
        if(printcondition) {
          averagescore = (count)/5;
          Serial.print("Average Score:  ");
          Serial.println(averagescore);
          printcondition = false;
        }
      }
    }

  else if (switchState == 0){
    CircuitPlayground.clearPixels();
    count = 0;
    intFlag = false;
    imtFlag = false;
    Serial.println("The game is reaction time click the light on the same side after flicking the switch");
    delay(5000);
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

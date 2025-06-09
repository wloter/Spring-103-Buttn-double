# Spring-103-Buttn-double
This code generates a game on the  adafruit circuit express playground board, that allows for the user to test their reaction time. 

This code uses two libaries:
https://github.com/stevemarple/AsyncDelay
https://github.com/adafruit/Adafruit_CircuitPlayground


when the board initiates touch the A1 capitence to random seed the board.
The switch needs to be flicked to get into gamemde, where there will initiate a 5 trial mode.
The board will after delay glow one led on the side of the board.
The button needs to be pressed on the correct side to record the reaction time.
The board will report the reaction time.

Capacitance sensor used on slot one to randomly seed the random number generator used to start reaction time games. Both buttons respond to the leds shining on their half of the board, when pressed, a section of time is noted and the async delay is used to measure the reaction time. When the switch is switched it moves from the main menu to the game mode and initiates the game. When the game happens a light lights up and a sound is played, the reaction time doesn't stop until the button on the right side is pressed. At the end the values of the time are mapped to see the average reaction time of the 5 trials. The main menu will have mapped overall reaction speed, and the end of the game phase will have mapped the average, with corresponding green to red colors, as an indicator of reaction speed.These will range from below 200 from 200-300 and then the rest will be too slow as red.

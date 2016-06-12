/*
  ChanceWheel
*/

#include <Arduboy.h>
#include "H/Snake.h"
#include "H/SnakeDrawer.h"
#include "H/Position.h"

Arduboy arduboy;

#define FRAMES_PER_SECOND 20   // The update and refresh speed

// Sounds
const byte PROGMEM bing [] = {
0x90,0x30, 0,107, 0x80, 0x90,0x60, 1,244, 0x80, 0xf0};
const byte PROGMEM point [] = {
0x90,83, 0,75, 0x80, 0x90,88, 0,225, 0x80, 0xf0};
const byte PROGMEM flap [] = {
0x90,24, 0,125, 0x80, 0xf0};
const byte PROGMEM hit [] = {
0x90,60, 0,31, 0x80, 0x90,61, 0,31, 0x80, 0x90,62, 0,31, 0x80, 0xf0};

#define INIT_SIZE 30
H::Position * pos = new H::Position[INIT_SIZE]() ;
H::Snake * snake = new H::Snake( pos, INIT_SIZE, WIDTH, HEIGHT ) ;

void setup() {
    arduboy.begin();
    arduboy.setFrameRate(FRAMES_PER_SECOND);
    playSound(bing);
    delay(1500);
    arduboy.clear();
    arduboy.setCursor(18,55);
    arduboy.print("Press Any Button");
    arduboy.display();

    while (!arduboy.buttonsState()) { } // Wait for any key press
    debounceButtons();


    // Create snake
    for ( unsigned int i = 0 ; i < INIT_SIZE ; ++i )
    {
        pos[i].x = 5 + i;
        pos[i].y = HEIGHT / 2 ;
    }

    arduboy.initRandomSeed();
    Serial.println("Init end");
}


void loop() {
    if (!arduboy.nextFrame())
        return;

    // Clear screen
    arduboy.clear();

    bool canMove = false ;
    if ( upPressed() )
    {
        Serial.println("UP");
        canMove = snake->up() ;
    }
    else if ( downPressed() )
    {
        Serial.println("DOWN");
        canMove = snake->down() ;
    }
    else if ( rightPressed() )
    {
        Serial.println("RIGHT");
        canMove = snake->right() ;
    }
    else if ( leftPressed() )
    {
        Serial.println("LEFT");
        canMove = snake->left() ;
    }
    else
    {
        canMove = snake->keepGoing() ;
    }

    // Draw snake
    H::SnakeDrawer::Draw( *snake, arduboy ) ;

    // Finally draw this thang
    arduboy.display();
}




boolean aPressed() {
  return (arduboy.buttonsState() & (A_BUTTON)) != 0;
}

boolean bPressed() {
  return (arduboy.buttonsState() & (B_BUTTON)) != 0;
}

boolean upPressed() {
  return (arduboy.buttonsState() & (UP_BUTTON )) != 0;
}

boolean downPressed() {
  return (arduboy.buttonsState() & (DOWN_BUTTON)) != 0;
}

boolean leftPressed() {
  return (arduboy.buttonsState() & (LEFT_BUTTON)) != 0;
}

boolean rightPressed() {
  return (arduboy.buttonsState() & (RIGHT_BUTTON)) != 0;
}

void playSound(const byte *score) {
  stopSound();                        // Stop any currently playing sound
  if (arduboy.audio.enabled()) {      // If sound is on
    arduboy.tunes.playScore(score);   // play the new sound
  }
}

void stopSound() {
  if (arduboy.tunes.playing()) {      // If something is playing
    arduboy.tunes.stopScore();        // stop playing
  }
}

void debounceButtons() { // prevent "noisy" buttons from appearing as multiple presses
  delay(10);
  while (arduboy.buttonsState()) { }  // Wait for all keys released
  delay(10);
}


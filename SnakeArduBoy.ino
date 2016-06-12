/*
  ChanceWheel
*/

#include <Arduboy.h>
#include "H/Snake.h"
#include "H/SnakeDrawer.h"
#include "H/Position.h"

Arduboy arduboy;

#define FRAMES_PER_SECOND 10   // The update and refresh speed
#define INIT_SIZE 3
#define APPLE_PERIOD 50 // Number of frames between apple spawns

// Sounds
const byte PROGMEM bing [] = {
0x90,0x30, 0,107, 0x80, 0x90,0x60, 1,244, 0x80, 0xf0};
const byte PROGMEM point [] = {
0x90,83, 0,75, 0x80, 0x90,88, 0,225, 0x80, 0xf0};
const byte PROGMEM flap [] = {
0x90,24, 0,125, 0x80, 0xf0};
const byte PROGMEM hit [] = {
0x90,60, 0,31, 0x80, 0x90,61, 0,31, 0x80, 0x90,62, 0,31, 0x80, 0xf0};

enum GameState
{
    INIT,
    RUNNING,
    GAME_OVER
} ;

//! Show apple
bool
H::Snake::showApple
(
)
{
    // Look for an empty spot
    m_apple.x = random(1, m_width) ;
    m_apple.y = random(1, m_height) ;
    while( hasBone( m_apple ) )
    {
        m_apple.x = random(1, m_width) ;
        m_apple.y = random(1, m_height) ;
    }
    // Spawn an apple
    m_isApple = true ;
}


void init( H::Snake ** snake )
{
    H::Position * pos[INIT_SIZE] ;

    // Create initial positions
    for ( unsigned int i = 0 ; i < INIT_SIZE ; ++i )
    {
        pos[i]= new H::Position( 3 + i, (HEIGHT - 1)/8 ) ;
    }

    *snake = new H::Snake( pos, INIT_SIZE, (WIDTH - 20)/8, (HEIGHT - 1)/4 ) ;
}

H::Snake * snake = NULL ;

unsigned short frames = 0 ;
GameState gameState = INIT ;
unsigned int score = 0 ;
unsigned int maxScore = 0 ;

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

    init( &snake ) ;

    arduboy.initRandomSeed();

    gameState = RUNNING ;
}


void loop() {
    if (!arduboy.nextFrame())
        return;

    // Increment frame count
    ++frames;

    // Clear screen
    arduboy.clear();

    bool canMove = false ;
    if ( gameState != GAME_OVER )
    {
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
        if ( snake->hasGrown() )
        {
            playSound(point);
            ++score;
            if ( maxScore < score )
            {
                maxScore = score ;
            }
            frames = 0 ;
        }

        if ( ! canMove )
        {
            playSound( flap ) ;
            gameState = GAME_OVER ;
        }
        else
        {
            if ( frames == APPLE_PERIOD - 5 )
            {
                snake->hideApple() ;
            }
            else if ( frames == 1 )
            {
                // Spawn an apple
                snake->showApple() ;
            }
            else if ( frames == APPLE_PERIOD )
            {
                frames = 0 ;
            }
        }
    }
    else
    {
        if ( aPressed() )
        {
            // Reset
            delete snake ;
            score = 0 ;
            init( &snake ) ;
            gameState = RUNNING ;
            frames = 0 ;
        }
    }
    if ( bPressed() )
    {
        if (arduboy.audio.enabled()) {    // If sound is enabled
            stopSound();                    // Stop anything that's playing
            arduboy.audio.off();            // Mute sounds
        } else {
            arduboy.audio.on();             // Enable sound
            playSound(bing);                // Play a sound to indicate sound has been turned on
        }
    }
    // Draw snake
    H::SnakeDrawer::Draw( *snake, arduboy, score, maxScore ) ;

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


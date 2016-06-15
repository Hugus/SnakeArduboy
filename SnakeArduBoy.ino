/*
  ChanceWheel
*/

#include <Arduboy.h>
#include "H/Snake.h"
#include "H/SnakeDrawer.h"
#include "H/Position.h"
#include "assets.h"

Arduboy arduboy ;

#define FRAMES_PER_SECOND 10   // The update and refresh speed
#define INIT_SIZE 3
#define APPLE_PERIOD 50 // Number of frames between apple spawns

// Sounds
const byte PROGMEM bing [] = {
0x90,0x30, 0,107, 0x80, 0x90,0x60, 1,244, 0x80, 0xf0} ;
const byte PROGMEM point [] = {
0x90,83, 0,75, 0x80, 0x90,88, 0,225, 0x80, 0xf0} ;
const byte PROGMEM flap [] = {
0x90,24, 0,125, 0x80, 0xf0} ;
const byte PROGMEM hit [] = {
0x90,60, 0,31, 0x80, 0x90,61, 0,31, 0x80, 0x90,62, 0,31, 0x80, 0xf0} ;

enum GameState
{
    INIT,
    RUNNING,
    GAME_OVER
} ;

//! Show apple
//! Should be implemented in Snake module but Snake has to be independant from
//! Arduboy.
bool
H::Snake::showApple
(
)
{
    // Look for an empty spot
    m_apple.x = random( 1, m_width ) ;
    m_apple.y = random( 1, m_height ) ;
    while( hasBone( m_apple ) )
    {
        m_apple.x = random( 1, m_width ) ;
        m_apple.y = random( 1, m_height ) ;
    }
    // Spawn an apple
    m_isApple = true ;
}

//! Allocate and init snake
void init( H::Snake ** snake )
{
    H::Position * pos[INIT_SIZE] ;

    // Create initial positions
    for ( unsigned int i = 0 ; i < INIT_SIZE ; ++i )
    {
        pos[i]= new H::Position( 3 + i, ( HEIGHT - 1 )/8 ) ;
    }

    *snake = new H::Snake( pos, INIT_SIZE, ( WIDTH - 20 )/8, ( HEIGHT - 1 )/4 ) ;
}

H::Snake * snake = NULL ;

//! Game state variables, should be encapsulated in a class
unsigned short frames = 0 ;
GameState gameState = INIT ;
unsigned int score = 0 ;
unsigned int maxScore = 0 ;
bool black = true ;

void setup() {
    arduboy.begin() ;
    arduboy.setFrameRate( FRAMES_PER_SECOND ) ;
    playSound( bing ) ;
    delay( 1500 ) ;

    init( &snake ) ;
}


void loop() {
    if ( !arduboy.nextFrame() )
        return ;

    // Wait for any key press
    if ( gameState == INIT )
    {
        arduboy.clear() ;
        if ( black )
        {
            arduboy.drawBitmap(0,0,snake_black,128,64,WHITE);
        }
        else
        {
            arduboy.drawBitmap(0,0,snake_white,128,64,WHITE);
        }
        black = !black ;
        Serial.println(black) ;
        arduboy.display() ;
        delay( 100 ) ;
        if ( aPressed() )
        {
            gameState = RUNNING ;
            arduboy.initRandomSeed() ;
        }
        else
        {
            return ;
        }
    }

    // Increment frame count
    ++frames ;

    // Clear screen
    arduboy.clear() ;

    bool canMove = false ;
    // If game running
    if ( gameState != GAME_OVER )
    {
        if ( upPressed() )
        {
            canMove = snake->up() ;
        }
        else if ( downPressed() )
        {
            canMove = snake->down() ;
        }
        else if ( rightPressed() )
        {
            canMove = snake->right() ;
        }
        else if ( leftPressed() )
        {
            canMove = snake->left() ;
        }
        else
        {
            canMove = snake->keepGoing() ;
        }
        // If snake has just eaten an apple
        if ( snake->hasGrown() )
        {
            playSound( point ) ;
            ++score ;
            if ( maxScore < score )
            {
                maxScore = score ;
            }
            frames = 0 ;
        }

        // Snake cannot move, game over
        if ( ! canMove )
        {
            playSound( flap ) ;
            gameState = GAME_OVER ;
        }
        else
        {
            // Apple is rotten, hide it
            if ( frames == APPLE_PERIOD - 5 )
            {
                snake->hideApple() ;
            }
            // Time for another apple
            else if ( frames == 1 )
            {
                // Spawn an apple
                snake->showApple() ;
            }
            // Re-init apple cycle
            else if ( frames == APPLE_PERIOD )
            {
                frames = 0 ;
            }
        }
    }
    else
    {
        // In game over state, A button re-init game
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
    // B button toggle sound
    if ( bPressed() )
    {
        toggleSound() ;
    }
    // Draw snake
    H::SnakeDrawer::Draw( *snake, arduboy, score, maxScore ) ;

    // Display screen
    arduboy.display() ;
}

boolean aPressed() {
  return ( arduboy.buttonsState() & ( A_BUTTON ) ) != 0 ;
}

boolean bPressed() {
  return ( arduboy.buttonsState() & ( B_BUTTON ) ) != 0 ;
}

boolean upPressed() {
  return ( arduboy.buttonsState() & ( UP_BUTTON ) ) != 0 ;
}

boolean downPressed() {
  return ( arduboy.buttonsState() & ( DOWN_BUTTON ) ) != 0 ;
}

boolean leftPressed() {
  return ( arduboy.buttonsState() & ( LEFT_BUTTON ) ) != 0 ;
}

boolean rightPressed() {
  return ( arduboy.buttonsState() & ( RIGHT_BUTTON ) ) != 0 ;
}

void playSound( const byte *score ) {
    // Stop any currently playing sound
    stopSound() ;
    // If sound is on
    if ( arduboy.audio.enabled() ) {
        // play the new sound
        arduboy.tunes.playScore( score ) ;
    }
}

void stopSound() {
    // If something is playing
    if ( arduboy.tunes.playing() ) {
        // stop playing
        arduboy.tunes.stopScore() ;
    }
}

void toggleSound() {
    // If sound is enabled
    if ( arduboy.audio.enabled() )
    {
        // Stop anything that's playing
        stopSound() ;
        // Mute sounds
        arduboy.audio.off() ;
    } else {
        // Enable sound
        arduboy.audio.on() ;
        // Play a sound to indicate sound has been turned on
        playSound( bing ) ;
    }
}

// Prevent "noisy" buttons from appearing as multiple presses
void debounceButtons() {
    delay( 10 ) ;
    // Wait for all keys released
    while ( arduboy.buttonsState() ) { }
    delay( 10 ) ;
}


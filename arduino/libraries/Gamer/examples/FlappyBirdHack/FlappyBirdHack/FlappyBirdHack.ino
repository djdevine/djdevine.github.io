#include <Gamer.h>

Gamer gamer;

// General
int score; boolean isPlaying;


// Wall - related
int wallThickness = 2;
int gapSize = 2;
int currentWallPosition;
int gapPosition;


// Bird - related
int flyingSpeed = 150;
int birdX = 2;
int birdY;
int gravity = 1;


//splashscreenstart
byte splashScreen[8] = {
  B11101110,
  B10001001,
  B10001001,
  B11101111,
  B10001001,
  B10001001,
  B10001110,
  B00000000
};


//splashscreenend
void setup() {
  gamer.begin();
  randomSeed(gamer.ldrValue());
}


void loop() {

  if (isPlaying) {
    gamer.clear();
    moveWall();
    drawWall();
    updateBird();
    detectCollision();
    recordScore();
    drawBird();
    gamer.updateDisplay();
    delay(flyingSpeed);

  } else {
    showSplashScreen();
  }


}
/* --------------------------------------------------------------- Updates the bird's position. If you press UP, it will move up. Otherwise, gravity will bring it down :) */
void updateBird() {

  /* If the UP button is pressed, move the bird up. Otherwise, move it down with gravity. Remember, the X axis' 0 is on the top of the screen. Therefore, when we move the bird up, we REDUCE birdY. When gravity brings it down, away from the axis' origin, we INCREASE birdY. */
  if (gamer.isPressed(UP)) {
    birdY = birdY - 1;
  }
  else {
    birdY = birdY + gravity;
  }

  // Detect if the bird is on the floor.
  if (birdY == 7) gameOver();
}


/* --------------------------------------------------------------- Draws the bird. Wherever it might be! */
void drawBird() {
  birdY = constrain(birdY, 0, 7);
  gamer.display[birdX][birdY] = 1;
}


/* --------------------------------------------------------------- Moves the walls from right to left on the screen, with a constant speed. */
void moveWall() {

  // If the wall is at the end of the screen, get a new wall going!
  if (currentWallPosition == 0 - wallThickness) {
    generateWall();
  }

  // Otherwise, move the wall.
  else {
    currentWallPosition = currentWallPosition - 1;
  }
}


/* --------------------------------------------------------------- Places a new wall on the edge of the screen, ready to be moved. */
void generateWall() {
  currentWallPosition = 8;
  gapPosition = random(1, 7 - gapSize);
}


/* --------------------------------------------------------------- Draws the walls at their current position */
void drawWall() {
  
  // Draw multiple walls, if we need to.
  for(int j=0; j<wallThickness; j++) {
    
    if(currentWallPosition+j >= 0 && currentWallPosition+j <= 7) {
      for(int i=0; i<8; i++) {
        
        // Draw the wall, but miss out the gap. 
        if(i > gapPosition + gapSize - 1 || i < gapPosition) {
          gamer.display[currentWallPosition+j][i] = 1;
        }
      }
    }
  }
}



void detectCollision() {
  if (gamer.display[birdX][birdY] == 1) {
    gameOver();
  }
}


void recordScore() {
  if (birdX > currentWallPosition + wallThickness) {
    score++;
  }
}


void showSplashScreen() {
  if (gamer.isPressed(START)) {
    isPlaying = true;
    generateWall();
    birdY = 2;
    score = 0;
  } else {
    gamer.printImage(splashScreen);
  }
}


void gameOver() {
  gamer.printString("Game over");
  delay(100);
  gamer.printString("Score");
  delay(500);
  gamer.showScore(score);
  delay(500);
  isPlaying = false;
}




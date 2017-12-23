
/**
 * This library is used for Sonar sensor
 */
#include <NewPing.h>


/**
 * Sonar sensor Pins
 */
#define TRIGGER_PIN  35
#define ECHO_PIN     34
#define MAX_DISTANCE 200


/**
 * Game charecters
 */
#define PLAYER  1
#define ENEMY  2
#define P_BULLET  3
#define E_BULLET  4

/**
 * Sonar works !!
 */
NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE);

/**
 * To keep track sonar
 */
int prevSonar=0;
int curSonar=0;




/**
 * This is array is used to keep track of the 
 * Objects in the Game
 * For example:
 * Player, Eenemy, bullet, etc.
 * object[x][0] == row number;
 * objects[x][1] == column; 
 * objects[x][2] == type;
 */
int objects[500][3]; 

/**
 * To keep track of # of objects
 */
int totalObjects=0 ;

int enemyPositionRow[500];

int enemyRowDist = 5;
int ENEMYDELAY = 5;
int LIFEP1 = 4;
int LIFEP2 = 4;
int numberOfPlayers = 1;
int deathP1 = 0;
int deathP2 = 0;
int score = 0;

void initializeVars() {
  enemyRowDist = 5;
  ENEMYDELAY = 5;
  LIFEP1 = 4;
  LIFEP2 = 4;
  numberOfPlayers = 1;
  deathP1 = 0;
  deathP2 = 0;
  score = 0;
}



/**
 * This is for dubug or calibration purposes
 */
void sonarSensor() {
  Serial.print("Ping: ");
  Serial.print(sonar.ping_cm());
  Serial.println("cm");
  //delay(300);
}

/**
 * Led Matrix
 * rows are the anodes
 * cols are the cathodes
 * So if you want to turn on the rows
 * use HIGH or 5V
 * to turn on the columns use 0V or LOW
 */


// 1-dimensional array of row pin numbers of Arduino
const int row[16] = {
  38, 39, 40, 41, 
  42, 43, 44, 45, 
  46, 47, 48, 49, 
  50, 51, 52, 53
};



// 1-dimensional array of column pin numbers: for GREEN
const int col[4] = {
  22, 23, 24, 25
};

/**
 * These are the enablers of the 
 * decoder which sends signal to the 
 * Green leds
 */
const int en0 = 26;
const int en1 = 27;


// 1-dimensional array of column pin numbers: for RED
const int col2[4] = {
  28, 29, 30, 31
};

/**
 * These are the enablers of the 
 * decoder which sends signal to the 
 * RED leds
 */
const int en20 = 32;
const int en21 = 33;


/**
 * Direction
 */
const int LEFT = 100;
const int RIGHT = 200;
const int UP=201;
const int DOWN=202;

/**
 * for gameState 
 */
const int RED=1;
const int GREEN=2;
const int BLANK=0;

const int buzzer = 9;




//// cursor position:
//int x = 5;
//int y = 5;
//int playerPositionX = 7;



/**
 * This is the most important array
 * This gets printed into the 
 * led matrix time to time
 */
int gameState[16][16]; 
// this is our main gamestate here we will store pixel color info: 
/// 0=Blank ,1 = Red , 2= Green;


/**
 * For initializtion 
 */
void initMatrix() {
  for(int i=0; i<16; i++) {
    for(int j=0; j<16; j++) {
      gameState[i][j] = 0;
    }
  }
}


int THREE[16][16] = 
{ {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};


int TWO[16][16] = 
{ {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};


int TWORIGHT[16][16] = 
{ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 1, 1, 1},

};

int TWOLEFT[16][16] = 
{ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, },
  {0, 1, 1, 1, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, },

};
int ONE[16][16] = 
{ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int ONELEFT[16][16] = 
{ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

int ONERIGHT[16][16] = 
{ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
};

int ZERO[16][16] = 
{ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
};


int ZEROLEFT[16][16] = 
{ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0, 1, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 1, 1, 1, 0},
};


int ZERORIGHT[16][16] = 
{ {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 0, 0, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
  {0, 1, 1, 1, 1, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
};



const int startGameDelay = 0;
const int countDownDelay = 500;

void startGameScreen() {
  for(int i=0; i<16; i++) {
    for(int j=0; j<16; j++) {
      gameState[i][j] = GREEN;
    }
    writeGame();
    delay(startGameDelay);
  }
  for(int i=0; i<16; i++) {
    for(int j=0; j<16; j++) {
      gameState[i][j] = RED;
    }
    writeGame();
    delay(startGameDelay);
  }

  displayCountDown(THREE);
  delay(countDownDelay);
  displayCountDown(TWO);
  delay(countDownDelay);
  displayCountDown(ONE);
  delay(countDownDelay);
  displayCountDown(ZERO);
  delay(countDownDelay);
}


void showLife() {
  if(LIFEP1 - deathP1 == 0) {
     displayCountDown(ZERO);
  }
  if(LIFEP1 - deathP1 == 1) {
     displayCountDown(ONE);
  }
  if(LIFEP1 - deathP1 == 2) {
     displayCountDown(TWO);
  }
  if(LIFEP1 - deathP1 == 3) {
     displayCountDown(THREE);
  }
  delay(countDownDelay);
  
}


void displayCountDown(int x[16][16]) {
  /**
   * Disable Green
   */
  digitalWrite(en0, HIGH);
  digitalWrite(en1, HIGH);
  /*
   * Enable RED
   */
  digitalWrite(en20, LOW);
  digitalWrite(en21, LOW);


  /**
   * d = mili s delay
   * md = micro s delay
   */
  float d=0;
  unsigned int md  = 500;

  
  for(int totalIt=0;totalIt<30;totalIt++){
   
    /// red part: enabling
    /**
     * Disable Green
     */
     digitalWrite(en0, HIGH);
    digitalWrite(en1, HIGH);
    /*
     * Enable RED
     */
    digitalWrite(en20, LOW);
    digitalWrite(en21, LOW);
  
    /**
     * Column wise muliplexing
     */
    for(int c=0; c<16; c++) {
      for(int r=0; r<16; r++) {
  
        /**
         * Decoder takes input as 4 bit
         * binary number
         */
        for(int b=0; b<4; b++) {
          int var1 = (c>>b) & 1;
          digitalWrite(col2[b], var1); //col2 == RED
          //digitalWrite(col[b], var1);  //col == GREEN
        }
  
        if(x[r][c] == 1 ) {
          digitalWrite(row[r], HIGH);
          delayMicroseconds(md); 
          //delay(d);
          digitalWrite(row[r], LOW);
        }   
      }
    }
  



    /// green part: enabling
    /*
     * Enable GREEN
     */
     digitalWrite(en0, LOW);
    digitalWrite(en1, LOW);
    /*
     * Disable RED
     */
    digitalWrite(en20, HIGH);
    digitalWrite(en21, HIGH);
    
    for(int c=0; c<16; c++) {
      for(int r=0; r<16; r++) {
        
        for(int b=0; b<4; b++) {
        int  var1 = (c>>b) & 1;
  //        digitalWrite(col2[b], var1); //col2 == RED
          digitalWrite(col[b], var1);  //col == GREEN
        }
  
        if(x[r][c] == 1) {
          digitalWrite(row[r], HIGH);
          delayMicroseconds(md); 
          //delay(d);
          digitalWrite(row[r], LOW);
        }   
      }
    }
 
}

  /**
   * Disable All
   */
  digitalWrite(en0, HIGH);
  digitalWrite(en1,  HIGH);
  digitalWrite(en20,  HIGH);
  digitalWrite(en21,  HIGH);

}




/**
 * Initialize the objects
 */
void initObjects(){
  /**
   * Set co-ordinate of the player
   * We don't want to play a game
   * without a payer. :p
   */
  objects[0][0]=14;
  objects[0][1]=7;
  objects[0][2]=PLAYER;

  /**
   * We need a purpose to live
   * The player's purpose is to kill
   * enemies. 
   * Let's create enemies
   */
  objects[1][0]=0;
  objects[1][1]=7;
  objects[1][2]=ENEMY;

  /**
   * wow !!!
   * We have already created 2 objects
   */
  totalObjects=2;


  for(int i=0; i<500; i++) {
    enemyPositionRow[i] = 0;
  }
  
}


void test(){
  for(int i=0;i<16;i++){
    gameState[i][i]=1;
    gameState[i][15-i]=2;
  }
}



void setup() {
  
//digitalWrite(buzzer, HIGH);
  /**
   * For DEBUG !!!
   */
  Serial.begin(9600);
  
  // put your setup code here, to run once:
  // initialize the I/O pins as outputs iterate over the pins:


  
  initMatrix();
  initObjects();
  initializeVars();

  /*
   * Configure row pins as digital output pins
   */
  for(int rowPin = 0; rowPin <16; rowPin++) {
    pinMode(row[rowPin], OUTPUT);
  }

  for(int rowPin = 0; rowPin <16; rowPin++) {
    digitalWrite(row[rowPin], LOW);
  }

  /*
   * Configure col pins as digital output pins
   */
  for(int colPin=0; colPin<4; colPin++) {
    pinMode(col[colPin], OUTPUT);
    pinMode(col2[colPin], OUTPUT);
  }

  for(int colPin=0; colPin<4; colPin++) {
    digitalWrite(col[colPin], LOW);
    digitalWrite(col2[colPin], LOW);
  }

  /**
   * Disable Decoders
   */
  pinMode(en0, OUTPUT);
  pinMode(en1, OUTPUT);
  digitalWrite(en0, HIGH);
  digitalWrite(en1, HIGH);

  pinMode(en20, OUTPUT);
  pinMode(en21, OUTPUT);
  digitalWrite(en20, HIGH);
  digitalWrite(en21, HIGH);

  pinMode(buzzer, OUTPUT);

  prevSonar = sonar.ping_cm();

  startGameScreen() ;
  initMatrix();
}





/**
  -----*---
  ----***--
 */
void drawPlayer(int row,int column,int color){
  gameState[row][column]=gameState[row][column+2]=BLANK;
  gameState[row][column+1]=gameState[row+1][column]=gameState[row+1][column+1]=gameState[row+1][column+2]=color;
}

/**
  -----***---
  -----*-*---
 */
void drawEnemy(int row,int column,int color) {
  gameState[row+1][column]=gameState[row+1][column+2]=BLANK;
  gameState[row][column]=gameState[row][column+1]=gameState[row][column+2]=gameState[row+1][column]=gameState[row+1][column+2]=color;
}



void drawBullet(int row,int column,int color)
{
  gameState[row][column]=color;
  
}

int getSonarPosition() {


  int s = sonar.ping_cm();
  Serial.println(s);
  int scounter=0;

  while(scounter++ <= 3) {
    Serial.println(s);
    if( s != sonar.ping_cm() ) return -1;
  }

  if(s == 0) {
    return -1;
  }
  
  return (s-3)/2;
}







boolean flexSensor() {
  float flex;
  flex = analogRead(A0)*5/1023.0;
  Serial.println(flex);
  
  if(flex<=1.0) {
    Serial.println("Shoot");
    
    return true;
  }
  
  flex = 2;
  return false ;
}

/**
 * This is more like setPlayer
 * I don't who the hell wrote this one
 */
void movePlayer(int x)
{
  /**
   * Actually x comes from sonar
   * if the sonar doesn't get any stable
   * feebdack, it will return -1
   * So we have to ignore it
   */
  if(x==-1)return;

  /**
   * Search for the player in the 
   * object array
   * if found, set the player position
   * otherwise dead !! :(
   */
  for(int i=0;i<totalObjects;i++){
    if(objects[i][2]==PLAYER && x<14){
      objects[i][1]=x;
      break;
    }
  }
  
}



/**
 * This name seems right
 */
void moveEnemy(int dir){
  /**
   * Search for the enemy
   */
  for(int i=0;i<totalObjects;i++)
  {

    /**
     * [][1] == col
     */
    if(objects[i][2]==ENEMY)
    {
      if(dir==LEFT){
        if(objects[i][1]>0){
          objects[i][1]--;
        }
      }
      
      else if(dir==RIGHT){
        if(objects[i][1]<13){
          objects[i][1]++;
        }
      }
      /**
       * [][0] == row
       */
      else if(dir==UP)
      {
        if(objects[i][0]>0){
          objects[i][0]--;
        }
      }
      else if(dir==DOWN)
      {
        if(objects[i][0]<14){
          objects[i][0]++;
        }
      }
    }
  }
}



void moveEnemy() {
  static long hardness = 0;
  /**
   * Search for the enemy
   */
  for(int i=0;i<totalObjects;i++)
  {

    /**
     * [][1] == col
     */
    if(objects[i][2]==ENEMY)
    {
      enemyPositionRow[i]++;
      if(enemyPositionRow[i]>=ENEMYDELAY) {
        enemyPositionRow[i] = 0;
        objects[i][0]++;
        if(objects[i][0] >= 15){
          removeObject(i);
          //delay(50);
        }
      }
    }
  }

  hardness++;
  if(hardness >100) {
    ENEMYDELAY--;
    hardness=0;
  }
}


int enemyInBetweenMinDistance() {
  int dis = 1000;
  for(int i=0;i<totalObjects;i++) {

    /**
     * [][1] == col
     */
    if(objects[i][2]==ENEMY) {
      dis = min(objects[i][0], dis); 
    }
   }
   return dis;
}


void createEnemy() {
  int enemyCount = 0;
    /**
   * We need a purpose to live
   * The player's purpose is to kill
   * enemies. 
   * Let's create enemies
   */
   for(int i=0;i<totalObjects;i++) {

    /**
     * [][1] == col
     */
    if(objects[i][2]==ENEMY) { 
      enemyCount++;
    }
   }

   if(enemyCount < 3 && enemyInBetweenMinDistance()>=enemyRowDist) {
    //delay(10);
    objects[totalObjects][0]=0;
    objects[totalObjects][1]=random(0, 14);
    objects[totalObjects][2]=ENEMY;
    totalObjects++;
   }
  
  
}



void checkSonar(){
  movePlayer(getSonarPosition());
}


int getPlayerBulletPosition(){
  /**
   * The bullet should be crated at 
   * top of the player mid position
   * So search for the player
   */
  for(int i=0;i<totalObjects;i++) {
    
    if(objects[i][2]==PLAYER) {
      /**
       * why +1 ?
       * Because you know .... :p
       */
      return objects[i][1]+1;
    }
  }
}




static int sound=0;
void checkFlex(){

  /**
   * bn mean bulletNumber
   */
  int bn=0;
  
  for(int i=0; i<totalObjects; i++) {
    if(objects[totalObjects][2]==P_BULLET) bn++;
  }
  /**
   * Don't create more than 5 bullets at a time
   * But pratically it doesn't create more than
   * 3 bullets 
   */
  if(bn>=5) {
    return;
  }
  /**
   * Add logic of
   * if(Player == dead) no bullet;
   */
   if(deathP1 == LIFEP1) {
    return ;
   }


   

  
  if(flexSensor()==true)
  {
    /// adding a new Player Bullet;
    digitalWrite(buzzer,HIGH);
      
    
    /**
     * 13 is the index of row
     * from where the bullet is created
     */
    objects[totalObjects][0]=13;
    objects[totalObjects][1]=getPlayerBulletPosition();
    objects[totalObjects][2]=P_BULLET;
    totalObjects++;
    delay(10);
    digitalWrite(buzzer,LOW);
    
  }
}







/**
 * Take input from the sensors
 */
void checkSensors(){
  checkSonar();
  checkFlex();
}



void writeGame() {

  /**
   * Disable Green
   */
  digitalWrite(en0, HIGH);
  digitalWrite(en1, HIGH);
  /*
   * Enable RED
   */
  digitalWrite(en20, LOW);
  digitalWrite(en21, LOW);


  /**
   * d = mili s delay
   * md = micro s delay
   */
  float d=0;
  unsigned int md  = 500;

  
  for(int totalIt=0;totalIt<3;totalIt++){
   
    /// red part: enabling
    /**
     * Disable Green
     */
     digitalWrite(en0, HIGH);
    digitalWrite(en1, HIGH);
    /*
     * Enable RED
     */
    digitalWrite(en20, LOW);
    digitalWrite(en21, LOW);
  
    /**
     * Column wise muliplexing
     */
    for(int c=0; c<16; c++) {
      for(int r=0; r<16; r++) {
  
        /**
         * Decoder takes input as 4 bit
         * binary number
         */
        for(int b=0; b<4; b++) {
          int var1 = (c>>b) & 1;
          digitalWrite(col2[b], var1); //col2 == RED
          //digitalWrite(col[b], var1);  //col == GREEN
        }
  
        if(gameState[r][c] == RED ) {
          digitalWrite(row[r], HIGH);
          delayMicroseconds(md); 
          //delay(d);
          digitalWrite(row[r], LOW);
        }   
      }
    }
  



    /// green part: enabling
    /*
     * Enable GREEN
     */
     digitalWrite(en0, LOW);
    digitalWrite(en1, LOW);
    /*
     * Disable RED
     */
    digitalWrite(en20, HIGH);
    digitalWrite(en21, HIGH);
    
    for(int c=0; c<16; c++) {
      for(int r=0; r<16; r++) {
        
        for(int b=0; b<4; b++) {
        int  var1 = (c>>b) & 1;
  //        digitalWrite(col2[b], var1); //col2 == RED
          digitalWrite(col[b], var1);  //col == GREEN
        }
  
        if(gameState[r][c] == GREEN) {
          digitalWrite(row[r], HIGH);
          delayMicroseconds(md); 
          //delay(d);
          digitalWrite(row[r], LOW);
        }   
      }
    }
 
}

  /**
   * Disable All
   */
  digitalWrite(en0, HIGH);
  digitalWrite(en1,  HIGH);
  digitalWrite(en20,  HIGH);
  digitalWrite(en21,  HIGH);


}



/**
 * if bullet goes out of the screen
 * if enemy is killed
 * or if player dies
 * Remove them from the game
 * id = ??
 */
void removeObject(int id){
  totalObjects--;
  if(objects[id][2] == ENEMY) {
    enemyPositionRow[id] = 0;
  }
  for(int i=id;i<totalObjects;i++)
  {
    objects[i][0]=objects[i+1][0];
    objects[i][1]=objects[i+1][1];
    objects[i][2]=objects[i+1][2];
  }
}


/**
 * Actually this means draw objects on the board
 */
void drawObjects()
{
  for(int i=0;i<totalObjects;i++)
  {
    collisionDetection(i);
    /**
     * Just pass the starting co-ordinate of the player
     * the drawplayer will do the rest
     */
    if(objects[i][2]==PLAYER) {
      drawPlayer(objects[i][0],objects[i][1],GREEN);
    }
    else if(objects[i][2]==ENEMY) {
      drawEnemy(objects[i][0],objects[i][1],RED);
    }
    else if(objects[i][2]==P_BULLET){
      
     
      drawBullet(objects[i][0],objects[i][1],GREEN);
      /**
       * Check the bullet is out of the 
       * screen or not
       * Player bullet goes up
       * row--
       */
      if(objects[i][0]>0) {
        objects[i][0]--;
      }
      else {
        removeObject(i);
      }
    }
    else if(objects[i][2]==E_BULLET) {
      drawBullet(objects[i][0],objects[i][1],RED);
      /**
       * enemy bullet goes down
       * row++
       */
      if(objects[i][0]<15) {
        objects[i][0]++;
      }
      else {
        removeObject(i);
      }
    }
  }
}


void enemyMotion() {
  
}
int horizontal=0;
int dir=LEFT;



void animateEnemy(){
  
//  static int vertical=0;
Serial.println("This");
Serial.println(horizontal);
Serial.println(dir);
  
  horizontal++;
//  vertical++;

  /**
   * if the enemy reaches the right side
   */
  if(horizontal%15==0)
  {
    if(dir==LEFT) {
      dir=RIGHT;
    }
    else if(dir==RIGHT) {
      dir=LEFT;
    }
    moveEnemy(DOWN);
    horizontal=0;
  }
  moveEnemy(dir);
 
}




boolean collidePointWithRect(int pr,int pc,int rr,int rc) {
  if(pr>=rr && pr<=rr+1 && pc>=rc && pc<=rc+2) {
    return true;
  }
  return false ;
}




boolean collideRectWithRect(int r1,int c1,int r2,int c2){
  return collidePointWithRect(r1,c1,r2,c2) || collidePointWithRect(r2,c2,r1,c1);
}





void collisionDetection(int id){
  if(objects[id][2]==P_BULLET){  // if it is a bullet from players
    for(int i=0;i<totalObjects;i++){
      if(i==id)continue;
      if(objects[i][2]==ENEMY)
      {
         /// collide bullet and enemy then remove them all and get points
        if(collidePointWithRect(objects[id][0],objects[id][1],objects[i][0],objects[i][1])){ 
          removeObject(i);
          removeObject(id);
          score++;
          //return;
        }
      }
    }
  }
  else if(objects[id][2]==PLAYER){
    for(int i=0;i<totalObjects;i++){
      if(i==id)continue;
      if(objects[i][2]==ENEMY)
      {
        /// collide player and enemy then remove player and game over
        if(collideRectWithRect(objects[id][0],objects[id][1],objects[i][0],objects[i][1])){  
          removeObject(i);
          deathP1++;
          if(deathP1 == LIFEP1) {
            removeObject(id);
          }
          showLife();
          //return;
        }
      }
    }
  }
}


void checkEndGame() {
  if(LIFEP1 == deathP1) {
    setup();
  }
}


void loop() {
//
  //animateEnemy();
  checkEndGame();
  moveEnemy();
  createEnemy();
  checkSensors();  /// get input from sensors and update matrix
  initMatrix();
  drawObjects();
  writeGame();     /// print the matrix to the display


  //startGameScreen() ;
}
#define PIN_ROW1 2
#define PIN_ROW2 3
#define PIN_ROW3 4
#define PIN_ROW4 5
#define PIN_ROW5 17
#define PIN_ROW6 16
#define PIN_ROW7 15
#define PIN_ROW8 14

#define PIN_COL1 6
#define PIN_COL2 7
#define PIN_COL3 8
#define PIN_COL4 9
#define PIN_COL5 10
#define PIN_COL6 11
#define PIN_COL7 12
#define PIN_COL8 13

#define PIN_INPUT_LEFT 18
#define PIN_INPUT_RIGHT 19

#define MAX_BODY_LENGTH 12
#define GAME_AREA_WIDTH 8
#define GAME_AREA_HEIGHT 8
#define GAME_OVER_TIME 3000

#define DIRECTION_UP 0
#define DIRECTION_RIGHT 1
#define DIRECTION_DOWN 2
#define DIRECTION_LEFT 3

typedef struct p
{
  int x;
  int y;
} Position;

Position body[MAX_BODY_LENGTH];
int lastInput;
int head;
int tail;
int bodyLength;
int direction;
Position food;
int gameover;
int score;
int elapsedTime;
bool readInput;
unsigned long previousTime;


void setPixel(int row, int column)
{
  digitalWrite(PIN_ROW1, LOW);
  digitalWrite(PIN_ROW2, LOW);
  digitalWrite(PIN_ROW3, LOW);
  digitalWrite(PIN_ROW4, LOW);
  digitalWrite(PIN_ROW5, LOW);
  digitalWrite(PIN_ROW6, LOW);
  digitalWrite(PIN_ROW7, LOW);
  digitalWrite(PIN_ROW8, LOW);
  digitalWrite(PIN_COL1, HIGH);
  digitalWrite(PIN_COL2, HIGH);
  digitalWrite(PIN_COL3, HIGH);
  digitalWrite(PIN_COL4, HIGH);
  digitalWrite(PIN_COL5, HIGH);
  digitalWrite(PIN_COL6, HIGH);
  digitalWrite(PIN_COL7, HIGH);
  digitalWrite(PIN_COL8, HIGH);
  
    switch(column)
    {
      case 0: digitalWrite(PIN_COL1, LOW); break;
      case 1: digitalWrite(PIN_COL2, LOW); break;
      case 2: digitalWrite(PIN_COL3, LOW); break;
      case 3: digitalWrite(PIN_COL4, LOW); break;
      case 4: digitalWrite(PIN_COL5, LOW); break;
      case 5: digitalWrite(PIN_COL6, LOW); break;
      case 6: digitalWrite(PIN_COL7, LOW); break;
      case 7: digitalWrite(PIN_COL8, LOW); break;
      default: break;
    }

    switch(row)
    {
      case 0: digitalWrite(PIN_ROW1, HIGH); break;
      case 1: digitalWrite(PIN_ROW2, HIGH); break;
      case 2: digitalWrite(PIN_ROW3, HIGH); break;
      case 3: digitalWrite(PIN_ROW4, HIGH); break;
      case 4: digitalWrite(PIN_ROW5, HIGH); break;
      case 5: digitalWrite(PIN_ROW6, HIGH); break;
      case 6: digitalWrite(PIN_ROW7, HIGH); break;
      case 7: digitalWrite(PIN_ROW8, HIGH); break;
      default: break;
   }
}

bool foodPositionIsValid()
{
  if (food.x < 0 || food.y < 0) return false;

  for (int i = tail; i <= (head > tail ? head : MAX_BODY_LENGTH - 1); i++)
  {
    if (body[i].x == food.x && body[i].y == food.y) return false;
  }

  if (head < tail)
  {
    for (int i = 0; i <= head; i++)
    {
      if (body[i].x == food.x && body[i].y == food.y) return false;
    }
  }
  return true;
}

void checkGameover()
{
  for (int i = tail; i <= (head > tail ? head - 1 : MAX_BODY_LENGTH - 1); i++)
  {
    if (body[head].x == body[i].x && body[head].y == body[i].y)
    {
      gameover = GAME_OVER_TIME;
        return;
    }
  }

  if (head < tail)
  {
    for (int i = 0; i < head; i++)
    {
      if (body[head].x == body[i].x && body[head].y == body[i].y)
      {
        gameover = GAME_OVER_TIME;
        return;
      }
    }
  }
}

void spawnFood()
{
  while (!foodPositionIsValid())
    food = { random(GAME_AREA_WIDTH), random(GAME_AREA_HEIGHT) };
}


void draw()
{
  for (int i = tail; i <= (head > tail ? head : MAX_BODY_LENGTH - 1); i++)
  {
    setPixel(body[i].x, body[i].y);
  }
  if (head < tail)
  {
    for (int i = 0; i <= head; i++)
    {
      setPixel(body[i].x, body[i].y);
    }
  }
  setPixel(food.x, food.y);
}

void move()
{
  tail = tail + 1 == MAX_BODY_LENGTH ? 0 : tail + 1;
  Position prevHead = body[head];
  head = head + 1 == MAX_BODY_LENGTH ? 0 : head + 1;
  body[head] = { prevHead.x + (direction == DIRECTION_LEFT ? -1 : (direction == DIRECTION_RIGHT ? 1 : 0)), prevHead.y + (direction == DIRECTION_UP ? -1 : (direction == DIRECTION_DOWN ? 1 : 0)) };
  body[head].x = body[head].x < 0 ? GAME_AREA_WIDTH - 1 : (body[head].x >= GAME_AREA_WIDTH ? 0 : body[head].x);
  body[head].y = body[head].y < 0 ? GAME_AREA_HEIGHT - 1 : (body[head].y >= GAME_AREA_HEIGHT ? 0 : body[head].y);
}

void eat()
{
  if (body[head].x == food.x && body[head].y == food.y)
  {
    if (bodyLength < MAX_BODY_LENGTH)
    {
      bodyLength++;
      tail--;
      if (tail < 0) tail = MAX_BODY_LENGTH - 1;
    }
    score++;
    food = { -1, -1 };
    spawnFood();
  }
}

void reset()
{
  body[0] = { 3,3 };
  body[1] = { 3,4 };
  body[2] = { 3,5 };
  bodyLength = 3;
  head = 2;
  tail = 0;
  direction = DIRECTION_DOWN;
  food = {-1, -1};
  gameover = 0;
  elapsedTime = 0;
  score = 0;
  spawnFood();
  readInput = true;
}

void setup(){    
 
  pinMode(PIN_ROW1, OUTPUT);
  pinMode(PIN_ROW2, OUTPUT);
  pinMode(PIN_ROW3, OUTPUT);
  pinMode(PIN_ROW4, OUTPUT);
  pinMode(PIN_ROW5, OUTPUT);
  pinMode(PIN_ROW6, OUTPUT);
  pinMode(PIN_ROW7, OUTPUT);
  pinMode(PIN_ROW8, OUTPUT);
  pinMode(PIN_COL1, OUTPUT);
  pinMode(PIN_COL2, OUTPUT);
  pinMode(PIN_COL3, OUTPUT);
  pinMode(PIN_COL4, OUTPUT);
  pinMode(PIN_COL5, OUTPUT);
  pinMode(PIN_COL6, OUTPUT);
  pinMode(PIN_COL7, OUTPUT);
  pinMode(PIN_COL8, OUTPUT);

  pinMode(PIN_INPUT_LEFT, INPUT);
  pinMode(PIN_INPUT_RIGHT, INPUT);
  
  reset(); 
}


void loop(){   

    unsigned long currentTime = millis(); 

    if(!gameover)
    {
        draw();
        elapsedTime += currentTime - previousTime;
        if(elapsedTime > 500)
        {
            move();
            eat();
            checkGameover();
            elapsedTime = 0;
            readInput = true;
        }
        if(readInput)
        {
          if(digitalRead(PIN_INPUT_RIGHT) && !lastInput) {  direction = (direction + 1) % 4; readInput = false; }
          if(digitalRead(PIN_INPUT_LEFT) && !lastInput) { direction = (4 + direction-1) % 4; readInput = false; }
        }
        lastInput = digitalRead(PIN_INPUT_RIGHT) || digitalRead(PIN_INPUT_LEFT);
        
    }
    else
    {
        if(currentTime % 800 > 400) draw();
        gameover -= currentTime - previousTime;
        
        if(gameover <= 0) 
           reset();
    }
      
    previousTime = currentTime;
} 


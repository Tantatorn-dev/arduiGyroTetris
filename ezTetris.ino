#include <TFT.h>
#include <SPI.h>

#define TEST_BUTTON 2

#define cs 10
#define dc 9
#define rst 8
//sck 13 sda 11 dc a0 9

//define the shapes
#define SHAPE1 21
#define SHAPE1_A 22
#define SHAPE1_B 23
#define SHAPE1_C 24
#define SHAPE2 31
#define SHAPE2_A 32
#define SHAPE2_B 33
#define SHAPE2_C 34
#define SHAPE3 41
#define SHAPE3_A 42
#define SHAPE3_B 43
#define SHAPE3_C 44
#define SHAPE4 51
#define SHAPE4_A 52
#define SHAPE4_B 53
#define SHAPE4_C 54
#define SHAPE5 61
#define SHAPE5_A 62
#define SHAPE5_B 63
#define SHAPE5_C 64

TFT TFTscreen = TFT(cs, dc, rst);

//position of all blocks
int posX[200],
    posY[200],
    shapeSelection,
    index = 0,
    score = 0,
    rowBlockCounter[10],
    unNamed;

String scoreString;
char Score[4];

bool onFalling = true,
     onSpawn = false,
     onControl,
     onSetBlockCounter = false;

unsigned long timer = 0;

void setup()
{
  setOffscreen();
  pinMode(TEST_BUTTON, INPUT_PULLUP);
  TFTscreen.begin();

  TFTscreen.background(0, 0, 0);
  decoration();
  Serial.begin(9600);
  randomSeed(analogRead(5));
}

void loop()
{
  if (!onSpawn)
  {
    randomShape();
    spawnShape(60, 20);
    onSpawn = true;
  }
  falling();
  control();
  stopFalling();
  showScore();

  destroyRow();

  gameOver();

  if (digitalRead(TEST_BUTTON) == LOW)
  {
    rotate();
    Serial.println("te");
    delay(100);
    timer = millis();
  }

  delay(300);
}

void drawBlock(int x, int y)
{
  TFTscreen.stroke(255, 0, 0);
  TFTscreen.rect(x, y, 10, 10);
  //keep the position of all blocks
  posX[index] = x;
  posY[index] = y;
}

void deleteBlock(int x, int y)
{
  TFTscreen.stroke(0, 0, 0);
  TFTscreen.rect(x, y, 10, 10);
}

void randomShape()
{
  int n = random(1, 6);
  if (n == 1)
  {
    shapeSelection = SHAPE1;
  }
  else if (n == 2)
  {
    shapeSelection = SHAPE2;
  }
  else if (n == 3)
  {
    shapeSelection = SHAPE3;
  }
  else if (n == 4)
  {
    shapeSelection = SHAPE4;
  }
  else if (n == 5)
  {
    shapeSelection = SHAPE5;
  }
}

void spawnShape(int x, int y)
{
  if (shapeSelection == SHAPE1)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x + 10, y);
    index++;
    drawBlock(x + 20, y);
    index++;
    drawBlock(x + 30, y);
    index++;
  }
  else if (shapeSelection == SHAPE1_A)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x, y - 10);
    index++;
    drawBlock(x, y - 20);
    index++;
    drawBlock(x, y - 30);
    index++;
  }
  else if (shapeSelection == SHAPE1_B)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x - 10, y);
    index++;
    drawBlock(x - 20, y);
    index++;
    drawBlock(x - 30, y);
    index++;
  }
  else if (shapeSelection == SHAPE1_C)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x, y + 10);
    index++;
    drawBlock(x, y + 20);
    index++;
    drawBlock(x, y + 30);
    index++;
  }
  else if (shapeSelection == SHAPE2)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x + 10, y);
    index++;
    drawBlock(x, y - 10);
    index++;
    drawBlock(x + 10, y - 10);
    index++;
  }
  else if (shapeSelection == SHAPE2_A)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x + 10, y);
    index++;
    drawBlock(x, y - 10);
    index++;
    drawBlock(x + 10, y - 10);
    index++;
  }
  else if (shapeSelection == SHAPE2_B)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x + 10, y);
    index++;
    drawBlock(x, y - 10);
    index++;
    drawBlock(x + 10, y - 10);
    index++;
  }
  else if (shapeSelection == SHAPE2_C)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x + 10, y);
    index++;
    drawBlock(x, y - 10);
    index++;
    drawBlock(x + 10, y - 10);
    index++;
  }
  else if (shapeSelection == SHAPE3)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x + 10, y);
    index++;
    drawBlock(x + 20, y);
    index++;
    drawBlock(x + 10, y - 10);
    index++;
  }
  else if (shapeSelection == SHAPE3_A)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x, y - 10);
    index++;
    drawBlock(x, y - 20);
    index++;
    drawBlock(x - 10, y - 10);
    index++;
  }
  else if (shapeSelection == SHAPE3_B)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x - 10, y);
    index++;
    drawBlock(x - 20, y);
    index++;
    drawBlock(x - 10, y + 10);
    index++;
  }
  else if (shapeSelection == SHAPE3_B)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x, y + 10);
    index++;
    drawBlock(x, y + 20);
    index++;
    drawBlock(x + 10, y + 10);
    index++;
  }
  else if (shapeSelection == SHAPE4)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x + 10, y);
    index++;
    drawBlock(x + 20, y);
    index++;
    drawBlock(x + 20, y - 10);
    index++;
  }
  else if (shapeSelection == SHAPE4_A)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x, y - 10);
    index++;
    drawBlock(x, y - 20);
    index++;
    drawBlock(x - 10, y - 20);
    index++;
  }
  else if (shapeSelection == SHAPE4_B)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x - 10, y);
    index++;
    drawBlock(x - 20, y);
    index++;
    drawBlock(x - 20, y + 10);
    index++;
  }
  else if (shapeSelection == SHAPE4_C)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x, y + 10);
    index++;
    drawBlock(x, y + 20);
    index++;
    drawBlock(x + 10, y + 20);
    index++;
  }
  else if (shapeSelection == SHAPE5)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x + 10, y);
    index++;
    drawBlock(x + 10, y - 10);
    index++;
    drawBlock(x + 20, y - 10);
    index++;
  }
  else if (shapeSelection == SHAPE5_A)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x, y - 10);
    index++;
    drawBlock(x - 10, y - 10);
    index++;
    drawBlock(x - 10, y - 20);
    index++;
  }
  else if (shapeSelection == SHAPE5_B)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x - 10, y);
    index++;
    drawBlock(x - 10, y + 10);
    index++;
    drawBlock(x - 20, y + 10);
    index++;
  }
  else if (shapeSelection == SHAPE5_C)
  {
    drawBlock(x, y);
    index++;
    drawBlock(x, y + 10);
    index++;
    drawBlock(x + 10, y + 10);
    index++;
    drawBlock(x + 10, y + 20);
    index++;
  }
}

void falling()
{
  for (int i = 0; i < 4; i++)
  {
    deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
    posY[index - 4 + i] += 10;
    drawBlock(posX[index - 4 + i], posY[index - 4 + i]);
  }
}

void stopFalling()
{

  if (collideWithGround() || collideWithAnotherBlock())
  {
    onSpawn = false;
  }
}

bool collideWithGround()
{
  for (int i = 0; i < 4; i++)
  {
    if (posY[index - 4 + i] == 110)
    {
      return true;
    }
  }
  return false;
}

bool collideWithAnotherBlock()
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 4; j++)
    {
      for (int k = 8; k <= 80; k += 4)
        if (posY[index - 4 + i] == posY[index - k + j] - 10 && posX[index - 4 + i] == posX[index - k + j])
        {
          return true;
        }
    }
  }

  return false;
}

bool collideWithSide()
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 8; j <= 400; j += 4)
    {
      if (posX[index - 4 + i] == 20 || posX[index - 4 + i] == 100)
      {
        return true;
      }
    }
  }
  return false;
}

void control()
{
  if (!collideWithSide())
  {
    //read the data from gyro module
    int x = analogRead(A0);
    if (x >= 266 && x <= 299)
    {
      moveLeft();
      onControl = true;
    }
    if (x >= 300 && x <= 365)
    {
      onControl = false;
    }
    if (x >= 366 && x <= 399)
    {
      moveRight();
      onControl = true;
    }
  }
}

void moveLeft()
{
  for (int i = 0; i < 4; i++)
  {
    deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
    posX[index - 4 + i] -= 10;
    drawBlock(posX[index - 4 + i], posY[index - 4 + i]);
  }
}

void moveRight()
{
  for (int i = 3; i >= 0; i--)
  {
    deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
    posX[index - 4 + i] += 10;
    drawBlock(posX[index - 4 + i], posY[index - 4 + i]);
  }
}

void decoration()
{
  TFTscreen.fill(0, 34, 54);
  TFTscreen.rect(0, 0, 20, 160);
  TFTscreen.rect(0, 120, 140, 20);
  TFTscreen.rect(110, 0, 50, 160);
  TFTscreen.fill(0, 0, 0);
}

void showScore()
{
  
  TFTscreen.text("SCORE: ", 112, 40);
  scoreString = String(score);
  scoreString.toCharArray(Score, 4);
  TFTscreen.stroke(255, 0, 0);
  TFTscreen.text(Score, 130, 50);
}

void destroyRow()
{
  for (int i = 0; i < 4; i++)
  {
    for (int j = 0; j < 10; j++)
    {
      if (posY[index - 4 + i] == 110 - 10 * j && onSpawn == false)
      {
        rowBlockCounter[j]++;
      }
    }
  }
  for (int rowIndex = 0; rowIndex < 10; rowIndex++)
  {
    if (rowBlockCounter[rowIndex] == 9)
    {
      unNamed = rowIndex;
      onSetBlockCounter = true;
      score+=10;
    }
  }

  if (onSetBlockCounter)
  {
    for (int i = 0; i < 200; i++)
    {
      if (posY[i] == 110 - 10 * unNamed)
      {
        deleteBlock(posX[i], posY[i]);
        posY[i] = 600;
        posX[i] = 600;
      }
      else if (posY[i] < 110 - 10 * unNamed)
      {
        deleteBlock(posX[i], posY[i]);
        posY[i] += 10;
        drawBlock(posX[i], posY[i]);
      }
    }
    for (int j = unNamed; j < 9; j++)
    {
      rowBlockCounter[j] = 0;
      rowBlockCounter[j] += rowBlockCounter[j + 1];
    }
    onSetBlockCounter = false;
    unNamed = -1;
  }
}

void setOffscreen()
{
  for (int i = 0; i < 200; i++)
  {
    posX[i] = 600;
    posY[i] = 600;
  }
}

void gameOver()
{
  if (rowBlockCounter[9] > 0)
  {
    TFTscreen.background(0, 0, 0);
    while (true)
    {
      TFTscreen.stroke(0, 0, 255);
      TFTscreen.text("GAME OVER!", 20, 60);
    }
  }
}

void rotate()
{
  if (shapeSelection == SHAPE1 && posX[index - 4] )
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE1_A;
    spawnShape(tempX, tempY);
  }
  else if (shapeSelection == SHAPE1_A && posX[index-4]>=50)
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE1_B;
    spawnShape(tempX, tempY);
  }
  else if (shapeSelection == SHAPE1_B && posY[index-4]<=90)
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE1_C;
    spawnShape(tempX, tempY);
  }
  else if (shapeSelection == SHAPE1_C && posX[index-4]<=80)
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE1;
    spawnShape(tempX, tempY);
  }

  else if (shapeSelection == SHAPE2 && posX[index - 4] >= 40)
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE2_A;
    spawnShape(tempX, tempY);
  }
  else if (shapeSelection == SHAPE2_A && posX[index - 4] >= 40 && posX[index - 4] <= 90)
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE2_B;
    spawnShape(tempX, tempY);
  }
  else if (shapeSelection == SHAPE2_B)
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE2_C;
    spawnShape(tempX, tempY);
  }
  else if (shapeSelection == SHAPE2_C)
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE2;
    spawnShape(tempX, tempY);
  }

  else if (shapeSelection == SHAPE3 && posX[index-4]>=30 )
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE3_A;
    spawnShape(tempX, tempY);
  }
  else if (shapeSelection == SHAPE3_A &&posX[index-4]>=40)
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE3_B;
    spawnShape(tempX, tempY);
  }
  else if (shapeSelection == SHAPE3_B &&posY[index-4]<=100)
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE3_C;
    spawnShape(tempX, tempY);
  }
  else if (shapeSelection == SHAPE3_C  && posX[index-4]<=90)
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE3;
    spawnShape(tempX, tempY);
  }

  else if (shapeSelection == SHAPE4 && posX[index-4]>=30)
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE4_A;
    spawnShape(tempX, tempY);
  }
  else if (shapeSelection == SHAPE4_A && posX[index-4]>=40)
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE4_B;
    spawnShape(tempX, tempY);
  }
  else if (shapeSelection == SHAPE4_B&& posY[index-4]<=100 && posX[index-4]<=100)
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE4_C;
    spawnShape(tempX, tempY);
  }
  else if (shapeSelection == SHAPE4_C && posX[index-4]<=90)
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE4;
    spawnShape(tempX, tempY);
  }

  else if (shapeSelection == SHAPE5 && posX[index-4]>=30)
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE5_A;
    spawnShape(tempX, tempY);
  }
  else if (shapeSelection == SHAPE5_A && posX[index-4]>=40)
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE5_B;
    spawnShape(tempX, tempY);
  }
  else if (shapeSelection == SHAPE5_B && posY[index-4]<=100)
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE5_C;
    spawnShape(tempX, tempY);
  }
  else if (shapeSelection == SHAPE5_C && posX[index-4]<=100)
  {
    int tempX = posX[index - 4], tempY = posY[index - 4];
    for (int i = 0; i < 4; i++)
    {
      deleteBlock(posX[index - 4 + i], posY[index - 4 + i]);
      posX[index - 4 + i] = 600;
      posY[index - 4 + i] = 600;
    }
    shapeSelection = SHAPE5;
    spawnShape(tempX, tempY);
  }
}
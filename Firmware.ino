/*Firmware for the 
* Smart Stepper Motor Controller Board
* 
*************************ELINT LABZ*********************************
*********************www.elintlabz.in*******************************
*********************KARTHIK.C**************************************
* Firmware For Controlling Stepper Motors using URAT Communication and I2C Protocol
*
*/
#include <Wire.h> // include the Wire library code
int mat[4][3]={ {'c','l','k'}, // clockwise rotation
                {'a','c','k'}, // anticlockwise rotation
                {'c','k','d'}, // to control clockwise rotation with the given degree
                {'a','c','d'}, // to control anticlockwise rotation with the given degree
              };
char cmd[24];
int i,x,y,z,m,n,s,q,a,c;
int blue1 = 17; // the number of the motor 1 wire 1  
int pink1 = 16; // the number of the motor 1 wire 2
int yellow1 = 15; // the number of the motor 1 wire 3
int orange1 = 14; // the number of the motor 1 wire 4
int blue2 = 5; // the number of the motor 2 wire 1
int pink2 = 6; // the number of the motor 2 wire 2
int yellow2 = 7; // the number of the motor 2 wire 3
int orange2 = 8; // the number of the motor 2 wire 4
void setup()
{
  pinMode(blue1,OUTPUT); // initialize the digital pin as an output
  pinMode(pink1,OUTPUT); // initialize the digital pin as an output
  pinMode(yellow1,OUTPUT); // initialize the digital pin as an output
  pinMode(orange1,OUTPUT); // initialize the digital pin as an output
  pinMode(blue2,OUTPUT); // initialize the digital pin as an output
  pinMode(pink2,OUTPUT); // initialize the digital pin as an output
  pinMode(yellow2,OUTPUT); // initialize the digital pin as an output
  pinMode(orange2,OUTPUT); // initialize the digital pin as an output
  Serial.begin(9600); // initialize the serial communication with baudrate 9600
  Wire.begin(4);  // i2c with adress #4               
  Wire.onReceive(command); // register event
}
void loop()
{
  get();
  compute();
} 
// This function is to get data from serial communication
void get()
{
  if (Serial.available()>1)
  {
    for (int i=0;i<25;i++)
    {
      delay(100);
      cmd[i]=Serial.read();
      Serial.print(cmd[i]);
      x = cmd[4] - '0';
      y = cmd[5] - '0';
      z = cmd[6] - '0';
      x = (x * 100) + (y * 10) + z;
      z = (x * 64)/360;
      z = z * 8;
      m = cmd[8] - '0';
      n = cmd[9] - '0';
      m = (m * 10) + n;
      s = cmd[11] - '0';
      q = cmd[12] - '0';
      s = (s * 10) + q;
    }
  }
}
// This function is to get data from i2c communication
void command(int stepper)
{
  if (Wire.available())
  {
    for (int i=0;i<14;i++)
    {
      delay(100);
      cmd[i]=Wire.read();
      x = cmd[4] - '0';
      y = cmd[5] - '0';
      z = cmd[6] - '0';
      x = (x * 100) + (y * 10) + z;
      z = (x * 64)/360;
      z = z * 8;
      m = cmd[8] - '0';
      n = cmd[9] - '0';
      a = cmd[10] - '0';
      m = (m * 100) + (n * 10) + a;
      s = cmd[12] - '0';
      q = cmd[13] - '0';
      s = (s * 10) + q;
    }
  }
 compute();
}
// This function is used to select the motor
void compute()
{
  if (s == 01)
  { 
    process1();
  }
  else if (s == 02)
  {
    process2();
  }
  else if (s== 12)
  {
    process1();
    process2();
  }
}
// This function is to compute the given command for motor 1
void process1()
{
  for(int j=0;j<4;j++)
  {
    c=0;
    for(int k=0;k<3;k++)
    {
      if (cmd[k]==mat[j][k])
      {
        c++;
        if (c==3)
        {
          c=0;
          switch(j)
          {
            case 0:
            clockwise1();
            break;
            case 1:
            anticlockwise1();
            break;
            case 2:
            clockdegree1();     
            break;
            case 3:
            antidegree1();
            break;
          }
        }
      }
    }
  }
}
// This function is to compute the given command for motor 2
void process2()
{
  for(int j=0;j<4;j++)
  {
    c=0;
    for(int k=0;k<3;k++)
    {
      if (cmd[k]==mat[j][k])
      {
        c++;
        if (c==3)
        {
          c=0;
          switch(j)
          {
            case 0:
            clockwise2();
            break;
            case 1:
            anticlockwise2();
            break;
            case 2:
            clockdegree2();     
            break;
            case 3:
            antidegree2();
            break;
          }
        }
      }
    }
  }
}
// This function is used to rotate motor 1 clockwise
void clockwise1()
{
  digitalWrite(blue1, HIGH);
  digitalWrite(pink1,LOW);
  digitalWrite(yellow1,LOW);
  digitalWrite(orange1,LOW);
  delay(m);
  digitalWrite(blue1, LOW);
  digitalWrite(pink1,HIGH);
  digitalWrite(yellow1,LOW);
  digitalWrite(orange1,LOW);
  delay(m);
  digitalWrite(blue1, LOW);
  digitalWrite(pink1,LOW);
  digitalWrite(yellow1,HIGH);
  digitalWrite(orange1,LOW);
  delay(m);
  digitalWrite(blue1, LOW);
  digitalWrite(pink1,LOW);
  digitalWrite(yellow1,LOW);
  digitalWrite(orange1,HIGH);
  delay(m);
  digitalWrite(blue1, HIGH);
  digitalWrite(pink1,LOW);
  digitalWrite(yellow1,LOW);
  digitalWrite(orange1,LOW);
  delay(m);
}    
// This function is used to rotate motor 1 anticlockwise
void anticlockwise1()
{
  digitalWrite(blue1, LOW);
  digitalWrite(pink1,LOW);
  digitalWrite(yellow1,LOW);
  digitalWrite(orange1,HIGH);
  delay(m);
  digitalWrite(blue1, LOW);
  digitalWrite(pink1,LOW);
  digitalWrite(yellow1,HIGH);
  digitalWrite(orange1,LOW);
  delay(m);
  digitalWrite(blue1, LOW);
  digitalWrite(pink1,HIGH);
  digitalWrite(yellow1,LOW);
  digitalWrite(orange1,LOW);
  delay(m);
  digitalWrite(blue1, HIGH);
  digitalWrite(pink1,LOW);
  digitalWrite(yellow1,LOW);
  digitalWrite(orange1,LOW);
  delay(m);
}
// This function is used to control the rotation of motor 1 in clockwise direction
void clockdegree1()
{
  for(int i=0;i<z;i++)
  {
   clockwise1();
  }
  Clear();
} 
// This function is used to control the rotation of motor 1 in anticlockwise direction
void antidegree1()
{
  for(int i=0;i<z;i++)
  {
    anticlockwise1();
  }
  Clear();
}
// This function is used to rotate motor 2 clockwise
void clockwise2()
{
  digitalWrite(blue2, HIGH);
  digitalWrite(pink2,LOW);
  digitalWrite(yellow2,LOW);
  digitalWrite(orange2,LOW);
  delay(m);
  digitalWrite(blue2, LOW);
  digitalWrite(pink2,HIGH);
  digitalWrite(yellow2,LOW);
  digitalWrite(orange2,LOW);
  delay(m);
  digitalWrite(blue2, LOW);
  digitalWrite(pink2,LOW);
  digitalWrite(yellow2,HIGH);
  digitalWrite(orange2,LOW);
  delay(m);
  digitalWrite(blue2, LOW);
  digitalWrite(pink2,LOW);
  digitalWrite(yellow2,LOW);
  digitalWrite(orange2,HIGH);
  delay(m);
  digitalWrite(blue2, HIGH);
  digitalWrite(pink2,LOW);
  digitalWrite(yellow2,LOW);
  digitalWrite(orange2,LOW);
  delay(m);
}    
// This function is used to rotate motor 2 anticlockwise
void anticlockwise2()
{
  digitalWrite(blue2, LOW);
  digitalWrite(pink2,LOW);
  digitalWrite(yellow2,LOW);
  digitalWrite(orange2,HIGH);
  delay(m);
  digitalWrite(blue2, LOW);
  digitalWrite(pink2,LOW);
  digitalWrite(yellow2,HIGH);
  digitalWrite(orange2,LOW);
  delay(m);
  digitalWrite(blue2, LOW);
  digitalWrite(pink2,HIGH);
  digitalWrite(yellow2,LOW);
  digitalWrite(orange2,LOW);
  delay(m);
  digitalWrite(blue2, HIGH);
  digitalWrite(pink2,LOW);
  digitalWrite(yellow2,LOW);
  digitalWrite(orange2,LOW);
  delay(m);
}
// This function is used to control the rotation of motor 2 in clockwise direction
void clockdegree2()
{
  for(int i=0;i<z;i++)
  {
   clockwise2();
  }
  Clear();
} 
// This function is used to control the rotation of motor 2 in anticlockwise direction
void antidegree2()
{
  for(int i=0;i<z;i++)
  {
    anticlockwise2();
  }
  Clear();
}
// This function is used to clear the Array and variables
void Clear()
{
  c=0;
  i = 0;
  for(int i=0; i<20; i++)
  cmd[i]=' ';
}

//End of the Program

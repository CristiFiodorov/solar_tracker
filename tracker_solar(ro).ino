#include <Servo.h> // include libraria Servo

Servo horizontal; // orizontal servo
int servoh = 90;

int servohLimitHigh = 210;
int servohLimitLow = 10;

// 65 degrees MAX
Servo vertical; // vertical servo
int servov = 90;

int servovLimitHigh = 125;
int servovLimitLow = 15;

// Unde pe placa Arduino sunt amplasate rezistorii de lumina

int ldrlt = 2;
int ldrrt = 1;
int ldrld = 3;
int ldrrd = 0;

void setup()
{
  Serial.begin(9600);

  horizontal.attach(9);
  vertical.attach(10);
  horizontal.write(180);
  vertical.write(45);
  delay(3000);
}

void loop()
{
  // citeste datele care vin de la rezistorii de lumina si stocheaza informatia in "lt","rt","ld","rd"
  int lt = analogRead(ldrlt);
  int rt = analogRead(ldrrt);
  int ld = analogRead(ldrld);
  int rd = analogRead(ldrrd);

  int dtime = 10;
  int tol = 30;

  int avt = (lt + rt) / 2; // calculeaza valoarea medie de sus
  int avd = (ld + rd) / 2; // calculeaza valoarea medie de jos
  int avl = (lt + ld) / 2; // calculeaza valoarea medie din stanga
  int avr = (rt + rd) / 2; // calculeaza valoarea medie din dreapta

  int dvert = avt - avd;  // verifica diferenta dintre partea de sus si jos
  int dhoriz = avl - avr; // verifica diferenta dintre partea stanga si dreapta

  Serial.print(avt);
  Serial.print(" ");
  Serial.print(avd);
  Serial.print(" ");
  Serial.print(avl);
  Serial.print(" ");
  Serial.print(avr);
  Serial.print("   ");
  Serial.print(dtime);
  Serial.print("   ");
  Serial.print(tol);
  Serial.println(" ");

  if (-1 * tol > dvert || dvert > tol) // verifica daca diferenta se afla in toleranta
  {
    if (avd > avt) // verifica daca este vreo diferenta dintre partea de sus si partea de jos ,daca este pai se schimba unghiul in partea necesara
    {
      servov = ++servov;
      if (servov > servovLimitHigh)
      {
        servov = servovLimitHigh;
      }
    }
    else if (avd < avt)
    {
      servov = --servov;
      if (servov < servovLimitLow)
      {
        servov = servovLimitLow;
      }
    }
    vertical.write(servov);
  }

  if (-1 * tol > dhoriz || dhoriz > tol) // verifica daca diferenta se afla in toleranta
  {
    if (avl > avr) // verifica daca este vreo diferenta dintre partea stanga si dreapta ,daca este pai se schimba unghiul in partea necesara
    {
      servoh = --servoh;
      if (servoh < servohLimitLow)
      {
        servoh = servohLimitLow;
      }
    }
    else if (avl < avr)
    {
      servoh = ++servoh;
      if (servoh > servohLimitHigh)
      {
        servoh = servohLimitHigh;
      }
    }
    else if (avl = avr)
    {
      // nothing
    }
    horizontal.write(servoh);
  }
  delay(dtime);
}

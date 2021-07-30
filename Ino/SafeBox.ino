#include <LiquidCrystal.h>
#include <Keypad.h>

String command = "";
String option = "";

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
    {'1', '2', '3', 'A'},
    {'4', '5', '6', 'B'},
    {'7', '8', '9', 'C'},
    {'*', '0', '#', 'D'}};

int buzzer = 2;
byte rowPins[ROWS] = {10, 9, 8, 7};
byte colPins[COLS] = {13, 12, 11, 6};
char Password[5];
int dir = 0;
boolean flag = false;

const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup()
{
  pinMode(3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  lcd.print("Press Any Key");
  lcd.setCursor(0, 1);
  digitalWrite(4, HIGH);
  Serial.begin(9600);
  Serial.println("Select the option number to modify the box configuration");
  Serial.println("1. Open the box remotly");
  Serial.println("2. Change your password");
}

void loop()
{

  if(Serial.available() && option.equals("")){
    command = Serial.readString();
    lcd.clear();
    lcd.setCursor(0,0);
    if(command == "1"){
      Serial.print("Option selected: 1");
      Serial.flush();
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("The box in opened now");
      command = "";
      delay(1000);
      lcd.clear();
      option = "1";
    }
    else if(command.equals("2")){
      Serial.print("Option selected: 2");
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("The password has changed");
      command = "";
      delay(1000);
      lcd.clear();
    }
    else if(option.equals("cambio")){
      Serial.print("Cambio");
    }
    else{
      lcd.clear();
      lcd.setCursor(0,0);
      lcd.println(command + " else");
      lcd.setCursor(0,1);
      lcd.print("It's not a valid option");
      delay(50000);
      lcd.clear();
    }
  } 
  else if(Serial.available() && option.equals("1")){
    option = Serial.readString();
    Serial.print("Hola");
  }
  char key = keypad.getKey();
  if (flag == false)
  {

    if (key)
    {
      Password[dir] = key;
      if (key != 'A')
      {
        lcd.print(key);
      }
      dir = dir + 1;

      if (Password[0] == 'C' || Password[1] == 'C' || Password[2] == 'C' || Password[3] == 'C' || Password[4] == 'C')
      {
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Write Password");
        Serial.println("Write Password");
        dir = 0;
        memset(Password, 0, 5);
        lcd.setCursor(0, 1);
      }
      if (Password[0] == 'D')
      {
        memset(Password, 0, 5);
        dir = 0;
        lcd.setCursor(0, 1);
        lcd.print(" ");
        lcd.setCursor(0, 1);
      }
      if (Password[1] == 'D')
      {
        memset(Password, 0, 5);
        dir = 0;
        lcd.setCursor(1, 1);
        lcd.print(" ");
        lcd.setCursor(0, 1);
        lcd.print(" ");
        lcd.setCursor(0, 1);
      }
      if (Password[2] == 'D')
      {
        char letraUno = Password[0];
        memset(Password, 0, 5);
        Password[0] = letraUno;
        dir = 1;
        lcd.setCursor(2, 1);
        lcd.print(" ");
        lcd.setCursor(1, 1);
        lcd.print(" ");
        lcd.setCursor(1, 1);
      }
      if (Password[3] == 'D')
      {
        char letraUno = Password[0];
        char letraDos = Password[1];
        memset(Password, 0, 5);
        Password[0] = letraUno;
        Password[1] = letraDos;
        dir = 2;
        lcd.setCursor(3, 1);
        lcd.print(" ");
        lcd.setCursor(2, 1);
        lcd.print(" ");
        lcd.setCursor(2, 1);
      }
      if (Password[4] == 'D')
      {
        char letraUno = Password[0];
        char letraDos = Password[1];
        char letraTres = Password[2];
        memset(Password, 0, 5);
        Password[0] = letraUno;
        Password[1] = letraDos;
        Password[2] = letraTres;
        dir = 3;
        lcd.setCursor(4, 1);
        lcd.print(" ");
        lcd.setCursor(4, 1);
        lcd.print(" ");
        lcd.setCursor(3, 1);
      }

      if (Password[4] == 'A')
      {

        if (Password[0] == '1' && Password[1] == '1' && Password[2] == '1' && Password[3] == '1')
        {
          Serial.println("Correct Password");
          lcd.setCursor(0, 0);
          lcd.print("Correct Password            ");
          digitalWrite(3, HIGH);
          delay(2000);
          digitalWrite(3, LOW);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Enter");
          dir = 0;
          memset(Password, 0, 5);
          lcd.setCursor(0, 1);
          digitalWrite(4, LOW);
          digitalWrite(5, HIGH);
          digitalWrite(buzzer, 240);
          delay(250);
          digitalWrite(buzzer, LOW);
          delay(1000);
          flag = true;
        }
        else
        {
          lcd.setCursor(0, 0);
          lcd.print("Incorrect Password           ");
          digitalWrite(3, HIGH);
          delay(2000);
          digitalWrite(3, LOW);
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Write Password");
          dir = 0;
          memset(Password, 0, 5);
          lcd.setCursor(0, 1);
          digitalWrite(5, LOW);
          digitalWrite(4, HIGH);
          digitalWrite(buzzer, 240);
          delay(500);
          digitalWrite(buzzer, 240);
          delay(500);
          digitalWrite(buzzer, 240);
          delay(500);
          digitalWrite(buzzer, LOW);
          delay(1000);
        }
      }
      if (dir > 4)
      {
        lcd.setCursor(0, 0);
        lcd.print("Incorrect Password           ");
        digitalWrite(3, HIGH);
        delay(2000);
        digitalWrite(3, LOW);
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Write Password");
        dir = 0;
        memset(Password, 0, 5);
        lcd.setCursor(0, 1);
        digitalWrite(buzzer, 240);
        delay(500);
        digitalWrite(buzzer, 240);
        delay(500);
        digitalWrite(buzzer, 240);
        delay(500);
        digitalWrite(buzzer, LOW);
        delay(1000);
      }
    }
  }
  else
  {
    if (key)
    {
      if (key == 'B')
      {
        flag = false;
        lcd.clear();
        lcd.setCursor(0, 0);
        lcd.print("Close");
        digitalWrite(5, LOW);
        digitalWrite(4, HIGH);
        delay(2000);
        lcd.clear();
        lcd.print("Write Password");
        lcd.setCursor(0, 0);

        lcd.setCursor(0, 1);
      }
    }
  }
}

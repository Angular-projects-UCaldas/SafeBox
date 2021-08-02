#include <LiquidCrystal.h>
#include <Keypad.h>
#include <time.h>

String command = "";
String option = "";

const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] = {
  {'1', '2', '3', 'A'},
  {'4', '5', '6', 'B'},
  {'7', '8', '9', 'C'},
  {'*', '0', '#', 'D'}
};

int buzzer = 2;
byte rowPins[ROWS] = {10, 9, 8, 7};
byte colPins[COLS] = {13, 12, 11, 6};
char preSetPassword[4];
char Password[5];
int dir = 0;
boolean flag = false;
int timeOpen = 1000;
int seconds = 1000;

const int rs = A0, en = A1, d4 = A2, d5 = A3, d6 = A4, d7 = A5;

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

void setup()
{
  pinMode(3, OUTPUT);
  pinMode(buzzer, OUTPUT);
  lcd.begin(16, 2);
  lcd.setCursor(0, 0);
  printSerialMessage("The system has been started");
  lcd.print("Enter password");
  lcd.setCursor(0, 1);
  digitalWrite(4, HIGH);
  Serial.begin(9600);
  preSetPassword[0] = '1';
  preSetPassword[1] = '1';
  preSetPassword[2] = '1';
  preSetPassword[3] = '1';
}

void loop()
{

  if (Serial.available()) {
    command = Serial.readString();
    lcd.clear();
    lcd.setCursor(0, 0);
    if (command[0] == '1') {
      openBoxRemotely();
    }
    else if (command[0] == '2') {
      lcd.clear();
      lcd.setCursor(0, 0);
      preSetPassword[0] = command[1];
      preSetPassword[1] = command[2];
      preSetPassword[2] = command[3];
      preSetPassword[3] = command[4];
      lcd.print("The password has changed");
      printSerialMessage("The password has changed");
      command = "";
      delay(1000);
      lcd.clear();
      closeBox(seconds);
    }
    else if (command[0] == '3') {
      seconds = int(command[1]);
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("The time has changed");
      printSerialMessage("The time has changed");
      command = "";
      delay(1000);
      lcd.clear();
      closeBox(seconds);
    }
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
        clearDisplay();
      }
      if (Password[0] == 'D')
      {
        deleteCharacter(0);
      }
      if (Password[1] == 'D')
      {
        deleteCharacter(1);
      }
      if (Password[2] == 'D')
      {
        deleteCharacter(2);
      }
      if (Password[3] == 'D')
      {
        deleteCharacter(3);
      }
      if (Password[4] == 'D')
      {
        deleteCharacter(4);
      }

      if (Password[4] == 'A')
      {
        if (Password[0] == preSetPassword[0] && Password[1] == preSetPassword[1] && Password[2] == preSetPassword[2] && Password[3] == preSetPassword[3])
        {
          openBox();
          printSerialMessage("The box was opened");
          setTimeOpen(5000, 's');
          closeBox(seconds);
        }
        else
        {
          printSerialMessage("Inserted wrong password");
          lcd.setCursor(0, 0);
          lcd.print("Wrong Password");
          notOkBuzzer();
          lcd.clear();
          lcd.setCursor(0, 0);
          lcd.print("Write Password");
          dir = 0;
          memset(Password, 0, 5);
          lcd.setCursor(0, 1);
        }
      }
      if (dir > 4)
      {
        lcd.setCursor(0, 0);
        lcd.print("Wrong Password");
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
        closeBox(seconds);
      }
    }
  }
}

void openBox() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Correct");
  lcd.setCursor(0, 1);
  lcd.print("Password");
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

void closeBox(int seconds) {
  flag = false;
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Close");
  digitalWrite(5, LOW);
  digitalWrite(4, HIGH);
  delay(seconds);
  lcd.clear();
  lcd.print("Write Password");
  lcd.setCursor(0, 0);
  lcd.setCursor(0, 1);
}

void printSerialMessage(String mensaje) {
  Serial.println(mensaje);
}

void setTimeOpen(int timeOpened, char set) {
  if (set == 's') {
    delay(timeOpened);
  } else {
    delay(timeOpen);
  }
}

void openBoxRemotely() {
  Serial.flush();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("The box in opened now");
  command = "";
  printSerialMessage("the box was opened remotely");
  setTimeOpen(5000, 's');
  lcd.clear();
  closeBox(seconds);
}

void clearDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Write Password");
  dir = 0;
  memset(Password, 0, 5);
  lcd.setCursor(0, 1);
}

void deleteCharacter(int chPosition) {

  char charOne = Password[0];
  char charTwo = Password[1];
  char charThree = Password[2];

  switch (chPosition)
  {
    case 0:
      memset(Password, 0, 5);
      dir = 0;
      lcd.setCursor(0, 1);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      break;

    case 1:
      memset(Password, 0, 5);
      dir = 0;
      lcd.setCursor(1, 1);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      lcd.print(" ");
      lcd.setCursor(0, 1);
      break;

    case 2:
      memset(Password, 0, 5);
      Password[0] = charOne;
      dir = 1;
      lcd.setCursor(2, 1);
      lcd.print(" ");
      lcd.setCursor(1, 1);
      lcd.print(" ");
      lcd.setCursor(1, 1);
      break;

    case 3:
      memset(Password, 0, 5);
      Password[0] = charOne;
      Password[1] = charTwo;
      dir = 2;
      lcd.setCursor(3, 1);
      lcd.print(" ");
      lcd.setCursor(2, 1);
      lcd.print(" ");
      lcd.setCursor(2, 1);
      break;

    case 4:
      Password[0] = charOne;
      Password[1] = charTwo;
      Password[2] = charThree;
      memset(Password, 0, 5);
      dir = 3;
      lcd.setCursor(4, 1);
      lcd.print(" ");
      lcd.setCursor(4, 1);
      lcd.print(" ");
      lcd.setCursor(3, 1);
      break;
  }

}

void notOkBuzzer() {
  digitalWrite(3, HIGH);
  delay(2000);
  digitalWrite(3, LOW);
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

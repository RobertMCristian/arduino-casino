#include <SPI.h>
#include <MFRC522.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

#define SS_PIN 10
#define RST_PIN 9

byte readCard[4];
String MasterTag = "891068C";
String tagID = "";

MFRC522 mfrc522(SS_PIN, RST_PIN);
LiquidCrystal_I2C lcd(0x27, 16, 2);

const int joystickButtonPin = 4;
const int diceThrowPin = 4;  // Pinul digital conectat la butonul joystickului

int menuOption = 0;

void setup() {
  lcd.begin();
  lcd.backlight();
  Serial.begin(9600);
  SPI.begin();
  mfrc522.PCD_Init();
  pinMode(joystickButtonPin, INPUT_PULLUP);
  lcd.print("Scanati cardul");
}

void loop() {
  if (getID()) {
    lcd.clear();
    lcd.print("Card valid!");
    delay(1500);
    lcd.clear();
    showMenu();
  }
}
void barbutGame() {
  int player1Score = 0; // Scorul primului jucator
  int player2Score = 0; // Scorul celui de-al doilea jucator

  lcd.clear();
  lcd.print("Barbut Jucator 1");
  delay(2000);

  // Jucatorul 1 arunca de doua ori zarurile
    lcd.clear();
    lcd.print("Arunca zarurile!");
    while (digitalRead(diceThrowPin) == HIGH); // Asteapta pana cand butonul este apasat
    int diceValue1 = rollDice();
    player1Score += diceValue1;
        int diceValue2 = rollDice();
    player1Score += diceValue2;
    lcd.clear();
    lcd.print("J1: ");
    lcd.print(diceValue1);
    lcd.setCursor(7, 0);
    lcd.print(diceValue2);
    delay(2000);
    lcd.setCursor(0, 0);
  

  lcd.clear();
  lcd.print("Barbut Jucator 2");
  delay(2000);

  // Jucatorul 2 arunca de doua ori zarurile
  
    lcd.clear();
    lcd.print("Arunca zarurile!");
    while (digitalRead(diceThrowPin) == HIGH); // Asteapta pana cand butonul este apasat
    diceValue1 = rollDice();
    player2Score += diceValue1;
    diceValue2 = rollDice();
    player2Score += diceValue2;
    lcd.clear();
    lcd.print("J2: ");
    lcd.print(diceValue1);
    lcd.setCursor(7, 0);
    lcd.print(diceValue2);
    lcd.setCursor(0,0);
    delay(2000);
  
  lcd.print("Jucator 1: ");
  lcd.setCursor(0, 1);
    lcd.print(player1Score);
  delay(2000);
  lcd.setCursor(0, 0);
  lcd.clear();
  lcd.print("Jucator 2: ");
  lcd.setCursor(0, 1);

    lcd.print(player2Score);
    lcd.setCursor(0, 0);
    delay(2000);
  // Comparam rezultatele si determinam castigatorul
  lcd.clear();
  if (player1Score > player2Score) {
    lcd.print("Jucatorul 1 ");
    lcd.setCursor(0, 1);
    lcd.print("castiga!");
    lcd.setCursor(0, 0);
  } else if (player1Score < player2Score) {
    lcd.print("Jucatorul 2 ");
    lcd.setCursor(0, 1);
    lcd.print("castiga!");
    lcd.setCursor(0, 0);
  } else {
    lcd.print("Egalitate!");
  }

  delay(3000);
}

int rollDice() {
  return random(1, 7); // Functie simpla pentru aruncarea zarurilor intre 1 si 6
}



boolean getID() {
  if (!mfrc522.PICC_IsNewCardPresent()) {
    return false;
  }
  if (!mfrc522.PICC_ReadCardSerial()) {
    return false;
  }
  tagID = "";
  for (uint8_t i = 0; i < 4; i++) {
    tagID.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  tagID.toUpperCase();
  mfrc522.PICC_HaltA();
  
  if (tagID == MasterTag) {
    return true;
  }
  return false;
}
bool isRed(int number) {
  if (number == 0) { // Daca numarul este 0, este verde
    return false;
  }
  // Verificam daca numarul este rosu
  if ((number >= 1 && number <= 10) || (number >= 19 && number <= 28)) {
    return number % 2 == 1; // Numerele impare intre 1-10 si 19-28 sunt rosii
  }
  return number % 2 == 0; // Restul numerelor sunt negre
}

void showMenu() {
  while (true) {
    int yValue = analogRead(A0);
   
    lcd.setCursor(0, 0);
    
    if (yValue < 50) {
      delay(200);
      menuOption--;
      Serial.print(menuOption);
      if (menuOption < 0) menuOption = 2;
    } else if (yValue > 950) {
      delay(200);
      menuOption++;
      Serial.print(menuOption);
      if (menuOption > 2) menuOption = 0;
    }
    delay(100);

    switch (menuOption) {
    case 0:
      lcd.print(">Ruleta   ");
      if (digitalRead(joystickButtonPin) == LOW) {
        lcd.clear();
        lcd.print("Se invarte...");

        // Generam si afisam 15 numere aleatoare
        for (int i = 0; i < 15; i++) {
          int randomNumber = random(0, 37); // Generam un numar aleator intre 0 si 36
          lcd.setCursor(0, 1);
          lcd.print(randomNumber);
          delay(500); 
          lcd.setCursor(1, 1);
          lcd.print(" ");// Asteptam 500 de milisecunde intre afisari
        }

        // Generam al 16-lea numar si determinam culoarea
        int lastNumber = random(0, 37);
        lcd.setCursor(0, 1);
        lcd.print(lastNumber);

        lcd.setCursor(4, 1);
        if (isRed(lastNumber)) {
          lcd.print("Rosu");
        } else if (lastNumber == 0){
          lcd.print("Verde");
        } else {
          lcd.print("Negru");
        }

        delay(3000);
        lcd.clear(); // Asteptam 3 secunde inainte de a reveni la meniu
      }
      break;

      case 1:
  lcd.print(">Barbut   ");
  if (digitalRead(joystickButtonPin) == LOW) {
    lcd.clear();
    lcd.print("Incepem barbut!");
    delay(2000);
    barbutGame();
    lcd.clear(); // Apelam functia pentru jocul de barbut
  }
  break;

case 2:
  lcd.print(">Blackjack");
  if (digitalRead(joystickButtonPin) == LOW) {
    lcd.clear();
    
    int dealerTotal = 0;  // Initializam totalul dealerului
    int dealerCards[10];  // Vector pentru cartile dealerului
    int cardCount = 0;     // Contor pentru numarul de carti

    // Primele doua carti ale dealerului
    dealerCards[cardCount++] = random(1, 11);  // Prima carte
    dealerTotal += dealerCards[0];  // Actualizam totalul pentru prima carte
    dealerCards[cardCount++] = random(1, 11);  // A doua carte, dar nu o afisam
    lcd.print("Dealer: ");
    lcd.print(dealerCards[0]);  // Afisam prima carte
    lcd.print(" ?");
    delay(2000);
    
    bool showCards = false;  // Variabila pentru a decide daca aratam cartile sau nu
    
    while (!showCards) {
      lcd.clear();
      lcd.print("Trage carte?");
      if (digitalRead(joystickButtonPin) == LOW) {
        dealerCards[cardCount] = random(1, 11);  // Adaugam o noua carte in vector
        cardCount++;  // Incrementam numarul de carti

        // Afisam cartile dealerului
        lcd.clear();
        lcd.print("Dealer: ");
        lcd.print(dealerCards[0]);  // Afisam prima carte
        lcd.print(" ?");
        for (int i = 2; i < cardCount; ++i) {
          lcd.print(" ?");
        }
        delay(2000);
      } else {
        if (analogRead(A0) > 700) {  // Daca joystickul este apasat in sus
          showCards = true;

          // Calculam totalul corect al cartilor pentru dealer
          dealerTotal = 0;  // Resetam totalul
          for (int i = 0; i < cardCount; ++i) {
            dealerTotal += dealerCards[i];
          }

          // Afisam toate cartile dealerului si totalul
          lcd.clear();
          for (int i = 0; i < cardCount; ++i) {
            lcd.print(dealerCards[i]);
            lcd.print(" ");
          }
          lcd.setCursor(0, 1);
          lcd.print("Total: ");
          lcd.print(dealerTotal);
          delay(3000);
          lcd.clear();  // Asteptam 3 secunde inainte de a reveni la meniu
        }
      
    }
  }
  break;

    }

  }

}
}
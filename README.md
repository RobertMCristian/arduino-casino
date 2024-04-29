# arduino-casino
This Arduino project implements a mini casino that features three popular games: roulette, blackjack, and barbut. The hardware components used include an Arduino Uno microcontroller, an RFID Scanner RC522, an LCD display, and a joystick, all housed within a shoebox casing.

Functionality:

Roulette:
Upon scanning a valid RFID card, the user is presented with the option to play roulette.
The user navigates the menu using the joystick and selects the roulette option.
Pressing the joystick button initiates the roulette wheel spin.
The LCD displays a sequence of randomly generated numbers representing the roulette wheel spins.
After 15 spins, the final number is displayed along with its color (red, black, or green).
The result is shown for 3 seconds before returning to the main menu.


Blackjack:
Upon selecting the blackjack option from the menu, the game begins.
The LCD displays the dealer's first card and a "?" for the second card.
The user decides whether to draw another card using the joystick.
If the user chooses to draw, a new card is added to the dealer's hand, and the total is updated.
The process continues until the user decides to stand or until the total exceeds 21.
After the user's turn, the dealer reveals their second card and draws cards until their total is 17 or higher.
The final hands and totals are displayed, and the winner is determined.
The result is shown for 3 seconds before returning to the main menu.


Barbut:
Upon selecting the barbut option from the menu, the game begins.
Each player takes turns rolling two dice.
The LCD displays the sum of the dice rolls for each player.
After both players have rolled, their totals are compared, and the winner is determined.
The result is shown for 3 seconds before returning to the main menu.


Setup:

-Connect the hardware components as per the provided circuit diagram.

-Upload the Arduino code to the Arduino Uno microcontroller.

-Power on the system and interact with the games using the joystick and RFID scanner.


Note:
Ensure that valid RFID cards are used for authentication.
Follow proper safety precautions while handling electronic components and wiring.
This project is for educational and entertainment purposes only and should not be used for real gambling.

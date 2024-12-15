#include <LiquidCrystal.h>  // Include the LiquidCrystal library for controlling LCD

// Pin definitions for switches and LCD connections
#define S1 7
#define S2 6
#define S3 5
#define S4 4
#define S5 3

LiquidCrystal lcd(13, 12, 11, 10, 9, 8);  // Initialize the LCD with pin numbers

// Array to hold vote counts for each candidate (A, B, C, D)
int votes[4] = {0, 0, 0, 0};

void setup() {
    // Set switches as input pins
    pinMode(S1, INPUT);
    pinMode(S2, INPUT);
    pinMode(S3, INPUT);
    pinMode(S4, INPUT);
    pinMode(S5, INPUT);

    // Initialize the LCD with 16 columns and 2 rows
    lcd.begin(16, 2);
    lcd.print("Electronic Voting");
    lcd.setCursor(0, 1);
    lcd.print("Machine");
    delay(4000);  // Wait for 4 seconds to show the message

    // Set all switches to HIGH to avoid floating inputs
    digitalWrite(S1, HIGH);
    digitalWrite(S2, HIGH);
    digitalWrite(S3, HIGH);
    digitalWrite(S4, HIGH);
    digitalWrite(S5, HIGH);

    lcd.clear();  // Clear the LCD screen
    lcd.setCursor(1, 0);
    lcd.print("A B C D");
}

void loop() {
    // Display the vote count for each option
    displayVotes();

    // Check each switch and increment corresponding vote count
    checkVote(S1, 0);  // S1 corresponds to vote for A
    checkVote(S2, 1);  // S2 corresponds to vote for B
    checkVote(S3, 2);  // S3 corresponds to vote for C
    checkVote(S4, 3);  // S4 corresponds to vote for D

    // Check if the result button (S5) is pressed
    if (digitalRead(S5) == 0) {
        showResult();
        resetVotes();
    }
}

// Function to display the current vote counts on the LCD
void displayVotes() {
    lcd.setCursor(0, 0);
    lcd.print("A: ");
    lcd.print(votes[0]);
    lcd.setCursor(5, 0);
    lcd.print("B: ");
    lcd.print(votes[1]);
    lcd.setCursor(9, 0);
    lcd.print("C: ");
    lcd.print(votes[2]);
    lcd.setCursor(13, 0);
    lcd.print("D: ");
    lcd.print(votes[3]);
}

// Function to check if a switch is pressed and update the corresponding vote count
void checkVote(int switchPin, int candidateIndex) {
    if (digitalRead(switchPin) == 0) {
        votes[candidateIndex]++;
        while (digitalRead(switchPin) == 0);  // Wait until the button is released
    }
}

// Function to calculate and display the result
void showResult() {
    int maxVotes = votes[0];
    int winnerIndex = 0;

    // Find the candidate with the maximum votes
    for (int i = 1; i < 4; i++) {
        if (votes[i] > maxVotes) {
            maxVotes = votes[i];
            winnerIndex = i;
        }
    }

    // Display the winner
    lcd.clear();
    lcd.print("Winner: ");
    switch (winnerIndex) {
        case 0:
            lcd.print("A");
            break;
        case 1:
            lcd.print("B");
            break;
        case 2:
            lcd.print("C");
            break;
        case 3:
            lcd.print("D");
            break;
    }
    delay(3000);  // Display the result for 3 seconds
    lcd.clear();
}

// Function to reset vote counts for the next round
void resetVotes() {
    for (int i = 0; i < 4; i++) {
        votes[i] = 0;
    }
}

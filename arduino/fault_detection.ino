#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// Pin Definitions for Push Buttons
const int buttonD1 = 2;  // Push button D1
const int buttonD2 = 3;  // Push button D2
const int buttonD3 = 4;  // Push button D3
const int buttonD4 = 5;  // Push button D4

// DFPlayer Mini Connections
const int DF_RX = 10;    // RX pin to DFPlayer Mini TX
const int DF_TX = 11;    // TX pin to DFPlayer Mini RX

SoftwareSerial mySerial(DF_RX, DF_TX);
DFRobotDFPlayerMini myDFPlayer;

// OLED Configuration
#define SCREEN_WIDTH 128  // OLED display width
#define SCREEN_HEIGHT 64  // OLED display height
#define OLED_RESET    -1  // Reset pin not used
#define OLED_I2C_ADDRESS 0x3C  // I2C address for the OLED screen (common value is 0x3C)

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

// Button States
int D1 = 0;
int D2 = 0;
int D3 = 0;
int D4 = 0;

void setup() {
  Serial.begin(9600);
  mySerial.begin(9600);

  // Initialize DFPlayer Mini
  if (!myDFPlayer.begin(mySerial)) {
    Serial.println(F("DFPlayer Mini not detected!"));
    while (true);  // Halt if DFPlayer Mini initialization fails
  }
  Serial.println(F("DFPlayer Mini Initialized."));
  myDFPlayer.volume(80); // Set volume to 40

  // Initialize OLED
  if (!display.begin(SSD1306_SWITCHCAPVCC, OLED_I2C_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed!"));
    while (true);  // Halt if OLED doesn't initialize
  }

  // Clear OLED
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.println(F("OLED Initialized"));
  display.display();

  // Initialize Push Buttons with Pull-up Resistor
  pinMode(buttonD1, INPUT_PULLUP);
  pinMode(buttonD2, INPUT_PULLUP);
  pinMode(buttonD3, INPUT_PULLUP);
  pinMode(buttonD4, INPUT_PULLUP);

  Serial.println(F("Setup Complete"));
}

void loop() {
  // Read Push Button States
  D1 = digitalRead(buttonD1);
  D2 = digitalRead(buttonD2);
  D3 = digitalRead(buttonD3);
  D4 = digitalRead(buttonD4);

  // Perform XOR Operations to calculate syndrome
  int P1 = D1 ^ D2;
  int P2 = D2 ^ D3;
  int P3 = D1 ^ D2 ^ D4;

  // Calculate Syndrome
  int syndrome = (P3 << 2) | (P2 << 1) | P1;

  // Handle each syndrome
  switch (syndrome) {
    case 4: // 1111
      playAudio(1, "0001.mp3");  // Play "Stable Signal" audio
      displayStableSignal();
      break;

    case 3: // 0111
      playAudio(2, "0002.mp3");
      displayData(syndrome, "34.3N", "118.2W");  // Correct latitude and longitude
      break;

    case 5: // 1011
      playAudio(3, "0003.mp3");
      displayData(syndrome, "34.2N", "118.2W");
      break;

    case 6: // 1101
      playAudio(4, "0004.mp3");
      displayData(syndrome, "40.71N", "74.0W");
      break;

    case 0: // Special case for Button 4 (1110)
      if (D1 == 1 && D2 == 1 && D3 == 1 && D4 == 0) { // Confirm it's Button 4 pressed
        playAudio(5, "0005.mp3"); // Play audio file 0005.mp3
        displayTriggerRequired(); // Display "Trigger Required" message
      } else {
        displayData(syndrome, "53.9S", "78.2N"); // Default condition
      }
      break;

    default:
      displayData(syndrome, "53.9S", "78.2N");  // Default values
      break;
  }

  delay(2500);  // Delay 2.5 seconds before next update
}

// Function to play audio and display message in Serial Monitor
void playAudio(int track, const char *fileName) {
  myDFPlayer.play(track);
  Serial.print(F("Playing: "));
  Serial.println(fileName);
}

// Function to display "Stable Signal" message
void displayStableSignal() {
  display.clearDisplay();
  display.setTextSize(2);
  display.setCursor(0, 10);
  display.println(F("Stable"));
  display.setCursor(0, 40);
  display.println(F("Signal"));
  display.display();
  Serial.println(F("Displaying Stable Signal"));
}

// Function to display "Trigger Required" message
void displayTriggerRequired() {
  display.clearDisplay();

  // Adjust font size to fit text properly
  display.setTextSize(2); // Medium size for "Trigger"
  display.setCursor(0, 10);
  display.println(F("Trigger"));

  display.setTextSize(2); // Medium size for "Required"
  display.setCursor(0, 40);
  display.println(F("Required"));

  display.display();

  // Debugging log
  Serial.println(F("Trigger Required displayed on OLED"));
}

// Function to display syndrome and coordinates
void displayData(int syndrome, String latitude, String longitude) {
  display.clearDisplay();

  // Syndrome
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print(F("Syndrome: "));
  display.println(syndrome);

  // Latitude
  display.setCursor(0, 20);
  display.print(F("Lat: "));
  display.println(latitude);

  // Longitude
  display.setCursor(0, 40);
  display.print(F("Long: "));
  display.println(longitude);

  display.display();

  // Output to Serial Monitor
  Serial.print(F("Syndrome: "));
  Serial.println(syndrome);
  Serial.print(F("Latitude: "));
  Serial.println(latitude);
  Serial.print(F("Longitude: "));
  Serial.println(longitude);
}
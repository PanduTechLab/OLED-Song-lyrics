#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

struct LyricLine {
  const char* text;
};

LyricLine lyrics[] = {
  { "I love it" },
  { "when you" },
  { "call me" },
  { "senorita" },
  { "I wish" },
  { "I could" },
  { "pretend" },
  { "I didn't" },
  { "need you" },
  { "But every" },
  { "touch is ooh" },
  { "la-la-la" },
  { "It's true" },
  { "la-la-la" },
  { "I should be" },
  { "runnin'" },
  { "You keep me" },
  { "coming for ya" },
};

const int numLines  = sizeof(lyrics) / sizeof(lyrics[0]);
int currentLine     = 0;

#define CHAR_DELAY   80
#define HOLD_DELAY  1400
#define TEXT_SIZE      2
#define CHAR_HEIGHT   16
#define MAX_COLS       9

// Split text into two lines at the last space before MAX_COLS
void splitText(const char* text, char* line1, char* line2) {
  int len = strlen(text);

  if (len <= MAX_COLS) {
    strcpy(line1, text);
    line2[0] = '\0';
    return;
  }

  int splitAt = MAX_COLS;
  for (int i = MAX_COLS; i >= 0; i--) {
    if (text[i] == ' ') { splitAt = i; break; }
  }

  strncpy(line1, text, splitAt);
  line1[splitAt] = '\0';
  strcpy(line2, text + splitAt + 1);
}

// Draw partial text centered on screen
void drawTyping(int idx, int charCount) {
  display.clearDisplay();

  char line1[32], line2[32];
  splitText(lyrics[idx].text, line1, line2);

  bool twoLines = (line2[0] != '\0');

  // Calculate Y positions for centering
  int text1Y, text2Y;
  if (twoLines) {
    text1Y = (SCREEN_HEIGHT - (CHAR_HEIGHT * 2 + 4)) / 2;
    text2Y = text1Y + CHAR_HEIGHT + 4;
  } else {
    text1Y = (SCREEN_HEIGHT - CHAR_HEIGHT) / 2;
    text2Y = -1;
  }

  display.setTextSize(TEXT_SIZE);
  display.setTextColor(SSD1306_WHITE);

  // --- Type line 1 ---
  int line1Len = strlen(line1);
  int show1    = min(charCount, line1Len);

  char partial1[32] = "";
  strncpy(partial1, line1, show1);
  partial1[show1] = '\0';

  // Center horizontally based on the full width of the line
  int16_t bx, by; uint16_t bw, bh;
  display.getTextBounds(line1, 0, 0, &bx, &by, &bw, &bh);
  int text1X = (SCREEN_WIDTH - bw) / 2;

  display.setCursor(text1X, text1Y);
  display.print(partial1);

  // --- Type line 2 ---
  if (twoLines && charCount > line1Len) {
    int show2 = min(charCount - line1Len, (int)strlen(line2));
    char partial2[32] = "";
    strncpy(partial2, line2, show2);
    partial2[show2] = '\0';

    display.getTextBounds(line2, 0, 0, &bx, &by, &bw, &bh);
    int text2X = (SCREEN_WIDTH - bw) / 2;

    display.setCursor(text2X, text2Y);
    display.print(partial2);
  }

  display.display();
}

void setup() {
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  display.setTextSize(TEXT_SIZE);
  display.setTextColor(SSD1306_WHITE);
  display.setTextWrap(false);
  display.display();
}

void loop() {
  char line1[32], line2[32];
  splitText(lyrics[currentLine].text, line1, line2);

  int totalChars = strlen(line1) + strlen(line2);

  for (int c = 1; c <= totalChars; c++) {
    drawTyping(currentLine, c);
    delay(CHAR_DELAY);
  }

  delay(HOLD_DELAY);

  currentLine++;
  if (currentLine >= numLines) currentLine = 0;
}
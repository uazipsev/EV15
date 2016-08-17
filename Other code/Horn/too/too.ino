//#include "pitches.h"

void setup() {
    delay(500);
    tone(11, 3300);

    delay(500);
    tone(11, 1000);

    delay(500);
    tone(11, 3300);

    delay(500);
    tone(11, 1000);

    delay(500);
    tone(11, 3300);

    delay(500);
    tone(11, 1000);

    delay(500);
    // stop the tone playing:
    noTone(11);
}

void loop() {
  // no need to repeat the melody.
}

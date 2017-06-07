int analogValue = 0;

void setup() {
  for (int i = 0; i<7; ++i) {
    pinMode(i, OUTPUT);
  }
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);

  digitalWrite(12, HIGH);
  
  byte seg[] = {
    B01000000,
    B01111001,
    B00100100, 
    B00110000, 
    B00011001, 
    B00010010, 
    B00000010, 
    B01111000, 
    B00000000, 
    B00010000
  };
  PORTD = seg[9];
  int ones = 0;
  int tens = 0;
  while(1) {
    analogValue = analogRead(0);
    tens = (analogValue-15)/10;
    ones = tens%10;
    tens = tens/10;
    update_display(seg[ones], seg[tens]);
    for (long int i = 0; i < 100000; ++i) {
      update_display(seg[ones], seg[tens]);
    }
    ones++;
    if (ones>9) {tens++; ones = 0;}
    if (tens>9) tens=0;
  }
}

void loop() {
}

void update_display(byte lower, byte upper) {
  if (PORTB == B00010000) {
    PORTB = B00000000;
    PORTD = upper;
    PORTB = B00100000;
  }
  else {
    PORTB = B00000000;
    PORTD = lower;
    PORTB = B00010000;
  }
}


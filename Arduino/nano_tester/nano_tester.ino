#include <Dots.h>
#include <Bounce.h>
#include <avr/pgmspace.h>

#define LED 4
#define BUTTON 5
#define LONG_PUSH 1500
#define DOUBLE_PUSH 500
#define ASCII_OFFSET 0x20

const unsigned long PROGMEM ascii_font[192]=
{
    0x00000000, 0x00000000, 0x18181818, 0x00180018, 0x00003636, 0x00000000, 0x367F3636, 0x0036367F, 
    0x3C067C18, 0x00183E60, 0x1B356600, 0x0033566C, 0x6E16361C, 0x00DE733B, 0x000C1818, 0x00000000, 
    0x0C0C1830, 0x0030180C, 0x3030180C, 0x000C1830, 0xFF3C6600, 0x0000663C, 0x7E181800, 0x00001818, 
    0x00000000, 0x0C181800, 0x7E000000, 0x00000000, 0x00000000, 0x00181800, 0x183060C0, 0x0003060C, 
    0x7E76663C, 0x003C666E, 0x181E1C18, 0x00181818, 0x3060663C, 0x007E0C18, 0x3860663C, 0x003C6660, 
    0x33363C38, 0x0030307F, 0x603E067E, 0x003C6660, 0x3E060C38, 0x003C6666, 0x3060607E, 0x00181818,
    0x3C66663C, 0x003C6666, 0x7C66663C, 0x001C3060, 0x00181800, 0x00181800, 0x00181800, 0x0C181800, 
    0x06186000, 0x00006018, 0x007E0000, 0x0000007E, 0x60180600, 0x00000618, 0x3060663C, 0x00180018, 

    0x5A5A663C, 0x003C067A, 0x7E66663C, 0x00666666, 0x3E66663E, 0x003E6666, 0x06060C78, 0x00780C06, 
    0x6666361E, 0x001E3666, 0x1E06067E, 0x007E0606, 0x1E06067E, 0x00060606, 0x7606663C, 0x007C6666, 
    0x7E666666, 0x00666666, 0x1818183C, 0x003C1818, 0x60606060, 0x003C6660, 0x0F1B3363, 0x0063331B, 
    0x06060606, 0x007E0606, 0x6B7F7763, 0x00636363, 0x7B6F6763, 0x00636373, 0x6666663C, 0x003C6666, 
    0x3E66663E, 0x00060606, 0x3333331E, 0x007E3B33, 0x3E66663E, 0x00666636, 0x3C0E663C, 0x003C6670, 
    0x1818187E, 0x00181818, 0x66666666, 0x003C6666, 0x66666666, 0x00183C3C, 0x6B636363, 0x0063777F, 
    0x183C66C3, 0x00C3663C, 0x183C66C3, 0x00181818, 0x0C18307F, 0x007F0306, 0x0C0C0C3C, 0x003C0C0C, 
    0x180C0603, 0x00C06030, 0x3030303C, 0x003C3030, 0x00663C18, 0x00000000, 0x00000000, 0x003F0000, 

    0x00301818, 0x00000000, 0x603C0000, 0x007C667C, 0x663E0606, 0x003E6666, 0x063C0000, 0x003C0606, 
    0x667C6060, 0x007C6666, 0x663C0000, 0x003C067E, 0x0C3E0C38, 0x000C0C0C, 0x667C0000, 0x3C607C66, 
    0x663E0606, 0x00666666, 0x18180018, 0x00301818, 0x30300030, 0x1E303030, 0x36660606, 0x0066361E,
    0x18181818, 0x00301818, 0x7F370000, 0x0063636B, 0x663E0000, 0x00666666, 0x663C0000, 0x003C6666, 
    0x663E0000, 0x06063E66, 0x667C0000, 0x60607C66, 0x663E0000, 0x00060606, 0x063C0000, 0x003E603C, 
    0x0C3E0C0C, 0x00380C0C, 0x66660000, 0x007C6666, 0x66660000, 0x00183C66, 0x63630000, 0x00367F6B, 
    0x36630000, 0x0063361C, 0x66660000, 0x0C183C66, 0x307E0000, 0x007E0C18, 0x0C181830, 0x00301818, 
    0x18181818, 0x00181818, 0x3018180C, 0x000C1818, 0x003B6E00, 0x00000000, 0x00000000, 0x00000000, 
};

byte demo_image[] = { 
  //カ
  B00000100,
  B10000100,
  B01111111,
  B00000100,
  B00000100,
  B10000100,
  B01111100,
  B00000000,
  //ワ
  B00001110,
  B00000010,
  B00000010,
  B10000010,
  B10000010,
  B01000010,
  B00111110,
  B00000000,
  //ハ
  B10000000,
  B01110000,
  B00001110,
  B00000000,
  B00001110,
  B01110000,
  B10000000,
  B00000000,
  //ラ
  B00001010,
  B00001010,
  B10001010,
  B10001010,
  B10001010,
  B01001010,
  B00111010,
  B00000000,
  //デ
  B00001010,
  B10001010,
  B10001010,
  B10001010,
  B01111010,
  B00001011,
  B00001000,
  B00000011,
  //ン
  B10000010,
  B10000010,
  B10000010,
  B10000000,
  B10000000,
  B01000000,
  B00111110,
  B00000000,
  //キ
  B00010010,
  B00010010,
  B00010010,
  B11111111,
  B00010010,
  B00010010,
  B00010010,
  B00000000
  };

byte image_data[8]; 
int mode_list[] = { 0, 8, 9, 98, 99 };
int mode_pointer = 0;
int mode = mode_list[mode_pointer];

long interval[] = { 1000, 500, 250, 100, 75, 50, 20, 10 };
unsigned int speed = 0;
unsigned long previousMillis = 0;
unsigned long pushButtonMillis = 0;
unsigned long previousButtonMillis = 0;

boolean debug = false;

// setup Bounce
Bounce button = Bounce(BUTTON, 5);

// setup dots
// for SZ*10788 (anode-common)
// ROW PIN_NO : 9, 14 8, 12, 1, 7, 2, 5
// COL PIN_NO : 13, 3, 4, 10, 6, 11, 15, 16
Dots dots = Dots(6, 11, 3, 9, 14, 2, 15, 18, //ROW
                 10, 16, 17, 7, 19, 8, 12, 13); //COL
                 
// setup
void setup() {                
  // initialize serial port.
  Serial.begin(9600);
  
   // initialize the digital pin as an output.
  pinMode(LED, OUTPUT);
  
  // initialize the digital pin as an input.
  pinMode(BUTTON, INPUT);
  digitalWrite(BUTTON, HIGH);
  button.write(HIGH); // use pullup register.
  
  // initialize randmom function.
  randomSeed(analogRead(0));
  
  // initialize dots
  dots.begin();
  
  // output starting message.
  Serial.println("Start Nanoduino Version 0.1");
  Serial.print("mode : ");
  Serial.println(mode);
  Serial.print("speed : ");
  Serial.print(interval[speed]);
  Serial.println("ms");
  blinker(LED, 2, 50);
}

// the loop routine runs over and over again forever:
void loop() {
  unsigned long currentMillis = millis();

  // checkStatus();
 
  switch (mode) {
    case 0:
      randomize();
      break;
    case 8:
      anime_demo();
      break;
    case 9:
      scroll_demo();
      break;
    case 98:
      pin_test();
      break;
    case 99:
      row_col_test();
      break;
  }
}

boolean checkCommand() {
   if (Serial.available() > 0) {
    char c = Serial.read();
    
    switch (c) {
      // regular command
      case 'r':
        mode = 0;
        Serial.print("mode : ");
        Serial.println(mode);
        blinker(LED, 1, 50);
        break;

      case 'a':
        Serial.write(c);
        Serial.println("");
        mode = 8;
        Serial.print("mode : ");
        Serial.println(mode);
        blinker(LED, 1, 50);
        break;
      
      case 's':
        Serial.write(c);
        Serial.println("");
        mode = 9;
        Serial.print("mode : ");
        Serial.println(mode);
        blinker(LED, 1, 50);
        break;
        
      case 'S':
        changeSpeed();
        blinker(LED, 1, 50);
        return false;
        
      // hidden commands
      
      // debug mode
      case 'D':
       Serial.write(c);
       Serial.println("");
       if (debug) {
         debug = false;
         Serial.println("debug mode : false");
         blinker(LED, 3, 200);
       } else {
         debug = true;
         Serial.println("debug mode : true");
         blinker(LED, 3, 200);
       }
       break;
        
      case 'T':
        Serial.write(c);
        Serial.println("");
        mode = 99;
        Serial.print("mode : ");
        Serial.println(mode);
        blinker(LED, 3, 200);
        break;
        
      case 't':
        Serial.write(c);
        Serial.println("");
        mode = 98;
        Serial.print("mode : ");
        Serial.println(mode);
        blinker(LED, 3, 200);
        break;
    }
    return true;
  }
  return false;
}

boolean checkButton() {
  unsigned long currentButtonMillis = millis();
  
  if (button.update()) { 
    if (button.read() == LOW) {
      digitalWrite(LED, HIGH);
      pushButtonMillis = currentButtonMillis;
    }  else {
      if (debug) {
        Serial.print("pushButtonMillis : ");
        Serial.println(pushButtonMillis);
        Serial.print("currentButtonMillis : ");
        Serial.println(currentButtonMillis);
        Serial.print("previousButtonMillis : ");
        Serial.println(previousButtonMillis);
      }
      if (currentButtonMillis - pushButtonMillis > LONG_PUSH) {
        Serial.println("BUTTON LONG_PUSH");
      } else {
        if (currentButtonMillis - previousButtonMillis < DOUBLE_PUSH) {
            Serial.println("BUTTON DOUBLE_PUSH");
            mode_pointer++;
            if (mode_pointer > (sizeof(mode_list)/sizeof(int) - 1)) mode_pointer = 0;
            mode = mode_list[mode_pointer];
            Serial.print("mode = ");
            Serial.println(mode);
            previousButtonMillis = currentButtonMillis; 
           digitalWrite(LED, LOW);
           return true;
        } else {
          Serial.println("BUTTON PUSH");
          changeSpeed();
        }
      }
      previousButtonMillis = currentButtonMillis; 
      digitalWrite(LED, LOW);
    }
  }
  return false;
}

void changeSpeed() {
  speed++;
  if (speed > (sizeof(interval)/sizeof(long) - 1)) speed = 0;
  Serial.print("SPEED = ");
  Serial.print(interval[speed]);
  Serial.println("ms");
}    

boolean checkStatus() {
  unsigned long currentMillis = millis();
  while(currentMillis - previousMillis < interval[speed]) {
    if (checkCommand()) {
      previousMillis = currentMillis;
      return true;
    }
    if (checkButton()) {
      previousMillis = currentMillis;
      return true;
    }
    currentMillis = millis();
  }
  previousMillis = currentMillis;
  return false;
}
    

void setChar(char c) {
  byte ascii_char[8];
  int i;
  unsigned long upper = ascii_font[c - ASCII_OFFSET];
  unsigned long lower = ascii_font[c - ASCII_OFFSET];
  for (i = 3; i > 0; i--) {
    ascii_char[i] = lowByte(upper);
    upper = upper >> 8;
  }
  for (i = 3; i > 0; i--) {
    ascii_char[i+4] = lowByte(lower);
    lower = lower >> 8;
  }
  // dots.write(ascii_char);
}

void blinker(uint8_t pin, int count, unsigned long time) {
  int i;
  for (i = 0; i < count; i ++) {
    digitalWrite(pin, HIGH);
    delay(time);
    digitalWrite(pin, LOW);
    delay(time);
  }
}

void randomize() {
  int i;
  for(i = 0; i < 8; i ++) {
    image_data[i] = random(0xFF);
  }
  dots.write(0, image_data, 8);
  if(checkStatus()) return;
}

void scroll(byte *image, int size) {
  int i, j;
  dots.clear();
  if (debug) {
    Serial.print("size : ");
    Serial.println(size);
  }
 
  for (i = 0; i < size; i++) {
    if (debug) {
      Serial.print("start_point : ");
      Serial.println(i);
    }
    for (j = 0; j <  8; j++) {
      if ((i + j) < size) {
        dots.write(j, image[i + j]);
      } else {
        dots.write(j, image[i + j - size]);
      }
    }
    if (checkStatus()) {
      return;
    }
  }
}

void animation(byte *image, int size) {
  int i, j;
  dots.clear();
  if (debug) {
    Serial.print("size : ");
    Serial.println(size);
  }
  
  for (i = 0; i < size; i = i + 8) {
     j =  i + 8;
     if (debug) {
       Serial.print("start_point : ");
       Serial.println(i);
       Serial.print("stop_point : ");
       Serial.println(j);
     }
     if (j < size) {
       dots.write(i, image, j);
     } else {
       dots.write(i, image, size);
     }
     if (checkStatus()) {
       return;
     }
  }
}

// demo mode
void scroll_demo() {
  int size = sizeof(demo_image);
  scroll(demo_image, size);
}

void anime_demo() {
  int size = sizeof(demo_image);
  animation(demo_image, size);
}

// debug mode
void pin_test() {
  int pins[] = { 14, 15, 16, 17, 18, 19, 2, 3, //ROW
                 13, 12, 11, 10, 9, 8, 7,6 }; //COL
  int i, j;
  
  dots.end();
  for (i = 0; i < 16; i++) {
    pinMode(pins[i], OUTPUT);
    digitalWrite(pins[i], LOW);
  }
  
  for (i = 0; i < 16; i++) {
    digitalWrite(pins[i], HIGH);
     if (debug) {
      Serial.print("Active Pin : ");
      Serial.println(pins[i]);
    }
    for (j = 0; j < 16; j++) {
      if (j == i) continue;
      pinMode(pins[j], INPUT);
      int pin_status = digitalRead(pins[j]);
      if ((pin_status == HIGH) && debug) {
        Serial.print("Passive Pin : ");
        Serial.println(pins[j]);
      }
      pinMode(pins[j], OUTPUT);
    }

    if (checkStatus()) {
      dots.begin();
      return;
    }
    digitalWrite(pins[i], LOW);
  }
}
  
 void row_col_test() {
   byte d[] = { 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
   int i, j;
   for (i = 0; i < 8; i++) {
     for (j = 0; j < 8; j++) {
       d[i] = 0x1 << j;
       dots.write(0, d, 8);
       if (debug) {
         Serial.print("Active Dot : ");
         Serial.print(i);
         Serial.print(",");
         Serial.println(j);
       }
       if (checkStatus()) return;
     }
     d[i] = 0x0;
   }
}

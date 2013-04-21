#include <Dots.h>
#include <EEPROM.h>
#include <Button.h>
#include <SerialCommand.h>
#include <Logging.h>

#define LED 4
#define BUTTON 5
#define MAX_IMAGE_BUFFER 256

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

byte image_size = 0;
byte image_buffer[MAX_IMAGE_BUFFER];
  

unsigned long previousMillis = 0;
unsigned int mode_list[] = { 0, 1, 2, 3, 4, 99 };
unsigned int mode_pointer = 0;
unsigned int mode = 0;

unsigned int interval_list[] = { 1000, 500, 100, 75, 50, 20, 10 };
unsigned int interval_pointer = 0;
unsigned int interval = interval_list[interval_pointer];

SerialCommand command;
Button button = Button(BUTTON, LOW);
Dots dots = Dots(6, 11, 3, 9, 14, 2, 15, 18, 10, 16, 17, 7, 19, 8, 12, 13); 
Logging logging = Logging(LOG_LEVEL_DEBUG);

void setup() {
  Serial.begin(9600);
  randomSeed(analogRead(0));
  dots.begin();
  digitalWrite(BUTTON, HIGH);
  
  command.addCommand("m", setMode);
  command.addCommand("E", setImage);
  command.addCommand("S", changeInterval);
  command.addCommand("P", printImage);
  command.addDefaultHandler(unrecognized);
  // debug mode
  //command.addCommand("D",debugger());
  loadImage();  
  Serial.println("Start nanoduino v1.0");
  button.listen();
}

void loop() {
  switch (mode) {
    case 0:
      randomize();
      break;
    case 1:
      // animation();
      break;
    case 2:
      // scroll();
      break;
    case 3:
      demo();
      break;
    case 99:
      testDot();
      break;
  }
}

boolean checkStatus() {
  unsigned long currentMillis = millis();
  while ( currentMillis - previousMillis < interval) {
    if (Serial.available()) logging.Debug("Serial recieved!"CR);
    command.readSerial();
    if (button.onChange(0)) {  
      if (button.onPress()) {
        while ((currentMillis + button.getDoubleClickDelay()) > millis()) {
          button.listen();
          if (button.onDoubleClick()) {
            logging.Debug("Button DoubleClick"CR);
            // changeMode();
            return true;
          }
        }
        logging.Debug("Button Press"CR);
        // changeInterval();
      }
      
    }
    if (button.isHold()) {
      logging.Debug("Button Hold"CR);
    }
    currentMillis = millis();
  }
  previousMillis = currentMillis;
  return false;
}

void changeMode() {
  mode_pointer++;
  if (mode_pointer > sizeof(mode_list) - 1) {
    mode_pointer = 0;
  }
  blinker(LED, 2, 50);
  mode = mode_list[mode_pointer];
  logging.Debug("set mode = %i"CR, mode);
}

void setMode() {
  char *arg;
  unsigned int i,m;
  logging.Debug("start setMode"CR);
  arg = command.next();
  Serial.println(arg);
  if (arg != NULL) {
    m = atoi(arg);
    for (i = 0; i < sizeof(mode_list) - 1; i++) {
      if(m == mode_list[i]) {
        blinker(LED, 2, 50);
        mode = i;
        logging.Debug("set mode = %i"CR, mode);
        return;
      }
    }
  }
}

void setImage() {
  char *arg;
  int i;
  byte hex;
  
  arg = command.next();
  if (arg != NULL) {
    logging.Debug("argument is : %s"CR, arg);
    i = 0;
    while (arg[i] != NULL) {
      hex = atoh(arg[i]);
      logging.Debug("HEX = %x"CR, hex);
      EEPROM.write(i + 1, hex);
      image_buffer[i] = hex;
      i++;
    }
    EEPROM.write(0, i);
    image_size = i;
    logging.Debug("size = %i"CR, image_size);
  }
}

void loadImage() {
  int i;
  image_size = EEPROM.read(0);
  
  for (i = 0; i < image_size; i++) {
    image_buffer[i] = EEPROM.read(i + 1);
  }
  printImage();
}

byte atoh(char c) {
  switch (c) {
    case '0':
    case '1':
    case '2':
    case '3':
    case '4':
    case '5':
    case '6':
    case '7':
    case '8':
    case '9':
      return c - '0';
    case 'A':
    case 'a':
      return 0xA;
    case 'B':
    case 'b':
      return 0xB;
    case 'C':
    case 'c':
      return 0xC;
    case 'D':
    case 'd':
      return 0xD;
    case 'E':
    case 'e':
      return 0xE;
    case 'F':
    case 'f':
      return 0xF;
  }
  return 0;
}

void printImage() {
  _printImage(image_buffer, image_size);
}
      
void _printImage(byte *image, int size) {
  int i;
  Serial.print("image_size = ");
  Serial.println(size);
  Serial.println("image : ");
  for (i = 0; i < size; i++) {
    if ((i % 8) == 0) Serial.println("");
    Serial.println(image[i], BIN);
  }
}
      
void changeInterval() {
  interval_pointer++;
  if (interval_pointer > sizeof(interval_list) - 1) {
    interval_pointer = 0;
  }
  blinker(LED, 1, 50);
  interval = interval_list[interval_pointer];
  logging.Debug("interval = %i"CR, interval);
}

void blinker(int pin, int count, int time) {
  int i;
  for (i = 0; i < count; i++) {
    digitalWrite(pin, HIGH);
    delay(time);
    digitalWrite(pin, LOW);
    delay(time);
  }
}
 

// mode methods

void randomize() {
  int i;
  for (i = 0; i < 8; i++) {
    dots.write(i, random(0xFF));
  }
  if (checkStatus()) return;
}

void animation(byte *image, int size) {
  int i;
  dots.clear();
  for (i = 0; i < size - 8; i = i + 8) {
    dots.write(i, image, i + 8);
  }
  if (checkStatus()) return;
}

void scroll(byte *image, int size) {
  int i, j;
  for (i = 0; i < size; i++) {
    for(j = i; j < i + 8; j++) {
      if ( j < size) {
        dots.write(j, image[i + j]); 
      } else {
        dots.write(j, image[i + j - size]);
      }
    }
    if (checkStatus()) return;
  }
}

void demo() {
  int size = sizeof(demo_image);
  animation(demo_image, size);
  scroll(demo_image, size);
}

void testDot() {
  byte d[] = {  0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0, 0x0 };
  int i, j;
  for (i = 0; i < 8; i++) {
    for (j = 0; j < 8; j++) {
      d[i] = 0x1 << j;
      dots.write(0, d, 8);
      if (checkStatus()) return;
    }
    d[i] = 0x0;
  }
}
      
void unrecognized() {
  Serial.println("?");
}


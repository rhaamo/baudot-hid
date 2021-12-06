#ifndef BaudotDecoder_h
#define BaudotDecoder_h

#include <Arduino.h>
#include <Keyboard.h>

class BaudotDecoder {
  public:
    static const unsigned int BIT_COUNT = 5;
    static char convertBitsToChar(int *bits);
    static unsigned int getLastIndex();
  private:
    static char _charsetLOW[33];
    static char _charsetHIGH[33];
    static int charsetLevel;
    static unsigned int _lastDecodedIndex;
};

#endif

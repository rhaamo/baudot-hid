#include "BaudotDecoder.h"

char BaudotDecoder::_charsetLOW[] = {
  0, 'T', 2, 'O', ' ', 'H', 'N', 'M', 8,
  'L', 'R', 'G', 'I', 'P', 'C', 'V', 'E', 'Z', 'D',
  'B', 'S', 'Y', 'F', 'X', 'A', 'W', 'J', 27 /* HIGH */, 'U',
  'Q', 'K', 31 /* LOW */, 32
};

char BaudotDecoder::_charsetHIGH[] = {
  0, '5', 2, '9', ' ', 5, ',', '.', '=',
  ')', '4', '%', '8', '0', ':', '=', '3', '+', 18,
  '?', '\'', '6', 22, '/', '-', '2', 26, 27,
  '7', '1', '(', 31, 32
};

// To charset low = 31 / 11111
// To charset high = 27 / 11011


unsigned int BaudotDecoder::_lastDecodedIndex = 0;
int BaudotDecoder::charsetLevel = 0;

char BaudotDecoder::convertBitsToChar(int* bits) { 
  _lastDecodedIndex = 0;
  
  for (int i = 0; i < BIT_COUNT; i++) {
    _lastDecodedIndex = _lastDecodedIndex | (bits[i] << (4 - i));  
  }
  
  if (charsetLevel == 0 && _lastDecodedIndex == 27) {
    // Switch to high level charset
    charsetLevel = 1;
    // return
    return 27;
  }

  if (charsetLevel == 1 && _lastDecodedIndex == 31) {
    // Switch to low level charset
    charsetLevel = 0;
    // return
    return 31;
  }

  switch (_lastDecodedIndex) {
      case 2:
        if (charsetLevel == 0) {
            // RET CHAR
            Serial.println();
            return '\r';
        } else {
            // Backspace
            Serial.println('\b');
            return '\b';
        }
        break;
      case 22:
        if (charsetLevel == 1) {
            Serial.print('É');
            return 'É';
        }
        break;
      case 18:
        if (charsetLevel == 1) {
            Serial.print('*');
            return '*';
        }
        break;
      case 26:
        if (charsetLevel == 1) {
            Serial.print('\a');
            return '\a';
        }
        break;
      case 5:
        if (charsetLevel == 1) {
            Serial.print('H');
            return 'H';
        }
        break;
  }

  if (_lastDecodedIndex == 27 || _lastDecodedIndex == 31) {
      // ignore further presses
      return NULL;
  }

  if (charsetLevel == 1) {
    Serial.print(_charsetHIGH[_lastDecodedIndex]);
    return _charsetHIGH[_lastDecodedIndex];
  }
  Serial.print(_charsetLOW[_lastDecodedIndex]);
  return _charsetLOW[_lastDecodedIndex];
}

unsigned int BaudotDecoder::getLastIndex() {
  return _lastDecodedIndex;
}

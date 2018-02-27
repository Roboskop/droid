/*
  Simple
  .h - Library for serial communication.
  Created by Ozan Cansel, August 11, 2016.
  Released into the public domain.
*/

#ifndef SIMPLE_SERIAL_H
#define SIMPLE_SERIAL_H

#define   _SIMPLE_SERIAL_DEFAULT_COMMAND_TIMEOUT 5
#define   _SIMPLE_SERIAL_DEFAULT_COMMAND_START '{'
#define   _SIMPLE_SERIAL_DEFAULT_COMMAND_END '}'
#define   _BUFFER_DEFAULT_ARG_SEPERATOR ','
#define   CONSOLE_OUTPUT_COMMAND           67       //{C<output>}

#include <Arduino.h> 
#include <SoftwareSerial.h>

enum _simpleSerialCommandStates {
  COMMAND_NONE = 1,
  COMMAND_START = 5,
  COMMAND_PROCESS = 10
};

inline int quick_pow10(int n)
{
  static int pow10[10] = {
    1, 10, 100, 1000, 10000,
    100000, 1000000, 10000000, 100000000, 1000000000
  };

  return pow10[n];
}

class Buffer {

  private:
    char buffer[64];
    uint8_t dataIndex = 0;
    uint8_t currentIdx = 0;
    uint8_t previousIdx = 0;
    char argSeperator = '\0';
  public:
    Buffer(char seperator) {
        argSeperator = seperator;
    }
    Buffer(){
      argSeperator = ',';
    }
    void append(char c) {
      buffer[dataIndex] = c;
      dataIndex++;
    }
    void end() {
      buffer[dataIndex] = NULL;
    }
    int readIntArg() {

      int result = 0;
      previousIdx = currentIdx;

      while (true) {

        if (buffer[currentIdx] == ',' || currentIdx == dataIndex) {
          uint8_t range = currentIdx - previousIdx;
          bool  negative = false;

          for (uint8_t i = range; i > 0; i--) {
            if(buffer[previousIdx + i - 1] == '-')
              negative = true;
            else
            result +=  (((int)buffer[previousIdx + i - 1]) - 48 ) * quick_pow10(range - i);
          }

          if(negative)
            result = -result;

          currentIdx++;
          break;
        }

        currentIdx++;
      }

      return result;
    }
    String readStrArg() {
      String str;

      while (true) {
{}
        if (buffer[currentIdx] == ',' || currentIdx == dataIndex) {
          currentIdx++;

          break;
        }

        str += buffer[currentIdx];

        currentIdx++;
      }

      return str;
    }
    void reset() {
      dataIndex = 0;
      currentIdx = 0;
      previousIdx = 0;
    }

};

class SerialWrapper {

  private:

  public:
    virtual int available() = 0;
    virtual int read() = 0;

};

class HardwareSerialWrapper : public SerialWrapper {
  private:
    HardwareSerial *serial;
  public:
    HardwareSerialWrapper(HardwareSerial *serial) {
      this->serial = serial;
    }
    int available() {
      return serial->available();
    }
    int read() {
      return serial->read();
    }
};

class SoftwareSerialWrapper : public SerialWrapper {
  private:
    SoftwareSerial *serial;
  public:
    SoftwareSerialWrapper(SoftwareSerial *serial) {
      this->serial = serial;
    }
    int available() {
      return serial->available();
    }
    int read() {
      return serial->read();
    }
};

class SimpleSerial {

  private:

    SerialWrapper *serial;
    char ch = '\0';
    uint8_t code = 0;
    uint8_t commandState = COMMAND_NONE;
    Buffer *buf;
    char commandStart = _SIMPLE_SERIAL_DEFAULT_COMMAND_START;
    char commandEnd = _SIMPLE_SERIAL_DEFAULT_COMMAND_END;
    uint16_t commandTimeout = _SIMPLE_SERIAL_DEFAULT_COMMAND_TIMEOUT;
    unsigned long commandStartTime = 0;
    void(*commandCallback)(uint8_t);
    void parseCommand();
    void checkTimeout();

  public:

       const static char COMMAND_END_CH  =  '}';
       const static char COMMAND_START_CH =  '{';
       const static char COMMAND_ARGS_SEPERATOR = ',';
    SimpleSerial(HardwareSerial *serial, void(*callback)(uint8_t), char argSeperator = _BUFFER_DEFAULT_ARG_SEPERATOR);
    SimpleSerial(SoftwareSerial *serial, void(*callback)(uint8_t), char argSeperator = _BUFFER_DEFAULT_ARG_SEPERATOR);

    void setCommandStart(char ch);

    void setCommandEnd(char ch);

    void setTimeout(uint16_t timeout);

    int readIntArg();

    String readStrArg();

    void check();

    void parseBuffer(uint8_t *buffer , int size);

};

#endif

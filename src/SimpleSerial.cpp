
#include "SimpleSerial.h"

SimpleSerial::SimpleSerial(HardwareSerial *serial, void(*callback)(uint8_t), char argSeperator) {
  this->serial = new HardwareSerialWrapper(serial);
  commandCallback = callback;
  buf = new Buffer(argSeperator);
}

SimpleSerial::SimpleSerial(SoftwareSerial *serial, void(*callback)(uint8_t), char argSeperator) {
  this->serial = new SoftwareSerialWrapper(serial);
  commandCallback = callback;
  buf = new Buffer(argSeperator);
}

void SimpleSerial::setCommandStart(char ch) {
  commandStart = ch;
}

void SimpleSerial::setCommandEnd (char ch) {
  commandEnd = ch;
}

void SimpleSerial::setTimeout(uint16_t timeout) {
  commandTimeout = timeout;
}

int SimpleSerial::readIntArg() {
  return buf->readIntArg();
}


String SimpleSerial::readStrArg() {
  return buf->readStrArg();
}

void SimpleSerial::checkTimeout() {
  if (commandState != COMMAND_NONE && ( millis() - commandStart ) <  commandTimeout) {
    commandState = COMMAND_NONE;
  }
}

void SimpleSerial::check() {
  while (serial->available())
    parseCommand();

  checkTimeout();
}

void SimpleSerial::parseCommand() {
  if (commandState == COMMAND_NONE) {
    ch = serial->read();

    if (ch == commandStart) {
      commandState = COMMAND_START;
      commandStartTime = millis();
    }

  }//Command starts
  else if (commandState == COMMAND_START) {
    code = serial->read();               //Reads command code

    if (code == commandStart) {
      commandState = COMMAND_START;
      buf->reset();
    }
    else if (code == commandEnd) {
      commandState = COMMAND_NONE;
    }
    else {
      commandState = COMMAND_PROCESS;     //After reads the command code, changes the flag as COMMAND_PROCESS
    }
  }
  else if (commandState == COMMAND_PROCESS) {
    ch = serial->read();                 //Reads args

    if (ch == commandStart) {
      commandState = COMMAND_START;
      buf->reset();
    }
    else if (ch == commandEnd) {                    //until reaches end of the command
      commandState = COMMAND_NONE;
      commandCallback(code);
      buf->reset();
    }
    else
      buf->append(ch);
  }
}

void SimpleSerial::parseBuffer(uint8_t *buffer, int size){
  for(int i = 0; i < size; i++){
    if (commandState == COMMAND_NONE) {
      ch = buffer[i];

      if (ch == commandStart) {
        commandState = COMMAND_START;
        commandStartTime = millis();
      }

    }//Command starts
    else if (commandState == COMMAND_START) {
      code = buffer[i];               //Reads command code

      if (code == commandStart) {
        commandState = COMMAND_START;
        buf->reset();
      }
      else if (code == commandEnd) {
        commandState = COMMAND_NONE;
      }
      else {
        commandState = COMMAND_PROCESS;     //After reads the command code, changes the flag as COMMAND_PROCESS
      }
    }
    else if (commandState == COMMAND_PROCESS) {
      ch = buffer[i];                 //Reads args

      if (ch == commandStart) {
        commandState = COMMAND_START;
        buf->reset();
      }
      else if (ch == commandEnd) {                    //until reaches end of the command
        commandState = COMMAND_NONE;
        commandCallback(code);
        buf->reset();
      }
      else
        buf->append(ch);
    }
  }
}

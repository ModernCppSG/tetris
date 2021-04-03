//
// Created by grilo on 27/02/2021.
//

#ifndef TETRIS_USER_INPUT_H
#define TETRIS_USER_INPUT_H

#include <fcntl.h>
#include <sys/types.h>
#include <termios.h>
#include <unistd.h>

#include <atomic>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <iomanip>
#include <iostream>
#include <list>
#include <map>
#include <mutex>
#include <queue>
#include <utility>

#define START_ESCAPE '\033'
#define MIDDLE_ESCAPE '['

// from https://stackoverflow.com/a/10995085/6609908
#define HIDE_CURSOR "\033[?25l"
#define SHOW_CURSOR "\033[?25h"

#define CLEAR_SCREEN "\033[2J"

#define MOVE_TO(x, y) \
  std::string("\033[" + std::to_string(y) + ";" + std::to_string(x) + "H")

#define PROTECT(operation, mutex_variable)                  \
  {                                                         \
    const std::lock_guard<std::mutex> lock{mutex_variable}; \
    operation;                                              \
  }

int posY = 3;
int posX = 1;

void setPosition(int x, int y) {
  posY = std::max(y, 0);
  posX = std::max(x, 0);
  // std::cout << "\033[" << y << ";" << x << "H";
  std::cout << MOVE_TO(x, y);
}
/*
void moveUp(int times = 1) {
    int posX_backup = posX;
    int posY_backup = posY;
    setPosition(0, 0);
    std::cout << std::setw(10) << "KEY_UP";
    setPosition(posX_backup, posY_backup);

    setPosition(posX, posY - times);
}

void moveRight(int times = 1) {
    int posX_backup = posX;
    int posY_backup = posY;
    setPosition(0, 0);
    std::cout << std::setw(10) << "KEY_RIGHT";
    setPosition(posX_backup, posY_backup);

    setPosition(posX + times, posY);
}

void moveDown(int times = 1) {
    int posX_backup = posX;
    int posY_backup = posY;
    setPosition(0, 0);
    std::cout << std::setw(10) << "KEY_DOWN";
    setPosition(posX_backup, posY_backup);

    setPosition(posX, posY + times);
}

void moveLeft(int times = 1) {
    int posX_backup = posX;
    int posY_backup = posY;
    setPosition(0, 0);
    std::cout << std::setw(10) << "KEY_LEFT";
    setPosition(posX_backup, posY_backup);

    setPosition(posX - times, posY);
}
*/
void clearScreen() {
  std::cout << CLEAR_SCREEN;
  setPosition(posX, posY);
}

class Key {
 public:
  Key(char value) noexcept
      : value(value), isEscaped(false), display(std::string{value}) {}

  Key(char value, bool isEscaped, std::string display) noexcept
      : value(value), isEscaped(isEscaped), display(std::move(display)) {}

  friend std::ostream& operator<<(std::ostream& os, const Key& key) {
    return os << key.display;
  }

  bool operator==(const Key& key) const { return display == key.display; }

 private:
  char value;
  bool isEscaped;
  std::string display;
};

const Key KEY_UP{'A', true, "↑"};
const Key KEY_DOWN{'B', true, "↓"};
const Key KEY_LEFT{'D', true, "←"};
const Key KEY_RIGHT{'C', true, "→"};
const Key KEY_R{'R'};
const Key KEY_SPACEBAR{' ', false, "∽"};
const Key KEY_ENTER{'\n', false, "↲"};

std::map<char, Key> mapOfKeys = {
    {'R', KEY_R},
    {' ', KEY_SPACEBAR},
};

// Singleton! //TODO is this a good idea?
class UserInput {
 public:
  static UserInput& getInstance() {
    static UserInput instance;

    return instance;
  }

  UserInput(UserInput const&) = delete;
  void operator=(UserInput const&) = delete;

  void initUserInput() {
    // get current attributes of terminal
    tcgetattr(fileno(stdin), &oldSettings);
    // copy to new settings to modify its copy and be able to restore current
    // settings
    newSettings = oldSettings;
    // setting to non-canonical and non-echo
    newSettings.c_lflag &= (~ICANON & ~ECHO);
    // change terminal NOW
    tcsetattr(fileno(stdin), TCSANOW, &newSettings);

    // unbuffered cout
    std::cout.setf(std::ios::unitbuf);

    std::cout << HIDE_CURSOR;
  }

  bool first = false;

  void loopReadInput() {
    keepLooping = true;
    while (keepLooping) {
      readInput();
    }
    
    void readInput() {
        
        char c;
        
        tv.tv_sec = 10;
        tv.tv_usec = 0;
        
        FD_ZERO( &set );
        FD_SET( fileno( stdin ), &set );
        
        int res = select( fileno( stdin )+1, &set, nullptr, nullptr, &tv );
        
        if( res > 0 )
        {
            if(!first) {
                //clearScreen();
            }
            
            first = true;
            read( fileno( stdin ), &c, 1 );
            
            switch(c) {
                case '\n':
                    PROTECT(inputQueue.push(KEY_ENTER), inputQueueMtx);
                    std::cout << KEY_ENTER;
                    break;
                case START_ESCAPE:
                    read( fileno( stdin ), &c, 1 );
                    //std::cout << c << std::endl;
                    if (c == MIDDLE_ESCAPE) {
                        read( fileno( stdin ), &c, 1 );
                        //std::cout << c << std::endl;
        
                        switch (c) {
                            case 'A':
                                PROTECT(inputQueue.push(KEY_UP), inputQueueMtx);
                                //moveUp();
                                break;
                            case 'B':
                                PROTECT(inputQueue.push(KEY_DOWN), inputQueueMtx);
                                //moveDown();
                                break;
                            case 'C':
                                PROTECT(inputQueue.push(KEY_RIGHT), inputQueueMtx);
                                //moveRight();
                                break;
                            case 'D':
                                PROTECT(inputQueue.push(KEY_LEFT), inputQueueMtx);
                                //moveLeft();
                                break;
                            default:
                                std::cerr << " DEU RUIM!";
                        }
                    }
                    break;
                default:
                    if(mapOfKeys.find(c) == mapOfKeys.end()){
                        mapOfKeys.emplace(c, c);
                    }
                    //std::cout << c;
                    PROTECT(inputQueue.push(c), inputQueueMtx);
                    //moveRight();
                    break;
            }
            
            auto oldPosX = posX;
            auto oldPosY = posY;
            //setPosition(0, 50);
            //printQueue();
            //setPosition(oldPosX, oldPosY);
        }
        else if( res < 0 )
        {
            perror( "select error" );
        }
        else
        {
            //printf( "Select timeout\n" );
        }
    }
    
    void endUserInput() {
        tcsetattr( fileno( stdin ), TCSANOW, &oldSettings );
    }
    
    Key popKey() {
        const std::lock_guard<std::mutex> lock{inputQueueMtx};
        Key key = inputQueue.front();
        inputQueue.pop();
        return key;
    }
    
    bool isEmpty() {
        return inputQueue.size() == 0;
    }
  }

  void endUserInput() { tcsetattr(fileno(stdin), TCSANOW, &oldSettings); }

  Key popKey() {
    const std::lock_guard<std::mutex> lock{inputQueueMtx};
    Key key = inputQueue.front();
    inputQueue.pop();
    return key;
  }

  bool isEmpty() { return inputQueue.size() == 0; }

  void stopLoop() { keepLooping = false; }

 private:
  UserInput(){

  };

  void printQueue() {
    std::queue<Key> copyInputQueue;
    {
      const std::lock_guard<std::mutex> lock(inputQueueMtx);
      copyInputQueue = inputQueue;
    }
    while (!copyInputQueue.empty()) {
      std::cout << copyInputQueue.front() << " ";
      copyInputQueue.pop();
    }
  }

  std::atomic<bool> keepLooping = false;

  std::queue<Key> inputQueue;
  std::mutex inputQueueMtx;

  struct termios oldSettings {
  }, newSettings{};
  fd_set set{};
  struct timeval tv {};
};

#endif  // TETRIS_USER_INPUT_H

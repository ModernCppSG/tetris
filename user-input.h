//
// Created by grilo on 27/02/2021.
//

#ifndef TETRIS_USER_INPUT_H
#define TETRIS_USER_INPUT_H

#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <queue>
#include <iomanip>

#define START_ESCAPE '\033'
#define MIDDLE_ESCAPE '['


int posY = 3;
int posX = 1;

void setPosition(int x, int y) {
    posY = std::max(y, 0);
    posX = std::max(x, 0);
    std::cout << "\033[" << y << ";" << x << "H";
}

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

void clearScreen() {
    std::cout << "\033[2J";
    setPosition(posX, posY);
}

class Key {
public:
    Key(char value, bool isEscaped = false) : value(value), isEscaped(isEscaped) {
    
    }
private:
    char value;
    bool isEscaped;
};

const Key KEY_UP{'A', true};
const Key KEY_DOWN{'B', true};
const Key KEY_LEFT{'D', true};
const Key KEY_RIGHT{'C', true};
const Key KEY_R{'R'};
const Key KEY_SPACEBAR{' '};
const Key KEY_ENTER{'\n'};

//Singleton! //TODO is this a good idea?
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
        tcgetattr( fileno( stdin ), &oldSettings );
        // copy to new settings to modify its copy and be able to restore current settings
        newSettings = oldSettings;
        // setting to non-canonical and non-echo
        newSettings.c_lflag &= (~ICANON & ~ECHO);
        // change terminal NOW
        tcsetattr( fileno( stdin ), TCSANOW, &newSettings );
        
        //unbuffered cout
        std::cout.setf(std::ios::unitbuf);
    }
    
    bool first = false;
    
    void loop() {
        
        keepLooping = true;
        char c;
        
        while ( keepLooping ) {
            
            tv.tv_sec = 10;
            tv.tv_usec = 0;
            
            FD_ZERO( &set );
            FD_SET( fileno( stdin ), &set );
            
            int res = select( fileno( stdin )+1, &set, nullptr, nullptr, &tv );
            
            if( res > 0 )
            {
                if(!first) {
                    clearScreen();
                }
                first = true;
                read( fileno( stdin ), &c, 1 );
                
                if (c == START_ESCAPE) {
                    read( fileno( stdin ), &c, 1 );
                    //std::cout << c << std::endl;
                    if (c == MIDDLE_ESCAPE) {
                        read( fileno( stdin ), &c, 1 );
                        //std::cout << c << std::endl;
                        
                        switch (c) {
                            case 'A':
                                inputQueue.push(KEY_UP);
                                moveUp();
                                break;
                            case 'B':
                                inputQueue.push(KEY_DOWN);
                                moveDown();
                                break;
                            case 'C':
                                inputQueue.push(KEY_RIGHT);
                                moveRight();
                                break;
                            case 'D':
                                inputQueue.push(KEY_LEFT);
                                moveLeft();
                                break;
                            default:
                                std::cerr << " DEU RUIM!";
                        }
                    }
                    
                } else {
                    std::cout << c;
                }
            }
            else if( res < 0 )
            {
                perror( "select error" );
                break;
            }
            else
            {
                printf( "Select timeout\n" );
            }
        }
        
        std::cout << std::endl << "Fim do loop!" << std::endl;
    }
    
    void endUserInput() {
        tcsetattr( fileno( stdin ), TCSANOW, &oldSettings );
    }
    
    void stopLoop() {
        keepLooping = false;
    }
    
private:
    
    UserInput() {
    
    };
    
    bool keepLooping = false;
    
    std::queue<Key> inputQueue;
    
    struct termios oldSettings, newSettings;
    fd_set set;
    struct timeval tv{};
    
};

#endif //TETRIS_USER_INPUT_H

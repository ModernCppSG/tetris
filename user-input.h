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

struct termios oldSettings, newSettings;
fd_set set;
struct timeval tv{};
bool keepLooping = true;

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

int posY = 3;
int posX = 1;

void setPosition(int x, int y) {
    posY = std::max(y, 0);
    posX = std::max(x, 0);
    std::cout << "\033[" << y << ";" << x << "H";
}

void moveUp(int times = 1) {
    setPosition(posX, posY - times);
}

void moveRight(int times = 1) {
    setPosition(posX + times, posY);
}

void moveDown(int times = 1) {
    setPosition(posX, posY + times);
}

void moveLeft(int times = 1) {
    setPosition(posX - times, posY);
}

void loopReadUserInput() {
    
    char c;
    int isArrow = 0;
    
    while ( keepLooping )
    {
        
        tv.tv_sec = 10;
        tv.tv_usec = 0;
        
        FD_ZERO( &set );
        FD_SET( fileno( stdin ), &set );
        
        int res = select( fileno( stdin )+1, &set, nullptr, nullptr, &tv );
        
        if( res > 0 )
        {
            read( fileno( stdin ), &c, 1 );
            
            if (c == '\033') {
                //std::cout << "seta";
                isArrow = 1;
            } else if (isArrow == 1) {
                isArrow = 2;
            } else if (isArrow == 2) {
                std::cout << c;
                switch (c) {
                    case 'A':
                        moveUp();
                        //std::cout << " para cima";
                        break;
                    case 'B':
                        moveDown();
                        //std::cout << " para baixo";
                        break;
                    case 'C':
                        moveRight();
                        //std::cout << " para direita";
                        break;
                    case 'D':
                        moveLeft();
                        //std::cout << " para esquerda";
                        break;
                    default:
                        std::cout << " DEU RUIM!";
                }
                
                isArrow = 0;
            } else {
                std::cout << c;
            }
            
            if(isArrow == 0) {
                //std::cout << std::endl;
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

#endif //TETRIS_USER_INPUT_H

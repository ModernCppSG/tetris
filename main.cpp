#include "user-input.h"
#include "internal_clock.hpp"
#include "interface.h"
#include "tetriminos.h"

using namespace std::chrono_literals;

internal_clock internalClock{1000ms};
UserInput& userInput{UserInput::getInstance()};

std::atomic_bool keepLooping = true;
std::atomic_bool pleaseGoDown = false;


void fnClock() {
    while(keepLooping) {
        if(internalClock.get_is_elapsed()) {
            pleaseGoDown = true;
        }
    }
}

Key key{' '};
std::atomic_bool keyAlreadyUsed = true;

void fnInput() {
    while(keepLooping) {
        if(userInput.isEmpty() == false) {
            key = userInput.popKey();
            keyAlreadyUsed = false;
        }
    }
}

int main() {
    auto x = "5";
    auto y = "3";
    prepInterface();
    refCursor(x, y);
    
    Size size{10, 20};
    
    printWalls(size);
    
    std::cout << "\033[H";
    
    userInput.initUserInput();
    std::thread ui{&UserInput::loopReadInput, &userInput};
    
    std::thread tUserInput{fnInput};
    //std::thread tClockInternal{fnClock};
    
    int posXOld = 10;
    int posYOld = 3;
    int posX = 10;
    int posY = 3;
    
    //printCerquilha(posXOld, posYOld, posX, posY);
    
    refCursor(x, y);
    setPosition();
    
    internalClock.run(10, 10);
    
    while(keepLooping) {
        if(!keyAlreadyUsed) {
            if(key == KEY_UP) {
                clearPosition();
                moveUp();
                setPosition();
            } else if (key == KEY_RIGHT) {
                clearPosition();
                moveRight();
                setPosition();
            } else if (key == KEY_DOWN) {
                clearPosition();
                moveDown();
                setPosition();
            } else if (key == KEY_LEFT) {
                clearPosition();
                moveLeft();
                setPosition();
            }
            
            //std::this_thread::sleep_for(20ms);
            
            //printCerquilha(posXOld, posYOld, posX, posY);
            keyAlreadyUsed = true;
        }
        
        if(internalClock.get_is_elapsed()) {
            clearPosition();
            moveDown();
            setPosition();
        }
    }
    
    getchar();
    
    userInput.stopLoop();
    
    ui.join();
    
    userInput.endUserInput();
>>>>>>> all-merged
}

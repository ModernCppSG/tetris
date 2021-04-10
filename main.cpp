#include "user-input.h"
#include "internal_clock.hpp"
#include "interface.h"
#include "tetriminos.h"

using namespace std::chrono_literals;

lock_wrapper clock_lock{};
internal_clock internalClock{1000ms, 1, &clock_lock};
UserInput& userInput{UserInput::getInstance()};

std::atomic_bool keepLooping = true;
std::atomic_bool pleaseGoDown = false;


/*void fnClock() {
    while(keepLooping) {
        if(internalClock.get_is_elapsed()) {
            pleaseGoDown = true;
        }
    }
}*/

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
    
//    int posXOld = 10;
//    int posYOld = 3;
//    int posX = 10;
//    int posY = 3;
    
    //printCerquilha(posXOld, posYOld, posX, posY);
    
    //refCursor(x, y);
    //setPosition();
    
    internalClock.run();
    
    Ohh ohh{};
    ohh.origin.translate(0, 2);
    printTetrimino(ohh);
    
    //TODO limpar o origin.origin
    //TODO x e y como int ao invés de float (dentro do origin)
    //TODO refCursor receber inteiros
    
    int count = 1;
    
    while(keepLooping) {
        if(!keyAlreadyUsed) {
            clearPosition(ohh.origin, ohh.origin.orientation, ohh.envelope);
            
            if(key == KEY_UP) {
                //moveUp();
                ohh.origin.translate(0,-1);
            } else if (key == KEY_RIGHT) {
                //moveRight();
                ohh.origin.translate(1,0);
            } else if (key == KEY_DOWN) {
//                moveDown();
                ohh.origin.translate(0,1);
            } else if (key == KEY_LEFT) {
//                moveLeft();
                ohh.origin.translate(-1,0);
            }
            
            printTetrimino(ohh);
            
            //std::this_thread::sleep_for(20ms);
            
            //printCerquilha(posXOld, posYOld, posX, posY);
            keyAlreadyUsed = true;
        }
        
        if(count == internalClock.get_elapsed_intervals()) {
            clearPosition(ohh.origin, ohh.origin.orientation, ohh.envelope);
            //moveDown();
            ohh.origin.translate(0,1);
            //setPosition();
            printTetrimino(ohh);
            count++;
        }
    }
    
    getchar();
    
    userInput.stopLoop();
    
    ui.join();
    
    userInput.endUserInput();
}

#include "user-input.h"
#include "internal_clock.hpp"
#include "interface.h"
#include "tetriminos.h"
#include "semaphore.h"

using namespace std::chrono_literals;

lock_wrapper clockLock{};
internal_clock internalClock{1000ms, 1, &clockLock};

lock_wrapper userInputLock{};
UserInput& userInput{UserInput::getInstance(userInputLock)};

std::atomic_bool keepLooping = true;

std::mutex commandQueueMtx;
semaphore commandQueueSem;
std::queue<Key> commandQueue;


void fnClock() {
    while(keepLooping) {
        clockLock.wait();
        {
            std::lock_guard<std::mutex> lg{commandQueueMtx};
            commandQueue.push(KEY_DOWN);
            commandQueueSem.notify();
        }
    }
}

Key key{' '};

void fnInput() {
    while(keepLooping) {
        userInputLock.wait();
        {
            std::lock_guard<std::mutex> lg{commandQueueMtx};
            while(!userInput.isEmpty()) {
                commandQueue.push(userInput.popKey());
                commandQueueSem.notify();
            }
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
    std::thread tClockInternal{fnClock};
    
    internalClock.run();
    
    Ohh ohh{};
    ohh.origin.translate(0, 2);
    printTetrimino(ohh);
    
    //TODO limpar o origin.origin
    //TODO x e y como int ao invés de float (dentro do origin)
    //TODO refCursor receber inteiros
    
    while(keepLooping) {
        commandQueueSem.wait();
        std::lock_guard<std::mutex> lg{commandQueueMtx};
        while(!commandQueue.empty()) {
            
            key = commandQueue.front();
            commandQueue.pop();
            
            clearPosition(ohh.origin, ohh.origin.orientation, ohh.envelope);
    
            if (key == KEY_UP) {
                ohh.origin.translate(0, -1);
            }
            else if (key == KEY_RIGHT) {
                ohh.origin.translate(1, 0);
            }
            else if (key == KEY_DOWN) {
                ohh.origin.translate(0, 1);
            }
            else if (key == KEY_LEFT) {
                ohh.origin.translate(-1, 0);
            }
    
            printTetrimino(ohh);
        }
    }
    
    getchar();
    
    userInput.stopLoop();
    
    ui.join();
    
    userInput.endUserInput();
}

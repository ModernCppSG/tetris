#include <iostream>
#include <thread>
#include <iostream>
#include "user-input.h"

lock_wrapper lockWrapper{};

std::atomic_bool pleaseReadKeys = false;

UserInput& userInput{UserInput::getInstance(lockWrapper)};

void allowConsumeKeys_fn() {
    while (1) {
        lockWrapper.wait();
        pleaseReadKeys = true;
        
        while(!userInput.isEmpty()) {
            userInput.popKey();
        }
        
        pleaseReadKeys = false;
    }
}

int main() {
    
    int time = 1e5;
    
    std::cout << "This will work for " << time << " milliseconds." << std::endl;
    std::cout << "Press arrow keys or anything to test." << std::endl;
    
    userInput.initUserInput();
    
    std::thread ui(&UserInput::loopReadInput, &userInput);
    
    std::thread allowConsumeKeys{allowConsumeKeys_fn};
    
    auto timeInit = std::chrono::high_resolution_clock::now();
    auto timeEnd = std::chrono::high_resolution_clock::now();
    
    do {
        timeEnd = std::chrono::high_resolution_clock::now();
    } while( std::chrono::duration<double, std::milli>{timeEnd - timeInit}.count() < time );
    
    userInput.stopLoop();
    
    std::cout << "precisa juntar?" <<std::endl;
    
    if(ui.joinable()) {
        std::cout << "sim!" << std::endl;
        std::cout << "esperando juntar" << std::endl;
        ui.join();
    
        std::cout << "juntou" << std::endl;
    } else {
        std::cout << "nao!" << std::endl;
    }
    
    std::cout << "acabou!" << std::endl << std::endl;
    
    userInput.endUserInput();
    
    std::string c;
    
    std::cin >> c;
    
    return 0;
}

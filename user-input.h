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
#include <list>
#include <utility>
#include <atomic>
#include <mutex>
#include <map>
#include <condition_variable>
#include <iostream>
#include "lockWrapper.h"

#define START_ESCAPE '\033'
#define MIDDLE_ESCAPE '['

//from https://stackoverflow.com/a/10995085/6609908
#define HIDE_CURSOR "\033[?25l"

// protect a single operation with a lock_guard on the mutex
#define PROTECT(operation, mutex_variable)                  \
{                                                           \
    const std::lock_guard<std::mutex> lock{mutex_variable}; \
    operation;                                              \
}

/// Class Key to represent a key pressed by the player with its value and a display char
/// Simple keys (non-escaped): a, b, c, ..., 0, 1, 2, ..., -, +, ], ;, ,, @,
/// Complex keys (escaped): Enter, Backspace, F1, F2, ..., Up, Down, Left, Right

class Key {
public:
    /// Simple constructor for simple keys
    /// \param char representing the simple key pressed
    Key (char value) noexcept :
    value(value), isEscaped(false), display(std::string{value}) {
    
    }
    
    /// Complex constructor for complex keys (escaped keys)
    /// \param value char representing the simple key pressed
    /// \param isEscaped flag storing escapeness of the key
    /// \param char to be used to display this key on terminal
    Key(char value, bool isEscaped, std::string display) noexcept :
    value(value), isEscaped(isEscaped), display(std::move(display)) {
    
    }
    
    /// Friend function to simplify the printing of the Key object
    /// \param os a output stream to be modified
    /// \param key  the Key object to be printed
    /// \return the output strem modified
    friend std::ostream& operator<<(std::ostream& os, const Key& key) {
        return os << key.display;
    }
    
    /// comparison operator for the Key object based on its value
    /// \param key1 Key to be compared
    /// \param key2 Key to be compared
    /// \return true if key1 and key2 has the same value
    friend bool operator==(const Key& key1, const Key& key2) {
        return key1.value == key2.value;
    }
    
private:
    /// char value of the Key
    char value;
    
    /// escapeness of the Key (for Up arrow, Down arrow, etc)
    bool isEscaped;
    
    /// how the key is displayed
    std::string display;
};

const Key KEY_UP{'A', true, "↑"};
const Key KEY_DOWN{'B', true, "↓"};
const Key KEY_LEFT{'D', true, "←"};
const Key KEY_RIGHT{'C', true, "→"};
const Key KEY_R{'R'};
const Key KEY_SPACEBAR{' ', false, "∽"};
const Key KEY_ENTER{'\n', false, "↲"};

/// This is for when a never-pressed-key is pressed for the first time. The key is initialized and stored here. For a real usage, this is useless, as all needed keys would be known at compile-time
std::map<char, Key> mapOfKeys = {{'R', KEY_R},
                                       {' ', KEY_SPACEBAR},
                                       };

//Singleton! //TODO is this a good idea?
class UserInput {
public:
    /// The get instance function of the singleton
    /// \return the instance of UserInput
    static UserInput& getInstance(lock_wrapper& lockWrapper) {
        if (m_instance == nullptr) {
            m_instance = new UserInput{lockWrapper};
        }
        
        return *m_instance;
    }
    
    /// deleted copy constructor
    UserInput(UserInput const&) = delete;
    
    /// deleted copy assignment
    void operator=(UserInput const&) = delete;
    
    /// function to set the input through the terminal
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
        
        std::cout << HIDE_CURSOR;
    }
    
    /// maybe useless: used to find out if the keyboard was used for the first time
    bool first = false;
    
    /// "helper" to loop. this is public
    void loopReadInput() {
        keepLooping = true;
        while(keepLooping) {
            readInput();
        }
    
        std::cout << std::endl << "Fim do loopReadInput!" << std::endl;
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
    
    void stopLoop() {
        keepLooping = false;
    }
    
private:
    
    explicit UserInput(lock_wrapper& lockWrapper) : lockWrapper(lockWrapper){
    
    };
    
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
            std::cin >> c;
            
            switch(c) {
                case '\n':
                    PROTECT(inputQueue.push(KEY_ENTER), inputQueueMtx);
                    lockWrapper.notify_all();
                    //std::cout << KEY_ENTER;
                    break;
                case START_ESCAPE:
    
                    std::cin >> c;
                    
                    //std::cout << c << std::endl;
                    if (c == MIDDLE_ESCAPE) {
    
                        std::cin >> c;
                        
                        //std::cout << c << std::endl;
                        
                        switch (c) {
                            case 'A':
                            PROTECT(inputQueue.push(KEY_UP), inputQueueMtx);
                                lockWrapper.notify_all();
                                //moveUp();
                                break;
                            case 'B':
                            PROTECT(inputQueue.push(KEY_DOWN), inputQueueMtx);
                                lockWrapper.notify_all();
                                //moveDown();
                                break;
                            case 'C':
                            PROTECT(inputQueue.push(KEY_RIGHT), inputQueueMtx);
                                lockWrapper.notify_all();
                                //moveRight();
                                break;
                            case 'D':
                            PROTECT(inputQueue.push(KEY_LEFT), inputQueueMtx);
                                lockWrapper.notify_all();
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
                    lockWrapper.notify_all();
                    //moveRight();
                    break;
            }
            
        }
        else if( res < 0 )
        {
            perror( "select error" );
        }
    }
    
    /// helper function to print queue on standard output. this is thread-safe
    void printQueue() {
        std::queue<Key> copyInputQueue;
        {
            const std::lock_guard<std::mutex> lock(inputQueueMtx);
            copyInputQueue = inputQueue;
        }
        while(!copyInputQueue.empty()) {
            std::cout << copyInputQueue.front() << " ";
            copyInputQueue.pop();
        }
    }
    
    /// control over the loop. when false, while loop from loopReadInput breaks.
    std::atomic<bool> keepLooping = false;
    
    //TODO should inputQueue and inputQueueMtx be a class?
    /// queue to keep the pressed and not (yet) consumed keys
    std::queue<Key> inputQueue;
    /// mutex to guard input queue
    std::mutex inputQueueMtx;
    
    /// settings from terminal. oldSettings should be applied when game is over
    struct termios oldSettings{}, newSettings{};
    
    /// file descriptor set to deal with select system call
    fd_set set{};
    
    /// timeout for select system call
    struct timeval tv{};
    
    static UserInput* m_instance;
    
    lock_wrapper& lockWrapper;
    
};

UserInput* UserInput::m_instance = nullptr;

#endif //TETRIS_USER_INPUT_H

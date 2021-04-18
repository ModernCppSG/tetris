//
// Created by grilo on 17/04/2021.
//

#ifndef TETRIS_LOCKWRAPPER_H
#define TETRIS_LOCKWRAPPER_H

/*
 * Well, this class utility might be a bit controversial.
 * It is just a wrapper to a "simplify" the use of a condition variable.
 * Main reasons:
 * 		- Avoid using a global variable, but allow thread sharing. This wrapper
 * 		will bind both mutex'es and cond. variable. objects and simplify sharing, reducing
 * 		the number of arguments;
 * 		- Unlocks at the destruction of the wrapper.
 */
class lock_wrapper {
private:
    std::mutex mtx;
    std::unique_lock<std::mutex> un_mtx;
    std::condition_variable cv;
public:
    lock_wrapper(){
        un_mtx = std::unique_lock<std::mutex>(mtx);
    }
    void wait(){
        cv.wait(un_mtx);
    }
    void notify_all(){
        cv.notify_all();
    }
    ~lock_wrapper(){
        cv.notify_all();
    }
};

#endif //TETRIS_LOCKWRAPPER_H

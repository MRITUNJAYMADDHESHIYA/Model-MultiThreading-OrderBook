// What Is SLEEP :
// 0. “I’m done with my time-slice, and please don’t give me another one for at least n milliseconds.”  The OS doesn’t even try to schedule the sleeping thread until requested time has passed.
// 1. It will keep the lock and sleep.
// 2. Sleep is directly to thread, it is a thread function.

// What Is WAIT :
// 0. “I’m done with my time-slice. Don’t give me another time-slice until someone calls notify().” As with sleep(), the OS won’t even try to schedule your task unless someone calls notify() (or one of a few other wakeup scenarios occurs).
// 1. It releases the lock and wait.
// 2. Wait is on condition variable, it is like there is a condition variable in a thread and wait is applied to that CV but it ends up putting thread in waiting state.




#ifndef TIMER_H
#define TIMER_H

#include "../graphic/graphic.h"

class timer {
    public:
        timer();
        ~timer();

        // clonk actions
        void start( graphic *graphic);
        void stop();
        void pause( graphic *graphic);
        void unpause( graphic *graphic);

        bool isStarted() { return p_started; }

        // get the current ticks of this timer
        int getTicks( graphic *graphic);

    private:
        // the clock time
        int p_startTicks;

        // the ticks stored when the timer was pause
        int p_pausedTicks;

        // timer status
        bool p_paused;
        bool p_started;
};

#endif // TIMER_H

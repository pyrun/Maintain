#ifndef INPUT_H
#define INPUT_H

#include <irrlicht.h>

using namespace irr;

class input : public IEventReceiver
{
    public:
        input();
        virtual ~input();

        virtual bool OnEvent(const SEvent& event) {
            // Remember whether each key is down or up
            if (event.EventType == irr::EET_KEY_INPUT_EVENT)
                p_keyIsDown[event.KeyInput.Key] = event.KeyInput.PressedDown;
            return false;
        }

        // This is used to check whether a key is being held down
        virtual bool isKeyDown(EKEY_CODE keyCode) const {
            return p_keyIsDown[keyCode];
        }
    protected:

    private:
        bool p_keyIsDown[KEY_KEY_CODES_COUNT];
};

#endif // INPUT_H

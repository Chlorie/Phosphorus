#include <phosphorus/phosphorus.h>

class Sandbox final : public ph::Application
{
protected:
    void update() override
    {
        ph::log_debug("Delta time = {}s", delta_time_sec());
    }
};

PH_APP_MAIN(Sandbox);

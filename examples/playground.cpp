#include <phosphorus/core/entry_point.h>
#include <phosphorus/core/log.h>

class Sandbox final : public ph::Application
{
protected:
    void update() override
    {
        ph::log_debug("Delta time = {}s", delta_time_sec());
    }
};

PH_APP_MAIN(Sandbox);

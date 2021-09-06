#include <phosphorus/phosphorus.h>

class Sandbox final : public ph::Application
{
public:
    Sandbox()
    {
        initialize_window("Hello world!", { 800, 600 }, ph::RenderBackend::opengl);
    }

protected:
    void update() override
    {
        ph::log_debug("Delta time = {}s", delta_time_sec());
    }
};

PH_APP_MAIN(Sandbox);

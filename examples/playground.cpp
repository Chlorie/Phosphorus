#include <phosphorus/phosphorus.h>

class TestLayer final
{
public:
    void on_event(ph::Event& ev) const
    {
        ev.dispatch([](const ph::KeyPressedEvent& kpe)
        {
            if (kpe.key() == ph::Key::n)
            {
                ph::Application::instance().window().set_vsync(false);
                ph::log_debug("Disabled VSync");
            }
        });
    }
};

class Sandbox final : public ph::Application
{
public:
    Sandbox()
    {
        initialize_window("Hello world!", { 800, 600 }, ph::RenderBackend::opengl);
        layer_stack().emplace_layer<TestLayer>("test layer");
    }
};

PH_APP_MAIN(Sandbox);

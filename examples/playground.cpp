#include <phosphorus/phosphorus.h>
#include <clu/overload.h>

class TestLayer final
{
public:
    void on_event(ph::Event& ev) const
    {
        ev.dispatch(clu::overload(
            [](const ph::KeyPressedEvent& e)
            {
                if (e.key() != ph::Key::escape) return;
                ph::log_info("Escape pressed, closing the program...");
                ph::Application::instance().quit();
            },
            [](const ph::MouseScrolledEvent&)
            {
                ph::log_info("You are scrolling...");
            }
        ));
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

protected:
    void update() override {}
};

PH_APP_MAIN(Sandbox);

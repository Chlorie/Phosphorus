#pragma once

#include <memory>

#include "application.h"
#include "error.h"

#define PH_APP_MAIN(T)                                                      \
    int main([[maybe_unused]] int argc, [[maybe_unused]] const char** argv) \
    {                                                                       \
        static_assert(std::is_base_of_v<ph::Application, T>,                \
            "The application type must be a subclass of ph::Application");  \
        try                                                                 \
        {                                                                   \
            const auto app = std::make_unique<T>();                         \
            app->run();                                                     \
        }                                                                   \
        PH_CATCH_FATAL;                                                     \
    } static_assert(true)

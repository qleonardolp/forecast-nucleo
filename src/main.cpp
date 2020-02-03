#include <forecast/App.hpp>
#include <mbed.h>

int main() {
    DigitalOut led(LED1);
    forecast::App app;

    float d = 12.0f;

    app.setLogger([&](const forecast::Hardware*, const control::Control*,
                     const control::Control*) {
        return std::vector<float>{6.f, 1.f, d};
    });

    d = app.requireFloatValue("hello");
    
    while (true) {
        app.logInfo();
    }

}
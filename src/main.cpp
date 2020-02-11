#include <forecast/App.hpp>
#include <mbed.h>

int main() {
    
    forecast::App app;

    float d = NAN;

    app.setLogger([&d](const forecast::Hardware*, const control::Control*,
                     const control::Control*) {
        return std::vector<float>{6.f, 1.f, d};
    });

    while(std::isnan(d)) 
        d = app.requireFloatValue("hello");

    // Timer t;
    // while (true) {
    //     t.start();
    //     app.logInfo();
    //     t.stop();
    //     d = 1.f/t.read();
    //     // wait(0.5);
    // }

    while (true) {
        d += .1f;
        app.logInfo();   
        wait(0.002); // 5kh
    }
}

// #include <forecast/debug.hpp>
// int main() {
//     DEBUG_INFO("0123456789\r\n");
//     // Serial debug(PC_10, PC_11, 9600);
//     // debug.printf("0123456789\r\n");
// }

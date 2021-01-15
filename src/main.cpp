#include <mbed.h>
#include <memory>
#include <forecast/App.hpp>
#include <forecast/controllers/ImpedanceControl.hpp>
#include <forecast/controllers/ForcePID.hpp>

int main() {

    // Main instance of the Forecast app
    forecast::App app;

    // Pick which values to log (time is automatically logged)
    app.setLogger([](float motorRef, const forecast::Hardware* hw,
        const forecast::Controller* motor, forecast::Controller* env) {
        return std::vector<float>{
            motorRef
        };
    });

    // Hard-coded reference for the environment
    app.setEnvRefGen([](const forecast::Hardware* hw) {
        return 0.f;
    });

    // Motor controller
    app.setMotor(new forecast::ForcePID);

    // Environment controller
    app.setEnvironment(new forecast::ImpedanceControl);

    // Handshake with the PC
    app.waitConnection();

    // Motor Reference
    app.setMotorRefSweep();

    // Require parameters for the controllers which are not already initialized
    app.requireMotorParams();
    app.requireEnvironmentParams();

    // Require the loop frequency
    auto freq = app.requireFloatValue("Loop frequency");

    // Execute control loop
    app.execControlLoop(static_cast<ulong>(freq));
}

#include <mbed.h>
#include <memory>
#include <forecast/App.hpp>
#include <forecast/controllers/ForceDOB_OL.hpp>
#include <forecast/controllers/ImpedanceControl.hpp>
#include <forecast/controllers/ForcePID.hpp>

int main() {
    forecast::App app;
    app.setLogger([](float motorRef, const forecast::Hardware* hw,
        const forecast::Controller* motor, forecast::Controller* env) {
        return std::vector<float>{
            hw->getTauS(),
            hw->getTauM(),
            hw->getThetaM(),
            hw->getThetaE(),
            motorRef
        };
    });

    app.setEnvRefGen([](const forecast::Hardware* hw) {
        return 0.f;
    });

    app.setMotor(new forecast::ForcePID);
    app.setEnvironment(new forecast::ImpedanceControl);

    app.waitConnection();

    app.setSinusoidMotorRef();

    app.requireMotorParams();
    app.requireEnvironmentParams();

    auto freq = app.requireFloatValue("Loop frequency");

    app.execControlLoop(static_cast<ulong>(freq));
}

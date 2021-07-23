
#ifdef TARGET_NUCLEO_L432KC

#include <mbed.h>
#include <forecast/controllers/ForcePID.hpp>
#include <forecast/controllers/PositionPID.hpp>
#include <forecast/platforms/RPC/RPCApp.hpp>
#include <debug.hpp>

int main() {

    forecast::RPCApp app;


    app.setLogger([](float motorRef, const forecast::RPCHardware* hw,
                     const forecast::Controller* motor) {
        return std::vector<float>{
            // hw->getTauM(),
            envRef,
            hw->getThetaM(), 
            // hw->getDThetaM(),
            // hw->getDDThetaM(),
            // hw->getTauS(),
        };
    });

    // Hard-coded reference for the motor
    app.setMotorRefGen([](const forecast::RPCHardware* hw) {
        float ref = M_PI/2.0f;
        static float t = 0.0;

        // // STEP
        // if(t >= 1.0f){
        //     ref = 1.0f;
        // }

        // RAMP
        // static float ramp = 0.0f;
        // ramp += 0.4 * hw->getDT();
        // if (ramp >= 3.5f) {
        //     ramp = 3.5f;
        // }
        // ref = ramp;

        // SIN
        // ref = 3*sin(2.0*M_PI*0.3*t);

        t += hw->getDT();
        return ref;
    });

    // Motor controller
    app.setMotor(new forecast::PositionPID);

    // Handshake with the PC
    app.waitConnection();

    // Require parameters for the controllers which are not already initialized
    app.requireMotorParams();

    // Require the loop frequency
    auto freq = app.requireFloatValue("Loop frequency");

    // Execute control loop
    app.execControlLoop(static_cast<ulong>(freq));
}

#endif  // TARGET_STM32F4
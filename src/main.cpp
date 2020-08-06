#include <mbed.h>
#include <debug.hpp>
#include <forecast/App.hpp>
#include <forecast/controllers/ForceDOB_OL.hpp>
#include <forecast/controllers/ImpedanceControl.hpp>
#include <forecast/controllers/ForcePID.hpp>


#include <memory>

int main() {
    forecast::App app;
    app.setLogger([](utility::ddvar motorRef, const forecast::Hardware* hw, 
        const forecast::Controller* motor, forecast::Controller* env) {
        return std::vector<float>{
            hw->getT(), 
            hw->getTauS().val,
            hw->getTauM().val,
            hw->getThetaM().val,
            hw->getThetaE().val, 
            motorRef.val
        }; 
    });

    app.setEnvRefGen([](const forecast::Hardware* hw) { 
        utility::ddvar test;
        test.val = 0.0f;
        test.dval = 0.0f;
        test.ddval = 0.0f;
        return test;
    });

    app.setMotorRefGen([](const forecast::Hardware* hw) {
        // utility::ddvar test;
        // float amplitude = 0.2;
        // float time = hw->getT();
        // static float startTime = 0.0f; 
        // static float startTime2 = 0.0f;

        // int t = 5;

        // if(startTime == 0)
        //     startTime = time;
        // if(time - startTime < 4*t) {
        //     float stepa;
        //     if(time - startTime < t)
        //         stepa = amplitude;
        //     else if(time - startTime < 2*t)
        //         stepa = 3*amplitude;
        //     else if(time - startTime < 3*t)
        //         stepa = 4*amplitude;
        //     else
        //         stepa = 2*amplitude;    
        //     test.val = stepa;
        //     test.dval = 0.0f;
        //     test.ddval = 0.0f;
        // } else {
        //     if(startTime2 == 0)
        //         startTime2 = time;
        //     float freq_max = 10.0f;
        //     float duration = 15.0f;
        //     float m = freq_max/duration;
        //     float freq = (m/2)*(time-startTime2);

        //     test.val = 2*amplitude+amplitude*sin(2*M_PI*freq*(time-startTime2));
        //     test.dval = 0.0f;
        //     test.ddval = 0.0f;
        //     if(time-startTime2 >= duration) {
        //         test.val = 0.0f;
        //         test.dval = 0.0f;
        //         test.ddval = 0.0f;
        //     }
        // }

        utility::ddvar test;
        test.val = 0.0f;
        test.dval = 0.0f;
        test.ddval = 0.0f;
        return test;
    });
    
    app.setMotor(new forecast::ForcePID);
    app.setEnviorment(new forecast::ImpedanceControl);

    app.waitConnection();

    app.requireMotorParams();
    app.requireEnvironmentParams();

    auto freq = app.requireFloatValue("frequency of the loop");

    app.execControlLoop(static_cast<ulong>(freq));
    // app.execControlLoop(3000);
}

// #include <forecast/debug.hpp>
// int main() {
//     DEBUG_INFO("0123456789\r\n");
//     // Serial debug(PC_10, PC_11, 9600);
//     // debug.printf("0123456789\r\n");
// }

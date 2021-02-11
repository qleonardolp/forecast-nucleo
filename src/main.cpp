#include <mbed.h>
#include <debug.hpp>
#include <forecast/App.hpp>
#include <forecast/controllers/ImpedanceControl.hpp>
#include <forecast/controllers/ForcePID.hpp>
#include <forecast/controllers/TransparencyControl.hpp>


#include <memory>

int main() {
    forecast::App app;
    app.setLogger([](float envRef, const forecast::Hardware* hw, 
        const forecast::Controller* motor, forecast::Controller* env) {
        // forecast::ImpedanceControl* c = static_cast<forecast::ImpedanceControl*>(env);

        // float err = 0 - hw->getThetaE().val;
        // float derr = hw->getThetaE().dval;
      
        // float tau_ref = c->k_des * err + c->b_des * derr;

        return std::vector<float>{
            hw->getT(),
            hw->getTauM(),
            // hw->control_motor->getTorqueFeedback(),
            // -hw->getTauS(),diff(dtheta_m)/ts
            // envRef,
            hw->getThetaM(),
            hw->getThetaE(),
            // hw->getDThetaM(),
            // hw->getDDThetaM(),
        }; 
    });

    app.setEnvRefGen([](const forecast::Hardware* hw) { 
        float test = 0;
        // float ts = 0.0005f;
        // static float t = 0.0;

        // t += 0.25*0.0005f;
        // if(t <= 1.0f){
        //     t = 1.0f;
        // }
        // test = 0.2*sin(2.0*M_PI*0.5*t);
        // t += ts;

        // // SWEEP GEN 
        // float sweep_amplitude = 0.2f;
        // float sweep_duration = 20.0f;
        // float sweep_max_freq = 10.0f;
        // float m = sweep_max_freq / sweep_duration;
        // float rect = (m/2.0)*t;
        // if(t<=sweep_duration) {
        //     t += ts;
        // }
        // test = sweep_amplitude * sin(2.0*M_PI*t*rect); 
        // END 
        
        return test;
    });

    app.setMotorRefGen([](const forecast::Hardware* hw) {
        float test = .0f;
        static float t = 0.0;

        // // STEP
        // if(t >= 1.0f){
        //     test = 1.0f;
        // }

        // // RAMP
        // static float ramp = 0.0f;
        // ramp += 0.15 * hw->getDT();
        // if(ramp >= 0.5f){
        //     ramp = 0.5f;
        // }
        // test = ramp;

        // SIN
        // if(t <= 1.0f){
            // t = 1.0f;
        // }
        // test = sin(2.0*M_PI*1.0*t);

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

        // static float t = 0;
        // t += 0.00001f;
        // if(t >= 1.0f){
        //     t = 1.0f;
        // }
        // test = t;

        t += hw->getDT();
        
        return test;
    });
    
    app.setMotor(new forecast::ForcePID);
    app.setEnvironment(new forecast::ImpedanceControl);

    app.waitConnection();

    app.requireMotorParams();
    app.requireEnvironmentParams();

    auto freq = app.requireFloatValue("frequency of the loop");

    app.execControlLoop(static_cast<ulong>(freq));
}

// #include <forecast/debug.hpp>
// int main() {
//     DEBUG_INFO("0123456789\r\n");
//     // Serial debug(PC_10, PC_11, 9600);
//     // debug.printf("0123456789\r\n");
// }

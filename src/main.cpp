#include <mbed.h>
#include <debug.hpp>
#include <forecast/App.hpp>
#include <forecast/controllers/ForcePID.hpp>
#include <forecast/controllers/PositionPID.hpp>
#include <forecast/controllers/ImpedanceControl.hpp>
#include <forecast/controllers/AdmittanceControl.hpp>
#include <forecast/controllers/EnvRenderingControl.hpp>
#include <memory>

void setInertiaTask(forecast::App &app);
void setForecastTask(forecast::App &app);

int main() {
    forecast::App app;

    // set the task
    // setInertiaTask(app);
    setForecastTask(app);

    // Require the loop frequency
    auto freq = app.requireFloatValue("Loop frequency");

    // Execute control loop
    app.execControlLoop(static_cast<ulong>(freq));
}

void setInertiaTask(forecast::App &app) {
    // Pick which values to log (time is logged as first value automatically)
    app.setLogger([](float envRef, const forecast::Hardware* hw,
        const forecast::Controller* motor, forecast::Controller* env) {
        return std::vector<float>{
            hw->getTauM(),
            // envRef,
            hw->getThetaM(),
            hw->getDThetaM(),
            // hw->getDDThetaM(),
            // hw->getTauSensor(),
            // hw->getTauE(),
            // hw->getThetaE(),
            // hw->getDThetaE(),
            // hw->getDDThetaE(),
            // hw->getTauSensor(),
            // hw->getTauS(),
            // hw->getDDThetaE(),
        };
    });

    // Hard-coded reference for the environment
    app.setEnvRefGen([](const forecast::Hardware* hw) {
        float test = 0;
        static float t = 0.0;

        // STEP
        // if(t >= 1.0f){
        //     test = .5f;
        // }

        // RAMP
        // static float ramp = 0.0f;
        // ramp += 0.3 * hw->getDT();
        // if(ramp >= 1.5f){
        //     ramp = 1.5f;
        // }
        // test = ramp;

        // // SIN
        // test = sin(2.0*M_PI*0.5*t);

        // // SWEEP GEN
        // float sweep_amplitude = 0.2f;
        // float sweep_duration = 20.0f;
        // float sweep_max_freq = 10.0f;
        // float m = sweep_max_freq / sweep_duration;
        // float rect = (m/2.0)*t;
        // if(t<=sweep_duration) {
        //     t += hw->DT;
        // }
        // test = sweep_amplitude * sin(2.0*M_PI*t*rect);

        t += hw->getDT();
        return test;
    });

    // Hard-coded reference for the motor
    app.setMotorRefGen([](const forecast::Hardware* hw) {
        float test = 0;
        static float t = 0.0;

        // // STEP
        // if(t >= 1.0f){
        //     test = 1.0f;
        // }

        // RAMP
        static float ramp = 0.0f;
        ramp += 0.4 * hw->getDT();
        if(ramp >= 3.5f){
            ramp = 3.5f;
        }
        test = ramp;

        // SIN
        // test = 3*sin(2.0*M_PI*0.3*t);

        // // SWEEP GEN
        // float sweep_amplitude = 0.2f;
        // float sweep_duration = 20.0f;
        // float sweep_max_freq = 10.0f;
        // float m = sweep_max_freq / sweep_duration;
        // float rect = (m/2.0)*t;
        // if(t<=sweep_duration) {
        //     t += hw->DT;
        // }
        // test = sweep_amplitude * sin(2.0*M_PI*t*rect);

        t += hw->getDT();
        return test;
    });

    // Motor controller
    app.setMotor(new forecast::ForcePID);
    // Environment controller
    app.setEnvironment(new forecast::EnvRenderingControl);

    // Handshake with the PC
    app.waitConnection();

    // Require parameters for the controllers which are not already initialized
    app.requireMotorParams();
    app.requireEnvironmentParams();
}

void setForecastTask(forecast::App &app) {
    // Pick which values to log (time is logged as first value automatically)
    app.setLogger([](float envRef, const forecast::Hardware* hw,
        const forecast::Controller* motor, forecast::Controller* env) {
        return std::vector<float>{
            hw->getTauM(),
            // envRef,
            hw->getThetaM(),
            hw->getDThetaM(),
            // hw->getDDThetaM(),
            // hw->getTauSensor(),
            // hw->getTauE(),
            // hw->getThetaE(),
            // hw->getDThetaE(),
            // hw->getDDThetaE(),
            // hw->getTauSensor(),
            // hw->getTauS(),
            // hw->getDDThetaE(),
        };
    });

    // Motor controller
    app.setMotor(new forecast::ForcePID);
    // Environment controller
    app.setEnvironment(new forecast::EnvRenderingControl);

    // Handshake with the PC
    app.waitConnection();

    float type_of_experiment = app.requireFloatValue("transparency enable_transparency");
    if(type_of_experiment==0) {
        // tracking experiment
        app.setMotorRefSignal();
        app.requireMotorParams();
        app.requireEnvironmentParams();
    } else if(type_of_experiment==1) {
        // transparency experiment with motor disabled
        app.setEnvRefSweep();
    } else if(type_of_experiment==2) {
        // transparency experiment with motor enabled
        app.setEnvRefSweep();
        app.requireMotorParams();
    }
}
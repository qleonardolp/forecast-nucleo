
#include <mbed.h>
#include <forecast/App.hpp>
#include <forecast/platforms/workbench/Hardware.hpp>
#include <forecast/controllers/PositionPID.hpp>
#include <forecast/controllers/SpeedPI.hpp>
#include <forecast/controllers/VelocityPID.hpp>
#include <forecast/controllers/EnvRenderingControl.hpp>
#include <forecast/reference_generators/ConstantRefGen.hpp>
#include <forecast/reference_generators/SmoothStep.hpp>
#include <forecast/reference_generators/Sinusoid.hpp>
#include <debug.hpp>

#include <signal.h>

using namespace forecast;
extern "C" void abort_handler(int signal_number)
{
    DEBUG_INFO("SIGNAL HANDLER CALLED\n");
}

int main() {
    signal(SIGABRT, &abort_handler);
    App app;
    DEBUG_INFO("App constructed\n");
    Hardware hw(app);
    hw.init();
    app.set_hw(&hw);

    DEBUG_INFO("hw constructed\n");

    app.get_ref_gen_factory().add("constant", make_constant_ref_gen_builder());
    app.get_ref_gen_factory().add("Smooth Step", make_smoothstep_ref_gen_builder());
    app.get_ref_gen_factory().add("Sinusoid", make_sinusoid_ref_gen_builder());

    app.get_controller_factory().add("position_P", make_Position_P_builder());
    DEBUG_INFO("Position P\n");
    app.get_controller_factory().add("position_PD", make_Position_PD_builder());
    DEBUG_INFO("Position PD\n");
    app.get_controller_factory().add("position_PID", make_Position_PID_builder());
    DEBUG_INFO("Position PID\n");
    app.get_controller_factory().add("position_PI", make_Position_PI_builder());
    DEBUG_INFO("Position PI\n");
    app.get_controller_factory().add("speed_PI", make_Speed_PI_builder());
    DEBUG_INFO("Speed PI\n");
    app.get_controller_factory().add("velocity_PID", make_Velocity_PID_builder());
    DEBUG_INFO("Velocity PID\n");
    app.get_controller_factory().add("EnvRender_damp", make_EnvRenderingController_damped());
    app.get_controller_factory().add("EnvRender", make_EnvRenderingController());

    DEBUG_INFO("finished with app\n");

    app.run();

    return 0;
}
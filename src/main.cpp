
#include <mbed.h>
#include <forecast/App.hpp>
#include <forecast/platforms/Hardware.hpp>
#include <forecast/controllers/PositionPID.hpp>
#include <debug.hpp>

#include <signal.h>

using namespace forecast;
extern "C" void abort_handler(int signal_number)
{
    DEBUG_INFO("SIGNAL HANDLER CALLED\n");
}


class HW : public IHardware {
    public:
    HW(App &app) : IHardware(app) {

    }

    virtual void update(float dt) override {
        // nothing to do.
    }
};

int main() {
    signal(SIGABRT, &abort_handler);
    App app;
    DEBUG_INFO("App constructed\n");
    IHardware *hw = new HW(app);
    app.set_hw(hw);

    DEBUG_INFO("hw constructed\n");

    auto fn = [](std::vector<float> params) -> Controller * {
        if (params.empty())
        return nullptr;
    
        return new PositionPID(params[0]);
    };

    auto p_b = ControllerFactory::Builder{fn, {"Kp"}, {"err"}};
    auto pd_b = std::move(p_b);
    // auto pd_b = make_Position_P_builder();
    // auto pid_b = make_Position_PID_builder();
    // auto pi_b = make_Position_PI_builder();

    // app.get_controller_factory().add("position_P", make_Position_P_builder());
    // DEBUG_INFO("Position P\n");
    // app.get_controller_factory().add("position_PD", make_Position_PD_builder());
    // DEBUG_INFO("Position PD\n");
    // app.get_controller_factory().add("position_PID", make_Position_PID_builder());
    // DEBUG_INFO("Position PID\n");
    // app.get_controller_factory().add("position_PI", make_Position_PI_builder());
    // DEBUG_INFO("Position PI\n");

    DEBUG_INFO("finished with app\n");

    // app.run();

    return 0;
}
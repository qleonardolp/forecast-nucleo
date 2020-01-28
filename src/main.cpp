#include <forecast/App.hpp>
#include <mbed.h>

int main() {
    
    forecast::App app;

    app.setLogger([](const forecast::Hardware*, const control::Control*,
                     const control::Control*) {
        return std::vector<float>{6.f, 1.f};
    });


    while (true) {
        app.logInfo();
        wait(0.5);
        app.logError("hello from mbed!");
        wait(0.5);
    }
}

// #include <USART/USART_interface.hpp>
// USART_interface pc(USBTX,
//                    USBRX,
//                    C_8bits,
//                    C_Use_RX_TX,
//                    921600,
//                    C_Parity_None,
//                    C_1stop,
//                    C_RX_TX_DMA,
//                    100,
//                    100);

// int main() {
//     pc.enable();
//     pc.receive_enable();
//     pc.transmit_enable();

//     // uint8_t bytes[] = {0x02, 0x00, 0x00, 0x00, 0x80, 0x3f,
//     //                    0x00, 0x00, 0x00, 0x40, 0x03};

//     // while (true) {
//     //     pc.put_tx_buffer(11, bytes);
//     //     pc.send(false);
//     //     wait(1);
//     // }
//     size_t i = 0;
//     while(true) {
//         pc.printf("test %u\r\n", i++);
//         wait(1);
//     }
// }
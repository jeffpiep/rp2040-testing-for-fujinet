#include <stdio.h>
#include "pico/stdlib.h"
#include "hardware/uart.h"
#include "hardware/gpio.h"
#include "hardware/divider.h"
#include "hardware/clocks.h"

// UART defines
// By default the stdout UART is `uart0`, so we will use the second one
#define UART_ID uart1
#define BAUD_RATE 9600

// Use pins 4 and 5 for UART1
// Pins can be changed, see the GPIO function select table in the datasheet for information on GPIO assignments
#define UART_TX_PIN 4
#define UART_RX_PIN 5

// GPIO defines
// Example uses GPIO 2
#define DCD_BASE 2
#define DCD_CA0 0
#define DCD_CA1 1
#define DCD_CA2 2
#define DCD_SEL 3
#define DCD_LSTRB 4
#define DCD_ENBL 5

#define RDDATA 21

// drive state bits
#define STAT_DIRTN   0b0000
#define STAT_STEP    0b0001
#define STAT_MOTORON 0b0010
#define STAT_EJECT   0b0011
#define STAT_DATAHD0 0b0100
#define STAT_SS      0b0110
#define STAT_DRVIN   0b0111
#define STAT_CSTIN   0b1000
#define STAT_WRTPRT  0b1001
#define STAT_TKO     0b1010
#define STAT_TACH    0b1011
#define STAT_DATAHD1 0b1100
#define STAT_READY   0b1110
#define STAT_REVISED 0b1111



volatile uint32_t bus_state = 0;
volatile bool bus_changed = false;
uint32_t drive_state = 0;

void myisr(uint gp, uint32_t events)
{
    // uint32_t bus = gpio_get_all();
    // bus >>= DCD_BASE;
    // bus &= 0b111111u;
    // bus_state = bus;
    bus_changed = true;
}

void setup()
{
    stdio_init_all();

    // // Set up our UART
    // uart_init(UART_ID, BAUD_RATE);
    // // Set the TX and RX pins by using the function select on the GPIO
    // // Set datasheet for more information on function select
    // gpio_set_function(UART_TX_PIN, GPIO_FUNC_UART);
    // gpio_set_function(UART_RX_PIN, GPIO_FUNC_UART);

/* To configure a clock, we need to know the following pieces of information:
    The frequency of the clock source
    The mux / aux mux position of the clock source
    The desired output frequency 
*/
// make a 400 Hz ish GPIO clock
// use the 12 MHz crystal or the 125 MHZ PLL as a source
    clock_gpio_init_int_frac(RDDATA, CLOCKS_CLK_GPOUT0_CTRL_AUXSRC_VALUE_CLK_SYS, 125*1000*1000/400, 0);

    // GPIO initialisation.
    // We will make this GPIO an input, and pull it up by default
    // gpio_init(DCD_CA0+DCD_BASE);
    // gpio_set_dir(DCD_CA0+DCD_BASE, GPIO_IN);
    // gpio_init(DCD_CA1+DCD_BASE);
    // gpio_set_dir(DCD_CA1+DCD_BASE, GPIO_IN);
    // gpio_init(DCD_CA2+DCD_BASE);
    // gpio_set_dir(DCD_CA2+DCD_BASE, GPIO_IN);
    // gpio_init(DCD_SEL+DCD_BASE);
    // gpio_set_dir(DCD_SEL+DCD_BASE, GPIO_IN);
    // gpio_init(DCD_LSTRB+DCD_BASE);
    // gpio_set_dir(DCD_LSTRB+DCD_BASE, GPIO_IN);
    // gpio_init(DCD_ENBL+DCD_BASE);
    // gpio_set_dir(DCD_ENBL+DCD_BASE, GPIO_IN);

    gpio_init(15);
    gpio_set_dir(15, GPIO_IN);
    gpio_init(16);
    gpio_set_dir(16, GPIO_OUT);

    // gpio_set_irq_enabled_with_callback(DCD_CA0+DCD_BASE, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true, &myisr);
    // gpio_set_irq_enabled(DCD_CA1+DCD_BASE, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);
    // gpio_set_irq_enabled(DCD_CA2+DCD_BASE, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);
    // gpio_set_irq_enabled(DCD_SEL+DCD_BASE, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);
    // gpio_set_irq_enabled(DCD_LSTRB+DCD_BASE, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);
    // gpio_set_irq_enabled(DCD_ENBL+DCD_BASE, GPIO_IRQ_EDGE_RISE | GPIO_IRQ_EDGE_FALL, true);


    // gpio_init(GPOUT);
    // gpio_set_dir(GPOUT,GPIO_OUT);


}


void service()
{
    gpio_put(16,gpio_get(15));
    // if (bus_changed)
    // {
    //     bus_changed = false;
    //     printf("%02x",bus_state);
    //     // if (!(bus_state & (1 << DCD_LSTRB)))
    //     // {
    //     //     // The host system can send four commands: /DIRTN,/STEP,
    //     //     // /MOTORON and EJECT. To send one of the control commands to the
    //     //     // drive, set CA2 to the value (a zero or a one) to which the host
    //     //     // system wishes the command to be set, and then set CAO, CA 1, and
    //     //     // SEL to the value which selects the desired command. Finally, bring
    //     //     // LSTRB first high and then low.
    //     //     puts("strobe");
    //     //     switch (bus_state & 0b11)
    //     //     {
    //     //     case 0:
    //     //         puts("dirtn");
    //     //         break;
    //     //     case 1:
    //     //         puts("step");
    //     //         break;
    //     //     case 2: 
    //     //         puts("motor");
    //     //         break;
    //     //     case 3:
    //     //         puts("eject");
    //     //         break;
    //     //     default:
    //     //         break;
    //     //     }
    //     //     if (bus_state & (1 << DCD_CA2))
    //     //         puts("1");
    //     //     else
    //     //         puts("0");
    //     // }
    // }
}

int main()
{
    puts("Hello, world!");
    setup();

    while (true)
        service();
    return 0;
}

/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

// this example outputs a register bit addressed by 4 GPIOs
// the register word is put to the PIO by the main program
// the PIO machine reads the 4 GPIOs then
// selects the bit from the register then 
// outputs the bit on a fifth GPIO

#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "phases.pio.h"

void pio_phases(PIO pio, uint sm, uint offset, uint pin);


int main() {
    setup_default_uart();

    // todo get free sm
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &phases_program);
    printf("Loaded program at %d\n", offset);

    pio_phases(pio, 0, offset, 10);
    pio_sm_put_blocking(pio, 0, 0b1001011001010010); // send the register word to the PIO
    while (true)
    {}
    }

void pio_phases(PIO pio, uint sm, uint offset, uint pin) {
    phases_program_init(pio, sm, offset, pin);
    pio_sm_set_enabled(pio, sm, true);
}

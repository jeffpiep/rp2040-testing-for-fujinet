/**
 * Copyright (c) 2020 Raspberry Pi (Trading) Ltd.
 *
 * SPDX-License-Identifier: BSD-3-Clause
 */

#include <stdio.h>

#include "pico/stdlib.h"
#include "hardware/pio.h"
#include "commands.pio.h"

void pio_commands(PIO pio, uint sm, uint offset, uint pin);

int main()
{
    setup_default_uart();

    // todo get free sm
    PIO pio = pio0;
    uint offset = pio_add_program(pio, &commands_program);
    printf("Loaded program at %d\n", offset);

    pio_commands(pio, 0, offset, 10);
    while (true)
    {
        uint32_t a = pio_sm_get_blocking(pio0, 0);
        printf("%c", (char)a + '0');
    }
}

void pio_commands(PIO pio, uint sm, uint offset, uint pin) {
    commands_program_init(pio, sm, offset, pin);
    pio_sm_set_enabled(pio, sm, true);
}

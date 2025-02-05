#include <stdio.h>
#include "pico/stdlib.h"  
#include "hardware/timer.h" 

#define LED_PIN_RED 13
#define LED_PIN_YELLOW 12
#define LED_PIN_GREEN 11

bool repeating_timer_callback(struct repeating_timer *t) {
    static int led_state = 0; 

    printf("mudando...\n");

    gpio_put(LED_PIN_RED, 0);
    gpio_put(LED_PIN_YELLOW, 0);
    gpio_put(LED_PIN_GREEN, 0);

    if (led_state == 0) {
        gpio_put(LED_PIN_RED, 1);
    } else if (led_state == 1) {
        gpio_put(LED_PIN_YELLOW, 1);  
    } else if (led_state == 2) {
        gpio_put(LED_PIN_GREEN, 1);  
    }

    led_state = (led_state + 1) % 3;

    return true;
}

int main() {
    stdio_init_all();

    gpio_init(LED_PIN_RED);
    gpio_set_dir(LED_PIN_RED, true);
    gpio_init(LED_PIN_YELLOW);
    gpio_set_dir(LED_PIN_YELLOW, true);
    gpio_init(LED_PIN_GREEN);
    gpio_set_dir(LED_PIN_GREEN, true);

    struct repeating_timer timer;

    add_repeating_timer_ms(3000, repeating_timer_callback, NULL, &timer);
    while (true) {
        sleep_ms(1000);
        printf("1 segundo passou\n");
    }

    return 0;
}
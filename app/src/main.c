#include <zephyr/kernel.h>
#include <zephyr/drivers/gpio.h>

/* LED aliases defined in the nRF52840DK device tree */
static const struct gpio_dt_spec led0 =
    GPIO_DT_SPEC_GET(DT_ALIAS(led0), gpios);
static const struct gpio_dt_spec led1 =
    GPIO_DT_SPEC_GET(DT_ALIAS(led1), gpios);
static const struct gpio_dt_spec led2 =
    GPIO_DT_SPEC_GET(DT_ALIAS(led2), gpios);
static const struct gpio_dt_spec led3 =
    GPIO_DT_SPEC_GET(DT_ALIAS(led3), gpios);

int main(void)
{
    /* Ensure all LEDs are ready */
    if (!gpio_is_ready_dt(&led0) ||
        !gpio_is_ready_dt(&led1) ||
        !gpio_is_ready_dt(&led2) ||
        !gpio_is_ready_dt(&led3)) {
        return 0;
    }

    /* Configure LEDs as outputs (active-low, start OFF) */
    gpio_pin_configure_dt(&led0, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&led1, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&led2, GPIO_OUTPUT_INACTIVE);
    gpio_pin_configure_dt(&led3, GPIO_OUTPUT_INACTIVE);

    while (1) {
        /* led0 on, others off */
        gpio_pin_set_dt(&led0, 1);
        gpio_pin_set_dt(&led1, 0);
        gpio_pin_set_dt(&led2, 0);
        gpio_pin_set_dt(&led3, 0);
        k_msleep(500);

        /* led1 on */
        gpio_pin_set_dt(&led0, 0);
        gpio_pin_set_dt(&led1, 1);
        gpio_pin_set_dt(&led2, 0);
        gpio_pin_set_dt(&led3, 0);
        k_msleep(500);

        /* led2 on */
        gpio_pin_set_dt(&led0, 0);
        gpio_pin_set_dt(&led1, 0);
        gpio_pin_set_dt(&led2, 1);
        gpio_pin_set_dt(&led3, 0);
        k_msleep(500);

        /* led3 on */
        gpio_pin_set_dt(&led0, 0);
        gpio_pin_set_dt(&led1, 0);
        gpio_pin_set_dt(&led2, 0);
        gpio_pin_set_dt(&led3, 1);
        k_msleep(500);
    }

    return 0;
}

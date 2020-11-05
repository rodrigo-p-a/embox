/**
 * @file stm32_gpio_cube.c
 * @brief
 * @author Denis Deryugin <deryugin.denis@gmail.com>
 * @version 0.1
 * @date 2016-02-12
 */

#include <assert.h>

#include <embox/unit.h>

#include <drivers/gpio/gpio_driver.h>

#include <framework/mod/options.h>

#include <embox/unit.h>

EMBOX_UNIT_INIT(efm32_gpio_init);

#define EFM32_GPIO_CHIP_ID      OPTION_GET(NUMBER,gpio_chip_id)
#define EFM32_GPIO_PORTS_COUNT  OPTION_GET(NUMBER,gpio_ports_number)

static struct gpio_chip efm32_gpio_chip;

static int efm32_gpio_setup_mode(unsigned char port, gpio_mask_t pins,
		int mode) {
	return 0;
}

static void efm32_gpio_set(unsigned char port, gpio_mask_t pins, char level) {
}

static gpio_mask_t efm32_gpio_get(unsigned char port, gpio_mask_t pins) {
	return 0;
}

static struct gpio_chip efm32_gpio_chip = {
	.setup_mode = efm32_gpio_setup_mode,
	.get = efm32_gpio_get,
	.set = efm32_gpio_set,
	.nports = EFM32_GPIO_PORTS_COUNT
};

static int efm32_gpio_init(void) {
	return gpio_register_chip(&efm32_gpio_chip, EFM32_GPIO_CHIP_ID);

}

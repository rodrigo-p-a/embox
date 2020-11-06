/**
 * @file stm32_gpio_cube.c
 * @brief
 * @author Denis Deryugin <deryugin.denis@gmail.com>
 * @version 0.1
 * @date 2016-02-12
 */

#include <assert.h>

#include <embox/unit.h>
#include <util/bit.h>

#include <drivers/gpio/gpio_driver.h>

#include <em_cmu.h>
#include <em_gpio.h>

#include <framework/mod/options.h>

#include <module/efm32zg_sk3200/bsp.h>

#include <embox/unit.h>

EMBOX_UNIT_INIT(efm32_gpio_init);

#define BSP_LED_POLARITY  1

#define EFM32_GPIO_CHIP_ID      OPTION_GET(NUMBER,gpio_chip_id)
#define EFM32_GPIO_PORTS_COUNT  (OPTION_GET(NUMBER,gpio_ports_number) + 1)

static const struct gpio_chip efm32_gpio_chip;

static int efm32_gpio_setup_mode(unsigned char port, gpio_mask_t pins, int mode) {
	int bit;

	switch(mode) {
	case GPIO_MODE_OUTPUT: {
		bit_foreach(bit, pins) {
			if (pins & (1 << bit)) {
				GPIO_PinModeSet(port, 10, gpioModePushPull, BSP_LED_POLARITY ? 0 : 1);
			}
		}
		break;
	}
	}

	return 0;
}

static void efm32_gpio_set(unsigned char port, gpio_mask_t pins, char level) {
	if (level) {
		GPIO_PortOutSet(port, pins);
	} else {
		GPIO_PortOutClear(port, pins);
	}
}

static gpio_mask_t efm32_gpio_get(unsigned char port, gpio_mask_t pins) {

	return GPIO_PortOutGet(port) & pins;
}

static const struct gpio_chip efm32_gpio_chip = {
	.setup_mode = efm32_gpio_setup_mode,
	.get = efm32_gpio_get,
	.set = efm32_gpio_set,
	.nports = EFM32_GPIO_PORTS_COUNT
};

static int efm32_gpio_init(void) {
#if (_SILICON_LABS_32B_SERIES < 2)
  CMU_ClockEnable(cmuClock_HFPER, true);
#endif

#if (_SILICON_LABS_32B_SERIES < 2) \
  || defined(_SILICON_LABS_32B_SERIES_2_CONFIG_2)
  CMU_ClockEnable(cmuClock_GPIO, true);
#endif
	return gpio_register_chip((struct gpio_chip *)&efm32_gpio_chip, EFM32_GPIO_CHIP_ID);

}

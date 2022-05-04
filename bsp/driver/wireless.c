#include <stdio.h>
#include <stdint.h>
#include "sdio.h"

#include "stm32h7xx_ll_gpio.h"
#include "stm32h7xx_ll_sdmmc.h"
#include "stm32h7xx_ll_utils.h"

#define WL_WIFI_EN()      LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_13)
#define WL_WIFI_DIS()     LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_13)

static SDMMC_TypeDef *wl_sdio = SDMMC2;

void hw_wl_init_test(void)
{
    uint32_t data = 0;
    uint8_t cnt = 0;

    WL_WIFI_DIS();
    LL_mDelay(10);

    mcu_sdio_init(wl_sdio);

    do {
        // cmd0
        mcu_sdio_cmd_no_resp(wl_sdio, 0x00, 0);
        // cmd5
        mcu_sdio_cmd_no_resp(wl_sdio, 0x05, 0);
        // cmd3 get RCA
        mcu_sdio_cmd_with_resp(wl_sdio, 0x03, 0, &data);
        // SDMMC_CmdSetRelAdd(wl_sdio, &data);
        printf("CMD3 RCA:0x%04lx\r\n", data);
        LL_mDelay(10);
    } while (cnt++ < 20);
}

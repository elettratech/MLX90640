#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "i2c.h"
#include "mlx90640.h"

void app_main(void)
{
    printf("ELETTRA INICIANDO...\n");

    i2c_iniciar();

    mlx90640_iniciar();

    while (1)
    {
        printf("ELETTRA FUNCIONANDO!\n");

        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
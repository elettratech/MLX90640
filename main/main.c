#include <stdio.h>

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "i2c.h"
#include "mlx90640.h"

void app_main(void)
{
    printf("ELETTRA INICIANDO...\n");

    i2c_iniciar();

    printf("I2C INICIADO!\n");

    mlx90640_iniciar();

    printf("TESTE DO MLX TERMINOU!\n");

    printf("ELETTRA FUNCIONANDO!\n");

    while (1)
    {
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}
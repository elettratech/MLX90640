#include "mlx90640.h"
#include "config.h"

#include "MLX90640_API.h"
#include "MLX90640_I2C_Driver.h"

#include <stdio.h>
#include <stdint.h>

static uint16_t eeData[832];
static paramsMLX90640 mlx_params;

void mlx90640_iniciar(void)
{
    printf("INICIANDO MLX90640...\n");

    MLX90640_I2CInit();

    printf("Lendo EEPROM do MLX90640...\n");

    int resultado = MLX90640_DumpEE(
        MLX90640_ADDR,
        eeData
    );

    if (resultado != MLX90640_NO_ERROR)
    {
        printf("ERRO AO LER EEPROM: %d\n", resultado);
        return;
    }

    printf("EEPROM LIDA COM SUCESSO!\n");

    resultado = MLX90640_ExtractParameters(
        eeData,
        &mlx_params
    );

    if (resultado != MLX90640_NO_ERROR)
    {
        printf("ERRO AO EXTRAIR CALIBRACAO: %d\n", resultado);
        return;
    }

    printf("CALIBRACAO EXTRAIDA COM SUCESSO!\n");
    printf("MLX90640 PRONTO PARA LEITURA TERMICA!\n");
}
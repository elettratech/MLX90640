#include "MLX90640_I2C_Driver.h"
#include "MLX90640_API.h"

#include "config.h"
#include "i2c.h"

#include "driver/i2c_master.h"
#include "esp_err.h"

#include <stdint.h>

static i2c_master_dev_handle_t mlx90640_handle;
static bool dispositivo_iniciado = false;

static esp_err_t mlx90640_dispositivo_iniciar(uint8_t slaveAddr)
{
    if (dispositivo_iniciado)
    {
        return ESP_OK;
    }

    i2c_master_bus_handle_t bus = i2c_get_bus();

    i2c_device_config_t config_sensor = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = slaveAddr,
        .scl_speed_hz = 100000
    };

    esp_err_t resultado = i2c_master_bus_add_device(
        bus,
        &config_sensor,
        &mlx90640_handle
    );

    if (resultado == ESP_OK)
    {
        dispositivo_iniciado = true;
    }

    return resultado;
}

void MLX90640_I2CInit(void)
{
    // O I2C do Elettra já é inicializado por i2c_iniciar().
}

int MLX90640_I2CRead(
    uint8_t slaveAddr,
    uint16_t startAddress,
    uint16_t nMemAddressRead,
    uint16_t *data)
{
    if (mlx90640_dispositivo_iniciar(slaveAddr) != ESP_OK)
    {
        return -MLX90640_I2C_NACK_ERROR;
    }

    uint16_t endereco_atual = startAddress;
    uint16_t restante = nMemAddressRead;
    uint16_t posicao = 0;

    while (restante > 0)
    {
        // Fazemos blocos de 64 palavras = 128 bytes
        uint16_t quantidade = restante > 64 ? 64 : restante;

        uint8_t endereco[2];

        endereco[0] = (uint8_t)(endereco_atual >> 8);
        endereco[1] = (uint8_t)(endereco_atual & 0xFF);

        uint8_t dados[128];

        esp_err_t resultado = i2c_master_transmit_receive(
            mlx90640_handle,
            endereco,
            2,
            dados,
            quantidade * 2,
            1000
        );

        if (resultado != ESP_OK)
        {
            return -MLX90640_I2C_NACK_ERROR;
        }

        for (uint16_t i = 0; i < quantidade; i++)
        {
            data[posicao + i] =
                ((uint16_t)dados[i * 2] << 8) |
                dados[i * 2 + 1];
        }

        endereco_atual += quantidade;
        restante -= quantidade;
        posicao += quantidade;
    }

    return MLX90640_NO_ERROR;
}

int MLX90640_I2CWrite(
    uint8_t slaveAddr,
    uint16_t writeAddress,
    uint16_t data)
{
    if (mlx90640_dispositivo_iniciar(slaveAddr) != ESP_OK)
    {
        return -MLX90640_I2C_NACK_ERROR;
    }

    uint8_t dados[4];

    dados[0] = (uint8_t)(writeAddress >> 8);
    dados[1] = (uint8_t)(writeAddress & 0xFF);
    dados[2] = (uint8_t)(data >> 8);
    dados[3] = (uint8_t)(data & 0xFF);

    esp_err_t resultado = i2c_master_transmit(
        mlx90640_handle,
        dados,
        4,
        1000
    );

    if (resultado != ESP_OK)
    {
        return -MLX90640_I2C_WRITE_ERROR;
    }

    return MLX90640_NO_ERROR;
}

void MLX90640_I2CFreqSet(int freq)
{
    // Estamos usando 100 kHz por enquanto.
}

int MLX90640_I2CGeneralReset(void)
{
    return MLX90640_NO_ERROR;
}
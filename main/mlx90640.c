#include "mlx90640.h"
#include "config.h"
#include "i2c.h"

#include "driver/i2c_master.h"
#include "esp_err.h"

static i2c_master_dev_handle_t mlx90640_handle;

void mlx90640_iniciar(void)
{
    i2c_master_bus_handle_t bus = i2c_get_bus();

    i2c_device_config_t config_sensor = {
        .dev_addr_length = I2C_ADDR_BIT_LEN_7,
        .device_address = MLX90640_ADDR,
        .scl_speed_hz = 100000
    };

    ESP_ERROR_CHECK(
        i2c_master_bus_add_device(
            bus,
            &config_sensor,
            &mlx90640_handle
        )
    );
}
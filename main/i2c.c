#include "i2c.h"
#include "config.h"

#include "driver/i2c_master.h" // controla o I2C
#include "esp_err.h"

static i2c_master_bus_handle_t i2c_bus_handle; // guarda referência do barramento I2C

void i2c_iniciar(void)
{
    i2c_master_bus_config_t config_i2c = {
        .i2c_port = I2C_NUM_0,
        .sda_io_num = I2C_SDA,
        .scl_io_num = I2C_SCL,
        .clk_source = I2C_CLK_SRC_DEFAULT,
        .glitch_ignore_cnt = 7,
        .flags.enable_internal_pullup = true
    };

    ESP_ERROR_CHECK(i2c_new_master_bus(&config_i2c, &i2c_bus_handle));
}

i2c_master_bus_handle_t i2c_get_bus(void)//retorno do barramento
{
    return i2c_bus_handle;
}
idf_component_register(
    SRCS
        "main.c"
        "i2c.c"
        "mlx90640.c"
         "MLX90640_API.c"
        "MLX90640_I2C_Driver.c"
    INCLUDE_DIRS "."
)
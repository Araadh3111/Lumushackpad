#pragma once

// OLED sits on the XIAO RP2040 hardware I2C: D4/SDA = GP6, D5/SCL = GP7 (I2C1)
#define I2C_DRIVER I2CD1
#define I2C1_SDA_PIN GP6
#define I2C1_SCL_PIN GP7

// 0.91" SSD1306, 128x32
#define OLED_BRIGHTNESS 128
#define OLED_TIMEOUT 60000

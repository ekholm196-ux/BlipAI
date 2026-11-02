#include <stdio.h>
#include "driver/spi_master.h"
// symbolic constants
#define LCD_MOSI 39
#define  LCD_SCLK 38

void app_main(void)
{
    spi_bus_config_t bus_config = {
        .mosi_io_num = LCD_MOSI, //GPIO that sends data to the display
        .miso_io_num = -1, //no miso
        .sclk_io_num = LCD_SCLK, //GPIO that sends clk signal
        .quadwp_io_num = -1, // quad spi not used
        .quadhd_io_num = -1, 
        .max_transfer_sz = 4096 // maximum nbr of bytes per tranfser
    };
    //check for errors in spi initialization and initialize
    ESP_ERROR_CHECK(spi_bus_initialize(SPI2_HOST, &bus_config, SPI_DMA_CH_AUTO)); //SPI2_HOST is the spi controller, auto choose DMA-channel
    printf("SPI bus initialized.\n");
}

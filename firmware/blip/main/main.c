#include <stdio.h>
#include "driver/spi_master.h" //ESP-IDF SPI driver
#include "esp_lcd_panel_io.h" //communication interface between esp and lcd
#include "esp_lcd_panel_vendor.h" //display specific driver
#include "esp_lcd_panel_ops.h" //control funtions for lcd
// hardware pins, symbolic constants
#define LCD_MOSI 39 //sends data from esp to lcd
#define  LCD_SCLK 38 //spi clock for syncinc data transmission
#define LCD_CS 21 //selects the LCD as the SPI receiver    
#define LCD_DC 45 //tells the LCD whether we send a command or data
#define LCD_RST 40 //reset

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

    
    // cnfigure the LCD connection on our SPI bus
    esp_lcd_panel_io_spi_config_t io_config = {
        .cs_gpio_num = LCD_CS, // chooses the display as the SPI receiver
        .dc_gpio_num = LCD_DC, // tell if a command or data is being sent
        .spi_mode = 0, 
        .pclk_hz = 20 * 1000 * 1000, //20mhz
        .trans_queue_depth = 10, 
        .lcd_cmd_bits = 8,
        .lcd_param_bits = 8
    };

    esp_lcd_panel_io_handle_t io_handle = NULL;

    ESP_ERROR_CHECK(
        esp_lcd_new_panel_io_spi((esp_lcd_spi_bus_handle_t)SPI2_HOST, &io_config, &io_handle));

    //configure the ST7789 display controller
    esp_lcd_panel_dev_config_t panel_config = {
        .reset_gpio_num = LCD_RST,
        .rgb_ele_order = LCD_RGB_ELEMENT_ORDER_RGB,
        .bits_per_pixel = 16
    };

    esp_lcd_panel_handle_t panel_handle = NULL;

    ESP_ERROR_CHECK(
        esp_lcd_new_panel_st7789(
            io_handle,
            &panel_config,
            &panel_handle
        )
    );

    ESP_ERROR_CHECK(esp_lcd_panel_reset(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_init(panel_handle));
    ESP_ERROR_CHECK(esp_lcd_panel_disp_on_off(panel_handle, true));

    printf("ST7789 initialized!\n");


}

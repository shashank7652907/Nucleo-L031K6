/* STM32 HAL Example for SPI TFT LCD (ILI9341)
 * Board: STM32 Nucleo-C031C6
 */

#include "main.h"
#include "spi.h"
#include "gpio.h"
#include "ili9341.h"  // Custom driver for ILI9341 (you can write your own or use open-source)

int main(void)
{
  /* Reset peripherals, init flash, system clock */
  HAL_Init();
  SystemClock_Config();

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_SPI1_Init();   // Configure SPI1 for TFT
  ILI9341_Init();   // Init display

  /* Example: display text */
  ILI9341_SetRotation(SCREEN_HORIZONTAL_1);
  ILI9341_FillScreen(ILI9341_BLACK);

  ILI9341_DrawText("Hello STM32", FONT3, 20, 120, ILI9341_RED, ILI9341_BLACK);
  ILI9341_DrawText("I can do SPI :-)", FONT2, 24, 160, ILI9341_GREEN, ILI9341_BLACK);

  while (1)
  {
    HAL_Delay(10);
  }
}


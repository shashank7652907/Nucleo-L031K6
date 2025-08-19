#include <stdio.h>
#include <stm32l0xx_hal.h>




#define VCP_TX_Pin GPIO_PIN_2
#define VCP_RX_Pin GPIO_PIN_15

UART_HandleTypeDef huart2;

// Redirect printf() to UART2
#define STDOUT_FILENO 1
#define STDERR_FILENO 2
int _write(int file, uint8_t *ptr, int len)
{
    switch(file)
    {
        case STDOUT_FILENO:
        case STDERR_FILENO:
            HAL_UART_Transmit(&huart2, ptr, len, HAL_MAX_DELAY);
            break;
        default: return -1;
    }
    return len;
}


// Initialize UART2
void MX_USART2_UART_Init(void)
{
    __HAL_RCC_GPIOA_CLK_ENABLE();

    // USART2 GPIO Config: PA2 -> TX, PA15 -> RX
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = VCP_TX_Pin | VCP_RX_Pin;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF4_USART2;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

    huart2.Instance = USART2;
    huart2.Init.BaudRate = 115200;
    huart2.Init.WordLength = UART_WORDLENGTH_8B;
    huart2.Init.StopBits = UART_STOPBITS_1;
    huart2.Init.Parity = UART_PARITY_NONE;
    huart2.Init.Mode = UART_MODE_TX_RX;
    huart2.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart2.Init.OverSampling = UART_OVERSAMPLING_16;
    huart2.Init.OneBitSampling = UART_ONE_BIT_SAMPLE_DISABLE;
    huart2.AdvancedInit.AdvFeatureInit = UART_ADVFEATURE_NO_INIT;

    if(HAL_UART_Init(&huart2) != HAL_OK)
        while(1); // Error handler (loop forever)
}

int main(void)
{
    HAL_Init();
    SystemClock_Config();   
    MX_USART2_UART_Init();  
    while(1){
    printf("Shashank \n");
    HAL_Delay(10);
      }
 }




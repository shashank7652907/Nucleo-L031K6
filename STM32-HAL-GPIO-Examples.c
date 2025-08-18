#include <stdio.h>
#include <stm32l0xx_hal.h>

#define LED_PORT GPIOB
#define LED_PIN  GPIO_PIN_3
#define LED_PIN_A  GPIO_PIN_4
#define LED_PIN_B  GPIO_PIN_5

#define BUTTON_PORT GPIOA
#define BUTTON_PIN  GPIO_PIN_0   // User button on many boards


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

// Initialize GPIO for LED
void initGPIO(void)
{
    __HAL_RCC_GPIOB_CLK_ENABLE();

    GPIO_InitTypeDef GPIO_InitStruct = {0};
    GPIO_InitStruct.Pin = LED_PIN | LED_PIN_A | LED_PIN_B;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    HAL_GPIO_Init(LED_PORT, &GPIO_InitStruct);
    // Button config (PA0) - Input, Pull-down
    GPIO_InitStruct.Pin = GPIO_PIN_0;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;   // important since button goes to GND
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
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
    initGPIO();             
    MX_USART2_UART_Init();  

    printf("STM32L0 LED ON-OFF every 300 ms!\n");

    uint32_t lastTick = 0;
    uint32_t blinkSpeed = 300; // ms
    uint8_t ledState = 0;      // 0 = OFF, 1 = ON
    uint8_t buttonPrev = 1;  // store last button state (1 = not pressed)

    while(1)
    {
        uint32_t tick = HAL_GetTick();
        if(tick - lastTick >= blinkSpeed)
        {
            lastTick = tick;

            if(ledState == 0)
            {
                HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_SET); // Turn ON
                printf(" RED LED ON\n");
                HAL_GPIO_WritePin(LED_PORT, LED_PIN_A, GPIO_PIN_RESET); 
                printf(" YELLOW LED OFF\n");
                ledState = 1;
            }
            else
            {
                HAL_GPIO_WritePin(LED_PORT, LED_PIN, GPIO_PIN_RESET); // Turn OFF
                printf(" RED LED OFF\n");
                HAL_GPIO_WritePin(LED_PORT, LED_PIN_A, GPIO_PIN_SET); 
                printf(" YELLOW LED ON\n");
                ledState = 0;
            }
        }
        uint8_t buttonNow = HAL_GPIO_ReadPin(BUTTON_PORT, BUTTON_PIN);

        // Detect falling edge: 1 -> 0 (button press)
        if (buttonPrev == 1 && buttonNow == 0)
        {
            HAL_GPIO_TogglePin(LED_PORT, LED_PIN_B);
            HAL_Delay(50);  // debounce delay
        }

        buttonPrev = buttonNow;
    }
}



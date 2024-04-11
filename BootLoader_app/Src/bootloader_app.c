#include "STMF446RE.h"
#include "USART_driver.h"
#include "bsp.h"

#define BOOTLOADER_SIZE   (0x8000U)

static void jump_to_main(void);
static void USART_setup(USART_Handle_t *pUSARTHandle);
static void SysTick_taredown(void);
static void USART_taredown(USART_Handle_t *pUSARTHandle);

uint32_t TICKS = 0;

char waiting[] = "waiting for firmware update....\r\n";
char timeout[] = "Timed Out!\r\n";

int main(void){
	USART_Handle_t USART;
	USART_GPIOInit(GPIOA, GPIO_PIN_NO_2, 7); //TX
	USART_GPIOInit(GPIOA, GPIO_PIN_NO_3, 7); //RX

	USART.pUSARTx = USART2;
	USART_setup(&USART);

	systick_init(1000);

	while(TICKS < 3000){
		USART_SendData(&USART, (uint8_t *)waiting, sizeof(waiting));
		delay(50);
	}
	USART_SendData(&USART, (uint8_t *)timeout, sizeof(timeout));

	SysTick_taredown();
	USART_taredown(&USART);

	jump_to_main();

	return 0; //should never reach this line
}

static void USART_setup(USART_Handle_t *pUSARTHandle){
	pUSARTHandle->USART_Config.USART_Baud =  USART_STD_BAUD_115200;
	pUSARTHandle->USART_Config.USART_Mode =  USART_MODE_TXRX;
	pUSARTHandle->USART_Config.USART_NoOfStopBits = USART_STOPBITS_1;
	pUSARTHandle->USART_Config.USART_ParityControl = USART_PARITY_DISABLE;
	pUSARTHandle->USART_Config.USART_WordLength = USART_WORDLEN_8BITS;
	USART_PeriClockControl(pUSARTHandle->pUSARTx, ENABLE);
	USART_Init(pUSARTHandle);
	*ISER1 |= (1 << (IRQ_USART2 % 32));//enable USART2 NVIC line
	pUSARTHandle->pUSARTx->CR1 |= (1U << USART_CR1_RXNEIE);//enable RXNE interrupt
}

static void USART_taredown(USART_Handle_t *pUSARTHandle){
	USART_PeripheralControl(pUSARTHandle->pUSARTx, DISABLE);
	USART_PeriClockControl(pUSARTHandle->pUSARTx, DISABLE);
}
static void jump_to_main(void){
	typedef void(*voidfun)(void);
	uint32_t verctor_table_entry = FLASH_BASEADRR + BOOTLOADER_SIZE;
	uint32_t *reset_handler_addr = (uint32_t *)(verctor_table_entry + 4U);//second entry in the table
	voidfun reset_handler = (voidfun)*reset_handler_addr;
	reset_handler();
}

void SysTick_Handler(void){
	TICKS++;
}

static void SysTick_taredown(void){
	SysTick ->CSR &= ~(1U << 0);
}

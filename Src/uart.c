#include "uart.h"

#define GPIOAEN						(1U<<0)
#define UART2EN						(1U<<17)
#define CR1_TE						(1U<<3)
#define CR1_RE						(1U<<2)
#define CR1_UE						(1U<<13)

#define SR_TXE						(1U<<7)
#define SR_RXNE						(1U<<5)

#define SYS_FREQ					16000000
#define APB1_CLK					SYS_FREQ
#define UART_BAUDRATE				115200

//*******************************************************************

static void uart_set_baudrate(USART_TypeDef* USARTx, uint32_t periphClk,uint32_t baudRate);
static uint16_t compute_uart_bd(uint32_t periphClk, uint32_t baudRate);
void uart2_write(int ch);
char uart2_read(void);

void uart2_rxtx_init(void);

//*******************************************************************

int __IO_putchar(int ch)
{
	uart2_write(ch);
	return ch;
}


//*******************************************************************

void uart2_rxtx_init(void)
{
	/******Configure UART GPIO pin******/
	// Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Set PA2 mode to alternate function mode
	// Reference manual p.157
	GPIOA->MODER &=~ (1U<<4);
	GPIOA->MODER |= (1U<<5);

	// Set PA2 alternate function type to UART_TX (AF07)
	// Reference manual p.161
	GPIOA->AFR[0] |= (1U<<8); // set pin 8 to 1
	GPIOA->AFR[0] |= (1U<<9); // set pin 9 to 1
	GPIOA->AFR[0] |= (1U<<10); // set pin 10 to 1
	GPIOA->AFR[0] &=~ (1U<<11); //set pin 11 to 0

	// NOTE: &=~ used for disabling

	// Set PA3 mode to alternate function mode
	GPIOA->MODER &=~ (1U<<6);
	GPIOA->MODER |= (1U<<7);


	// Set PA3 alternate function type to UART_RX (AF07)

	GPIOA->AFR[0] |= (1U<<12); // set pin 12 to 1
	GPIOA->AFR[0] |= (1U<<13); // set pin 13 to 1
	GPIOA->AFR[0] |= (1U<<14); // set pin 14 to 1
	GPIOA->AFR[0] &=~ (1U<<15); //set pin 15 to 0


	/******Configure USART Module******/
	// Enable clock access to UART2
	// Connected to the APB1 Bus, Data sheet p. 15
	RCC->APB1ENR |= UART2EN;

	// Configure UART BAUDRATE
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);

	// Configure the transfer direction
	// Reference manual p. 550 set bit number 3 to 1 to enable transmitter
	USART2->CR1 = (CR1_TE | CR1_RE);


	// Enable the UART Module
	USART2->CR1 |= CR1_UE; // do not want to clean out register this time

}

//*******************************************************************

void uart2_tx_init(void)
{
	/******Configure UART GPIO pin******/
	// Enable clock access to GPIOA
	RCC->AHB1ENR |= GPIOAEN;

	// Set PA2 mode to alternate function mode
	// Reference manual p.157
	GPIOA->MODER &=~ (1U<<4);
	GPIOA->MODER |= (1U<<5);

	// Set PA2 alternate function type to UART_TX (AF07)
	// Reference manual p.161
	GPIOA->AFR[0] |= (1U<<8); // set pin 8 to 1
	GPIOA->AFR[0] |= (1U<<9); // set pin 9 to 1
	GPIOA->AFR[0] |= (1U<<10); // set pin 10 to 1
	GPIOA->AFR[0] &=~ (1U<<11); //set pin 11 to 0

	// NOTE: &=~ used for disabling


	/******Configure USART Module******/
	// Enable clock access to UART2
	// Connected to the APB1 Bus, Data sheet p. 15
	RCC->APB1ENR |= UART2EN;

	// Configure UART BAUDRATE
	uart_set_baudrate(USART2,APB1_CLK,UART_BAUDRATE);

	// Configure the transfer direction
	// Reference manual p. 550 set bit number 3 to 1 to enable transmitter
	USART2->CR1 = CR1_TE; // cleans out the register when use =


	// Enable the UART Module
	USART2->CR1 |= CR1_UE; // do not want to clean out register this time

}

//*******************************************************************

char uart2_read(void)
{
	// make sure receive data register is not empty RXNE flag
	while((USART2->SR & SR_RXNE)){}

	// Read data
	return USART2->DR;

}


//*******************************************************************

void uart2_write(int ch)
{
	// Make sure transmit data register is empty
	while(!(USART2->SR & SR_TXE)){}

	// Write to transmit data register
	USART2->DR = (ch & 0xFF);

}

//*******************************************************************

static void uart_set_baudrate(USART_TypeDef* USARTx, uint32_t periphClk,uint32_t baudRate)
{
	USARTx->BRR = compute_uart_bd(periphClk, baudRate);

}

//*******************************************************************

static uint16_t compute_uart_bd(uint32_t periphClk, uint32_t baudRate)
{
	return (periphClk + (baudRate/2U)/baudRate);
}










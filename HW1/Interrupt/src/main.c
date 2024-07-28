#include <xio.h>
#include <string.h>
#include <stdio.h>
#include <mb_interface.h>
#include "xparameters.h"
#include "xuartlite.h"

// Define the UART_BASE_ADDRESS.
#define UART_BASE_ADDRESS XPAR_UARTLITE_0_BASEADDR

// Define the UART register offset.
#define XUARTLITE_CONTROL_REG_OFFSET 0x0C
#define XUARTLITE_STATUS_REG_OFFSET 0x08
#define XUARTLITE_RX_FIFO_OFFSET 0x00
#define XUARTLITE_TX_FIFO_OFFSET 0x04

// Define the bit masks for the appropriate status flags.
#define XUARTLITE_CR_ENABLE_INTR (1 << 3)
#define XUARTLITE_SR_RX_FIFO_VALID_DATA (1 << 0)

// Define interrupt enable bit for the UART module
#define XIN_IER_INTERRUPT_ENABLE_MASK 0x10

void ISR() __attribute__((interrupt_handler));
u32 count = 0;
XUartLite UartLite;

void set_bit_in_reg(u32 addr, u32 bit) {
    // RMW
    u32 val;
    val = XIo_In32((volatile u32 *)addr);
    val |= bit;
    XIo_Out32((volatile u32 *)addr, val);
}

void clear_bit_in_reg(u32 addr, u32 bit) {
    // RMW
    u32 val;
    val = XIo_In32((volatile u32 *)addr);
    val &= ~bit;
    XIo_Out32((volatile u32 *)addr, val);
}

void ISR(void) {
    // Service the interrupt
    // We need to know the source of interrupt
    u32 status = XIo_In32(UART_BASE_ADDRESS + XUARTLITE_STATUS_REG_OFFSET);

    // Check if RX FIFO has valid data
    if (status & XUARTLITE_SR_RX_FIFO_VALID_DATA) {
        u32 data = XIo_In32(UART_BASE_ADDRESS + XUARTLITE_RX_FIFO_OFFSET);
        count++;
        xil_printf("Find interrupt here, which is: %d, Count: %d\n", data, count);
    }
}

int main(void) {
    int Status;

    // Initialization of UART
    Status = XUartLite_Initialize(&UartLite, XPAR_UARTLITE_0_DEVICE_ID);
    if (Status != XST_SUCCESS) {
        xil_printf("UART Initialization Failed\n");
        return XST_FAILURE;
    }
    else{
    	xil_printf("UART Initialization Successfully\n");
    }

    // Enable the UART to generate interrupts
    set_bit_in_reg(UART_BASE_ADDRESS + XUARTLITE_CONTROL_REG_OFFSET, XUARTLITE_CR_ENABLE_INTR);

    // Enable MicroBlaze to respond to interrupts
    microblaze_enable_interrupts();

    xil_printf("Start simulation. The loop will be terminated if interrupt occurs\n");

    while (1) {
        ; // Useful work goes here
    }

    // Disable Interrupts (if needed)
    microblaze_disable_interrupts();

    return 0;
}

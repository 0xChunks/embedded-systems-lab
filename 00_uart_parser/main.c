#include "includes.h"

char uart_buffer[BUF_SIZE];
int buffer_index = 0;



void post_sim(void) {
    //simulate power on self test

    //simulate diagnostic test
    printf("Checking UART connection...\n");
    sleep(1); // Simulate delay
    printf("UART connection OK\n");
    sleep(1); // Simulate delay
    printf("Checking amplifier status...\n");
    sleep(1); // Simulate delay
    printf("Amplifier status OK\n");
    sleep(1); // Simulate delay
    printf("Checking Memory...\n");
    sleep(1); // Simulate delay
    printf("Memory OK\n");
    printf("All systems OK\n");

    log_command("POST", "Power On Self Test completed successfully\n");

    printf("UART Command Parser Ready. Type HELP for Commands\n");

}

int main() {
   
    // Simulate power on self test
    post_sim();

    while (1) {
        char c = getchar(); // Simulate receiving a character from UART

        if (c == '\n' || c == '\r') {
            // End of command
            uart_buffer[buffer_index] = '\0'; // Null-terminate the string
            process_command(uart_buffer);
            buffer_index = 0; // Reset buffer index for next command
        } else if (buffer_index < BUF_SIZE - 1) {
            // Store character in buffer
            uart_buffer[buffer_index++] = c;
        } else {
            printf("Buffer overflow. Resetting input.\n");
        }
    }

    return 0;
}
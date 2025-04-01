#include "includes.h"

int amp_status = 0; // Example: 0 for OFF, 1 for ON
int amp_cycles = 0; // Example: Number of cycles for the amplifier
int gain_level = 0; // Example: Gain level for the amplifier
int curr_gpio = 0; //Set which pin to use for gpio

void log_command(const char *command, const char *result) {
    
    FILE *log_file = fopen("log.txt", "a");
    if (log_file != NULL) {
        fprintf(log_file, "Command: %s, Result: %s\n", command, result);
        fclose(log_file);
    } else {
        printf("Error opening log file\n");
    }

    printf("%s", result); // Print to console

}


void handle_amp_on(void) {
    char result[BUF_SIZE];
    if (!amp_status) {
        snprintf(result, sizeof(result), "Amplifier turned ON\n");
        log_command("AMP ON", result); // Log the command
        amp_cycles++; // Increment cycles if turned ON
    } else {
        printf("Amplifier is already ON\n");
    }
    amp_status = 1; // Example: Set amplifier status to ON
}

void handle_amp_off(void) {
    char result[BUF_SIZE];
    if (amp_status) {
        snprintf(result, BUF_SIZE, "Amplifier turned OFF\n");
        log_command("AMP OFF", result); // Log the command
    } else {
        printf("Amplifier is already OFF\n");
    }
    amp_status = 0; // Example: Set amplifier status to OFF
}

void handle_amp(char *input) {
    strtok(input, " "); // Skip the first token (AMP)
    char *token = strtok(NULL, " ");
    
    if (token == NULL) {
        printf("Invalid command format. Use 'AMP ON' or 'AMP OFF'\n");
        return;
    }

    if (strcmp(token, "ON") == 0) {
        handle_amp_on();
    } else if (strcmp(token, "OFF") == 0) {
        handle_amp_off();
    } else {
        printf("Unknown command: %s\n", token);
    }
}

void handle_status(char *input) {
    (void)input; // Unused parameter
    char result[BUF_SIZE];
    snprintf(result, sizeof(result), "Amplifier status: %s, Gain level: %d\n", amp_status ? "ON" : "OFF", gain_level);
    log_command("STATUS", result);
}

void handle_toggle(char *input) {
    (void)input; // Unused parameter
    char result[BUF_SIZE];
    snprintf(result, sizeof(result), "Amplifier toggled to: %s\n", amp_status ? "OFF" : "ON");
    log_command("TOGGLE", result); // Log the command
    amp_status = !amp_status; // Toggle amplifier status
    if (amp_status) amp_cycles++; // Increment cycles if turned ON
}

void handle_cycles(char *input) {
    (void)input; // Unused parameter
    char result[BUF_SIZE];
    snprintf(result, sizeof(result), "Number of amplifier cycles: %d\n", amp_cycles);
    log_command("CYCLES", result); // Log the command
}

void handle_reset(char *input) {
    (void)input; // Unused parameter
    char result[BUF_SIZE];
    snprintf(result, sizeof(result), "Amplifier cycles, status, and gain level reset\n");
    log_command("RESET", result); // Log the command
    // Reset amplifier cycles, status, and gain level
    amp_cycles = 0; // Reset cycles
    amp_status = 0; // Reset status
    gain_level = 0; // Reset gain level
}

void handle_help(char *input) {
    (void)input; // Unused parameter
    printf("Available commands:\n");
    printf("AMP ON - Turn amplifier ON\n");
    printf("AMP OFF - Turn amplifier OFF\n");
    printf("STATUS - Get current amplifier status\n");
    printf("TOGGLE - Toggle amplifier status\n");
    printf("CYCLES - Get number of amplifier cycles\n");
    printf("RESET - Reset amplifier cycles, status, and gain\n");
    printf("HELP - Show this help message\n");
}

void handle_gpio(int pin, char *input) {

    char path[BUF_SIZE];

    snprintf(path, BUF_SIZE, "/sys'/class/gpio%d", pin);
    if (access(path, F_OK) == -1) {
        FILE *export_file = fopen("/sys/class/gpio/export", "w");
        if (!export_file) {
            perror("Export failed");
            return;
        }
        fprintf(export_file, "%d", pin);
        fclose(export_file);
    }

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", pin);
    FILE *dir_file = fopen(path, "w");
    if (!dir_file) {
        perror("Set direction failed");
        return;
    }
    fprintf(dir_file, "out");
    fclose(dir_file);

    int value = -1;
    if (strcmp(input, "ON") == 0) value = 1;
    else if (strcmp(input, "OFF") == 0) value = 0;
    else {
        printf("Invalid GPIO state: %s\n", input);
        return;
    }

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
    FILE *val_file = fopen(path, "w");
    if (!val_file) {
        perror("Write value failed");
        return;
    }
    fprintf(val_file, "%d", value);
    fclose(val_file);

    printf("GPIO %d set to %s\n", pin, value ? "ON" : "OFF");

}

void handle_set(char *input) {

    char result[BUF_SIZE];
    char cmd[BUF_SIZE];
    strtok(input, " "); // Skip the first token (SET)
    char *token = strtok(NULL, " ");
    
    if (token == NULL) {
        printf("Invalid command format. Use 'SET <command> #'\n");
        return;
    }

    if (strcmp(token, "GAIN") == 0) {
        token = strtok(NULL, " ");
        if (token != NULL) {
            gain_level = atoi(token);
            snprintf(result, sizeof(result), "Gain level set to: %d\n", gain_level);
            snprintf(cmd, sizeof(cmd), "SET GAIN %d", gain_level);
            log_command(cmd, result); // Log the command
        } else {
            printf("Invalid command format. Use 'SET GAIN <value>'\n");
        }
    } 
    else if (strcmp(token, "GPIO") == 0) {
        token = strtok(NULL, " ");
        if (token != NULL) {
            curr_gpio = atoi(token);
            token = strtok(NULL, " ");
            if (token != NULL) {
                handle_gpio(curr_gpio, token);
            }
        } else {
            printf("Invalid command format. Use 'SET GPIO <pin> <ON|OFF>");
        }
    } else {
        printf("Unknown command: %s\n", token);
    }  

}


typedef struct {
    const char *command;
    void (*handler)(char *input);
} Command;

Command commands[] = {
    {"AMP", handle_amp},
    {"STATUS", handle_status},
    {"TOGGLE", handle_toggle},
    {"CYCLES", handle_cycles},
    {"RESET", handle_reset},
    {"HELP", handle_help},
    {"SET", handle_set}
};

void process_command(char *input) {
    // Process the command received in the input buffer
    printf("Processing command: %s\n", input);

    char input_copy[BUF_SIZE];
    strncpy(input_copy, input, BUF_SIZE);
    input_copy[BUF_SIZE - 1] = '\0'; // Ensure null-termination

    char *cmd = strtok(input_copy, " ");
    if (cmd == NULL) {
        printf("Invalid command format. Type 'HELP' for Commands\n");
        return;
    }
    
    for (size_t i = 0; i < sizeof(commands) / sizeof(Command); i++) {
        if (strcmp(cmd, commands[i].command) == 0) {
            commands[i].handler(input);
            return;
        }
    }

    printf("Unknown command: %s\nType 'HELP' for Commands\n", input);

}
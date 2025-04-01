

void log_command(const char *command, const char *result);
void handle_amp_on(void);
void handle_amp_off(void);
void handle_amp(char *input);
void handle_status(char *input);
void handle_toggle(char *input);
void handle_cycles(char *input);
void handle_reset(char *input);
void process_command(char *input);
void handle_set(char *input);
void handle_help(char *input);
void log_command(const char *command, const char *result);
void handle_gpio(int pin, char *input);
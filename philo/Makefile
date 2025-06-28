SRC = philo_acts.c philo_pars.c philo_setup.c philo_start.c philo_utils.c philo_utils1.c philo_utils2.c  philo.c
OBJ = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror
NAME = philo

all: $(NAME)

$(NAME): $(OBJ)
	@echo "\033[1;32m✅ Compiling complete source code into executable...\033[0m"
	@$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "\033[1;32m🎉 Build successful! You can now run ./philo\033[0m"

%.o: %.c philo.h
	@$(CC) $(CFLAGS) -c $< -o $@
	@echo "\033[1;34m🔹 Compiling: $< -> $@\033[0m"

clean:
	@echo "\033[0;33m🧼 Removing compiled object files to clean up...\033[0m"
	@rm -f $(OBJ)
	@echo "\033[0;32m✔️  Clean complete.\033[0m"

fclean: clean
	@echo "\033[0;31m🗑️ Removing final executable (philosophers)...\033[0m"
	@rm -f $(NAME)
	@echo "\033[0;32m✔️  Full clean complete.\033[0m"

re: fclean all

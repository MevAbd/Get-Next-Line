# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#   Makefile                                            :+:      :+:    :+:   #
#                                                     +:+ +:+         +:+      #
#   By: malbrand <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#   Created: 2021/01/26 12:00:00 by malbrand          #+#    #+#              #
#   Updated: 2021/01/26 12:00:00 by malbrand         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Colors
RESET	= \033[0m
RED		= \033[31m
GREEN	= \033[32m
YELLOW	= \033[33m
BLUE	= \033[34m
MAGENTA	= \033[35m
CYAN	= \033[36m
WHITE	= \033[37m
BOLD	= \033[1m

# Compiler and flags
CC		= cc
CFLAGS	= -Wall -Wextra -Werror
AR		= ar
ARFLAGS	= rcs

# Project name
NAME	= get_next_line.a

# Directories
SRC_DIR	= .
OBJ_DIR	= obj

# Source files
SRC		= get_next_line.c \
		  get_next_line_utils.c

# Object files
OBJ		= $(SRC:%.c=$(OBJ_DIR)/%.o)

# Default BUFFER_SIZE if not defined
ifndef BUFFER_SIZE
BUFFER_SIZE = 42
endif

# Compiler flags with BUFFER_SIZE
CFLAGS += -D BUFFER_SIZE=$(BUFFER_SIZE)

# Rules
all: $(NAME)
	@echo "$(GREEN)$(BOLD)✓ $(NAME) compiled successfully!$(RESET)"

$(NAME): $(OBJ)
	@echo "$(CYAN)$(BOLD)Creating library $(NAME)...$(RESET)"
	@$(AR) $(ARFLAGS) $(NAME) $(OBJ)
	@echo "$(GREEN)$(BOLD)✓ Library created!$(RESET)"

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)Compiling $(CYAN)$<$(YELLOW)...$(RESET)"
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)
	@echo "$(BLUE)$(BOLD)Created directory $(OBJ_DIR)/$(RESET)"

clean:
	@echo "$(RED)$(BOLD)Cleaning object files...$(RESET)"
	@rm -rf $(OBJ_DIR)
	@echo "$(GREEN)$(BOLD)✓ Object files removed!$(RESET)"

fclean: clean
	@echo "$(RED)$(BOLD)Cleaning library...$(RESET)"
	@rm -f $(NAME)
	@echo "$(GREEN)$(BOLD)✓ Library removed!$(RESET)"
	@echo "$(RED)$(BOLD)Cleaning test executable...$(RESET)"
	@rm -f $(TEST_NAME)
	@echo "$(GREEN)$(BOLD)✓ Test executable removed!$(RESET)"

re: fclean all
	@echo "$(MAGENTA)$(BOLD)✓ Project rebuilt!$(RESET)"

# Test executable
TEST_NAME	= test_gnl
TEST_SRC	= test.c

# Bonus rules (will be added when bonus files are created)
bonus: all
	@echo "$(GREEN)$(BOLD)✓ Bonus compiled!$(RESET)"

test: $(NAME)
	@echo "$(CYAN)$(BOLD)Compiling test program...$(RESET)"
	@$(CC) $(CFLAGS) $(TEST_SRC) $(NAME) -o $(TEST_NAME)
	@echo "$(GREEN)$(BOLD)✓ Test program compiled!$(RESET)"
	@echo "$(YELLOW)Run with: ./$(TEST_NAME) [file]$(RESET)"

test_run: test
	@echo "$(CYAN)$(BOLD)Running tests...$(RESET)"
	@./$(TEST_NAME)

test_clean:
	@echo "$(RED)$(BOLD)Cleaning test files...$(RESET)"
	@rm -f test_*.txt testeur* test_simple.txt
	@echo "$(GREEN)$(BOLD)✓ Test files removed!$(RESET)"

.PHONY: all clean fclean re bonus test test_run test_clean


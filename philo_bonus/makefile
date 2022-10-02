.PHONY: all re clean fclean

B_NAME = philo_bonus
CC = gcc
B_INCL = ./src/philo.h
FALGS = -Wall -Wextra -Werror -g
B_SRC_NAME = main philo_utils philo_init philo_child
BUILD_DIR = build/
B_SRC_DIR  = src/
LIBS = ../lib/libft/libft.a
LIB_FT = ../lib/libft/
B_SRC = $(addsuffix .c, $(B_SRC_NAME))
B_SRC_P = $(addprefix $(B_SRC_DIR), $(B_SRC))
B_OBJ = $(addsuffix .o, $(B_SRC_NAME))
B_OBJ_P = $(addprefix $(BUILD_DIR), $(B_OBJ))

all : $(B_NAME)
	@echo everything is in order...

$(B_NAME) : $(B_OBJ_P) $(B_INCL)
	$(CC) $(FALGS) $(B_OBJ_P) $(LIBS) -o $(B_NAME)

$(BUILD_DIR)%.o : $(B_SRC_DIR)%.c $(B_INCL)
	@make -C $(LIB_FT)
	@mkdir -p $(BUILD_DIR)
	$(CC) $(FALGS) -c $< -o $@

clean :
	@make clean -C $(LIB_FT)
	rm -rf $(BUILD_DIR)

fclean : clean
	@make fclean -C $(LIB_FT)
	rm -rf $(B_NAME)

re : fclean all

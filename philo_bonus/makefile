.PHONY: all re clean fclean

B_NAME = philo_bonus
CC = gcc
B_INCL = philo_bonus.h
FALGS = -Wall -Wextra -Werror -pthread -g
B_SRC_NAME = main philo_utils philo_init philo_child
BUILD_DIR = build/
B_SRC_DIR  = src/
LIBS = ../lib/libft/libft.a
LIB_FT = ../lib/libft/
B_SRC = $(addsuffix .c, $(B_SRC_NAME))
B_SRC_P = $(addprefix $(B_SRC_DIR), $(B_SRC))
B_OBJ = $(addsuffix .o, $(B_SRC_NAME))
B_OBJ_P = $(addprefix $(BUILD_DIR), $(B_OBJ))

all : $(B_OBJ_P)
	make -C $(LIB_FT)
	$(CC) $(FALGS) $(B_OBJ_P) $(LIBS) -o $(B_NAME)
	
$(BUILD_DIR)%.o : $(B_SRC_DIR)%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(FALGS) -c $< -o $@

clean : 
	make fclean -C $(LIB_FT)
	rm -rf $(BUILD_DIR)

fclean : clean
	rm -rf $(B_NAME)

re : fclean all

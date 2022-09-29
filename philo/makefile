.PHONY: all re clean fclean

NAME = philo
CC = gcc
M_INCL = philo.h
FALGS = -Wall -Wextra -Werror -pthread -g
M_SRC_NAME = main philo_utils philo_init
BUILD_DIR = build/
M_SRC_DIR  = src/
LIBS = ../lib/libft/libft.a
LIB_FT = ../lib/libft/
M_SRC = $(addsuffix .c, $(M_SRC_NAME))
M_SRC_P = $(addprefix $(M_SRC_DIR), $(M_SRC))
M_OBJ = $(addsuffix .o, $(M_SRC_NAME))
M_OBJ_P = $(addprefix $(BUILD_DIR), $(M_OBJ))

all : $(M_OBJ_P)
	$(CC) $(FALGS) $(M_OBJ_P) $(LIBS) -o $(NAME)

$(BUILD_DIR)%.o : $(M_SRC_DIR)%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(FALGS) -c $< -o $@

clean : 
	make -C $(LIB_FT)
	rm -rf $(BUILD_DIR)

fclean : clean
	rm -rf $(NAME)

re : fclean all

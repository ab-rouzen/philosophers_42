.PHONY: all re clean fclean $(NAME)

NAME = philo
CC = gcc
INCL = philo.h
FALGS = -Wall -Wextra -Werror -pthread -g
M_SRC_NAME = main philo_utils
BUILD_DIR = build/
SRC_DIR  = src/
LIBS = src/libft/libft.a
LIB_FT = src/libft/
M_SRC = $(addsuffix .c, $(M_SRC_NAME))
M_SRC_P = $(addprefix $(SRC_DIR), $(M_SRC))
M_OBJ = $(addsuffix .o, $(M_SRC_NAME))
M_OBJ_P = $(addprefix $(BUILD_DIR), $(M_OBJ))

all : $(M_OBJ_P)
	$(CC) $(FALGS) $(M_OBJ_P) $(LIBS) -o $(NAME)

$(BUILD_DIR)%.o : $(SRC_DIR)%.c
	mkdir -p $(BUILD_DIR)
	$(CC) $(FALGS) -c $< -o $@

clean : 
	make -C $(LIB_FT)
	rm -rf $(BUILD_DIR)

fclean : clean
	rm -rf $(NAME)

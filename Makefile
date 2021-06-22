INC_DIR := inc/
SRC_DIR	:= srcs/
OBJ_DIR	:= obj/

OBJ_DIRS = $(OBJ_DIR)

PRE_SRCS =	main

SRCS = $(addsuffix .cpp, $(addprefix $(SRC_DIR), $(PRE_SRCS)))
OBJS = $(addsuffix .o, $(addprefix $(OBJ_DIR), $(PRE_SRCS)))


NAME := ircPower


CC := clang++
CFLAGS := -Wall -Wextra -Werror -std=c++98
INC	:= -I./$(INC_DIR)
RM = rm -f

all:	$(NAME)

$(NAME): $(OBJ_DIRS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 
	echo "----- \033[32m $@ created\033[0m  -----"

$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)

$(OBJS) : $(INC_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
	echo "$@ \033[32mcreated\033[0m"

clean:
	rm -rf $(OBJ_DIR)

fclean: 	clean
	rm -f $(NAME)

re:		fclean all

.PHONY : all clean fclean re
.SILENT :
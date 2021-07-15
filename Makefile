INC_DIR := inc/
SRC_DIR	:= srcs/
CLASS_DIR := class/
COM_DIR := com/
OBJ_DIR	:= obj/

OBJ_DIRS = $(OBJ_DIR)


CLASS_SRCS = Socket Client Server Channel

COM_SRCS = com messages poll welcome 

PRE_SRCS =	main init connexion \
			$(addprefix $(CLASS_DIR), $(CLASS_SRCS)) \
			$(addprefix $(COM_DIR), $(COM_SRCS))

SRCS = $(addsuffix .cpp, $(addprefix $(SRC_DIR), $(PRE_SRCS)))
OBJS = $(addsuffix .o, $(addprefix $(OBJ_DIR), $(PRE_SRCS)))


NAME := ircserv


CC := clang++
CFLAGS := -Wall -Wextra -Werror -std=c++98 -g
INC	:= -I./$(INC_DIR) -I./$(INC_DIR)Messages/
RM = rm -f

all:	$(NAME)
	echo "----- \033[33m| --- --- --- --- TO USE --- --- --- --- |\033[0m -----"
	echo "----- \033[33m| ./ircserv  \033[34m   6667     <set password>\033[33m  |\033[0m -----"
	echo "----- \033[33m| nc 127.0.0.1 \033[34m 6667                 \033[33m    |\033[0m -----"
	echo "----- \033[33m| --- --- --- --- ------ --- --- --- --- |\033[0m -----"

$(NAME): $(OBJ_DIRS) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME) 
	echo "----- \033[32m $@ created\033[0m  -----"


$(OBJ_DIRS):
	mkdir -p $(OBJ_DIRS)
	mkdir -p $(OBJ_DIRS)class
	mkdir -p $(OBJ_DIRS)com

$(OBJS) : $(INC_DIR)

$(OBJ_DIR)%.o: $(SRC_DIR)%.cpp $(wildcard $(INC_DIR)*.hpp)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@
	echo "$@ \033[32mcreated\033[0m"

clean:
	rm -rf $(OBJ_DIR)

fclean: 	clean
	rm -f $(NAME)

re:		fclean all

.PHONY : all clean fclean re
.SILENT :
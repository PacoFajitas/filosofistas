NAME = philo

#########
RM = rm -f
CC = cc
CFLAGS = -Werror -Wextra -Wall -g #-fsanitize=thread
#########

#########
FILES = philo args errors utils routine

SRC = $(addsuffix .c, $(FILES))

vpath %.c srcs
#########

#########
OBJ_DIR = objs
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))
DEP = $(addsuffix .d, $(basename $(OBJ))) 
#########

#########
$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	${CC} $(CFLAGS) -c $< -o $@

all:
	$(MAKE) $(NAME) --no-print-directory

$(NAME): $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)
	@echo "EVERYTHING DONE  "

clean:
	$(RM) $(OBJ) $(DEP) --no-print-directory
	$(RM) -r $(OBJ_DIR) --no-print-directory
	@echo "OBJECTS REMOVED   "

fclean: clean
	$(RM) $(NAME) --no-print-directory
	@echo "EVERYTHING REMOVED   "

re:	fclean all

.PHONY: all clean fclean re

-include $(DEP)

#########

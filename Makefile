CC = cc
CFLAGS = -Wall -Wextra -Werror -pthread -MMD -MP
NAME = codexion
INCLUDES = coders

SRCS = main.c \
	parsing.c \
	dongles.c \
	coders.c \
	coder_actions.c \
	utils.c \
	utils_second.c \
	queue.c \
	queue_schedulers.c \
	mutexes.c
OBJ_DIR = objs/
OBJS =$(addprefix $(OBJ_DIR), $(SRCS:.c=.o))
DEP = $(OBJS:.o=.d)


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -I$(INCLUDES) -o $@

$(OBJ_DIR)%.o: %.c 
	@mkdir -p $(OBJ_DIR)
	$(CC) $(CFLAGS) -I$(INCLUDES) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re

-include $(DEP)

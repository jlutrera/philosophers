#Files
SRCS		=	main.c utils.c life.c life_utils.c messages.c

# Sources and objects
OBJS		=	$(SRCS:.c=.o)
DEPS		=	$(SRCS:.c=.d)

# Constant strings
NAME		=	philo
CC			=	gcc
#CFLAGS		=	-MMD -Wall -Wextra -Werror -fsanitize=thread -g3
CFLAGS		=	-MMD -Wall -Wextra -Werror
RM 			=	rm -rf
LDFLAGS		=	-pthread

#  Colors
CYAN		=	\033[0;36m
YELLOW		=	\033[0;33m
GREEN		=	\033[0;32m
BLUE 		= 	\033[0;94m
RED			=	\033[0;31m
RESET		=	\033[0m

# Rules
all			:	$(NAME)

%.o			:	%.c
				echo "Compiling $(BLUE)$@$(RESET) ... \c"
				$(CC) $(CFLAGS) -c $< -o $@
				echo "$(GREEN)OK !$(RESET)" 

$(NAME) 	:	$(OBJS)
				echo "Linking object files ...\c"
				$(CC) $(CFLAGS) $^ $(LDFLAGS) -o $(NAME)
				echo "$(GREEN)OK !$(RESET)"
				echo "$(YELLOW)$(NAME) programme created successfully !$(RESET)"

clean		:	
				$(RM) $(OBJS) $(DEPS)
				echo "Object files $(RED)DELETED $(RESET)!"

fclean		:	clean
				$(RM) $(NAME)
				echo "Binary files $(RED)DELETED $(RESET)!"

re			:	fclean all

-include $(DEPS)

.SILENT		:	all $(NAME) clean fclean re $(OBJS)
.PHONY		:	all clean fclean re
#Files
SRCS		=	main.c utils.c life.c messages.c
HEADER		=	philo.h

# Sources and objects
OBJS		=	$(SRCS:.c=.o)

# Constant strings
NAME		=	philo
CC			=	gcc
RM 			=	rm -rf
#LEAKS		=	-g3 -fsanitize=thread
LEAKS		=	-g3 -fsanitize=address
LIB			=	-pthread
W_FLAGS		=	-Wall -Wextra -Werror -pedantic

#  Colors
CYAN		=	\033[0;36m
YELLOW		=	\033[0;33m
GREEN		=	\033[0;32m
BLUE 		= 	\033[0;94m
RED			=	\033[0;31m
RESET		=	\033[0m

# Rules
all			:	$(NAME)

%.o			:	%.c $(HEADER)
				@echo "Compiling $(BLUE)$@$(RESET) ... \c"
				@$(CC) $(W_FLAGS) $(LIB) -c $< -o $@
				@echo "$(GREEN)OK !$(RESET)" 

$(NAME) 	:	$(OBJS)       
				@echo "Linking object files ...\c"
				@$(CC) $(OBJS) $(LEAKS) -I$(HEADER)$(LIB) -o $(NAME)
				@echo "$(GREEN)OK !$(RESET)"
				@echo "$(YELLOW)$(NAME) programme created successfully !$(RESET)"

clean		:	
				@$(RM) $(OBJS)
				@echo "Object files $(RED)DELETED $(RESET)!"

fclean		:	clean
				@$(RM) $(NAME)
				@echo "Binary files $(RED)DELETED $(RESET)!"

re			:	fclean all

.PHONY		:	all clean fclean re
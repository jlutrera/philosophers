#Files
SRCS		=	philo.c philo_utils.c philosopher.c

# Sources and objects
RM 			=	rm -rf
OBJS		=	$(SRCS:.c=.o)
HEADER		=	philo.h

# Constant strings
NAME		=	philo
INCL		=	-I$(HEADER)
LEAKS		=	-g3 -fsanitize=address
LIB			=	-pthread
W_FLAGS		=	-Wall -Wextra -Werror

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
				@echo "Compiling $(BLUE)$@$(RESET) ... \c"
				@$(CC) $(W_FLAGS) $(LIB) -c $< -o $@
				@echo "$(GREEN)OK !$(RESET)" 

$(NAME) 	:	$(OBJS)           
				@echo "Linking object files ...\c"
				@$(CC) $(OBJS) $(LEAKS) $(INCL)$(LIB) -o $(NAME)
				@echo "$(GREEN)OK !$(RESET)"
				@echo "$(YELLOW)$(NAME) programme created successfully !$(RESET)"

clean		:	
				@$(RM) $(OBJS)
				@echo "All the object files $(RED)DELETED $(RESET)!"

fclean		:	clean
				@$(RM) $(NAME)
				@echo "All files $(RED)DELETED $(RESET)!"

re			:	fclean all

.PHONY		:	all clean fclean re
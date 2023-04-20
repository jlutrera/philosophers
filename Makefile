#Files
SRCS		=	$(wildcard *.c)

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
CYAN		=	\e[36m
YELLOW		=	\e[33m
GREEN		=	\e[32m
BLUE 		= 	\e[94m
RESET		=	\e[0m

# Rules
all			:	$(NAME)

%.o			:	%.c
				@echo "$(BLUE)Compiling $@ ! $(RESET)\c"
				@$(CC) $(W_FLAGS) $(LIB) -c $< -o $@
				@echo "... $(GREEN)OK$(RESET)" 

$(NAME) 	:	$(OBJS)           
				@echo "$(YELLOW)Linking object files ! $(RESET)\c"
				@$(CC) $(OBJS) $(LEAKS) $(INCL)$(LIB) -o $(NAME)
				@echo "$(GREEN)SUCCESS !$(RESET)"
				@echo "$(NAME) created successfully !"

clean		:	
				@$(RM) $(OBJS)
				@echo "$(CYAN)Deleted all the object files$(RESET)"

fclean		:	clean
				@$(RM) $(NAME)
				@echo "$(CYAN)Deleted all the exec files$(RESET)"

re			:	fclean all

.PHONY		:	all clean fclean re
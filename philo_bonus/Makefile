NAME	=	philo_bonus

SRCS	=	main.c \
			actions.c \
			philo.c \
			print.c \
			semaphore.c \
			utils.c \
			monitor.c \

OBJS	=	$(SRCS:.c=.o)

CC		=	gcc

CFLAGS	=	-Wall -Wextra -Werror -g -I. -pthread

all 	:	$(NAME)

$(NAME)	:	$(OBJS)
			@echo "Compiling $@.."
			@$(CC) $(CFLAGS) -o $@ $(OBJS)

clean	:
			@echo "Cleaning all .o files.."
			@rm -f $(OBJS)

fclean	:	clean
			@echo "Cleaning $(NAME)"
			@rm -f $(NAME)

re		:	fclean all

.PHONY : all bonus clean fclean re

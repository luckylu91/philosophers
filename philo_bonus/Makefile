
FLAGS = -Wall -Wextra -Werror -I. -lpthread
NAME =	philo

SRCS =	$(addprefix main/, handle_args.c main.c main_utils.c valid_numeric_arg.c)
SRCS +=	$(addprefix philo_life/, philo_life.c philo_life_utils.c say.c)
SRCS +=	$(addprefix utils/, crate_table.c create_sem.c libft_utils.c quit.c time_utils.c)
OBJS =	$(SRCS:.c=.o)
HEADERS =	philosophers.h

all:	$(NAME)

$(NAME):	$(OBJS) $(HEADERS)
	gcc -o $@ $(OBJS) $(FLAGS)

%.o:	%.c
	gcc -c -o $@ $< $(FLAGS)

$(OBJS):	$(HEADERS)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re db

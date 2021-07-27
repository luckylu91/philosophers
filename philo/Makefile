NAME =		philo
NAME_DB =	philo_db
FLAGS = -Wall -Wextra -Werror -I.

SRCS =		$(addprefix main/, handle_args.c main.c main_utils.c quit.c tell_end.c valid_numeric_arg.c)
SRCS +=		$(addprefix philo_life/, crate_table.c philo_life.c philo_life_utils.c)
SRCS +=		$(addprefix utils/, libft_utils.c time_utils.c)
OBJS =		$(SRCS:.c=.o)
OBJS_DB =	$(SRCS:.c=.o_db)
HEADERS =	philosophers.h

all:	$(NAME)

$(NAME):	$(OBJS) $(HEADERS)
	gcc -o $@ $(OBJS) $(FLAGS)

db:	$(OBJS_DB)
	gcc -o $(NAME_DB) $(OBJS_DB) $(FLAGS) -g3 -fsanitize=address

%.o:	%.c
	gcc -c -o $@ $< $(FLAGS)
%.o_db:	%.c
	gcc -c -o $@ $< $(FLAGS) -g3 -fsanitize=address

$(OBJS):		$(HEADERS)


clean:
	rm -f $(OBJS)
	rm -f $(OBJS_DB)

fclean:	clean
	rm -f $(NAME)
	rm -f $(NAME_DB)

re:	fclean all

.PHONY:	all clean fclean re db

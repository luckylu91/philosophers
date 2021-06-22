NAME =		philo/philo
LIBFT =		$(LIBFT_DIR)/libft.a
FLAGS = -Wall -Wextra -Werror -Iphilo

SRCS =		$(addprefix philo/main/, handle_args.c main.c main_utils.c quit.c tell_end.c valid_numeric_arg.c)
SRCS +=		$(addprefix philo/philo_life/, crate_table.c philo_life.c philo_life_utils.c)
SRCS +=		$(addprefix philo/utils/, libft_utils.c time_utils.c)
OBJS =		$(SRCS:.c=.o)
HEADERS =	$(addprefix philo/, philosophers.h)

all:	$(NAME)

$(NAME):	$(OBJS)
	gcc -o $@ $(OBJS) $(FLAGS)
$(NAME):	$(HEADERS)

%.o:	%.c
	gcc -c -o $@ $< $(FLAGS)

clean:
	rm -f $(OBJS)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re

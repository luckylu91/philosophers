
CC = gcc
CFLAGS = -Wall -Wextra -Werror -Iinclude
NAME =	philo
SUBDIRS = $(addprefix src/, libft main philo_life utils)
SUBDIRS_OBJ = $(SUBDIRS:src/%=obj/%)
SRCS_RAW = $(addprefix main/, \
	handle_args.c \
	launch_simulation.c \
	main.c \
	valid_numeric_arg.c \
	wait_children.c \
)
SRCS_RAW +=	$(addprefix philo_life/, \
	init_philo.c \
	philo_eat.c \
	philo_life_utils.c \
	philo_life.c \
	philo_sleep.c \
	say.c \
)
SRCS_RAW +=	$(addprefix utils/, \
	crate_table.c \
	create_sem.c \
	quit.c \
	time_utils.c \
)
SRCS_RAW += $(addprefix libft/, \
	ft_atoi.c \
	ft_bzero.c \
	ft_calloc.c \
	ft_putstr_fd.c \
	ft_stpcpy.c \
	ft_stricpy.c \
	ft_strlen.c \
)
SRCS = $(addprefix src/, $(SRCS_RAW))
OBJS = $(SRCS:src/%.c=obj/%.o)
HEADERS =	$(addprefix include/, philosophers.h libft.h)

all:	$(NAME)

$(NAME):	$(OBJS) $(HEADERS)
	$(CC) -o $@ $(OBJS) $(CFLAGS)


obj/%.o:	src/%.c
	$(CC) -o $@  -c $< $(CFLAGS)
$(OBJS):	| $(SUBDIRS_OBJ)

$(SUBDIRS_OBJ):
	mkdir -p $(SUBDIRS_OBJ)

echo:
	echo $(OBJS)

clean:
# rm -f $(OBJS)
	rm -rf $(SUBDIRS_OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all

.PHONY:	all clean fclean re db

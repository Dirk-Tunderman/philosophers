NAME	= philo
CFLAGS	= -Wextra -Wall -Werror
CC		= gcc

RM		= rm -rf
LIBNAME	= philo.a

SOURCES	= main.c initiation.c action.c timing.c

OBJECTS	= $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC)  $(CFLAGS) $(OBJECTS) -o $(NAME)
clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all
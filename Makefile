NAME	= philosophers
CFLAGS	= -Wextra -Wall -Werror
CC		= gcc

RM		= rm -rf
LIBNAME	= philo.a

SOURCES	= main.c

OBJECTS	= $(SOURCES:.c=.o)

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CC)  $(CFLAGS) $(Name)
clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all
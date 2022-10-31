# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 08:14:11 by kalmheir          #+#    #+#              #
#    Updated: 2022/10/31 17:04:22 by kalmheir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo
BNSNAME	:= philo_bonus
SRCSDIR	:= src/
SRCFILS	:= main.c parsing.c table.c simulation.c life.c utils.c
SOURCES	:= $(addprefix $(SRCSDIR), $(SRCFILS))
OBJECTS	:= $(SOURCES:.c=.o)
CC		:= gcc
CFLAGS	:= -Wall -g -Wextra -Werror -pthread
RM		:= rm -f

$(NAME): mandatory 

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: mandatory

mandatory: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)
	
clean:
	$(RM) $(OBJECTS)

fclean: clean
	$(RM) $(NAME)

re: fclean mandatory


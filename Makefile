# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 08:14:11 by kalmheir          #+#    #+#              #
#    Updated: 2022/10/30 14:02:20 by kalmheir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo
BNSNAME	:= philo_bonus
SRCSDIR	:= $(NAME)/src/
SRCFILS	:= main.c parsing.c table.c simulation.c life.c time.c
SOURCES	:= $(addprefix $(SRCSDIR), $(SRCFILS))
BSRCDIR := $(BNSNAME)/src/
BSRCFIL	:= main.c
BNSSRCS := $(addprefix $(BSRCDIR), $(BSRCFIL))
OBJECTS	:= $(SOURCES:.c=.o)
BNSOBJS	:= $(OBJECTS:.c=.o)
CC		:= gcc
CFLAGS	:= -Wall -g -Wextra -Werror #-fsanitize=thread #-lpthread 
RM		:= rm -f

$(NAME): mandatory 

.c.o:
	$(CC) $(CFLAGS) -c $< -o $(<:.c=.o)

all: mandatory bonus

mandatory: $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(NAME)/$(NAME)
	
bonus: $(BNSOBJS)
	$(CC) $(CFLAGS) $(BNSOBJS) -o $(BNSNAME)/$(BNSNAME)

clean:
	$(RM) $(OBJECTS)
	$(RM) $(BNSOBJS)

fclean: clean
	$(RM) $(NAME)/$(NAME)
	$(RM) $(BNSNAME)/$(BNSNAME)

re: fclean mandatory

rea: fclean all

reb: fclean bonus

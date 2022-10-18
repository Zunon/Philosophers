# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kalmheir <kalmheir@student.42abudhabi.ae>  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/18 08:14:11 by kalmheir          #+#    #+#              #
#    Updated: 2022/10/18 08:39:46 by kalmheir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo
BNSNAME	:= philo_bonus
SOURCES	:= $(NAME)/src/main.c
BNSSRCS	:= $(BNSNAME)/src/main.c
OBJECTS	:= $(SOURCES:.c=.o)
BNSOBJS	:= $(OBJECTS:.c=.o)
CC			:= gcc
CFLAGS	:= -Wall -Wextra -Werror -lpthread 
RM			:= rm -f

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
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: modysseu <modysseu@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/11/19 14:39:25 by modysseu          #+#    #+#              #
#    Updated: 2021/11/25 15:31:13 by modysseu         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SERVER = server
CLIENT = client
SRC = server.c 
SRC2 = client.c

CC = gcc

FLAGS = -Wall -Wextra -Werror

all : $(SERVER) $(CLIENT)

$(SERVER) : $(SRC)
	${CC} ${FLAGS} $(SRC) -o $(SERVER)
	
$(CLIENT): $(SRC2)
	${CC} ${FLAGS} $(SRC2) -o $(CLIENT)
	
clean :
	rm -rf

fclean : clean
	rm -rf $(SERVER)
	rm -rf $(CLIENT)

re: fclean all

.PHONY : all clean fclean re
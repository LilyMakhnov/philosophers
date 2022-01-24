# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esivre <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 16:19:19 by esivre            #+#    #+#              #
#    Updated: 2022/01/24 14:51:35 by esivre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = philo

SRCS	=	main.c time.c

OBJS	=	$(addprefix $(OBJDIR),$(SRCS:.c=.o))
DEPS	=	$(addprefix $(DEPDIR),$(SRCS:.c=.d))
LIBFT	=   libft/libft.a
FLAGS	=	-Wall -Wextra -Werror
SRCDIR	=	./srcs/
OBJDIR	=	./objs/
DEPDIR	=	./objs/
INCDIR	=	./includes/

all:		$(LIBFT) $(LIBMLX) $(NAME)

$(OBJDIR)%.o:	$(SRCDIR)%.c
			gcc $(FLAGS) -MMD -MP -c -I libft -I $(INCDIR) $< -o $@

$(LIBFT):		
			make bonus -C libft

$(OBJDIR):
			mkdir -p $(OBJDIR)

$(NAME):	$(OBJDIR) $(OBJS)
		gcc $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lpthread

clean:
			/bin/rm -rf objs
			make -C ./libft clean

fclean:		clean
			/bin/rm -f $(NAME)
			make -C ./libft/ fclean

re:			fclean all

.PHONY:		all clean fclean re

-include $(DEPS)
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: esivre <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/27 16:19:19 by esivre            #+#    #+#              #
#    Updated: 2022/02/08 16:38:41 by esivre           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #
NAME = philo

SRCS	=	main.c time.c action.c init.c exit.c

OBJS	=	$(addprefix $(OBJDIR),$(SRCS:.c=.o))
DEPS	=	$(addprefix $(DEPDIR),$(SRCS:.c=.d))
FLAGS	=	-Wall -Wextra -Werror  -g3 -fsanitize=thread
SRCDIR	=	./srcs/
OBJDIR	=	./objs/
DEPDIR	=	./objs/
INCDIR	=	./includes/

all:		$(NAME)

$(OBJDIR)%.o:	$(SRCDIR)%.c
			gcc $(FLAGS) -MMD -MP -c -I libft -I $(INCDIR) $< -o $@

$(OBJDIR):
			mkdir -p $(OBJDIR)

$(NAME):	$(OBJDIR) $(OBJS)
		gcc $(FLAGS) $(OBJS) -o $(NAME) $(LIBFT) -lpthread

clean:
			/bin/rm -rf objs

fclean:		clean
			/bin/rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re

-include $(DEPS)

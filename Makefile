# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: adebray <adebray@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/02/11 01:49:54 by amaurer           #+#    #+#              #
#    Updated: 2015/10/26 04:27:16 by adebray          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	bin/lem-ipc

export CC		=	clang
export CFLAGS	=	-Iinc -Iglfw/include -Wall -Werror -Wextra -pedantic -O3
LDFLAGS			=	-Lglfw/src -lglfw3 -Llibft -lft -Lbin -lcommon -framework Cocoa -framework OpenGL -framework IOKit -framework CoreVideo

GSRC			=	$(addprefix src/graphic/, $(shell ls src/graphic | grep '\.c'))
GOBJ			=	$(GSRC:.c=.o)
CSRC			=	$(addprefix src/lemipc/, $(shell ls src/lemipc | grep '\.c'))
COBJ			=	$(CSRC:.c=.o)
COMSRC			=	$(addprefix src/common/, $(shell ls src/common | grep '\.c'))
COMOBJ			=	$(COMSRC:.c=.o)

all: _depend

_depend:
	@mkdir -p bin
	sh depend.sh
	make -C libft
	make bin/libcommon.a
	make $(NAME)
	make bin/graphic

bin/libcommon.a: $(COMOBJ) inc/common.h
	ar rc $@ $(COMOBJ)
	ranlib $@
	@echo "\033[32m•\033[0m $@ is ready."

bin/graphic: $(GOBJ) inc/graphic.h bin/libcommon.a
	$(CC) $(LDFLAGS) -o $@ $(GOBJ)
	@echo "\033[32m•\033[0m $@ is ready."

$(NAME): $(COBJ) bin/libcommon.a
	$(CC) $(LDFLAGS) -o $@ $(COBJ)
	@echo "\033[32m•\033[0m $@ is ready."

clean:
	make -C libft clean
	make -C minilibx_macos clean
	rm -rf $(GOBJ) $(COBJ) $(COMOBJ)

fclean:
	make -C libft fclean
	rm -rf $(GOBJ) $(COBJ) $(COMOBJ)
	rm -rf bin

re: fclean all

.PHONY: all re fclean clean $(NAME) bin/graphic

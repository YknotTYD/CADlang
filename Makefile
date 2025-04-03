##
## EPITECH PROJECT, 2025
## CADlang
## File description:
## Makefile;
##

SRC  = $(shell find -name *.c)
NAME = cadlang
DEFAULTARGS = temp.cads

compile:
	@ gcc -g -Wall -Wextra $(SRC) $(LIBS) \
		-o $(NAME)

run: compile
	@ ./$(NAME)  $(DEFAULTARGS)
	@ rm $(NAME)

valgrinds: compile
	@valgrind -s --show-leak-kinds=all \
		--track-origins=yes \
		--track-fds=yes \
		--leak-check=full \
		--error-limit=no \
	./$(NAME) $(DEFAULTARGS)
	@ rm $(NAME)

valgrind: compile
	@valgrind -s --show-leak-kinds=all \
		--track-origins=yes \
		--track-fds=yes \
		--leak-check=full \
		--error-limit=no \
		--quiet \
	./$(NAME) $(DEFAULTARGS)
	@ rm $(NAME)

update: re
	@ sudo mv $(NAME) /usr/local/bin

clean:
	@ rm -fr *.o

fclean: clean
	@ rm -f $(NAME)

re: fclean compile

kronk:
	@ echo "Oh ouais."

##
## EPITECH PROJECT, 2021
## Makefile
## File description:
## Makefile
##

SRC = \
	src/button/button.c                                \
	src/button/change_button.c                         \
	src/button/get_button_ev.c                         \
	src/button/build_button.c                          \
	src/button/setters.c                               \
	src/button/setters_next.c                          \
	src/sprite/init_sprite.c                           \
	src/sprite/sprite_modif.c                          \
	src/sprite/rotate_vector.c                         \
	src/globals/fonts.c                                \
	src/globals/texture.c                              \
	src/globals/sounds.c                               \
	src/globals/window.c                               \
	src/globals/pnj.c                                  \
	src/settings/apply.c                               \
	src/settings/checkbox.c                            \
	src/settings/destroy.c                             \
	src/settings/load.c                                \
	src/settings/move_settings.c                       \
	src/settings/rendering_evt.c                       \
	src/settings/save.c                                \
	src/settings/scale_settings.c                      \
	src/settings/set_evt.c                             \
	src/settings/set_evt_manager.c                     \
	src/settings/settings.c                            \
	src/settings/sound_evt.c                           \
	src/settings/visu_updates.c                        \
	src/global_win/rescale_all.c                       \
	src/global_win/transition.c                        \
	src/global_win/init_window.c                       \
	src/clock/time.c                                   \
	src/clock/my_clock.c                               \
	src/clock/clock_list.c                             \
	src/line_edit/create.c                             \
	src/line_edit/events.c                             \
	src/sound_builder/build_sfx.c                      \
	src/sound_builder/build_music.c                    \
	src/rand/srand.c                                   \
	src/main.c                                         \
	src/free.c \
	src/main_menuu/create.c

OBJ = $(SRC:.c=.o)

NAME = my_rpg

CFLAGS = -Wall -Wextra -I ./include/ -I lib/my/include/

LDFLAGS += -L lib/my/ -lmy -lcsfml-graphics -lcsfml-window -lcsfml-audio \
			-lcsfml-system -lm

all: $(NAME)

$(NAME):   $(OBJ)
	make -s -C lib/my/
	gcc -o $(NAME) $(FLAGS) $(OBJ) $(LDFLAGS)

clean:
	find . -name "*.o" -delete
	rm -f $(OBJ)

fclean:    clean
	rm -f $(NAME)
	rm -f *.c~
	rm -f *.out
	rm -f vgcore*
	rm -f *.gcda
	rm -f *.gcno
	rm -f unit_tests*

re:        fclean all

debug: CFLAGS += -g
debug: all

run: all
	./$(NAME)

lib_fclean:
	cd lib/my/ && make fclean

push_fclean: fclean
	cd lib/my/ && make fclean

re:	fclean all

valgrind: all
	valgrind --track-origins=yes --leak-check=full \
	--show-leak-kinds=definite,indirect ./$(NAME)

tests_run: exec_lib
	gcc -o unit_tests $(SRC) tests/*.c -Llib/ -lmy --coverage -lcriterion
	./unit_tests
	gcovr --exclude tests
	gcovr -b --exclude tests

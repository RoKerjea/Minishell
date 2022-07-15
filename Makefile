# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: nvasilev <nvasilev@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/16 00:51:39 by nvasilev          #+#    #+#              #
#    Updated: 2022/07/16 01:06:16 by nvasilev         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

################################################################################
#                                      VARS                                    #
################################################################################

# This is a minimal set of ANSI/VT100 color codes
_END =		$'\033[0m
_BOLD =		$'\033[1m
_UNDER =	$'\033[4m
_REV =		$'\033[7m

# Colors
_GREY =		$'\033[30m
_RED =		$'\033[31m
_GREEN =	$'\033[32m
_YELLOW =	$'\033[33m
_BLUE =		$'\033[34m
_PURPLE =	$'\033[35m
_CYAN =		$'\033[36m
_WHITE =	$'\033[37m

################################################################################
#                                     CONFIG                                   #
################################################################################


NAME =		minishell
CC =		cc $(CFLAGS)
CFLAGS		= -Wall -Werror -Wextra

INCLUDES =	-I ./includes/
RM =		rm -rf

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRCS =		${addprefix parsing/, \
			bool_str.c \
			tokenizer.c \
			token_assign.c \
			parser.c \
			parsing_struct.c \
			print_parsed.c \
			print_token.c} \
			${addprefix libft/, \
			ft_strlen.c \
			ft_split.c \
			ft_strjoin.c \
			ft_freetab.c \
			ft_strdup.c \
			ft_strchr.c \
			ft_strncmp.c} \
			${addprefix builtin/, \
			builtins.c \
			directories.c \
			env_make.c \
			env_use.c} \
			minishell.c

################################################################################
#                                     OBJECTS                                  #
################################################################################

OBJECTS = 	$(subst /,/build/,${SRCS:.c=.o})
DEPEND =	${OBJECTS:.o=.d}

################################################################################
#                                     RULES                                    #
################################################################################

all: $(NAME)

${NAME}: ${OBJECTS}
	@echo "${_UNDER}${_RED}Creating Executable${_END}"
	@echo "${_BOLD}${_GREEN}${CC} -o ${NAME} ${OBJECTS} -lreadline ${_END}"
	@${CC} -o ${NAME} ${OBJECTS} -lreadline

-include ${DEPEND}

${OBJECTS}: $(subst .o,.c,$(subst /build/,/,$@))
	@if [ ! -d "./parsing/build" ]; then\
		echo "${_UNDER}${_RED}"Creating Objects Directories"${_END}";\
	fi
	@if [ ! -d "./$(dir $@)" ]; then\
		echo "${_BOLD}${_UNDER}${_BLUE}"mkdir -p $(dir $@)"${_END}";\
		mkdir -p $(dir $@);\
	fi
	@echo "${_BOLD}${_BLUE}"$(CC) -MMD -c $(subst .o,.c,$(subst /build/,/,$@)) -o $@"${_END}"
	@$(CC) -MMD -c $(subst .o,.c,$(subst /build/,/,$@)) -o $@

clean:
	@echo "${_UNDER}${_RED}Deleting Objects and Dependencies${_END}"
	@echo "${_BOLD}${_YELLOW}"${RM} ${OBJECTS} ${DEPEND}"${_END}"
	@${RM} ${OBJECTS} ${DEPEND}
	@echo "${_BOLD}${_YELLOW}"${RM} parsing/build"${_END}"
	@${RM} parsing/build
	@echo "${_BOLD}${_YELLOW}"${RM} libft/build"${_END}"
	@${RM} libft/build
	@echo "${_BOLD}${_YELLOW}"${RM} builtin/build"${_END}"
	@${RM} builtin/build

fclean: clean
	@echo "${_UNDER}${_RED}Deleting Executable${_END}"
	@echo "${_BOLD}${_RED}"${RM} ${NAME}"${_END}"
	@${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re

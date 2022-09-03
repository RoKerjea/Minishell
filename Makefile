# This is a minimal set of ANSI/VT100 color codes
_END=$'\033[0m
_BOLD=$'\033[1m
_UNDER=$'\033[4m
_REV=$'\033[7m

# Colors
_GREY=$'\033[30m
_RED=$'\033[31m
_GREEN=$'\033[32m
_YELLOW=$'\033[33m
_BLUE=$'\033[34m
_PURPLE=$'\033[35m
_CYAN=$'\033[36m
_WHITE=$'\033[37m

SRCS		=	${addprefix parsing/, \
				bool_str.c \
				tokenizer.c \
				token_assign.c \
				field_splitter.c \
				expander.c \
				token_parser.c \
				unquoter.c \
				parser.c \
				parsing_struct.c} \
				${addprefix libft/, \
				ft_strlen.c \
				ft_split.c \
				ft_atoi.c \
				ft_strtrim.c \
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
				${addprefix testdir/, \
				print_parsed.c \
				print_token.c} \
				minishell.c

HEADER		= include/shell_parsing.h
RM			= rm -rf
NAME		= minishell
CC			= gcc $(CFLAGS)

OBJECTS = $(subst /,/build/,${SRCS:.c=.o})
DEPEND	= ${OBJECTS:.o=.d}

CFLAGS		= -Wall -Werror -Wextra -g3 #-fsanitize=address

all:	$(NAME)

${NAME}:	${OBJECTS}
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

gitm: fclean
	git add .
	git commit
	git push

VER_H = include/Version_minishell.h
USER := $(shell env | grep USER | tail --bytes=+6)
TIME=$(shell date +"%d %m %Y %Hh%M %Z")

git: fclean
	$(eval MIN=$(shell expr $$(awk '/# define MINOR_VERSION/' $(VER_H) | tr -cd "[0-9]") + 1))
	$(eval MAJ=$(shell awk '/# define MAJOR_VERSION/' $(VER_H) | tr -cd "[0-9]"))
	sed -i 's/# define MINOR_VERSION .*/# define MINOR_VERSION \"$(MIN)\"/' $(VER_H)
	sed -i 's/# define BUILD_DATE .*/# define BUILD_DATE \"$(TIME)\"/' $(VER_H)
	git add .
	git commit -m "V$(MAJ).$(MIN) by $(USER) at $(TIME)"
	git push

re:			fclean all

.PHONY:		all clean fclean re gitm git
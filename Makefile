NAME = minishell

PARSING =	main.c \
			parsing/utils.c \
			parsing/ft_free.c parsing/parsing.c \

EXECUTION =	execution/exec_comandes.c \
			execution/exec_echo.c execution/exec_pwd.c   \
			execution/exec_env.c execution/exec_unset.c   \
			execution/prompt_utils.c execution/exec_cd.c   \
			execution/env_to_list.c execution/exec_export.c \
			

CFLAGS = -Wall -Wextra -Werror -w #-fsanitize=address 


all: $(NAME)

$(NAME): $(PARSING) $(EXECUTION) 
	cc $(CFLAGS) $(PARSING) $(EXECUTION) -lreadline -o $(NAME)

clean:

fclean: clean
	rm -rf $(NAME)

re: fclean all


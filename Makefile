NAME		:=	fdf

INC			:=	fdf.h 
INC_DIR		:=	includes/

HEADERS		:= $(addprefix $(INC_DIR), $(INC))

SRC_DIR		:=	sources/
SRC			:=	main.c draw.c read_file.c\
				

LIBFT_DIR	:=	libft/
LIBFT_A		:=	$(LIBFT_DIR)libft.a

OBJ_DIR		:=	build/
OBJ			:=	$(SRC:%.c=$(OBJ_DIR)%.o)

# Compiler options
CC			:=	cc
CC_FLAGS	:=	-Wextra -Werror -Wall
DEBUG_FLAG	:=	-ggdb3

# define standard colors
_END		:=	\x1b[0m
_BOLD		:=	\x1b[1m
_UNDER		:=	\x1b[4m
_REV		:=	\x1b[7m
_GREY		:=	\x1b[30m
_RED		:=	\x1b[31m
_GREEN		:=	\x1b[32m
_YELLOW		:=	\x1b[33m
_BLUE		:=	\x1b[34m
_PURPLE		:=	\x1b[35m
_CYAN		:=	\x1b[36m
_WHITE		:=	\x1b[37m

MLX_DIR	=	mlx/
MLX_A	=	$(MLX_DIR)libmlx.a
MLX_FLAG = -lm -framework OpenGL -framework AppKit

#########################
# 		RULES			#
#########################
all: build_libft $(NAME)

$(NAME): $(OBJ) $(LIBFT_A) $(MLX_A) 
	@$(CC) $(CC_FLAGS) $(OBJ) $(LIBFT_A) $(MLX_A) $(MLX_FLAG) -o $@ 
	@echo "> FdF Done!\n"
	
# Libft Makefile
build_libft:
	@$(MAKE) -C $(LIBFT_DIR)

# MinilibX makefile
$(MLX_A): $(MLX_DIR)
	@$(MAKE) -C $(MLX_DIR)
	@echo "> MLX Done!\n"

$(OBJ): $(OBJ_DIR)%.o: $(SRC_DIR)%.c $(LIBFT_DIR) $(HEADERS) 
	@mkdir -p $(@D)
	@echo "$(_GREEN)compiling: $<$(_END)"
	@$(CC) $(CC_FLAGS) -I$(INC_DIR) -I$(LIBFT_INC) -I$(MLX_DIR) -c $< -o $@

# clean commands
clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MLX_DIR)
	@rm -rf $(OBJ_DIR)

fclean: clean
	@echo "remove $(NAME)"
	@rm -rf $(NAME)
	@$(MAKE) fclean -C $(LIBFT_DIR)

re: fclean all

.PHONY: all clean fclean re build_libft
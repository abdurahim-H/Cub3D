# ============================================
# ||  🔦  BUILD SYSTEM v1.5 (Cub3D)         ||
# ============================================
# ||  Project: Cub3D                       ||
# ||  Program: cub3D                       ||
# ||  Author: Abdurahim Hudulov            ||
# ||  Date: 2025                           ||
# ============================================

# Colors
BLACK    = \033[1;30m
RED      = \033[1;31m
GREEN    = \033[1;32m
YELLOW   = \033[1;33m
BLUE     = \033[1;34m
MAGENTA  = \033[1;35m
CYAN     = \033[1;36m
WHITE    = \033[1;37m
NC       = \033[0m  # No Color

# Compiler, Removal Utility and Flags
CC       = cc
CFLAGS   = -Wall -Wextra -Werror
RM       = rm -f

# MiniLibX and Linux Libraries
# For Linux (using the MLX from mlx_linux):
MLXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lz
LDFLAGS  = $(MLXFLAGS) -lm

# Project Name
NAME     = cub3D

# Directories
SRC_DIR  = src
OBJ_DIR  = obj

# Source Files - all .c files in the src directory
SRCS     = $(wildcard $(SRC_DIR)/*.c)

# Object Files - stored in the obj directory with the same filename
OBJS     = $(patsubst $(SRC_DIR)/%.c, $(OBJ_DIR)/%.o, $(SRCS))

# Fancy Styling
SEP_LINE  = "$(BLUE)=========================================== $(NC)"
HEADER    = "$(CYAN)|| BUILD SYSTEM (Cub3D) ||$(NC)"
SUCCESS   = "$(GREEN)==> BUILD SUCCESSFUL$(NC)"
CLEAN_MSG = "$(GREEN)==> CLEANUP COMPLETE$(NC)"
FAIL_MSG  = "$(RED)==> BUILD FAILED$(NC)"

# Default Target: display banner then build the executable
all: banner $(NAME)

# Banner Display
banner:
	@echo $(SEP_LINE)
	@echo $(HEADER)
	@echo $(SEP_LINE)

# Linking Target Executable
$(NAME): $(OBJS)
	@echo "$(BLUE)[ Linking Objects... ]$(NC)"
	$(CC) $(OBJS) $(LDFLAGS) -o $@ && \
		echo $(SUCCESS) || echo $(FAIL_MSG)

# Compile Source Files
# This rule compiles each .c file from src/ into a corresponding .o file in obj/
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)[ Compiling: $< ]$(NC)"
	$(CC) $(CFLAGS) -Imlx_linux -O3 -c $< -o $@
	@echo "$(GREEN)[ Object Created: $@ ]$(NC)"

# Ensure the object directory exists
$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

# Clean: remove only object files (delete the obj directory)
clean:
	@echo "$(RED)[ Cleaning Object Files... ]$(NC)"
	$(RM) -r $(OBJ_DIR)
	@echo $(CLEAN_MSG)

# Full Clean: remove object files and the executable
fclean: clean
	@echo "$(RED)[ Removing Executable... ]$(NC)"
	$(RM) $(NAME)
	@echo $(CLEAN_MSG)

# Rebuild Everything
re: fclean all

# Bonus target: compiles with bonus features enabled.
# (This adds a -DBONUS flag so that your code may conditionally compile bonus code.)
bonus: CFLAGS += -DBONUS
bonus: re

# Help: displays usage and target info
help:
	@echo $(SEP_LINE)
	@echo "$(CYAN)Build System Help:$(NC)"
	@echo $(SEP_LINE)
	@echo "  $(GREEN)make$(NC)         - Build the project."
	@echo "  $(GREEN)make bonus$(NC)   - Build with bonus features enabled."
	@echo "  $(GREEN)make clean$(NC)   - Remove object files."
	@echo "  $(GREEN)make fclean$(NC)  - Remove object files and executable."
	@echo "  $(GREEN)make re$(NC)      - Rebuild the project."
	@echo "  $(GREEN)make help$(NC)    - Display this help."
	@echo ""
	@echo "Usage:"
	@echo "  ./cub3D <mapfile.cub> [--save]"
	@echo $(SEP_LINE)

# Declare Phony Targets
.PHONY: all clean fclean re bonus help banner

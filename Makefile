# ============================================
# ||  \U0001F526 BUILD SYSTEM v1.6 (Cub3D) ||
# ============================================
# ||  Project: Cub3D                       ||
# ||  Program: cub3D                       ||
# ||  Author: Abdurahim Hudulov            ||
# ||  Date: 2025                           ||
# ============================================

# Colors for Styling
BLACK    = \033[1;30m
RED      = \033[1;31m
GREEN    = \033[1;32m
YELLOW   = \033[1;33m
BLUE     = \033[1;34m
MAGENTA  = \033[1;35m
CYAN     = \033[1;36m
WHITE    = \033[1;37m
NC       = \033[0m  # No Color

# Compiler, Removal Utility, and Flags
CC       = cc
CFLAGS   = -O3 -Iincludes -Imlx_linux  # Added -Imlx_linux
RM       = rm -f

# MiniLibX and Linux Libraries
MLXFLAGS = -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lz
LDFLAGS  = $(MLXFLAGS) -lm

# Project Name
NAME     = cub3D

# Directories
SRC_DIR  = src
OBJ_DIR  = obj
INC_DIR  = includes

# Future-Proofing: Additional Directories (Empty Now, Can be Extended)
TEXTURES_DIR = textures
SOURCES_DIR  = sources
MAPS_DIR     = maps

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
$(NAME): mlx_linux/.configured $(OBJS)
	@echo "$(BLUE)[ Linking Objects... ]$(NC)"
	$(CC) $(OBJS) $(LDFLAGS) -o $@ && \
		echo $(SUCCESS) || echo $(FAIL_MSG)

# Check and configure mlx_linux only if needed (stamp file-based)
mlx_linux/.configured:
	@echo "$(BLUE)[ Running mlx_linux ./configure... ]$(NC)"
	@cd mlx_linux && ./configure && touch .configured

# Compile Source Files
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c | $(OBJ_DIR)
	@echo "$(YELLOW)[ Compiling: $< ]$(NC)"
	$(CC) $(CFLAGS) -c $< -o $@
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

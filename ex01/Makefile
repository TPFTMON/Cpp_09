NAME		= 

SRCS		=

OBJ_DIR		= obj

CPP			= c++
CMPFLAGS	= -Wall -Wextra -Werror -std=c++98
CPPFLAGS	= -MMD -MP         # Flags to be able to create dependencies

OBJS		= $(SRCS:%.cpp=$(OBJ_DIR)/%.o)
DEPS		= $(OBJS:.o=.d)

# --- Rules ---
all: $(NAME)

$(NAME): $(OBJS)
	$(CPP) $(CMPFLAGS) $(OBJS) -o $(NAME)

$(OBJ_DIR)/%.o: %.cpp
	@mkdir -p ${OBJ_DIR}
	$(CPP) $(CMPFLAGS) $(CPPFLAGS) -c $< -o $@

# Includes dependencies (if they exist)
# This handles the re-compilation if a header file changes
-include $(DEPS)

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re #debug

NAME	= exec

CC		= clang++
RM		= rm -rf

SRCS_PATH	= ./
OBJS_PATH	= objs/
INC			= -I./utils -I./
SRCS		= $(notdir $(shell find $(SRCS_PATH) -type f -name *.cpp))
OBJS		= $(addprefix $(OBJS_PATH),$(SRCS:.cpp=.o))

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp
	@ mkdir -p $(OBJS_PATH)
	$(CC) $(INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(INC) -o $(NAME)

clean: 
	$(RM) $(OBJS) $(OBJS_PATH)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re
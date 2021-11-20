NAME	= exec

RM		= rm -rf

CCFLAGS = 

UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Linux)
	CCFLAGS += g++ -g -D TESTED_NAMESPACE=ft
endif
ifeq ($(UNAME_S),Darwin)
	CCFLAGS += clang++ -fsanitize=address -g -D TESTED_NAMESPACE=ft
endif

SRCS_PATH	= ./
OBJS_PATH	= objs/
INC			= -I./utils -I./
SRCS		= $(notdir $(shell find $(SRCS_PATH) -type f -name *.cpp))
OBJS		= $(addprefix $(OBJS_PATH),$(SRCS:.cpp=.o))

$(OBJS_PATH)%.o: $(SRCS_PATH)%.cpp
	@ mkdir -p $(OBJS_PATH)
	$(CCFLAGS) $(INC) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	$(CCFLAGS) $(OBJS) $(INC) -o $(NAME)

clean: 
	$(RM) $(OBJS) $(OBJS_PATH)

fclean: clean
	$(RM) $(NAME)

re: clean all

.PHONY: all clean fclean re
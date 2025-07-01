# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tjooris <tjooris@student.42lyon.fr>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/01/20 14:10:16 by tjooris           #+#    #+#              #
#    Updated: 2025/06/27 12:44:52 by tjooris          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = philo

#=-=-=-=-=-=-FILES-=-=-=-=-=-=#

MAKE_DIR    :=  .make/
BUILD_DIR   :=  $(MAKE_DIR)build_$(or $(shell git branch --show-current),default)/
BASE_DIR    :=  normal/

SRC_DIR     =   src/

OBJS        =   $(patsubst %.c, $(BUILD_DIR)%.o, $(SRC))
DEPS        =   $(patsubst %.c, $(BUILD_DIR)%.d, $(SRC))

OBJS_BONUS        =   $(patsubst %.c, $(BUILD_DIR)%.o, $(SRC_BONUS))
DEPS_BONUS        =   $(patsubst %.c, $(BUILD_DIR)%.d, $(SRC_BONUS))

#=-=-=-=-=-=-ROOT-=-=-=-=-=#

SRC =   ft_philosophers.c \
		clear.c \
		init.c \
		utils.c \
		utils_2.c \

#=-=-=-=-=-=-ACTION-=-=-=-=-=#

SRC +=  $(addprefix $(ACTION_DIR), $(ACTION_SRC))

ACTION_DIR    =   action/
ACTION_SRC    =   is_eating.c \
				  is_thinking.c \
				  is_sleeping.c \

#=-=-=-=-=-=-DYING-=-=-=-=-=#

SRC +=  $(addprefix $(DYING_DIR), $(DYING_SRC))

DYING_DIR    =   dying/
DYING_SRC    =   is_dead.c \

#=-=-=-=-=-=-FORK-=-=-=-=-=#

SRC +=  $(addprefix $(FORK_DIR), $(FORK_SRC))

FORK_DIR    =   fork/
FORK_SRC    =   fork.c \

#=-=-=-=-=-=-PARSING-=-=-=-=-=#

SRC +=  $(addprefix $(PARSING_DIR), $(PARSING_SRC))

PARSING_DIR    =   parsing/
PARSING_SRC    =   pars.c \

#=-=-=-=-=-=-INCLUDES-=-=-=-=-=#

LIB_DIR     =   lib/
LIB_PATH    =   

LIB_PATH    :=  $(addprefix $(LIB_DIR),$(LIB_PATH))
LIB         =   $(patsubst lib%.a, %, $(notdir $(LIB_PATH)))

#SYS_LIB     =   -lmlx -lX11 -lXext -lm

INC_DIR     =   include/
INCLUDES    =   $(INC_DIR) \
                $(dir $(LIB_PATH))$(INC_DIR)

#=-=-=-=-=-=-COMPIL-=-=-=-=-=#

CC          =   cc

FLAGS       +=  -Wall -Wextra -Werror -Ofast
PPFLAGS     +=  $(addprefix -I, $(INCLUDES)) -MMD -MP

LDFLAGS     +=  $(addprefix -L, $(dir $(LIB_PATH)))
LDLIB       +=  $(addprefix -l, $(LIB))

AR          =   ar
ARFLAGS     =   -rcs

MAKEFLAG    +=  --no-print-directory

#=-=-=-=-=-=-MODES-=-=-=-=-=#

MODES       :=  debug fsanitize optimize full-optimize

MODES_TRACE :=  $(BUILD_DIR).modes_trace
LAST_MOD    :=  $(shell cat $(MODES_TRACE) 2>/dev/null)

MODE    ?=

ifneq ($(MODE), )
    BUILD_DIR := $(BUILD_DIR)$(MODE)/
else
    BUILD_DIR := $(BUILD_DIR)$(BASE_BUILD_DIR)
endif

ifeq ($(MODE), debug)
    FLAGS = -g3
else ifeq ($(MODE), fsanitize)
    FLAGS = -g3 -fsanitize=address
else ifeq ($(MODE), optimize)
    FLAGS += -O2
else ifeq ($(MODE), full-optimize)
    FLAGS += -O3
else ifneq ($(MODE),)
    ERROR = MODE
endif


ifneq ($(LAST_MOD), $(MODE))
$(NAME): force
endif

#=-=-=-=-=-=-CAST-=-=-=-=-=#

.PHONY: all clean fclean $(MODE) re help bonus print-% force

all: $(NAME)

$(NAME): $(OBJS) $(LIB_PATH)
	@echo $(MODE) > $(MODES_TRACE)
	$(CC) $(FLAGS) $(OBJS) $(LDFLAGS) $(LDLIB) $(SYS_LIB) -o $(NAME)

$(BUILD_DIR)%.o: $(SRC_DIR)%.c $(LIB_PATH)
	@mkdir -p $(@D)
	$(CC) $(PPFLAGS) $(FLAGS) -c $< -o $@

$(LIB_PATH): force
	@$(MAKE) -C $(@D)

clean:
	-for lib in $(dir $(LIB_PATH)); do $(MAKE) -s -C $$lib $@; done
	rm -rf $(MAKE_DIR)

fclean:
	-for lib in $(dir $(LIB_PATH)); do $(MAKE) -s -C $$lib $@; done
	rm -rf $(MAKE_DIR) $(NAME) $(NAME_BONUS)

re: fclean
	$(MAKE)

help:
	@echo "Usage: make [target]"
	@echo "Targets:"
	@echo "  all       Build the project"
	@echo "  clean     Remove object files and dependencies"
	@echo "  fclean    Remove all build files, binary, and mode trace"
	@echo "  re        Clean and rebuild"

print-%:
	@echo $(patsubst print-%,%,$@)=
	@echo $($(patsubst print-%,%,$@))

force:

-include $(DEPS)

.DEFAULT_GOAL := all
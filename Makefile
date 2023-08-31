NAME		= ftContainer
NAME_STD	= stdContainer

CC		= c++
CFLAGS		= -Wall -Wextra -Werror -std=c++98 -g

INCLUDE_DIR	= include
HEADER_EXT	= hpp
HEADER		= $(shell find $(INCLUDE_DIR) -type f -name "*.$(HEADER_EXT)")
HEADER_COUNT	= $(shell find $(INCLUDE_DIR) -type f -name "*.$(HEADER_EXT)" | wc -l)

SRC_EXT		= cpp

FT_SRC_DIR	= ft_src
FTSRCS		= $(shell find $(FT_SRC_DIR) -type f -name "*.$(SRC_EXT)")
FTSRCS_COUNT	= $(shell find $(FT_SRC_DIR) -type f -name "*.$(SRC_EXT)" | wc -l)

FT_OBJ_DIR	= ft_obj
FT_OBJ_SUBDIR	= $(shell find $(FT_SRC_DIR) -type d | grep '/' | sed 's/$(FT_SRC_DIR)/$(FT_OBJ_DIR)/g')
FTOBJS		= $(subst $(FT_SRC_DIR),$(FT_OBJ_DIR),$(FTSRCS:.$(SRC_EXT)=.o))

STD_SRC_DIR	= std_src
STDSRCS		= $(shell find $(STD_SRC_DIR) -type f -name "*.$(SRC_EXT)")
STDSRCS_COUNT	= $(shell find $(STD_SRC_DIR) -type f -name "*.$(SRC_EXT)" | wc -l)

STD_OBJ_DIR	= std_obj
STD_OBJ_SUBDIR	= $(shell find $(STD_SRC_DIR) -type d | grep '/' | sed 's/$(STD_SRC_DIR)/$(STD_OBJ_DIR)/g')
STDOBJS		= $(subst $(STD_SRC_DIR),$(STD_OBJ_DIR),$(STDSRCS:.$(SRC_EXT)=.o))

RM		= rm -rf

all			: $(NAME)

ifeq ($(HEADER_COUNT), 8)
ifeq ($(FTSRCS_COUNT), 5)
$(NAME)			: $(FT_OBJ_DIR) $(FT_OBJ_SUBDIR) $(FTOBJS) $(NAME_STD)
			${CC} $(CFLAGS) ${FTOBJS} -o ${NAME}
else
$(NAME)			:
			@echo "Srcs corrupted, abording "
endif
else
$(NAME)			:
			@echo "Srcs corrupted, aborting"
endif

ifeq ($(STDSRCS_COUNT), 5)
$(NAME_STD)		: $(STD_OBJ_DIR) $(STD_OBJ_SUBDIR) $(STDOBJS)
			${CC} $(CFLAGS) ${STDOBJS} -o ${NAME_STD}
else
$(NAME_STD)		:
			@echo "Srcs corrupted, abording "
endif

$(FT_OBJ_DIR)		:
			@mkdir $(FT_OBJ_DIR)

$(FT_OBJ_SUBDIR)	:
			@mkdir $(FT_OBJ_SUBDIR)

$(FT_OBJ_DIR)/%.o	: $(FT_SRC_DIR)/%.$(SRC_EXT) $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $(<:.$(SRC_EXT)=.o)
			@mv $(FT_SRC_DIR)/*/*.o $@

$(STD_OBJ_DIR)		:
			@mkdir $(STD_OBJ_DIR)

$(STD_OBJ_SUBDIR)	:
			@mkdir $(STD_OBJ_SUBDIR)

$(STD_OBJ_DIR)/%.o	: $(STD_SRC_DIR)/%.$(SRC_EXT) $(HEADER)
			$(CC) $(CFLAGS) -c $< -o $(<:.$(SRC_EXT)=.o)
			@mv $(STD_SRC_DIR)/*/*.o $@

clean			:
			$(RM) $(FT_OBJ_DIR) $(STD_OBJ_DIR)

fclean			: clean
			$(RM) $(NAME) $(NAME_STD)

re			: fclean all

.PHONY			: all bonus clean fclean re

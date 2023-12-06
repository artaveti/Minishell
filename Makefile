NAME 			= minishell
HEADERS_DIR		= headers
SOURCES_DIR 	= sources
OBJECTS_DIR		= objects
HEADER_FILES	= $(wildcard $(HEADERS_DIR)/*.h)
SOURCE_FILES	= $(wildcard $(SOURCES_DIR)/*.c)
OBJECT_FILES	= $(patsubst $(SOURCES_DIR)/%.c, $(OBJECTS_DIR)/%.o, $(SOURCE_FILES))
RD_FOLDER_NAME	= for_readline_1
PREFIX 			= $(shell pwd)/$(RD_FOLDER_NAME)
#PREFIX 		= $(shell find ${HOME} -name ${RD_FOLDER_NAME} 2>/dev/null)

CC 		= cc
CFLAGS 	= -Wall -Wextra -Werror -g -fsanitize=address
INC 	= -I 
RDLN	= -lreadline
AR 		= ar rcs
RM 		= rm -rf
MK 		= mkdir -p

all: $(OBJECTS_DIR) $(NAME) #petke avelacnel "readline" bary "all:"-ic heto

$(OBJECTS_DIR): $(HEADERS_DIR) $(SOURCES_DIR)
	$(MK) $(OBJECTS_DIR)

$(OBJECTS_DIR)/%.o: $(SOURCES_DIR)/%.c $(HEADER_FILES)
	$(CC) $(CFLAGS) -I./$(RD_FOLDER_NAME)/include $(INC) $(HEADERS_DIR) -c $< -o $@

$(NAME): $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(RDLN) -L./$(RD_FOLDER_NAME)/lib -I./$(RD_FOLDER_NAME)/include $(OBJECT_FILES) -o $(NAME)

clean:
	$(RM) $(OBJECTS_DIR)

fclean: clean
	$(RM) $(NAME)

readline:
	cd readline-master && ./configure --prefix=$(PREFIX) && make && make install

re: fclean all

.PHONY: all clean fclean re

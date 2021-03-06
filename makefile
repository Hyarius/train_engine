NAME=		ts_engine

##
##		RESSOURCES
##

##List every folder where he will find header
INC_DIR = 	$(shell find includes -type d) $(shell find jgl/includes -type d)
##List every folder where he will find source file
SRC_DIR = 	$(shell find srcs -type d)
##List every folder where he will find lib file
LIB_DIR = 	$(shell find ~/.brew/lib -type d) jgl
##Folder where he will store the .o
OBJ_DIR	=	obj

##Add to the vpath the folder find in SRC_DIR
vpath %.cpp $(foreach dir, $(SRC_DIR), $(dir):)

##Set the download program to brew
DWL =		brew

##List every .c found inside SRC_DIR
SRC = 		$(foreach dir, $(SRC_DIR), $(foreach file, $(wildcard $(dir)/*.cpp), $(notdir $(file))))

##Transform and place every .o from SRC
OBJ=		$(addprefix $(OBJ_DIR)/, $(SRC:%.cpp=%.o))

##List of libraries to download and install using the function defined in DWL
LIB_DWN =	sdl2 sdl2_image sdl2_mixer sdl2_ttf
##List of libraries to link while compiling
LIB =		SDL2 SDL2_image SDL2_mixer SDL2_ttf jgl

##
##		COMPILER FLAGS
##

##Basics flags
CFLAGS=		-std=c++11

##Create the flags to includes every .h needed by this program
IFLAGS =	$(foreach dir, $(INC_DIR), -I$(dir)) $(foreach dir, $(shell find ~/.brew/include -type d), -I$(dir))

##Create the flags to link every libraries needed by this program (-L and -l)
LFLAGS = 	$(foreach dir, $(LIB_DIR), -L $(dir) ) $(foreach lib, $(LIB), -l$(lib)) -framework OpenGL

##Define the compiler to use
CC=			g++

all:
				make $(NAME)

install:
				make install -C jgl

re-jgl:
				make re -C jgl

jgl:
				make -C jgl

$(NAME):		$(OBJ) jgl/libjgl.a
				@echo "Compiling $(NAME) ...\c"
				@$(CC) $(CFLAGS) $(IFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)
				@echo " DONE"

$(OBJ_DIR)/%.o : %.cpp
				@mkdir $(OBJ_DIR) 2> /dev/null || true
				@echo "Compiling $< ...\c"
				@$(CC) $(CFLAGS) $(IFLAGS) -o $@ -c $<
				@echo " DONE"

clean:
				@rm -rf $(OBJ_DIR)
				@echo "clean"

fclean:			clean
				@rm -f $(NAME)
				@echo "fclean"

re:				fclean all

.PHONY: all clean fclean re jgl

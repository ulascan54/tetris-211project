SFML_FLAGS_LINUX=-L "./lib/linux" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -lGL -lGLU -lX11 -lXrandr -lXinerama -lXi -lXcursor -ldl -lXext -lXrender -lXfixes -lX11-xcb -lxcb-glx -lxcb-dri2 -lXxf86vm -lXau -lXdmcp -lpthread -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio -lsfml-network -lGL -lGLU -lX11 -lXrandr -lXinerama -lXi -lXcursor -ldl -lXext -lXrender -lXfixes -lX11-xcb -lxcb-glx -lxcb-dri2 -lXxf86vm -lXau -lXdmcp -lpthread
SFML_FLAGS_MAC=-L "./lib/mac" -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio
SFML_FLAGS_WINDOWS=-L"./lib/windows" -lsfml-main -lsfml-audio-s -lflac -lvorbisenc -lvorbisfile -lvorbis -logg -lsfml-network-s -lws2_32 -lsfml-graphics-s -lfreetype -lsfml-window-s -lopengl32 -lgdi32 -lsfml-system-s -lwinmm -lgdi32 -luser32 -lkernel32 -lcomctl32 -lmingw32 -luser32 -lgdi32 -ldxguid -mwindows -lopenal32
VERSION=g++ -std=c++17
PATH_LIB_LINUX=./lib/linux/
PATH_LIB_MAC=./lib/mac/
PATH_LIB_WINDOWS=./lib/windows/
PATH_INCLUDE="./include"
PATH_SRC=./src/
DEBUG=-g
OPT=-O0
WARN=-Wall


l: compile-l link-l run-l

compile-l:

	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)GetColorTheme.cpp -o $(PATH_LIB_LINUX)GetColorTheme.o 
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Game.cpp -o $(PATH_LIB_LINUX)Game.o 
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)highscores.cpp -o $(PATH_LIB_LINUX)highscores.o 
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Logic.cpp -o $(PATH_LIB_LINUX)Logic.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)MainMenu.cpp -o $(PATH_LIB_LINUX)MainMenu.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Piece.cpp -o $(PATH_LIB_LINUX)Piece.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Board.cpp -o $(PATH_LIB_LINUX)Board.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)CustomShapeEditor.cpp -o $(PATH_LIB_LINUX)CustomShapeEditor.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Portal.cpp -o $(PATH_LIB_LINUX)Portal.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Position.cpp -o $(PATH_LIB_LINUX)Position.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)pieceColors.cpp -o $(PATH_LIB_LINUX)pieceColors.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)app-main.cpp -o $(PATH_LIB_LINUX)app-main.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Vector.cpp -o $(PATH_LIB_LINUX)Vector.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)LinkedList.cpp -o $(PATH_LIB_LINUX)LinkedList.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Node.cpp -o $(PATH_LIB_LINUX)Node.o

link-l:
	$(VERSION) $(PATH_LIB_LINUX)Portal.o $(PATH_LIB_LINUX)pieceColors.o $(PATH_LIB_LINUX)CustomShapeEditor.o $(PATH_LIB_LINUX)Board.o $(PATH_LIB_LINUX)Position.o $(PATH_LIB_LINUX)Piece.o $ $(PATH_LIB_LINUX)MainMenu.o $(PATH_LIB_LINUX)Game.o $(PATH_LIB_LINUX)GetColorTheme.o $(PATH_LIB_LINUX)highscores.o $(PATH_LIB_LINUX)Logic.o $(PATH_LIB_LINUX)Vector.o $(PATH_LIB_LINUX)LinkedList.o $(PATH_LIB_LINUX)Node.o $(PATH_LIB_LINUX)app-main.o -o ./bin/app-l $(DEBUG) $(OPT) $(WARN) $(SFML_FLAGS_LINUX) 

run-l:
	./bin/app-l



m: compile-m link-m run-m

compile-m:

	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)GetColorTheme.cpp -o $(PATH_LIB_MAC)GetColorTheme.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Game.cpp -o $(PATH_LIB_MAC)Game.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)highscores.cpp -o $(PATH_LIB_MAC)highscores.o 
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Logic.cpp -o $(PATH_LIB_MAC)Logic.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)MainMenu.cpp -o $(PATH_LIB_MAC)MainMenu.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Piece.cpp -o $(PATH_LIB_MAC)Piece.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Board.cpp -o $(PATH_LIB_MAC)Board.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)CustomShapeEditor.cpp -o $(PATH_LIB_MAC)CustomShapeEditor.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Portal.cpp -o $(PATH_LIB_MAC)Portal.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Position.cpp -o $(PATH_LIB_MAC)Position.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)pieceColors.cpp -o $(PATH_LIB_MAC)pieceColors.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)app-main.cpp -o $(PATH_LIB_MAC)app-main.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Vector.cpp -o $(PATH_LIB_MAC)Vector.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)LinkedList.cpp -o $(PATH_LIB_MAC)LinkedList.o
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Node.cpp -o $(PATH_LIB_MAC)Node.o

link-m:
	$(VERSION) $(PATH_LIB_MAC)Portal.o $(PATH_LIB_MAC)pieceColors.o $(PATH_LIB_MAC)CustomShapeEditor.o $(PATH_LIB_MAC)Board.o $(PATH_LIB_MAC)Position.o $(PATH_LIB_MAC)Piece.o $ $(PATH_LIB_MAC)MainMenu.o $(PATH_LIB_MAC)Game.o $(PATH_LIB_MAC)GetColorTheme.o $(PATH_LIB_MAC)highscores.o $(PATH_LIB_MAC)Logic.o $(PATH_LIB_MAC)Vector.o $(PATH_LIB_MAC)LinkedList.o $(PATH_LIB_MAC)Node.o $(PATH_LIB_MAC)app-main.o -o ./bin/app-m $(DEBUG) $(OPT) $(WARN) $(SFML_FLAGS_MAC) 

run-m:
	./bin/app-m



w: compile-w link-w run-w

compile-w:

	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)GetColorTheme.cpp -o $(PATH_LIB_WINDOWS)GetColorTheme.o -DSFML_STATIC
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Game.cpp -o $(PATH_LIB_WINDOWS)Game.o -DSFML_STATIC  
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)highscores.cpp -o $(PATH_LIB_WINDOWS)highscores.o  -DSFML_STATIC  
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Logic.cpp -o $(PATH_LIB_WINDOWS)Logic.o -DSFML_STATIC 
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)MainMenu.cpp -o $(PATH_LIB_WINDOWS)MainMenu.o -DSFML_STATIC 
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Piece.cpp -o $(PATH_LIB_WINDOWS)Piece.o -DSFML_STATIC 
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Board.cpp -o $(PATH_LIB_WINDOWS)Board.o -DSFML_STATIC 
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)CustomShapeEditor.cpp -o $(PATH_LIB_WINDOWS)CustomShapeEditor.o -DSFML_STATIC 
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Portal.cpp -o $(PATH_LIB_WINDOWS)Portal.o -DSFML_STATIC 
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Position.cpp -o $(PATH_LIB_WINDOWS)Position.o -DSFML_STATIC 
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)pieceColors.cpp -o $(PATH_LIB_WINDOWS)pieceColors.o -DSFML_STATIC 
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)app-main.cpp -o $(PATH_LIB_WINDOWS)app-main.o -DSFML_STATIC 
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Vector.cpp -o $(PATH_LIB_WINDOWS)Vector.o -DSFML_STATIC 
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)LinkedList.cpp -o $(PATH_LIB_WINDOWS)LinkedList.o -DSFML_STATIC
	$(VERSION) -c -I $(PATH_INCLUDE) $(PATH_SRC)Node.cpp -o $(PATH_LIB_WINDOWS)Node.o -DSFML_STATIC
link-w:
	$(VERSION) $(PATH_LIB_WINDOWS)Portal.o $(PATH_LIB_WINDOWS)pieceColors.o $(PATH_LIB_WINDOWS)CustomShapeEditor.o $(PATH_LIB_WINDOWS)Board.o $(PATH_LIB_WINDOWS)Position.o $(PATH_LIB_WINDOWS)Piece.o $(PATH_LIB_WINDOWS)MainMenu.o $(PATH_LIB_WINDOWS)Game.o $(PATH_LIB_WINDOWS)GetColorTheme.o $(PATH_LIB_WINDOWS)highscores.o $(PATH_LIB_WINDOWS)Logic.o $(PATH_LIB_WINDOWS)Vector.o $(PATH_LIB_WINDOWS)LinkedList.o $(PATH_LIB_WINDOWS)Node.o $(PATH_LIB_WINDOWS)app-main.o -o ./bin/app-w.exe $(DEBUG) $(OPT) $(WARN) $(SFML_FLAGS_WINDOWS) 

run-w:
	./bin/app-w.exe


clear:
	rm -f $(PATH_LIB_LINUX)*.o
	rm -f $(PATH_LIB_MAC)*.o
	rm -f $(PATH_LIB_WINDOWS)*.o
	rm -f ./bin/app-l
	rm -f ./bin/app-m
	rm -f ./bin/app-w.exe
	del lib\*.o
	del bin\app-w.exe

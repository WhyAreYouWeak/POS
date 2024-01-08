CLIENT_INC=-Iclient/raylib/src
CLIENT_SRC=client/main.cpp \
		   client/PongGame.cpp \
		   client/Paddle.cpp \
		   client/Ball.cpp \
		   client/Objects.cpp\
		   client/SocketReceive.cpp\
		   client/my_socket.cpp
CLIENT_LIBS=-lstdc++ -lws2_32 -lraylib -lGdi32 -lWinmm -LBuild/Client 
CLIENT_OBJS=$(patsubst client/%.cpp,Build/Client/%.o,$(CLIENT_SRC))

Build/Client/%.o: client/%.cpp
ifeq ($(OS), Windows_NT)
	-@mkdir .\Build\Client
	gcc -std=c++23 $(CLIENT_INC) -c $< -o $@ $(CLIENT_LIBS)
endif
	

Client: $(CLIENT_OBJS)
ifeq ($(OS), Windows_NT)
	-@mkdir .\Build\Client
	gcc -std=c++23 $(CLIENT_INC) $^ -o ./Build/Client/$@ $(CLIENT_LIBS)
endif

  
SERVER_SRC=server/main.cpp \
		   server/PongGame.cpp \
		   server/Ball.cpp\
		   server/Paddle.cpp\
		   server/active_socket.c\
		   server/char_buffer.c\
		   server/Objects.cpp\
		   server/passive_socket.c
SERVER_LIBS=
SERVER_OBJS=$(patsubst server/%.cpp,Build/Server/%.o,$(SERVER_SRC))

Build/Server/%.o: server%.cpp
	-@mkdir -p ./Build/Server
	gcc -std=c++23 -c $< -o $@ $(SERVER_LIBS)


Server: $(SERVER_OBJS)
	-@mkdir -p ./Build/Server
	gcc -std=c++23 $^ -o ./Build/Server/$@ $(SERVER_LIBS)


Clean:
ifeq ($(OS), Windows_NT)
	-@del /q .\Build\Client
	-@del /q .\Build\Server
else
	-@rm -rf ./Build/Client
	-@rm -rf ./Build/Server
endif

All: Client Server
build:
	g++ -Wall -fdiagnostics-color=always ./src/*.cpp ./lib/rlImGui-main/objects/*.o -o main.exe -lraylib

distribute:
	g++ -Wall -fdiagnostics-color=always -O0 -flto -fdata-sections -ffunction-sections ./src/*.cpp ./lib/rlImGui-main/objects/*.o -o Sorting_Visual.exe -lraylib -lglfw3 -luser32 -lgdi32 -lwinmm -lwinpthread -static -static-libgcc -static-libstdc++ -s -Wl,--gc-sections

run:
	./Sorting_Visual.exe

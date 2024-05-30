if [[ ! -e .out ]]; then
    mkdir .out
fi

g++ -c main.cpp -o .out/main.o
g++ -c FlyEye.cpp -o .out/FlyEye.o
g++ -c Process.cpp -o .out/Process.o
g++ .out/main.o .out/FlyEye.o .out/Process.o -o .out/sfml-app -lsfml-graphics -lsfml-window -lsfml-system
.out/sfml-app
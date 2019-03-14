aco: obj/main.o obj/antsystem.o obj/problem.o obj/utils.o
	g++ -o aco obj/main.o obj/antsystem.o obj/problem.o obj/utils.o

obj/main.o: src/main.cpp 
	g++ -c src/main.cpp -o obj/main.o -I include

obj/antsystem.o: src/antsystem.cpp include/antsystem.h
	g++ -c src/antsystem.cpp -o obj/antsystem.o -I include

obj/problem.o: src/problem.cpp include/problem.h
	g++ -c src/problem.cpp -o obj/problem.o -I include

obj/utils.o: src/utils.cpp include/utils.h
	g++ -c src/utils.cpp -o obj/utils.o -I include

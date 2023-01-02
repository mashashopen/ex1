both: server.out client.out

server.out: server.o ReadDataSet.o Distance.o Knn.o ParseAndValidate.o
	g++ -std=c++11 main.o ReadDataSet.o Distance.o Knn.o server.o -o a.out
server.o: server.cpp ReadDataSet.h Knn.h Distance.h ParseAndValidate.h
	g++ -std=c++11 -c main.cpp
ReadDataSet.o: ReadDataSet.cpp ReadDataSet.h
	g++ -std=c++11 -c ReadDataSet.cpp
Distance.o: Distance.cpp Distance.h
	g++ -std=c++11 -c Distance.cpp
Knn.o: Knn.cpp Knn.h Distance.h
	g++ -std=c++11 -c Knn.cpp
ParseAndValidate.o: ParseAndValidate.cpp Distance.h
	g++ -std=c++11 -c server.cpp
clean:
	rm *.o output


client.out: client.o ReadDataSet.o Distance.o Knn.o ParseAndValidate.o
	g++ -std=c++11 -ggdb -Iinclude main.o ReadDataSet.o Distance.o Knn.o server.o -o a.out
client.o: client.cpp Distance.h ParseAndValidate.h
	g++ -std=c++11 -ggdb -Iinclude -c main.cpp
Distance.o: Distance.cpp Distance.h
	g++ -std=c++11 -ggdb -Iinclude -c Distance.cpp
ParseAndValidate.o: ParseAndValidate.cpp Distance.h
	g++ -std=c++11 -ggdb -Iinclude -c server.cpp
clean:
	rm *.o output

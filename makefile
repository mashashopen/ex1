both: server.out client.out

server.out: server.o ReadDataSet.o Distance.o Knn.o ParseAndValidate.o
	g++ -std=c++11 server.o ReadDataSet.o Distance.o Knn.o ParseAndValidate.o -o server.out
client.out: client.o Distance.o ParseAndValidate.o
	g++ -std=c++11 client.o Distance.o ParseAndValidate.o -o client.out
client.o: client.cpp Distance.h ParseAndValidate.h
	g++ -std=c++11 -c client.cpp
server.o: server.cpp ReadDataSet.h Distance.h Knn.h ParseAndValidate.h
	g++ -std=c++11 -c server.cpp
ReadDataSet.o: ReadDataSet.cpp ReadDataSet.h
	g++ -std=c++11 -c ReadDataSet.cpp
Distance.o: Distance.cpp Distance.h
	g++ -std=c++11 -c Distance.cpp
Knn.o: Knn.cpp Knn.h Distance.h
	g++ -std=c++11 -c Knn.cpp
ParseAndValidate.o: ParseAndValidate.cpp Distance.h
	g++ -std=c++11 -c ParseAndValidate.cpp
clean:
	rm *.o output

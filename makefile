
a.out: main.o ReadDataSet.o Distance.o Knn.o
	g++ -std=c++11 main.o ReadDataSet.o Distance.o Knn.o -o a.out
main.o: main.cpp ReadDataSet.h Knn.h
	g++ -std=c++11 -c main.cpp
ReadDataSet.o: ReadDataSet.cpp ReadDataSet.h
	g++ -std=c++11 -c ReadDataSet.cpp
Distance.o: Distance.cpp Distance.h
	g++ -std=c++11 -c Distance.cpp
Knn.o: Knn.cpp Knn.h Distance.h
	g++ -std=c++11 -c Knn.cpp
clean:
	rm *.o output
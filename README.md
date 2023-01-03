"# ex3" 

=============================== Short Description Of The Project =============================== 

this project is built from two programs, server and client sides. the client gets a vector, distance metric type and a number (=k) and sends it t the server. the server calculates the label of this vector with the desired distance metric and number k, using the KNN algorithm. 

the server program gets 2 argument from command line, so that:
first argument is a path of  file of vectors with their labels, meaning classified vectors.
second argument is a port number, in which the server will listen to potential clients.

the client program gets 2 argument from command line, so that:
first argument is an ip address of the server the client should connect to.
second argument is a port number, in which the client will connect to the server.

if the connection is nut successful, the program will exit.

after the connection between server and client has been done, the client waits for input from the user.
the input should be as following:
vector distance_metric k

types of possible distance metrics are:
- euclidean
- manhattan
- chebyshev
- canberra
- minkowski

the input of the user may be not valid (due to user misuse). not valid input, means it is one of the following:
- vector contains chars
- vector's size is not as the vectors in the given file with which the server is working
- distance metric is not one of the list: MAN, AUC, CHB, CAN, MIN
- k number, is not a positive whole number.

if the input is not valid, the server will send to the client "invalid input" and will wait for the next input, infinitly.
if the user will enter "-1" as input, the client will close the connection with the server and the server will wait for the next client.

in order to simplify the parsing and validating the input from the user, we created a class named ParseAndValidate from which we can get all the parameters seperatly after they were validated, and use safely the KNN algorithm that we implemented. 

note that if a distance between two vectors can't be calculated (because they are with different sizes), we set the distance to be -1 which is of course not a valid distance. that is how KNN knows if two vectors are with same size or not.


=============================== Running Example ===============================

example 1:
- valid input (according iris dataset):
* 1 2 3 4 MAN 3 

output: 
* Iris-versicolor


example 2:
- invalid input (according iris dataset):
* 1 2 3 MIN 3

output: 
* invalid input
 (reason: the vector input is not in the same size of vectors from iris dataset, should be size=4)
 
 
 
 =============================== Cloning ===============================
 
First, we used the same repository from ex1 (part 1). The current assignment is on branch "ex3". Because the previous exercise wasn't checked yet, we didn't merge this branch to "main" branch. Therefore, in order to get the code of the current assignment, please clone the "ex3" branch ONLY, using this command:

  * git clone --branch "ex3" https://github.com/mashashopen/ex1.git


 =============================== Compiling Command ===============================

 * make 


 =============================== Running Command ===============================

 * ./server.out <file_path> <port_number>
 * ./client.out <ip_address> <port_number> 

note that the client program should run from a different computer or a different terminal (if working on one computer for both client and server programs)
 
 for example:
 ./server.out iris_classified.csv 1024
 ./client.out 127.0.0.1 1024

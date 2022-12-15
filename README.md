"# ex2" 

=============================== Short Description Of The Project =============================== 

first, the program get 3 arguments from command line, so that:
first argument is an integer number (k) that represent the number of neighbors for knn algorithm.
second argument is the path of the classified vectors file.
third argument is the compute distance metic to use in the knn algorithm. one of the followong:
- euclidean
- manhattan
- chebyshev
- canberra
- minkowski

areValidArguments function (in main) checks if command line arguments are valid.
if so, we set the arguments respectively.

then, we get a vector from user (in infinitely way). this vector will use for the knn algorithm. which
mean that we want to classsify this vector and get its label according to all vectors from the data
set and the k number that we get in command line.

when vector content added, getVectorAsInput function is generating a string type into a vector type.
in this function,we call inputValidation function that checks two cases:
case 1: if the string is empty, we exit the program cause distance of empty vector 
cannot be calculated.
case 2: if the input contains chars, we exit the program from the same reason. 

if the input is valid, getVectorAsInput function is generating the string into a vector type.
then ,the program is returning back to main where the data set is read (from file path) and generated
into a map so that the key is the vector (numbers) and the value is the label.

then, an Knn object is initialized with input vector ,k number, the distance metric and the mapped data 
mentioned before. 

in the knn algorithm we first calculate distance of all vectors (from mapped data) from the input vector.
and then find the k nearest neighbors to this vector. the next step is to find the predicted label of this
vector using the predict function.

back to the main, we call the predict function and print its result. 
the user can now give another vector to check its label, and so on.


=============================== Running Example ===============================

example 1:
- valid input (according iris dataset, k=3, manhattan distance):
* 6.9 3.1 4.9 1.5 

output: 
* Iris-versicolor


example 2:
- valid input (according wine dataset, k=7, minkowski distance):
* 3.4 7 6 3.1 2.9 4.1 4 7.8 9 6.5 1.1 1.2 3.4

output: 
* white wine


example 3:
- invalid input (according beans dataset, k=4, canberra distance):
* 1 6 7
  
 output: 
* invalid input!
 (reason: the vector input is not in the same size of vectors from beans dataset, should be size=16)
 
 
 
 =============================== Cloning ===============================
 
First, we used the same repository from ex1 (part 1). The current assignment is on branch "ex2". Because the previous exercise wasn't checked yet, we didn't merge this branch to "main" branch. Therefore, in order to get the code of the current assignment, please clone the "ex2" branch ONLY, using this command:

  * git clone --branch "ex2" https://github.com/mashashopen/ex1.git


 =============================== Compiling Command ===============================

 * make 


 =============================== Running Command ===============================

 * ./a.out \<k> <file_path> <distance_type>
  
   for example:  ./a.out 3 iris_classified.csv CAN

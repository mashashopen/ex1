"# ex1" 

==================== Short Description Of The Project ====================
When string input is added:
first, getVectorAsInput function is generating a string type into a vector type.
in this function,we call inputValidation function that checks two cases:
case 1: if the string is empty, we exit the program cause distance of empty vector 
cannot be calculated.
case 2: if the input contains chars, we exit the program from the same reason. 

if the input is valid, getVectorAsInput function is generating the string into a vector type.
then ,the program is returning back to main where the two created vectors are checked:
case 3: if vectors are not at the same size, we exit the program.

when 2 inputs are valid and generated into vectors, main function calls 5 different functions
that declared in Distance.cpp file. 
these 5 functions calculate the distance following the algorithms:
- euclidean
- manhattan
- chebyshev
- canberra
- minkowski

then main function print the distance values that each function return.

==================== Running Example ====================

- valid input:
 3 4 5 6
 5 7 9 1

output: 
7.34847
14.0
5.0
1.52273
6.07318

- invalid input:
1 6 7
5 9 A
  
 output: 
 invalid input!


 ==================== Compiling Command ====================












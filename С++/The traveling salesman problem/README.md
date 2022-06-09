# The traveling salesman problem
A schematic map of the city quarters is given (file inside the project)

    17 8
    0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
    0 2 1 1 0 1 1 1 0 1 1 1 0 1 1 1 0
    0 1 1 1 0 1 1 1 0 1 1 1 1 1 1 2 0
    0 1 0 0 0 0 0 0 0 1 1 1 1 1 1 1 0
    0 0 0 1 1 1 1 2 0 1 1 0 0 0 0 0 0
    0 1 0 0 0 0 1 1 0 0 1 1 2 1 1 1 0
    0 3 0 1 1 1 1 1 0 1 1 1 0 1 1 1 0
    0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0

The numbers on the map indicate:

    0 - road
    1 - building
    2 - store
    3 - warehouse
Write a program that, using the map entered from the file, builds the shortest route that allows you to take all the goods from the warehouse to the stores and return back. The program should build a map of the city and display the calculated route on it
# Advanced-Programing-Project-Part-2

To compile: make

to run: 

In 1 terminal: ./server.out [a port]

In Another terminal: ./client.out [an ip] [a port]

When running from the second terminal (the client side), אhe program expects an input from the user that includes a vector, a metrica and a number.

The file should have classified vectors in the format: num1, num2, ..., numN, classification.

The program will calculate the distances of the given vector to all of the vectors from the file the server got, and the server will find the k vectors that are the closes to it according to the metricas.

The classification that will be the most prevelant among those k vectors, will be the given vector's classification.

The metricas are:

Euclidean distance with the formula: sqrt[(v1[1] - v2[1])^2] + ... + (v1[n] - v2[n])^2]

Manhatten distance with the formula: |v1[1] - v2[1]| + ... + |v1[n] - v2[n]|

Chebyshev distance with the formula: Max(|v1[1] - v2[1]| + ... + |v1[n] - v2[n]|)

Canberra distance with the formula: |v1[1] - v2[1]|/(|v1[1]| + |v2[1]|) + ... + |v1[n] - v2[n]|/(|v1[n]| + |v2[n]|)

Minkowski distance with the formula: (|v1[1] - v2[1]|^P + ... + |v1[n] - v2[n]|^P)^(1/P). Our P is 4.

For P = 1 Minkowski will use Manhatten distance.

For P = 2 Euclidean will use Manhatten distance.

If when calculating the distance there is an overflow, prints a message.

The server will send the classification back to the client and it will be printed on the client side, and wait for more inputs.

if the client enters -1, it will stop sending inputs.

The communication between the client and the server is through a TCP socket.

If at some point the input is not as expected, or if an error occore, should print a message and stop.

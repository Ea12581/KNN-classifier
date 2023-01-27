# Advanced-Programing-Project-Part-3
To compile: make

to run: 

In 1 terminal: ./server.out [a port]

In Another terminal: ./client.out [an ip] [a port]

The server waits for clients to connect.

When a client connects, the server sends a menu with 5 options and an option to exit.

Option 1: the serrver asks the client to upload a file with classified vectors and a file with an unclassified vectors.

The file should of the classified vectors should be in the format: num1, num2, ..., numN, classification, while the unclassified doesn't have classification.

Option 2: the server print's the current K and metric in order to classify vectors later. if the client presses enter. returns to the menu. else, they can enter input in the next format "[k] [metric]" in order to update the current K and metric value.

The metricas are:

Euclidean distance with the formula: sqrt[(v1[1] - v2[1])^2] + ... + (v1[n] - v2[n])^2]

Manhatten distance with the formula: |v1[1] - v2[1]| + ... + |v1[n] - v2[n]|

Chebyshev distance with the formula: Max(|v1[1] - v2[1]| + ... + |v1[n] - v2[n]|)

Canberra distance with the formula: |v1[1] - v2[1]|/(|v1[1]| + |v2[1]|) + ... + |v1[n] - v2[n]|/(|v1[n]| + |v2[n]|)

Minkowski distance with the formula: (|v1[1] - v2[1]|^P + ... + |v1[n] - v2[n]|^P)^(1/P). Our P is 4.

For P = 1 Minkowski will use Manhatten distance.

For P = 2 Euclidean will use Manhatten distance.

If when calculating the distance there is an overflow, prints a message.

Option 3: the server will classify the unclassified vectors according to the k and the metric and the classified vectors, and will hold their data.

The classification works like this: for each vector of the unclassified vectors The program will calculate the distances of the given vector to all of the vectors from the classified file the server got, and the server will find the k vectors that are the closes to it according to the metricas.

The classification that will be the most prevelant among those k vectors, will be the given vector's classification.

Option 4: The server will send the client a list of the classifications (of the unclassified vectors after being classified) and the client will print them.

Option 5: The server will send the client a list of the classifications (of the unclassified vectors after being classified) and the client will save them in a file.

if the client enters 8, it will disconnect and stop.

The communication between the client and the server is through a TCP socket.

The server creates a new thread for each client.

The client downloads and creates the file in option 5 in a new thread.

If at some point the input is not as expected, or if an error occore, should print a message.


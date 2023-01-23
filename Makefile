all: server.out client.out

server.out: CheckInput.o VectorCalDis.o KnnVec.o KnnDB.o KnnServer.o Command.o Download.o Display.o Settings.o StandardIO.o UploadC.o mainServer.o 
	g++ -o server.out mainServer.o CheckInput.o VectorCalDis.o KnnVec.o KnnDB.o KnnServer.o Command.o Download.o Display.o server.o StandardIO -std=c++11
client.out: CheckInput.o VectorCalDis.o KnnVec.o KnnDB.o Client.o
	g++ -o client.out Client.o CheckInput.o VectorCalDis.o KnnVec.o KnnDB.o -std=c++11
CheckInput.o: CheckInput.cpp
	g++ -c -o CheckInput.o CheckInput.cpp -std=c++11
VectorCalDis.o: VectorCalDis.cpp
	g++ -c -o VectorCalDis.o VectorCalDis.cpp -std=c++11
KnnVec.o: KnnVec.cpp
	g++ -c -o KnnVec.o KnnVec.cpp -std=c++11 
KnnDB.o: KnnDB.cpp
	g++ -c -o KnnDB.o KnnDB.cpp -std=c++11
KnnServer.o: KnnServer.cpp
	g++ -c -o KnnServer.o KnnServer.cpp -std=c++11
mainServer.o: mainServer.cpp
	g++ -c -o mainServer.o mainServer.cpp -std=c++11
Client.o: Client.cpp
	g++ -c -o Client.o Client.cpp -std=c++11
CLI.o: CLI.cpp
	g++ -c -o CLI.o CLI.cpp -std=c++11
Classify.o: Classify.cpp
	g++ -c -o Classify.o Classify.cpp -std=c++11
Command.o: Command.cpp
	g++ -c -o Command.o Command.cpp -std=c++11
Download.o: Download.cpp
	g++ -c -o Download.o Download.cpp -std=c++11
Display.o: Display.cpp
	g++ -c -o Display.o Display.cpp -std=c++11
Settings.o: Settings.cpp
	g++ -c -o Settings.o Settings.cpp -std=c++11
UploadC.o: UploadC.cpp
	g++ -c -o UploadC.o UploadC.cpp -std=c++11
StandardIO.o: StandardIO.cpp
	g++ -c -o StandardIO.o StandardIO.cpp -std=c++11
clean:
	rm -f *.o *.out

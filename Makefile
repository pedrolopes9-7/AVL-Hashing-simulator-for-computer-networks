all: AVLTree.o Hash.o Intranet.o Lista.o NoH.o Tratamento.o Vetor.o main.cpp
	g++ -o main main.cpp AVLTree.o Hash.o Intranet.o Lista.o NoH.o Tratamento.o Vetor.o

AVLTree.o: AVLTree.cpp
	g++ -o AVLTree.o -c AVLTree.cpp

Hash.o: Hash.cpp
	g++ -o Hash.o -c Hash.cpp
	
Intranet.o: Intranet.cpp
	g++ -o Intranet.o -c Intranet.cpp
	
Lista.o: Lista.cpp
	g++ -o Lista.o -c Lista.cpp
	
NoH.o: NoH.cpp
	g++ -o NoH.o -c NoH.cpp
	
Tratamento.o: Tratamento.cpp
	g++ -o Tratamento.o -c Tratamento.cpp
	
Vetor.o: Vetor.cpp
	g++ -o Vetor.o -c Vetor.cpp

clean:
	rm -f *.o main <iput.txt> output.txt

run:
	./main < input.txt > output.txt

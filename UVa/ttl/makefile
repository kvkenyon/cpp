all:
	make clean
	make RunNode

RunNode: Node.h Node.c++ RunNode.c++
	g++-4.7 -pedantic -std=c++11 -Wall Node.c++ RunNode.c++ -o RunNode

UVaNode: UVaNode.c++
	g++-4.7 -pedantic -std=c++11 -Wall UVaNode.c++

clean:
	rm -f RunNode
	rm -f RunNode.out
	rm -f RunNode.tmp
	
clean2:
	rm -f a.out


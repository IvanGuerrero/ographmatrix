#include <iostream>
#include <algorithm>
#include <cassert>
#include <string>

#include "voce.h"
#include "graph.h"
#include <cmath>

struct equal_int{
	bool operator()(int val1, int val2) const{
		return (val1 == val2);
	}
};
struct equal_char{
	bool operator()(char c1, char c2) const{
		return c1 == c2;
	}
};
struct equal_float{
	bool operator()(float f1, float f2) const{
		return fabs(f2-f1) < 0.001;
	}
};
struct equal_str{
	bool operator()(std::string &s1, std::string &s2) const{
		if(s1.compare(s2) == 0)
			return true;
		else
			return false;
	}
};

struct equal_voce {
	bool operator() (voce a, voce b) const {
		return (a == b);
	}
};

void test_constructor_int () {
	std::cout << "--- Test constructor int ---" << std::endl;
	//Senza elementi
	//costruttore di default
	graph<int, equal_int> graphI1;
	//copy constructor
	graph<int, equal_int> graphI2(graphI1);
	//Clone
	graph<int, equal_int> graphI3 = graphI2;

	//Con elementi
	graph<int, equal_int> graphI4;
	graphI4.addNode(5);
	graphI4.addNode(10);
	graphI4.addNode(6);
	graphI4.addArc(10,6);
	graphI4.addArc(6,5);

	//clone di graphI4
	graphI2 = graphI4;
	//copy constructor, copia degli stessi elementi di graphI4 in graphI5
	graph<int, equal_int> graphI5(graphI4);

	std::cout << "- Perfetto -" << std::endl;
}
void test_constructor_char () {
	std::cout << "--- Test constructor char---" << std::endl;
	graph<char, equal_char> graphC1;
	graph<char, equal_char> graphC2(graphC1);
	graph<char, equal_char> graphC3 = graphC2;
	std::cout << "- Perfetto -" << std::endl;

	//Con elementi
	graph<char, equal_char> graphC4;
	graphC4.addNode('a');
	graphC4.addNode('b');
	graphC4.addNode('c');
	graphC4.addArc('a','a');
	graphC4.addArc('b','b');

	//clone di graphC4
	graphC2 = graphC4;
	//copy constructor, copia degli stessi elementi di graphC4 in graphC5
	graph<char, equal_char> graphC5(graphC4);
	std::cout << "- Perfetto -" << std::endl;
}
void test_constructor_float () {
	std::cout << "--- Test constructor float ---" << std::endl;
	graph<float, equal_float> graphF1;
	graph<float, equal_float> graphF2(graphF1);
	graph<float, equal_float> graphF3 = graphF2;

	//Con elementi
	graph<float, equal_float> graphF4;
	graphF4.addNode(5.5);
	graphF4.addNode(9.5);
	graphF4.addNode(6.12);
	graphF4.addArc(5.5,9.5);
	graphF4.addArc(6.12,5.5);

	//clone di graphF4
	graphF2 = graphF4;
	//copy constructor, copia degli stessi elementi di graphF4 in graphF5
	graph<float, equal_float> graphF5(graphF4);
	std::cout << "- Perfetto -" << std::endl;
}
void test_constructor_string () {
	std::cout << "--- Test constructor string ---" << std::endl;
	graph<std::string, equal_str> graphS1;
	graph<std::string, equal_str> graphS2(graphS1);
	graph<std::string, equal_str> graphS3 = graphS2;

	//Con elementi
	graph<std::string, equal_str> graphS4;
	graphS4.addNode("abc");
	graphS4.addNode("bcd");
	graphS4.addNode("cdf");
	graphS4.addArc("abc","cdf");
	graphS4.addArc("bcd","cdf");

	//clone di graphS4
	graphS2 = graphS4;
	//copy constructor, copia degli stessi elementi di graphS4 in graphS5
	graph<std::string, equal_str> graphS5(graphS4);
	std::cout << "- Perfetto -" << std::endl;
}
void test_constructor_voce () {
	std::cout << "--- Test constructor voce ---" << std::endl;
	graph<voce, equal_voce> graphV1;
	graph<voce, equal_voce> graphV2(graphV1);
	graph<voce, equal_voce> graphV3 = graphV2;
	std::cout << "-Voce senza elementi -" << std::endl;
	std::cout << "- Stampa di voce 1 senza elementi -" << std::endl;
	std::cout << graphV1;
	std::cout << "- Stampa di voce 2  contente copia di v1 -" << std::endl;
	std::cout << graphV2;
	std::cout << "- Stampa di voce 3 che e' il clone di voce 2 -" << std::endl;
	std::cout << graphV3;

	voce a("utente2","C_utente2", "234567891");
	voce b("utente3","C_utente13", "345678912");
	voce c("nessuno1","C_nessuno1", "456789123");
	//Con elementi
	graph<voce, equal_voce> graphV4;
	graphV4.addNode(a);
	graphV4.addNode(b);
	graphV4.addNode(c);
	graphV4.addArc(c,b);
	graphV4.addArc(a,b);

	//clone di graphV4
	graphV2 = graphV4;
	//copy constructor, copia degli stessi elementi di graphV4 in graphV5
	graph<voce, equal_voce> graphV5(graphV4);

	std::cout << "-Voce con elementi -" << std::endl;
	std::cout << "- Stampa di voce 4 con elementi -" << std::endl;
	std::cout << graphV4 << std::endl;
	std::cout << "- Stampa di voce 2 che e' il clone di voce 4 -" << std::endl;
	std::cout << graphV2  << std::endl;
	std::cout << "- Stampa di voce 5 contente la copia di voce 4-" << std::endl;
	std::cout << graphV5 << std::endl;
	std::cout << "- Perfetto -" << std::endl;
}

void test_addNode_int() {
	graph<int, equal_int> g1;
	std::cout << "--- Test addNode int ---" << std::endl;
	g1.addNode(20);
	g1.addNode(3);
	g1.addNode(2);
	g1.addNode(5);
	g1.addNode(1);
	assert(g1.countNodes() == 5);
	std::cout<< "- Perfetto -" << std::endl;

	//g1.add("ehi"); invalid conversion (compilazione)

	try {
		std::cout << "/ Add node already existing: [3] /" << std::endl;
		g1.addNode(3);
	} catch(graph_node_already_existing_exception e) {
		std::cout << "/ Error add, node already existing /" << std::endl;
	}

	std::cout << "--- Test Exist Node int ---" << std::endl;
	assert(g1.exists(20) == true);
	assert(g1.exists(55) == false);

	//assert(g1.exists("ciao") == false); errore in compilazione

	std::cout << "- OK -" << std::endl;
}
void test_addNode_char() {
	graph<char, equal_char> gc1;
	std::cout << "--- Test addNode Char ---" << std::endl;
	gc1.addNode('a');
	gc1.addNode('b');
	gc1.addNode('d');
	assert(gc1.countNodes() == 3);
	std::cout<< "- Perfetto -" << std::endl;

	//gc1.add(0); invalid conversion (compilazione)

	try {
		std::cout << "/ Add node already existing: 'a' /" << std::endl;
		gc1.addNode('a');
	} catch(graph_node_already_existing_exception e) {
		std::cout << "/ Error add, node already existing /" << std::endl;
	}

	std::cout << "--- Test Exist Node Char ---" << std::endl;
	assert(gc1.exists('b') == true);
	assert(gc1.exists('f') == false);

	//assert(gc1.exists(1) == false); errore in compilazione

	std::cout << "- OK -" << std::endl;
}
void test_addNode_float() {
	graph<float, equal_float> gf1;
	std::cout << "--- Test addNode Float ---" << std::endl;
	gf1.addNode(1.2);
	gf1.addNode(2.5);
	gf1.addNode(1.8);
	assert(gf1.countNodes() == 3);
	std::cout<< "- Perfetto -" << std::endl;

	//gf1.add("lei"); invalid conversion (compilazione)

	try {
		std::cout << "/ Add node already existing: 'a' /" << std::endl;
		gf1.addNode(2.5);
	} catch(graph_node_already_existing_exception e) {
		std::cout << "/ Error add, node already existing /" << std::endl;
	}

	std::cout << "--- Test Exist Node Float ---" << std::endl;
	assert(gf1.exists(1.2) == true);
	assert(gf1.exists(4.0) == false);

	//assert(gf1.exists('C') == false); errore in compilazione

	std::cout << "- OK -" << std::endl;
}
void test_addNode_string() {
	graph<std::string,equal_str> gS1;
	std::cout << "--- Test addNode String ---" << std::endl;
	std::string s[3] = {"Pippo", "Pluto", "Topolino"};

	gS1.addNode(s[0]);
	gS1.addNode(s[2]);
	gS1.addNode(s[1]);
	assert(gS1.countNodes() == 3);
	std::cout<< "- Perfetto -" << std::endl;

	try {
		std::cout << "/ Add node already existing: 'Topolino' /" << std::endl;
		gS1.addNode(s[2]);
	} catch(graph_node_already_existing_exception e) {
		std::cout << "/ Error add, node already existing /" << std::endl;
	}

	std::cout << "--- Test Exist Node String ---" << std::endl;
	assert(gS1.exists(s[0]) == true);
	assert(gS1.exists("Paperina") == false);

	//assert(gS1.exists('Topolina') == false); errore in compilazione
	std::cout << "- OK -" << std::endl;
}
void test_addNode_voce() {
	graph<voce,equal_voce> graphV;

	std::cout << "--- Test Add Node voce ---" << std::endl;
	voce a;
	voce b("utente2","C_utente2", "234567891");
	voce c("utente3","C_utente3", "345678912");
	voce d("nessuno1","C_nessuno1", "456789123");
	graphV.addNode(a);
	graphV.addNode(b);
	graphV.addNode(c);
	assert(graphV.countNodes() == 3);
	//std::cout << graphV << std::endl;
	std::cout<< "- Perfetto -" << std::endl;

	try {
		std::cout << "/ Add node already existing: 'Voce a' /" << std::endl;
		graphV.addNode(a);
	} catch(graph_node_already_existing_exception e) {
		std::cout << "/ Error add, node already existing /" << std::endl;
	}
	std::cout << "--- Test Exist Node Voce ---" << std::endl;
	assert(graphV.exists(a) == true);
	assert(graphV.exists(d) == false);
	assert(graphV.exists(c) == true);
	std::cout << "- OK -" << std::endl;
}

void test_addArc_int() {
	graph<int, equal_int> g1;
	std::cout << "--- Test addArc int ---" << std::endl;
	g1.addNode(20);
	g1.addNode(3);
	g1.addNode(2);
	g1.addNode(5);
	g1.addNode(1);
	g1.addArc(20,20);
	g1.addArc(5,1);
	g1.addArc(5,3);
	g1.addArc(3,2);
	g1.addArc(2,3);
	g1.addArc(2,2);
	assert(g1.countArcs() == 6);
	//gc1.addArc('c','d'); invalid conversion (compilazione)
	// std::cout << g1 << std::endl;
	// g1.printMatrix();
	std::cout << "- Perfetto -" << std::endl;

	std::cout << "--- Test hasEdge int---" << std::endl;
	assert(g1.hasEdge(20,20) == true);
	assert(g1.hasEdge(20,2) == false);
	try {
		assert(g1.hasEdge(2011,20012) == false);
	} catch(graph_node_not_existing_exception e) {
		std::cout << "/ Imposible to verify arc, nodoes not existing /" << std::endl;
	}
	try {
		assert(g1.hasEdge(20,20012) == false);
	} catch(graph_node_not_existing_exception e) {
		std::cout << "/ Imposible to verify arc, node not exist /" << std::endl;
	}
	//assert(g1.hasEdge('c','a') == true) //error conversion
	std::cout << "- OK -" << std::endl;

	std::cout << "--- Test removeArc int -" << std::endl;
	//remove loop arc
	g1.removeArc(20, 20);
	//remove arc simetrico
	g1.removeArc(2, 3);
	g1.removeArc(3, 2);
	//std::cout << g1;
	try {
		std::cout << "/ Remove arc not exist: (3, 5) : ";
		g1.removeArc(3,5);
	} catch(graph_arc_not_exist_exception e) {
		std::cout << "Error remove arc, arc not existing. /" << std::endl;
	}
	try {
		std::cout << "/ Remove arc with node not exist: (99,2) : ";
		g1.removeArc(99,2);
	} catch(graph_node_not_existing_exception e) {
		std::cout << "Error remove arc, node not existing. /" << std::endl;
	}
	std::cout << "- OK -" << std::endl;
}
void test_addArc_char() {
	graph<char, equal_char> gc1;
	std::cout << "--- Test addArc Char ---" << std::endl;
	gc1.addNode('a');
	gc1.addNode('b');
	gc1.addNode('d');
	gc1.addArc('a', 'a');
	gc1.addArc('d', 'b');
	gc1.addArc('b', 'd');
	assert(gc1.countNodes() == 3);
	// std::cout << gc1 << std::endl;
	// gc1.printMatrix();
	std::cout<< "- Perfetto -" << std::endl;

	//gc1.addArc(1,1); invalid conversion (compilazione)
	std::cout << "--- Test hasEdge char ---" << std::endl;
	assert(gc1.hasEdge('a','a') == true);
	assert(gc1.hasEdge('a','d') == false);
	try {
		assert(gc1.hasEdge('e','f') == false);
	} catch(graph_node_not_existing_exception e) {
		std::cout << "/ Imposible to verify arc, nodoes not existing /" << std::endl;
	}
	try {
		assert(gc1.hasEdge('a','c') == false);
	} catch(graph_node_not_existing_exception e) {
		std::cout << "/ Imposible to verify arc, node not exist /" << std::endl;
	}
	//assert(gc1.hasEdge(1,2) == true) //errore di conversione
	std::cout << "- OK -" << std::endl;

	std::cout << "--- Test removeArc char -" << std::endl;
	//remove loop arc
	gc1.removeArc('a', 'a');
	//remove arc
	gc1.removeArc('d', 'b');
	//std::cout << gc1;
	try {
		std::cout << "/ Remove arc not exist: ('b', 'a') : " ;
		gc1.removeArc('b','a');
	} catch(graph_arc_not_exist_exception e) {
		std::cout << "Error remove arc, arc not existing" << std::endl;
	}
	try {
		std::cout << "/ Remove arc with node not exist: ('f','a') :";
		gc1.removeArc('f','a');
	} catch(graph_node_not_existing_exception e) {
		std::cout << "Error remove arc, node not existing /" << std::endl;
	}
	std::cout << "- OK -" << std::endl;
}
void test_addArc_float() {
	graph<float, equal_float> gf1;
	std::cout << "--- Test addArc Float ---" << std::endl;
	gf1.addNode(1.2);
	std::cout << "addNode1" << std::endl;
	gf1.addNode(2.5);
	gf1.addNode(1.8);
	gf1.addArc(1.2, 1.8);
	gf1.addArc(2.5, 1.2);
	gf1.addArc(1.8, 1.8);
	assert(gf1.countNodes() == 3);
	// std::cout << gf1 << std::endl;
	// gf1.printMatrix();
	std::cout<< "- Perfetto -" << std::endl;
	//gf1.addArc("lei","milly"); invalid conversion (compilazione)

	std::cout << "--- Test hasEdge float ---" << std::endl;
	assert(gf1.hasEdge(2.5,1.2) == true);
	assert(gf1.hasEdge(1.8,1.2) == false);
	try {
		assert(gf1.hasEdge(3.6,3.62) == false);
	} catch(graph_node_not_existing_exception e) {
		std::cout << "/ Imposible to verify arc, nodoes not existing /" << std::endl;
	}
	try {
		assert(gf1.hasEdge(1.23,1.8) == false);
	} catch(graph_node_not_existing_exception e) {
		std::cout << "/ Imposible to verify arc, node not exist /" << std::endl;
	}
	//assert(gf1.hasEdge('a','b') == true) //errore di conversione
	std::cout << "- OK -" << std::endl;

	std::cout << "--- Test removeArc float -" << std::endl;
	gf1.removeArc(2.5, 1.2);
	//std::cout << gf1;
	try {
		std::cout << "/ Remove arc not exist: (2.5, 1.88) : ";
		gf1.removeArc(2.5, 1.8);
	} catch(graph_arc_not_exist_exception e) {
		std::cout << "Error remove arc, arc not existing" << std::endl;
	}
	try {
		std::cout << "Remove arc with node not exist: (2.5, 2.52) : ";
		gf1.removeArc(2.5,2.52);
	} catch(graph_node_not_existing_exception e) {
		std::cout << "Error remove arc, node not existing" << std::endl;
	}

	std::cout << "- OK -" << std::endl;
}
void test_addArc_string() {
	graph<std::string,equal_str> gS1;
	std::cout << "--- Test addNode String ---" << std::endl;
	std::string s[5] = {"Pippo", "Pluto", "Topolino", "Minny", "Paperino"};
	gS1.addNode(s[0]);
	gS1.addNode(s[1]);
	gS1.addNode(s[4]);
	gS1.addNode(s[3]);
	gS1.addNode(s[2]);
	gS1.addArc(s[0],s[0]);
	gS1.addArc(s[0],s[1]);
	gS1.addArc(s[1],s[3]);
	gS1.addArc(s[2],s[2]);
	gS1.addArc(s[1],s[2]);
	gS1.addArc(s[2],s[1]);
	assert(gS1.countArcs() == 6);

	// std::cout << gS1 << std::endl;
	// gS1.printMatrix();
	std::string ns[3] = {"Paperina", "boom", "Topolina"};
	std::cout << "- OK -" << std::endl;

	std::cout << "--- Test hasEdge String ---" << std::endl;
	assert(gS1.hasEdge(s[0],s[0]) == true);
	assert(gS1.hasEdge(s[1],s[2]) == true);
	assert(gS1.hasEdge(s[3],s[1]) == false);
	try {
		std::cout << "/ hasEdge('Paperina', 'Paperino') : ";
		assert(gS1.hasEdge(ns[1], s[4]) == false);
	} catch(graph_node_not_existing_exception e) {
		std::cout << "Imposible to verify arc, node not existing /" << std::endl;
	}
	try {
		std::cout << "/ hasEdge('Topolina', 'Paperina') : ";
		assert(gS1.hasEdge(ns[2], ns[0]) == false);
	} catch(graph_node_not_existing_exception e) {
		std::cout << "Imposible to verify arc, nodes not existing /" << std::endl;
	}
	//assert(hasEdge(1,2) == tru) //error conversione
	std::cout << "- OK -" << std::endl;

	std::cout << "--- Test removeArc string -" << std::endl;
	//remove arc loop
	gS1.removeArc(s[2], s[2]);
	//remove arc;
	gS1.removeArc(s[1], s[2]);
	//std::cout << gS1;
	try {
		std::cout << "/ Remove arc not exist: ('Pluto', 'Topolino') : ";
		gS1.removeArc(s[1], s[2]);
	} catch(graph_arc_not_exist_exception e) {
		std::cout << "Error remove arc, arc not existing. /" << std::endl;
	}

	try {
		std::cout << "/ Remove arc with node not exist: ('Topolina','Topolino') : ";
		gS1.removeArc("Topolina", s[2]);
	} catch(graph_node_not_existing_exception e) {
		std::cout << "Error remove arc, node not existing. /" << std::endl;
	}

	std::cout << "- OK -" << std::endl;
}
void test_addArc_voce() {
	graph<voce,equal_voce> graphV;

	std::cout << "--- Test Add Arc voce ---" << std::endl;
	voce a;
	voce b("name","surname","123456789");
	voce c("name2","surname2","21212121");
	graphV.addNode(a);
	graphV.addNode(b);
	graphV.addNode(c);
	graphV.addArc(a,b);
	graphV.addArc(c,b);
	graphV.addArc(c,c);
	assert(graphV.countArcs() == 3);
	//std::cout << graphV << std::endl;
	//graphV.printMatrix();
	std::cout << "- Perfetto -" << std::endl;

	voce d("nessuno1","nessuno2","31313131");
	voce f;
	std::cout << "- OK -" << std::endl;

	std::cout << "--- Test hasEdge Voce ---" << std::endl;
	assert(graphV.hasEdge(a,c) == false);
	assert(graphV.hasEdge(a,b) == true);
	try {
		std::cout << "/ hasEdge('Voce d', 'Voce b') : ";
		assert(graphV.hasEdge(d, b) == false);
	} catch(graph_node_not_existing_exception e) {
		std::cout << "Imposible to verify arc, node not existing /" << std::endl;
	}
	try {
		std::cout << "/ hasEdge('Voce d', 'Voce f') : ";
		assert(graphV.hasEdge(d, f) == false);
	} catch(graph_node_not_existing_exception e) {
		std::cout << "Imposible to verify arc, nodes not existing /" << std::endl;
	}
	//assert(hasEdge(1,2) == true) //error conversione
	std::cout << "- OK -" << std::endl;
	std::cout << "--- Test removeArc voce -" << std::endl;

	//remove arc loop
	graphV.removeArc(c, c );
	//remove first arc;
	graphV.removeArc(a, b);
	//std::cout << graphV;
	try {
		std::cout << "/ Remove arc not exist: ('Voce a', 'Voce b') : ";
		graphV.removeArc(a, b);
	} catch(graph_arc_not_exist_exception e) {
		std::cout << "Error remove arc, arc not existing. /" << std::endl;
	}

	try {
		std::cout << "/ Remove arc with node not exist: ('Voce c','Voce d') : ";
		graphV.removeArc(c, d);
	} catch(graph_node_not_existing_exception e) {
		std::cout << "Error remove arc, node not existing. /" << std::endl;
	}
	std::cout << "- OK -" << std::endl;
}

void test_removeNode_int() {
	graph<int, equal_int> g1;
	std::cout << "--- Test Remove int ---" << std::endl;
	g1.addNode(20);
	g1.addNode(3);
	g1.addNode(2);
	g1.addNode(5);
	g1.addNode(1);
	//std::cout << g1;
	//remove node
	g1.removeNode(5);
	//remove first node
	g1.removeNode(20);
	//remove last node
	g1.removeNode(1);
	//std::cout << g1;

	std::cout << "- Perfetto -" << std::endl;

	//remove node not exist
	try {
		std::cout << "/ remove node not exist: [99]" << std::endl;
		g1.removeNode(99);
	} catch(graph_node_not_existing_exception e) {
		std::cout << "Error remove node, node not exist /" << std::endl;
	}

	std::cout << "- OK -" << std::endl;
}
void test_removeNode_char() {
	graph<char, equal_int> gc1;
	std::cout << "--- Test removeNode Char ---" << std::endl;
	gc1.addNode('a');
	gc1.addNode('b');
	gc1.addNode('d');
	//std::cout << gc1;
	//remove first node
	gc1.removeNode('a');
	//remove node
	gc1.removeNode('b');
	//remove last node
	gc1.removeNode('d');
	//std::cout << gc1;
	std::cout << "- Perfetto -" << std::endl;

	//remove node not exist
	try {
		std::cout << "/ remove node not exist: ['f']" << std::endl;
		gc1.removeNode('f');
	} catch(graph_node_not_existing_exception e) {
		std::cout << "Error remove node, node not exist /" << std::endl;
	}

	std::cout << "- OK -" << std::endl;
}

void test_removeNode_float() {
	graph<float, equal_float> gf1;
	std::cout << "--- Test addNode Float ---" << std::endl;
	gf1.addNode(1.2);
	gf1.addNode(2.5);
	equal_float e1;
	std::cout << e1(1.2,1.8) << " " << e1(2.5, 1.8) << std::endl;
	gf1.addNode(1.8);
	//std::cout << gf1;

	//remove node
	gf1.removeNode(2.5);
	//remove last node
	gf1.removeNode(1.8);
	//std::cout << gf1;
	std::cout << "- Perfetto -" << std::endl;

	//remove node not exist
	try {
		std::cout << "/ remove node not exist: [1.25]" << std::endl;
		gf1.removeNode(1.25);
	} catch(graph_node_not_existing_exception e) {
		std::cout << "Error remove node, node not exist /" << std::endl;
	}

	std::cout << "- OK -" << std::endl;
}


void test_removeNode_string() {
	graph<std::string,equal_str> gS1;
	std::cout << "--- Test removeNode String ---" << std::endl;

	std::string s[4] = {"Pippo", "Pluto", "Michu" "Topolino"};
	gS1.addNode(s[0]);
	gS1.addNode(s[2]);
	gS1.addNode(s[3]);
	gS1.addNode(s[1]);
	//std::cout << gS1;
	//remove last node
	gS1.removeNode(s[3]);
	//remove node
	gS1.removeNode(s[2]);
	//remove first node
	gS1.removeNode(s[0]);
	//std::cout << gS1;
	std::cout << "- Perfetto -" << std::endl;

	//remove node not exist
	try {
		std::cout << "/ remove node not exist: ['Pinguino']" << std::endl;
		gS1.removeNode("Pinguino");
	} catch(graph_node_not_existing_exception e) {
		std::cout << "Error remove node, node not exist /" << std::endl;
	}
	std::cout << "- OK -" << std::endl;
}
void test_removeNode_voce() {
	graph<voce,equal_voce> graphV;

	std::cout << "--- Test removeNode voce ---" << std::endl;
	voce a;
	voce b("utente2","C_utente2", "234567891");
	voce c("utente3","C_utente13", "345678912");
	voce d("nessuno1","C_nessuno1", "456789123");
	graphV.addNode(a);
	graphV.addNode(b);
	graphV.addNode(c);
	//std::cout << graphV;
	//remove node
	graphV.removeNode(b);
	//remove node
	graphV.removeNode(c);
	//std::cout << graphV;
	std::cout << "- Perfetto -" << std::endl;

	//remove node not exist
	try {
		std::cout << "/ remove node not exist: ['Voce d']" << std::endl;
		graphV.removeNode(d);
	} catch(graph_node_not_existing_exception e) {
		std::cout << "Error remove node, node not exist /" << std::endl;
	}
	std::cout << "- OK -" << std::endl;
}

void test_iterator() {
	std::cout << "--- Test iteratori voce---" << std::endl;

	graph<voce, equal_voce> graphV;
	voce b("utente2","C_utente2", "234567891");
	voce c("utente3","C_utente13", "345678912");
	voce d("nessuno1","C_nessuno1", "456789123");
	graphV.addNode(c);
	graphV.addNode(b);
	graphV.addNode(d);
	std::cout << "|il mio array di nodi|" << std::endl;
	std::cout << graphV << std::endl;

	graph<voce, equal_voce>::const_iterator i = graphV.begin(), ie = graphV.end();
	std::cout << "Valore iniziale di i : " << *i << std::endl;
	++i;
	std::cout << "Valore di ++i : " << *i << std::endl;
	ie = i;
	std::cout << "Valore di ie : " << *ie << std::endl;

	//test metodo di confronto tra due iteratori
	std::cout << "- confronto iteratori i e ie -" << std::endl;
	std::cout << "- iteratore i : " << *i << "iteratore ie : " << *ie << std::endl;
	std::cout << "- confronto iteratori i e ie : ";
	assert((ie==i) == true);
	std::cout << "ok -" << std::endl;
	++i;
	std::cout << "-Variazione iteratore ++i che sara' : " << *i << std::endl;
	std::cout << "- confronto iteratori i == ie : ";
	assert((ie==i) == false);
	std::cout << "ok -" << std::endl;
	std::cout << "- confronto iteratori i != ie : ";
	assert((ie!=i) == true);
	std::cout << "ok -" << std::endl;
	std::cout << "- Perfetto -" << std::endl;
}

void test_constructos() {
	//test costruttori con oggetti vuoti
	test_constructor_int();
	test_constructor_float();
	test_constructor_char();
	test_constructor_string();
	test_constructor_voce();
}

void test_print() {
	std::cout << "--- Test Print node and Matrix---" << std::endl;

	//tipo primitivo
	std::cout << "- Aggiunta nodi -" << std::endl;
	graph<int, equal_int> g1;
	g1.addNode(2);
	std::cout << g1;
	g1.printMatrix();
	g1.addNode(5);
	std::cout << g1;
	g1.printMatrix();
	g1.addNode(1);
	std::cout << g1;
	g1.printMatrix();
	std::cout << "- Aggiunta archi -" << std::endl;
	g1.addArc(2,2);
	g1.printMatrix();
	g1.addArc(2,1);
	g1.printMatrix();
	g1.addArc(5,2);
	g1.printMatrix();
	std::cout << "- rimozione archi -" << std::endl;
	g1.removeArc(2,2);
	g1.printMatrix();
	std::cout << "- rimozione nodi -" << std::endl;
	g1.removeNode(2);
	std::cout << g1;
	g1.printMatrix();
	g1.removeNode(5);
	std::cout << g1;
	g1.printMatrix();
	g1.removeNode(1);
	std::cout << g1;
	g1.printMatrix();

	//tipo complesso
	voce a("utente1","C_utente1", "123456789");
	voce b("utente2","C_utente2", "234567891");
	voce c("utente3","C_utente13", "345678912");
	voce d("utente4","C_utente4", "456789123");
	graph<voce, equal_voce> gv;
	std::cout << "- Aggiunta nodi voce -" << std::endl;
	gv.addNode(a);
	std::cout << gv;
	gv.printMatrix();
	gv.addNode(b);
	std::cout << gv;
	gv.printMatrix();
	gv.addNode(c);
	std::cout << gv;
	gv.printMatrix();
	gv.addNode(d);
	std::cout << gv;
	gv.printMatrix();
	std::cout << "- aggiunta archi voci-" << std::endl;
	gv.addArc(d,d);
	gv.printMatrix();
	gv.addArc(a,b);
	gv.printMatrix();
	gv.addArc(b,a);
	gv.printMatrix();
	gv.addArc(a,d);
	gv.printMatrix();
	std::cout << "- rimozione archi voce -" << std::endl;
	gv.removeArc(d,d);
	gv.printMatrix();
	gv.removeArc(b,a);
	gv.printMatrix();
	std::cout << "- rimozione nodi  voci -" << std::endl;
	gv.removeNode(c);
	std::cout << gv;
	gv.printMatrix();
	gv.removeNode(d);
	std::cout << gv;
	gv.printMatrix();
	gv.removeNode(a);
	std::cout << gv;
	gv.printMatrix();
	gv.removeNode(b);
	std::cout << gv;
	gv.printMatrix();

	std::cout << "- Perfetto -" << std::endl;
}
void test_add_allType() {
	//test di aggiunta nodo con i casi che lanciano eccezioni
	test_addNode_int();
	test_addNode_char();
	//test_addNode_float();
	test_addNode_string();
	test_addNode_voce();

	//test di aggiunta arco con i casi che lanciano eccezioni
	//inoltre ci sono anche i test di rimozione archi con i casi che lanciano eccezioni
	test_addArc_int();
	test_addArc_char();
	test_addArc_float();
	test_addArc_string();
	test_addArc_voce();
}

void test_removeNode() {
	//I test di rimozione archi con i casi che lanciano eccezioni
	test_removeNode_int();
	test_removeNode_char();
	test_removeNode_float();
	test_removeNode_string();
	test_removeNode_voce();
}

int main(int argc, char const *argv[])
{
	test_constructos();
	test_add_allType();
	test_removeNode();
	test_print();
	test_iterator();
	return 0;
}
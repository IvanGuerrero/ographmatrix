#ifndef GRAPH_H
#define GRAPH_H

#include <iostream> // ostream
#include <algorithm> // std::swap
#include <iterator>
#include <cstddef>   // std::ptrdiff_t
#include <cassert>
#include <string>

class graph_node_not_existing_exception: public std::exception{};
class graph_node_already_existing_exception: public std::exception{};
class graph_arc_already_exist_exception: public std::exception{};
class graph_arc_not_exist_exception: public std::exception{};

template <typename T, typename Equal>
class graph {
	typedef unsigned int size_type;
	size_type _numNodes;
	T *_nodes;
	Equal _equal;
	bool** _arcs;

public:

	/**
	* Costruttore di default
	*/
	graph() : _numNodes(0), _nodes(0), _arcs(0) {}

	/**
	* Costruttore con un attributo in input
	* param: size_type numNodes dimensione del mio grafo
	*/
	graph(size_type numNodes) :_nodes(0), _arcs(0) {
		_nodes = new T[numNodes];
		_arcs = new bool*[numNodes];
		for(size_type i = 0; i < numNodes; ++i)
			_arcs[i] = new bool[numNodes];

		_numNodes = numNodes;
	}

	/**
	*  Copy costructor
	* param graph &other ovvero il grafo di cui effettuare la copia
	*/
	graph(const graph &other) : _numNodes(0), _nodes(0), _arcs(0) {
		T* tempNodes = other._nodes;
		bool** tempArcs = other._arcs;
		size_type tempNumNodes = other._numNodes;
		try {
				if(tempNodes != 0)
				{
					for (size_type i = 0; i < tempNumNodes; ++i)
						addNode(tempNodes[i]);

					if(tempArcs != 0)
					{
						for (size_type r = 0; r < tempNumNodes; ++r)
						{
							for (size_type c = 0; c < tempNumNodes; ++c)
								if(tempArcs[r][c] == true)
									addArc(tempNodes[r], tempNodes[c]);
						}
					}

				}
			}
		catch (...) {
			clear();
			throw;
		}
	}

	/**
	* Assegnamento di un grafo
	* param graph &other ovvero grafo da assegnare a this
	* oprator =
	*/
	graph &operator=(const graph &other) {
		if (&other != this) {
			graph tmp(other);
			std::swap(tmp._nodes, _nodes);
			std::swap(tmp._arcs, _arcs);
			std::swap(tmp._numNodes, _numNodes);
		}
		return *this;
	}

	/**
	* Verifica se un nodo esiste
	* param: reference node di T
	* return true/false del nodo trovato
	*/
	bool exists(T node) {
		for(unsigned i = 0; i < countNodes(); ++i)
			if(_equal(_nodes[i], node))
				return true;

		return false;
	}

	/**
	* Verifica se un arco esiste
	* param: reference node di T
	* param: reference node di T
	* return true/false dell'arco trovato
	*/
	bool hasEdge(T node1, T node2) {
		if((!exists(node1)) || (!exists(node2))) throw graph_node_not_existing_exception();

		size_type index_r, index_c;

		//cerco l'identificatore della riga e lo converto in intero
		index_r  = indexNode(node1);

		//cerco l'identificatore della colonna e lo converto in intero
		index_c = indexNode(node2);

	    //mi ritorna true o false dalla mia matrice di adiacenza
	    return _arcs[index_r][index_c];
	}

	/**
	* Restituisce l'identificatore riga/colonna e lo converto in intero dato un nodo
	* param: un reference a node di tipo T
	* ritorno : indice del nodo trovato
	*/
	size_type indexNode(T &node) {
		size_type index=0;
		for (size_type i = 0; i < countNodes(); ++i)
		    	if(_equal(node, _nodes[i]))
		        	index = i;

		return index;
	}

	/**
	* Aggiunta di un nodo
	* param: T node
	*/
	void addNode(T node) {
		if(exists(node)) throw graph_node_already_existing_exception();

		T* tempNodes;
		bool** tempArcs;

		_numNodes += 1;

		//allocazione di memoria dinamica
		tempNodes = new T[countNodes()];
		tempArcs = new bool*[countNodes()];
		for(size_type i = 0; i < countNodes(); ++i)
			tempArcs[i] = new bool[countNodes()];

		//inizializzazione del mio array
		for(size_type i = 0; i < countNodes() - 1; ++i)
			tempNodes[i] = _nodes[i];

		//aggiungo il mio nodo al mio array
		tempNodes[countNodes()-1] = node;

		//inizializzazione della matrice
		for(size_type r = 0; r < countNodes() - 1; ++r)
		{
			for (size_type c = 0; c < countNodes() - 1; ++c)
				tempArcs[r][c] = _arcs[r][c];
		}

		//setto la mia riga aggiunta a false
		for(size_type c = 0; c < countNodes(); ++c)
			tempArcs[countNodes()-1][c] = false;

		//setto la mia colonna aggiunta a false
		for(size_type r = 0; r < countNodes(); ++r)
			tempArcs[r][countNodes() - 1] = false;

		//dellocazione di memoria
		for(size_type i = 0; i < countNodes()-1; ++i)
			delete[] _arcs[i];

		delete[] _arcs;
		delete[] _nodes;

		_nodes = tempNodes;
		_arcs = tempArcs;
	}

	/**
	* Aggiunta di un arco dati due nodi in param	* param: node di T
	* param: node di T
	* return
	*/
	void addArc(T node1, T node2) {

		if(hasEdge(node1, node2)) throw graph_arc_already_exist_exception();

		_arcs[indexNode(node1)][indexNode(node2)] = true;
	}

	/**
	* Rimuovere un nodo
	* param: T node
	*/
	void removeNode(T node) {
		if(!exists(node)) throw graph_node_not_existing_exception();

		if(countNodes() > 1) {
			T* tempNodes;
			bool** tempArcs;
			size_type sizeOld;

			sizeOld = countNodes();
			_numNodes -= 1;
			size_type tempIndex = indexNode(node);

			//allocazione di memoria dinamica
			tempNodes = new T[countNodes()];
			tempArcs = new bool*[countNodes()];
			for (size_type i = 0; i < countNodes(); ++i)
				tempArcs[i] = new bool[countNodes()];

			//copia dell'array con rimozione del nodo
			for (size_type i = 0, j = 0; i < sizeOld; ++i)
				if(!(_equal(_nodes[i], node)))
					tempNodes[j++] = _nodes[i];

			//copia della matrice senza la riga e colonna corrispondenti al nodo rimosso
			for (size_type r = 0, rt = 0; r < sizeOld; ++r)
			{
				if(!(r == tempIndex))
				{
					for (size_type c = 0, ct = 0; c < sizeOld; ++c)
					{
						if(!(c == tempIndex))
							tempArcs[rt][ct++] = _arcs[r][c];
					}

					rt++;
				}
			}

			//libero memoria
			for(size_type i = 0; i < countNodes()+1; ++i)
				delete[] _arcs[i];
			delete[] _arcs;
			delete[] _nodes;

			_nodes = tempNodes;
			_arcs = tempArcs;

		} else {
			_numNodes = 0;
			//caso in cui si ha un solo nodo
			delete[] _arcs[0];
			delete[] _arcs;
			delete[] _nodes;

			_nodes=0;
			_arcs=0;
		}

	}

	/**
	* Rimozione di un arco
	* param: T node1
	* param: T node2
	*/
	void removeArc(T node1, T node2)
	{
		if(!hasEdge(node1, node2)) throw graph_arc_not_exist_exception();

		_arcs[indexNode(node1)][indexNode(node2)] = false;
	}

	/**
	* Distruttore
	*/
	~graph() {
		clear();
	}

	/**
	* dellocazione di memoria
	*/
	void clear() {
			if(_nodes != 0) {
				for(size_type i = 0; i < countNodes(); ++i)
					delete[] _arcs[i];
				delete[] _nodes;
				_numNodes = 0;
			}
			if(_arcs != 0)
				delete[] _arcs;
	}

	/**
	* Ritorna il numero di nodi presenti nel grafo
	*/
	size_type countNodes() const {
		return _numNodes;
	}

	/**
	* Ritorna il numero di archi presenti nel grafo
	*/
	size_type countArcs() const {
		size_type cnt = 0;
		for(size_type i = 0; i < countNodes(); ++i)
			for(size_type j = 0; j < countNodes(); ++j)
				if(_arcs[i][j] == true)
					cnt += 1;

		return cnt;
	}

	/**
	* Stampa la mia matrice booleana con riferimento il mio array di nodi
	*/
	void printMatrix () {
		std::cout << "-- Matrice --" << std::endl;
		for (size_type i = 0; i < countNodes(); ++i)
		{
			for (size_type j = 0; j < countNodes(); ++j)
			{
				std::cout << "[ " << _arcs[i][j] << " ]";
			}
			std::cout << std::endl;
		}
		std::cout << std::endl;
	}

/*********************const iterator*****************************/
	class const_iterator {
		const T* ns;

	public:
		typedef std::forward_iterator_tag iterator_category;
		typedef T                         value_type;
		typedef ptrdiff_t                 difference_type;
		typedef const T*                  pointer;
		typedef const T&                  reference;


		const_iterator() : ns(0) {}

		const_iterator(const const_iterator &other) : ns(other.ns) {}

		const_iterator& operator=(const const_iterator &other) {
			ns = other.ns;
			return *this;
		}

		~const_iterator() { }

		// Ritorna il dato riferito dall'iteratore (dereferenziamento)
		reference operator*() const {
			return ns[0];
		}

		// Ritorna il puntatore al dato riferito dall'iteratore
		pointer operator->() const {
			return &ns[0];
		}

		// Operatore di iterazione post-incremento
		const_iterator operator++(int) {
			const_iterator tmp(*this);
			ns = ns + 1;
			return tmp;

		}

		// Operatore di iterazione pre-incremento
		const_iterator& operator++() {
			ns = ns + 1;
			return *this;
		}

		// Uguaglianza
		bool operator==(const const_iterator &other) const {
			return(ns == other.ns);
		}

		// Diversita'
		bool operator!=(const const_iterator &other) const {
			return(ns != other.ns);
		}

	private:
		//Dati membro

		// La classe container deve essere messa friend dell'iteratore per poter
		// usare il costruttore di inizializzazione.
		friend class graph; // !!! Da cambiare il nome!

		// Costruttore privato di inizializzazione usato dalla classe container
		// tipicamente nei metodi begin e end
		const_iterator(const T* nod) : ns(nod) {
			//!!!
		}

		// !!! Eventuali altri metodi privati

	}; // classe const_iterator

	// Ritorna l'iteratore all'inizio della sequenza dati
	const_iterator begin() const {
		return const_iterator(_nodes);
	}

	// Ritorna l'iteratore alla fine della sequenza dati
	const_iterator end() const {
		return const_iterator(&_nodes[countNodes()]);
	}
};

/**
*	Stampa tutti gli elementi del mio grafo
*/
template <typename T, typename E>
std::ostream &operator<<(std::ostream &os, const graph<T,E> &g) {
	typename graph<T,E>::const_iterator i, ie;
	os << "Array Nodes: {";
	for(i = g.begin(), ie = g.end(); i != ie; ++i) {
		os << "[" << *i << "]";
	}
	os << "}" << std::endl;

	return os;
}

#endif
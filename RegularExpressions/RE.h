#pragma once
#include <string>

namespace std
{
	template <class _Ty>
	class allocator;

	template <class _Ty, class _Alloc = allocator<_Ty>>
	class forward_list;
}

class RE_Graph
{
private:
	class Node
	{
	public:
		struct Itr
		{
			int i;
			Node* n;

			Itr(Node* b, int a) : i{ a }, n{ b } { };

			void operator++()
			{
				++i;
			}

			bool operator==(const Itr& l)
			{
				return i == l.i;
			}

			Node& operator*()
			{
				return *(n->adj[i]);
			}
		};

		char c;
		Node* adj[3] = { nullptr };
		int k = 0;

		void add(Node* n);
		bool operator==(const char& cl);

		Itr begin();
		Itr end();
	};

public:
	Node* v;
	int N;
	std::string r;
	void addEdge(int a, int b);
	void DFS(std::forward_list<int>& new_states, std::forward_list<int>& from_states);
	void parse_re(const std::string& reg_expr);

	RE_Graph(const std::string& reg_expr);
};


class RE
{
	static RE_Graph* nfa;
	static bool recongines(const std::string& re, std::string txt);
	static bool recongines(const std::string& re, std::istream st);
};
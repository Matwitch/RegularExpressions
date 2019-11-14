#pragma once
#include <string>

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

	void addEdge(int a, int b);

	void parse_re(const std::string& reg_expr);

	RE_Graph(const std::string& reg_expr);
};
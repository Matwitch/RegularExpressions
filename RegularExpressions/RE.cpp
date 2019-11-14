#include "RE.h"
#include <stack>

void RE_Graph::Node::add(Node* n)
{
	adj[k++] = n;
}

bool RE_Graph::Node::operator==(const char& cl)
{
	return c == cl;
}

RE_Graph::Node::Itr RE_Graph::Node::begin()
{
	return Itr(this, 0);
}
RE_Graph::Node::Itr RE_Graph::Node::end()
{
	return Itr(this, k + 1);
}

void RE_Graph::addEdge(int a, int b)
{
	if (a < N && b < N)
		v[a].add(&v[b]);
	else throw;
}

void RE_Graph::parse_re(const std::string& reg_expr)
{
	std::stack<int> stack;

	for (int i = 0; i < reg_expr.length(); ++i)
	{
		if (reg_expr.at(i) == '(' || reg_expr.at(i) == '|')
			stack.push(i);

		else if (reg_expr.at(i) == ')')
		{
			//
		}


	}
}

RE_Graph::RE_Graph(const std::string& reg_expr)
{
	N = reg_expr.length() + 1;
	v = new RE_Graph::Node[N];
	for (int i = 0; i < N - 1; i++)
		v[i].c = reg_expr.at(i);

	v[N - 1].c = '\0';

	parse_re(reg_expr);
}

#include "RE.h"
#include <stack>
#include <iostream>
#include <forward_list>

RE_Graph* RE::nfa = nullptr;

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

void RE_Graph::DFS(std::forward_list<int>& new_states, std::forward_list<int>& from_states)
{
}

void RE_Graph::parse_re(const std::string& reg_expr)
{
	std::stack<int> stack;

	for (int i = 0, lp = 0; i < reg_expr.length(); ++i)
	{
		if (reg_expr.at(i) == '(' || reg_expr.at(i) == '|')
			stack.push(i);
		else if (reg_expr.at(i) == ')')
		{
			lp = stack.top();
			stack.pop();
			if (v[lp].c == '|')
			{
				int beg = stack.top();
				stack.pop();
				addEdge(beg, lp + 1);
				addEdge(lp, i);
				lp = beg;
			}
		}

		if (reg_expr.at(i) == '*')
		{
			addEdge(lp, i);
			addEdge(i, lp);
		} 
		else if (reg_expr.at(i) == '+')
			addEdge(i, lp);

		if (reg_expr.at(i) == '(' || reg_expr.at(i) == '*' || reg_expr.at(i) == '+' || reg_expr.at(i) == ')')
			addEdge(i, i + 1);

		lp = i;
	}
}

RE_Graph::RE_Graph(const std::string& reg_expr)
{
	N = reg_expr.length() + 1;
	v = new RE_Graph::Node[N];
	r = reg_expr;
	for (int i = 0; i < N - 1; i++)
		v[i].c = reg_expr.at(i);

	v[N - 1].c = '\0';

	parse_re(reg_expr);
}

bool RE::recongines(const std::string& re, std::string txt)
{
	if (!nfa || !re._Equal(nfa->r))
	{
		delete nfa;
		nfa = new RE_Graph(re);
	}
	
	std::forward_list<int> possible;
	std::forward_list<int> match;
	match.push_front(0);
	nfa->DFS(possible, match);

	for (int i = 0; i < txt.length(); ++i)
	{

	}

	return true;
}

bool RE::recongines(const std::string& re, std::istream st)
{
	return false;
}

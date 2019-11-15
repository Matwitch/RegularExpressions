#include "RE.h"
#include <stack>
#include <iostream>
#include <queue>
#include <forward_list>

RE_Graph* RE::nfa = nullptr;
bool* RE_Graph::marked = nullptr;

void RE_Graph::Node::add(int n)
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
		v[a].add(b);
	else throw;
}

void RE_Graph::DFS(std::forward_list<int>& new_states, std::forward_list<int>& from_states)
{
	std::queue<int> q;
	for (int i = 0; i < N; ++i)
		 marked[i] = false;

	for (int t : from_states)
		q.push(t);

	while (!q.empty())
	{
		for (int t : v[q.back()])
		{
			q.push(t);
			new_states.push_front(t);
			marked[t] = true;
		}
		q.pop();
	}
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
	marked = new bool[N] { false };
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
	match.clear();

	for (int i = 0; i < txt.length(); ++i)
	{
		if (possible.empty())
			return false;

		for (int t : possible)
		{
			if (nfa->v[t].c == re.at(i) || re.at(i) == '.')
				match.push_front(t);
		}

		possible.clear();
		nfa->DFS(possible, match);
	}

	return false;
}

bool RE::recongines(const std::string& re, std::istream st)
{
	return false;
}

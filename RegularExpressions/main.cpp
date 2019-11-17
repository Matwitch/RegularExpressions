#pragma once
#include <vector>
#include <iostream>
#include "RE.h"

int main()
{
	std::cout << RE::recongines("(A(C|B)+)", "ACB");
	return 0;
}
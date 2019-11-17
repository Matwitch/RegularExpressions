#pragma once
#include <vector>
#include <iostream>
#include "RE.h"
#include <queue>
int main()
{
	std::cout << RE::recongines(".*(CDA).*", "ulglkhkjbhjABCDCDABA");

	return 0;
}
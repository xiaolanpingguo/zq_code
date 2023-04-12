#include <iostream>
#include <string>
#include "test_coroutine.h"


int main()
{
	testCoroutineWithNoDalay();
	testCoroutineWithLazy();
	testCoroutineAwait();
	testError();
	testYield();

	std::getchar();
	return 0;
}
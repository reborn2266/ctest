#include <stdio.h>
#include "ctest.h"

int foo0(void)
{
	return 1;
}

int foo1(void)
{
	return 0;
}

int foo2(int arg)
{
	return arg == 100;
}

struct bar {
	int arg1;
	char arg2;
};

int foo3(struct bar *arg)
{
	return (arg->arg1 == 100) && (arg->arg2 == 'Y');
}

struct nested_bar {
	int arg1;
	struct bar bar_obj;
	struct bar *pbar;
};

int foo4(struct nested_bar *obj)
{
	return (obj->arg1 == 100) && (obj->bar_obj.arg2 == 'Y') && (obj->pbar->arg1 == 100);
}

int main(void)
{
	struct bar bar_correct = { 100, 'Y' };
	struct bar bar_wrong = { 100, 'N' };
	struct nested_bar nested_bar_correct = { 100, {100, 'Y'}, &bar_correct}; 
	const char *extra_msg = "item0002";

	CTEST_ADD(foo0, "");
	CTEST_ADD(foo1, "");
	CTEST_ADD_WITH_ARG(foo2, 100, "");
	CTEST_ADD_WITH_ARG(foo2, 50, "");
	CTEST_ADD_WITH_ARG(foo3, &bar_correct, "");
	CTEST_ADD_WITH_ARG(foo3, &bar_wrong, "");
	CTEST_ADD_WITH_ARG(foo3, &bar_correct, "item0001");
	CTEST_ADD_WITH_ARG(foo3, &bar_correct, extra_msg);
	CTEST_ADD_WITH_ARG(foo4, &nested_bar_correct, "");

	return 0;
}

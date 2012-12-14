#ifndef __CTEST_H__
#define __CTEST_H__

#include <stdio.h>

typedef int (*ctest_func)(void);
typedef int (*ctest_func_arg)(void *);

static inline void _ctest_add(ctest_func f, const char *func_name, const char *extra_msg)
{
	if (f()) {
		printf("%s %s pass\n", extra_msg, func_name);
	} else {
		printf("%s %s failed\n", extra_msg, func_name);
	}
}

static inline void _ctest_add_with_arg(ctest_func_arg f, const char *func_name, void *arg, const char *extra_msg)
{
	if (f(arg)) {
		printf("%s %s pass\n", extra_msg, func_name);
	} else {
		printf("%s %s failed\n", extra_msg, func_name);
	}
}

#define CTEST_ADD(test_func, extra_msg) do {\
			_ctest_add((ctest_func)test_func, #test_func, extra_msg);\
		} while (0)

#define CTEST_ADD_WITH_ARG(test_func, arg, extra_msg) do {\
			_ctest_add_with_arg((ctest_func_arg)test_func, #test_func, (void *)arg, extra_msg);\
		} while (0)

#define CTEST_EQ(expression, expected) do {\
					  if ((expression) != (expected)) {\
                                                printf("%s:%s:%d: 0x%lx mismatches expected 0x%lx.\n",\
                                                        __FILE__, __FUNCTION__, __LINE__,\
							(unsigned long)(expression), (unsigned long)(expected)); return 0;\
					  }\
                                       } while (0)

#endif // eof __CTEST_H__

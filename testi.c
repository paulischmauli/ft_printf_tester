#include "ft_printf.h"
#include <stdio.h>
#include <limits.h>

#define RUN(label, fmt, ...) do {	\
	printf("[OG] "); fflush(stdout); \
	int og = printf(fmt, ##__VA_ARGS__);	\
	printf("\n[FT] "); fflush(stdout); \
	int ft = ft_printf(fmt, ##__VA_ARGS__);	\
	printf("\n[%s] returns: og = %d, ft = %d %s\n\n",	\
	label, og, ft, (og == ft ? "OK" : "MISMATCH"));	\
	printf("---------------------------------\n");	\
} while (0)

int	main (void)
{
	printf("-------- FT_PRINTF TESTS --------\n");

	// ---------- SIMPLE TXT BASED TESTS ----------
	printf("-------- BASIC TESTS --------\n");
	RUN("empty", "%s", "");
	RUN("text", "Servas 42\n");
	RUN("char", "%c", 'E');
	RUN("string", "%s", "Hawidere 42\n");
	RUN("null string", "%s", NULL);
	// ---------- %d TESTS ----------
	printf("-------- %%d TESTS --------\n");
	RUN("decimal positive", "%d", 42);
	RUN("decimal negative", "%d", -1);
	RUN("decimal zero", "%d", 0);
	RUN("decimal -zero", "%d", -0);
	RUN("decimal INT_MIN", "%d", INT_MIN);
	RUN("decimal INT_MAX", "%d", INT_MAX);
	// ---------- %u TESTS ----------
	printf("-------- %%u TESTS --------\n");
	RUN("u zero", "%u", 0);
	RUN("u small", "%u", 4);
	RUN("u two digits", "%u", 42);
	RUN("u three digits", "%u", 420);
	RUN("u max uint", "%u", 4294967295u);
	RUN("u near max", "%u", 4294967294u);
	RUN("u near max2", "%u", 4294967290u);
	RUN("u -1", "%u", -1);
	RUN("u -42", "%u", -42);
	RUN("u INT_MIN", "%u", (unsigned int)-2147483648);
	RUN("u INT_MAX", "%u", 2147483647);
	RUN("u UINT_MAX", "%u", UINT_MAX);
	RUN("u mix 1", "value: %u %u %u", 0u, 42u, 12345u);
	RUN("u mix 2", "negatives: %u %u %u", -1, -2, -100);
	// ---------- %x TESTS ----------
	printf("-------- %%x TESTS --------\n");
	RUN("x zero", "%x", 0u);
	RUN("x small", "%x", 42u);
	RUN("x alphabet start", "%x", 10u);
	RUN("x alphabet end", "%x", 15u);
	RUN("x mid-range", "%x", 48879u);
	RUN("x max", "%x", 4294967295u);
	RUN("x near max", "%x", 4294967290u);
	RUN("x -1", "%x", (unsigned int)-1);
	RUN("x -42", "%x", (unsigned int)-42);
	RUN("x INT_MIN", "%x", (unsigned int)-2147483648);
	RUN("x INT_MAX", "%x", (unsigned int)2147483647);
	RUN("x UINT_MAX", "%x", UINT_MAX);
	RUN("x mix", "%x %x %x", 0u, 255u, 4095u);
	// ---------- %X TESTS ----------
	printf("-------- %%X TESTS --------\n");
	RUN("X zero", "%X", 0u);
	RUN("X small", "%X", 42u);
	RUN("X alphabet start", "%X", 10u);
	RUN("X alphabet end", "%X", 15u);
	RUN("X mid-range", "%X", 48879u);
	RUN("X max", "%X", 4294967295u);
	RUN("X near max", "%X", 4294967290u);
	RUN("X -1", "%X", (unsigned int)-1);
	RUN("X -42", "%X", (unsigned int)-42);
	RUN("X INT_MIN", "%X", (unsigned int)-2147483648);
	RUN("X INT_MAX", "%X", (unsigned int)2147483647);
	RUN("x UINT_MAX", "%X", UINT_MAX);
	RUN("X mix", "%X %X %X", 0u, 255u, 4095u);
	// ---------- %p TESTS ----------
	int a = 42;
	int arr[3] = {1,2,3};
	char *str = "hello";

	printf("-------- %%p TESTS --------\n");
	RUN("p NULL", "%p", (void *)0);
	RUN("p &a", "%p", (void *)&a);
	RUN("p arr", "%p", (void *)arr);
	RUN("p arr+1", "%p", (void *)(arr + 1));
	RUN("p str literal", "%p", (void *)"hi");
	RUN("p str variable", "%p", (void *)str);
	RUN("p mix", "%p %p %p", (void *)&a, (void *)arr, (void *)str);
	// ---------- %% TESTS ----------
	printf("-------- %% TESTS --------\n");
	RUN("percent alone", "%%");
	RUN("percent before text", "%% hello");
	RUN("percent after text", "hello %%");
	RUN("percent double", "%%%%");
	RUN("percent mixed", "start %% mid %% end");
	RUN("percent next to specs", "x=%x %% y=%u", 42u, 7u);
	printf("--------The weird ones --------\n");
	RUN("Trailing %", "abc%");
	RUN("Unknown format", "%z");
}


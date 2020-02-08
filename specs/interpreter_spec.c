#include "../minishell.h"
#include <string.h>
#include <stdio.h>

void	test_simple_arg(const char *arg, const char *expected_arg, int expected_ret)
{
		char *test;
		int ret;

		if (!(test = strdup(arg)))
		{ printf("Error: could't allocate memory for test.\n"); return ; }
		ret = clean_arg(test);
		if (ret == expected_ret && strcmp(test, expected_arg) == 0)
			printf(".");
		else if (ret == expected_ret && expected_ret == 1)
			printf(".");
		else
		{
			printf(
				"\nFor arg %s :\nexpected %d got %d\nexpected %s got %s\n",
				arg, expected_ret, ret, expected_arg, test
			);
		}
		free(test);
		return ;
}

int		main(void)
{
	// NO QUOTES
	test_simple_arg("unicorn", "unicorn", 0);	
	test_simple_arg("\\unicorn", "unicorn", 0);	
	test_simple_arg("\\unicorn\\", "unicorn", 0);	
	test_simple_arg("\\", "", 0);	
	test_simple_arg("\\uni\\\\corn", "uni\\corn", 0);	
	test_simple_arg("\\\\", "\\", 0);	
	test_simple_arg("\\u\\n\\i\\c\\o\\r\\n", "unicorn", 0);	
	test_simple_arg("\\\"", "\"", 0);	
	test_simple_arg("\\$PWD", "$PWD", 0);	
	test_simple_arg("\\\"uni\\'corn\\'\\\"", "\"uni'corn'\"", 0);	
	test_simple_arg("\\\"\\'\\\"\\'\\\"\\'", "\"'\"'\"'", 0);	
	test_simple_arg("\\\\\\\\\\\\\\\\", "\\\\\\\\", 0);	
	test_simple_arg("\"\"\"", "", 1);	
	test_simple_arg("\"", "", 1);	
	test_simple_arg("'", "", 1);	
	test_simple_arg("'''", "", 1);	
	test_simple_arg("\"\"unicorn\"", "", 1);	
	test_simple_arg("unicorn\"", "", 1);	
	test_simple_arg("uni\"corn", "", 1);	
	test_simple_arg("uni'", "", 1);	
	test_simple_arg("'unicorn''", "", 1);	
	test_simple_arg("unicorn\\\\\"", "", 1);	
	test_simple_arg("uni\\\\\"corn", "", 1);	
	test_simple_arg("uni\\'\\", "uni'", 0);	
	test_simple_arg("'uni\\corn'\\\\'", "", 1);	
	test_simple_arg("$PWD", "", 0);	
	test_simple_arg("$PWD", "", 0);	
	// DOUBLE QUOTES
	test_simple_arg("\"unicorn\"", "unicorn", 0);	
	test_simple_arg("\"\\unicorn\"", "\\unicorn", 0);	
	test_simple_arg("\"\\unicorn\\\"", "", 1);	
	test_simple_arg("\"\\\"", "", 1);	
	test_simple_arg("\"\\uni\\\\corn\"", "\\uni\\corn", 0);	
	test_simple_arg("\"\\\\\"", "\\", 0);	
	test_simple_arg("\"\\u\\n\\i\\c\\o\\r\\n\"", "\\u\\n\\i\\c\\o\\r\\n", 0);	
	test_simple_arg("\"\\\"\"", "\"", 0);	
	test_simple_arg("\"\\$PWD\"", "$PWD", 0);	
	test_simple_arg("\"\\\"uni\\'corn\\'\\\"\"", "\"uni\\'corn\\'\"", 0);	
	test_simple_arg("\"\\\"\\'\\\"\\'\\\"\\'\"", "\"\\'\"\\'\"\\'", 0);	
	test_simple_arg("\"\\\\\\\\\\\\\\\\\"", "\\\\\\\\", 0);	
	test_simple_arg("\"          \"", "          ", 0);	
	test_simple_arg("\"\"\"\"\"", "", 1);
	test_simple_arg("\"\\\"\"", "\"", 0);
	test_simple_arg("\"\\\"\\\"\"", "\"\"", 0);
	test_simple_arg("\"'\"", "'", 0);	
	test_simple_arg("\"'''\"", "'''", 0);	
	test_simple_arg("\"\"\"unicorn\"\"", "", 1);	
	test_simple_arg("\"unicorn\"\"", "", 1);	
	test_simple_arg("\"uni\"corn\"", "", 1);	
	test_simple_arg("\"uni'\"", "uni'", 0);	
	test_simple_arg("\"'unicorn''\"", "'unicorn''", 0);	
	test_simple_arg("\"unicorn\\\\\"\"", "", 1);
	test_simple_arg("\"uni\\\\\"corn\"", "", 1);	
	test_simple_arg("\"uni\\'\\\"", "", 1);	
	test_simple_arg("\"uni\\'\"", "uni\\'", 0);	
	test_simple_arg("\"'uni\\corn'\\\\'\"", "'uni\\corn'\\'", 0);	
	// SINGLE QUOTES
	test_simple_arg("'unicorn'", "unicorn", 0);	
	test_simple_arg("'\\unicorn'", "\\unicorn", 0);	
	test_simple_arg("'\\unicorn\\'", "\\unicorn\\", 0);	
	test_simple_arg("'\\uni\\\\corn'", "\\uni\\\\corn", 0);	
	test_simple_arg("'\\$PWD'", "\\$PWD", 0);
	test_simple_arg("'\\\"uni\\'corn\\'\\\"'", "", 1);	
	test_simple_arg("'\\\"\\'\\\"\\'\\\"\\''", "", 1);	
	test_simple_arg("'\\\\\\\\\\\\\\\\'", "\\\\\\\\\\\\\\\\", 0);	
	test_simple_arg("'''", "", 1);	
	test_simple_arg("'''''", "", 1);	
	test_simple_arg("'''unicorn", "", 1);	
	test_simple_arg("'''unicorn'''unicorn''unicorn'unicorn''", "", 1);	
	test_simple_arg("'\\''", "", 1);	
	test_simple_arg("''\\'\\\\\\\\", "'\\\\", 0);
	test_simple_arg("''\\'\\\\\\", "'\\", 0);
	printf("\n");
}

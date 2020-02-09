#include "../minishell.h"
#include <string.h>
#include <stdio.h>

void	test_simple_arg(const char *arg, const char *expected_arg, int expected_ret)
{
		char *test;
		int ret;

		if (!(test = strdup(arg)))
		{ printf("Error: could't allocate memory for test.\n"); return ; }
		ret = clean_arg(&test);
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

t_env	g_env = NULL;
t_ret	g_ret = 0;

int		main(void)
{
	// Prepare test environement
	if (!(g_env = (char**)malloc(sizeof(char*) * 6)))
		return (1);
	g_env[0] = strdup("VAR=spaceship");
	g_env[1] = strdup("HOME=Users/alien");
	g_env[2] = strdup("USER=alien");
	g_env[3] = strdup("TRAP1='unclo\\se?hey;\"");
	g_env[4] = strdup("TRAP2=$VAR$USER$TRAP1$");
	g_env[5] = NULL;

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
	test_simple_arg("\"unc'", "", 1);
	test_simple_arg("'unc\"", "", 1);
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
	test_simple_arg("$?", "0", 0);	
	test_simple_arg("$?$USER", "0alien", 0);	
	test_simple_arg("$USER", "alien", 0);	
	test_simple_arg("$VAR", "spaceship", 0);	
	test_simple_arg("$HOME", "Users/alien", 0);	
	test_simple_arg("$\\VAR", "$VAR", 0);	
	test_simple_arg("$=VAR", "$=VAR", 0);
	test_simple_arg("$\\\\VAR", "$\\VAR", 0);	
	test_simple_arg("$HO,ME", ",ME", 0);	
	test_simple_arg("$VAR$HOME$USER", "spaceshipUsers/alienalien", 0);	
	test_simple_arg("$", "$", 0);
	test_simple_arg("$NOTAVAR", "", 0);	
	test_simple_arg("$NOTAVAR,", ",", 0);
	test_simple_arg("abcde$NOTAVAR", "abcde", 0);	
	test_simple_arg("abcde$NOTAVAR,", "abcde,", 0);
	test_simple_arg("wowa$VARcool", "wowa", 0);	
	test_simple_arg("abcde$VAR,", "abcdespaceship,", 0);
	test_simple_arg("$USER\"", "", 1);
	test_simple_arg("$USER'", "", 1);
	test_simple_arg("$TRAP1", "'unclo\\se?hey;\"", 0);	
	test_simple_arg("\"$TRAP1", "", 1);	
	test_simple_arg("$TRAP2", "$VAR$USER$TRAP1$", 0);	
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
	test_simple_arg("\"$NOTAVAR\"", "", 0);	
	test_simple_arg("\"$NOTAVAR, , ,\"", ", , ,", 0);
	test_simple_arg("\"abcde$NOTAVAR\"", "abcde", 0);	
	test_simple_arg("\"abcde$NOTAVAR, , ,\"", "abcde, , ,", 0);
	test_simple_arg("\"wowa$VARcool\"", "wowa", 0);	
	test_simple_arg("\"abcde$VAR,\"", "abcdespaceship,", 0);
	test_simple_arg("\"$USER\"", "alien", 0);	
	test_simple_arg("\"$?\"", "0", 0);	
	test_simple_arg("\"$?$USER\"", "0alien", 0);	
	test_simple_arg("\"$VAR\"", "spaceship", 0);	
	test_simple_arg("\"$HOME\"", "Users/alien", 0);	
	test_simple_arg("\"$\\VAR\"", "$\\VAR", 0);	
	test_simple_arg("\"$=VAR\"", "$=VAR", 0);	
	test_simple_arg("\"$\\\\VAR\"", "$\\VAR", 0);	
	test_simple_arg("\"$HO,ME\"", ",ME", 0);	
	test_simple_arg("\"$VAR$HOME$USER\"", "spaceshipUsers/alienalien", 0);	
	test_simple_arg("\"var=$VAR,home=$HOME,user=$USER\"", "var=spaceship,home=Users/alien,user=alien", 0);	
	test_simple_arg("\"$\"", "$", 0);
	test_simple_arg("\"$USER", "", 1);
	test_simple_arg("\"$USER'", "", 1);
	test_simple_arg("\"'$USER'\"", "'alien'", 0);
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
	test_simple_arg("'$VAR'", "$VAR", 0);	
	test_simple_arg("'$?'", "$?", 0);	
	test_simple_arg("'$HOME'", "$HOME", 0);	
	test_simple_arg("'\"$HOME\"'", "\"$HOME\"", 0);	
	// NQ && SQ && DQ
	test_simple_arg("", "", 0);
	test_simple_arg("'$USER'\" var content is \"$USER.", "$USER var content is alien.", 0);
	test_simple_arg("$FAIL'          '\"          \"", "                    ", 0);
	test_simple_arg("'a'\"l\"i\"e\"\"n\"'s''&''u'\"n\"\"i\"cor'n'\"s\"", "aliens&unicorns", 0);
	test_simple_arg("$VAR$'a'\"l\"i\"e\"\"n\"'s''&''u'\"n\"\"i\"cor'n'\"s\"", "spaceshipaliens&unicorns", 0);
	test_simple_arg("$USER$", "alien$", 0);
	test_simple_arg("\"$USER$\"", "alien$", 0);
	test_simple_arg("$USER$''", "alien", 0);
	test_simple_arg("\"$USER$''\"", "alien$''", 0);
	test_simple_arg("$''", "", 0);
	test_simple_arg("$\\'", "$'", 0);
	test_simple_arg("$''wtf", "wtf", 0);
	test_simple_arg("$\"\"", "", 0);
	test_simple_arg("$\\\"", "$\"", 0);
	test_simple_arg("$\"\"wtf", "wtf", 0);
	g_ret = 255;
	test_simple_arg("'Last cmd returned '$?\" $??\"", "Last cmd returned 255 255?", 0);

	printf("\n");

	free(g_env[0]);
	free(g_env[1]);	
	free(g_env[2]);
	free(g_env[3]);
	free(g_env[4]);
	free(g_env[5]);
}

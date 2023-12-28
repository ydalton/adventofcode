#include <glib.h>
#include <glib/gprintf.h>

#include "../aoc.h"

int main(void)
{
	GError *err = NULL;
	char *contents;
	char **split_str;
	size_t len = 0;
	size_t i, j;
	int first = 0, last;
	char c, *str;
	int converted, sum;


	g_file_get_contents(INPUT_FILE, &contents, NULL, &err);
	if(err != NULL) {
		g_fprintf(stderr, "%s\n", err->message);
		g_error_free(err);
		return EXIT_FAILURE;
	}

	/* split string into file lines */
	split_str = g_strsplit(contents, "\n", -1);
	g_free(contents);

	while(split_str[++len]);
	len--;

	for(i = 0; i < len; i++) {
		first = 0;
		last = 0;
		str = split_str[i];
		for(j = 0; j < strlen(str); j++) {
			c = str[j];
			if(g_ascii_isdigit(c)) {
				converted = g_ascii_digit_value(c);
				if(!first)
					first = converted;
				else 
					last = converted;
				if(!last)
					last = first;
			}
		}
		g_assert(first != 0);
		printf("%d%d\n", first, last);
		sum += 10 * first + last;
	}

	g_printf("%d\n", sum);
}

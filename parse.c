/*Parse for joker
 * 
 *Accepts the buffer separating args by spaces and returns the arg
 * specified by the int arg position
 *
 */

#include <stdio.h>
#include <stdlib.h>
//char* parse (char* buf, int arg);
char* args[1024] = {'\0'};

char* parse (char* buf, int arg) {
	int letter_count = 0;
	int buf_count = 0;
	int string_count = 0;
	char *string = calloc(1024, sizeof(char));
	int done = -1;

	while(buf[buf_count] != '\0' && done != 1) {	
		if ( buf[buf_count] == ' ') {
			if (string_count == arg) {
				done = 1;
			} else {
				int i = 0;
				while(string[i] != '\0') {
					string[i] = '\0';
					i++;
				}
				letter_count = 0;
				string_count++;
			}
		} else {
			string[letter_count] = buf[buf_count];
			letter_count++;
		}
		buf_count++;
	}
	return string;
}

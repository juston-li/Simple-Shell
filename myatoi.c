/*parser to help joker parse command args
 *
 *Only handles intergers else returns -1
 *
 */

#include <stdio.h>

int myatoi (char *string) {
	int total = 0;
	int count = 0;
	while(string[count] != '\0') {
		if(string[count]<'0' || string[count]>'9'){
			return -1;
		}		
		int value = string[count] - '0';
		total = total*10;
		total = total + value;
		count++;
	}
	return total;
}

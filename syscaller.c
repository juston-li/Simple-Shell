/* 
 *Credit:
 *http://macboypro.wordpress.com/2009/05/15/adding-a-custom-system-call-to-the-linux-os/
*/

#include <sys/syscall.h>
#include <unistd.h>
#include <stdio.h>

#define __NR_mysyscall       543

int mysyscall() {
   return (int) syscall(__NR_mysyscall);
};

main () {
   printf("return code %d\n", mysyscall());
}

#include <stdio.h>
#include <unistd.h>
int glo_init_data = 99;
int glo_noninit_data;
void func(unsigned long number) {
    unsigned long local_data = number;
    printf("Process ID=%d\n", getpid());
    printf ("Addresses of the process :\n");
    printf (" 1. glo_init_data =%p\n", &glo_init_data );
    printf (" 2. glo_noninit_data =%p\n", & glo_noninit_data );
    printf (" 3. print func ( ) =%p\n", & func);
    printf (" 4. local data =%p\n", & local_data );
}

int main() {
    func(10);
    while (1)
    usleep(0);
}
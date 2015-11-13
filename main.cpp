#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <string>

#include <signal.h>
#include <sys/types.h>
#include <unistd.h>

using std::cout;
using std::endl;
using std::string;

void _sigusr1(int sig);
void _sigusr2(int sig);

int main(void) {
    signal(SIGUSR1, _sigusr1);
    signal(SIGUSR2, _sigusr2);

    for(;;) {
        cout << "?" << endl;
        sleep(1);
    }

    return EXIT_SUCCESS;
}

void _sigusr1(int sig) {
    cout << "Bonjour" << endl;
    signal(SIGUSR1, SIG_IGN);
}

void _sigusr2(int sig) {
    cout << "Bonsoir" << endl;
}




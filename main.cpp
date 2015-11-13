#include <iostream>
#include <cstdlib>
#include <cstdio>

#include <string>

#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

using std::cout;
using std::endl;
using std::string;

void _sigint(int sig);
void _sigint2(int sig);
void _sigalrm(int sig);

int main(void) {

    signal(SIGINT, _sigint);
    signal(SIGALRM, _sigalrm);

    for(;;) {
        cout << "." << endl;
        sleep(1);
    }

    return EXIT_SUCCESS;
}

void _sigint(int sig) {
    cout << "Refaite la combinaison Ctrl-C avant 3 secondes pour quitter" << endl;
    signal(SIGINT, _sigint2);
    alarm(3);
}

void _sigint2(int sig) {
    cout << "Fin du programme" << endl;
    exit(EXIT_SUCCESS);
}

void _sigalrm(int sig) {
    cout << "Les 3 secondes sont épuisées, le programme n'est pas terminé" << endl;
    signal(SIGINT, _sigint);
}

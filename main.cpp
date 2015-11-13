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

void _sigusr1(int sig);

int main(void) {

    int status;
    pid_t pid;

    signal(SIGUSR1, _sigusr1);

    pid = fork();

    switch(pid) {
    case -1: {
            perror("fork");
            break;
        }

    case 0: {
            cout << "Enfant créé (" << getpid() << ")" << endl;

            cout << "Attente de 3 secondes..." << endl;
            sleep(3);

            cout << "Envoie du signal SIGUSR1 au père (" << getppid() << ")" << endl;
            kill(getppid(), SIGUSR1);
            exit(EXIT_SUCCESS);
            break;
        }

    default: {
            cout << "Parent (" << getpid() << ")" << endl;
            pause();

            do {
                cout << "Attente de la fin du processus fils... " << endl;
                waitpid(pid, &status, WUNTRACED);
            } while(!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }

    cout << "Programme terminé !" << endl;
    return EXIT_SUCCESS;
}

void _sigusr1(int sig) {
    cout << "Le père a reçu le signal SIGUSR1" << endl;
}

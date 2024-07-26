/*
* Very basic example of Finite-State Machine
* https://en.wikipedia.org/wiki/Finite-state_machine
*/
#include <stdio.h>
#include <string.h>

enum State {
    Locked,
    Unlocked
};

enum Event {
    Push,
    Coin
};

enum State nextState(enum State state,enum Event event){
    if ( state == Locked  ) {
        if (event == Push) return Locked;
        if (event == Coin) return Unlocked;
    }
    if ( state == Unlocked ) {
        if (event == Push) return Locked;
        if (event == Coin) return Unlocked;
    }

    return Locked;
}

int main()
{
    char input[10], output[10];
    enum State state = Locked;

    do {
        printf("> ");
        fflush(stdout);
        scanf("%s", input);

        if (strcmp(input, "quit") == 0) break;
        if (strcmp(input, "push") == 0) state = nextState(state, Push);
        if (strcmp(input, "coin") == 0) state = nextState(state, Coin);

        state == Locked ? strcpy(output, "Locked"): strcpy(output,"Unlocked");

        printf("State: %s\n", output);

    } while ( strcmp(input, "quit") != 0 );

    return 0;
}

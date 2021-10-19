#ifndef CH04_CALC
#define CH04_CALC

/** text, string, character */
#define NUMBER '0' // found a num

int _getch (void);   // get next character
void _ungetch (int); // push back
int _getop (char[]); // get next op or num

/** statck */
void _push (double);
double _pop (void);

#endif /* CH04_CALC */

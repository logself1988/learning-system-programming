int a(int *p);

int main (int argc, char **argv)
{
    int *p = 0; /* null pointer */
    return a(p);
}

int a(int *p)
{
    int y = *p;
    return y;
}

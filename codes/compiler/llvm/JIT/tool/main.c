// $ clang -c main.c -o main.o
// $ clang -c add.c -o add.o
// $ clang -c sub.c -o sub.o
// $ llvm-rtdyld -execute -entry=main main.o add.o sub.o; echo $?
// loaded 'main' at: 0x7f5ad1a8a000
// 5


int add(int a, int b);
int sub(int a, int b);

int main() 
{
    return sub(add(3, 4), 2);
}
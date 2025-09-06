build:
    gcc main.c -o app.exe

run:
    ./app.exe

valgrind:
    valgrind -s --tool=memcheck --leak-check=yes --track-origins=yes ./app.exe

run_redirect:
    ./app.exe < testing.txt

run_test:
    ./app.exe -t


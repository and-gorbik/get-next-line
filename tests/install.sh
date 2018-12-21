cd .. && pwd # get-next-line
git clone https://github.com/and-gorbik/libft
cd - && pwd # tests
cd ../libft && pwd # libft
echo "building libft.."
make
make clean
cd - && pwd # tests
echo "compiling a program.."
make
echo "use ./a.out to start"
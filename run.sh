if [[ "$OSTYPE" == "linux-gnu"* ]]; then
        # Linux

	gcc main.cpp -std=c++11 -lstdc++ && ./a.out
elif [[ "$OSTYPE" == "darwin"* ]]; then
        # Mac OSX

	clang++ -std=c++11 main.cpp && ./a.out
fi

g++ -std=c++11 test.cpp -o test
# ./test ./inputs/private_case_3.in ./jy/private_case_3.out
# g++ -std=c++11 src/validate2.cpp -o check_cycle
# ./check_cycle ./inputs/private_case_3.in ./jy/private_case_3.out
./test ./inputs/public_case_3.in ./jy/public_case_3.out
g++ -std=c++11 src/validate2.cpp -o check_cycle
g++ -std=c++11 src/validate.cpp -o check_connect
./check_cycle ./inputs/public_case_3.in ./jy/public_case_3.out
./check_connect ./inputs/public_case_3.in ./jy/public_case_3.out
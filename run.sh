clang++ main.cpp -D NAMESPACE=ft -I ./ && ./a.out > ft
clang++ main.cpp -D NAMESPACE=std -I ./ && ./a.out > std

diff ft std
# rm -rf ft std
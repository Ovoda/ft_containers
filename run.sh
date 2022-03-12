clang++ main.cpp -D NAMESPACE=ft -I ./ && ./exec > ft
clang++ main.cpp -D NAMESPACE=std -I ./ && ./exec > std

diff ft std
rm -rf ft std
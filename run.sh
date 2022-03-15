clang++ main.cpp -D TESTED_NAMESPACE=ft -I ./ && ./exec > ft
clang++ main.cpp -D TESTED_NAMESPACE=std -I ./ && ./exec > std

# diff ft std
# rm -rf ft std
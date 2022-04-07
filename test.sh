clang++ main.cpp -I./ && ./a.out > ft
clang++ main.cpp -I./ -D STD=1 && ./a.out > std
diff ft std

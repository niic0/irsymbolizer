compile:
	clang -O3 -g -Wall dummy_driver.c -o dummy_driver
	clang -O3 -g -S -emit-llvm dummy_driver.c -o dummy_driver.ll

clean:
	rm dummy_driver

run: compile
	./dummy_driver 2048

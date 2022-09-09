CC = gcc

.PHONY: vm

vm:
	gcc vm.c -o vm -Wextra
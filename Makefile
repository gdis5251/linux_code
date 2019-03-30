1.proc:1.proc.c
	gcc 1.proc.c -o 1.proc

.PHONY:clean
clean:
	rm -rf 1.proc

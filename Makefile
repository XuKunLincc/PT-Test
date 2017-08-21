CC = arm-none-linux-gnueabi-gcc
FLAG = -m32

arm_all:
	$(CC) -D VOLATILE main-arm.c -o volatile
	$(CC) main-arm.c -o novolatile

ia86_all:
	$(CC) $(FLAG) -D VOLATILE main-ia86.c -o volatile
	$(CC) $(FLAG) main-ia86.c -o novolatile

clean:
	rm *.o novolatile volatile *.s *.S

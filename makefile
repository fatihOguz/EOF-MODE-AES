
main: eof.h eofmake.c eof_yedek.c 
	gcc eof_yedek.c -o eof 
	./eof key.txt sbox.txt invSbox.txt IV.txt plainText1.txt plainText2.txt plainText3.txt 

clean: 
	rm main
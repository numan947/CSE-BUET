if flex -o 1305043.c 1305043.l;then
	if g++ -o 1305043.out 1305043.c;then
		./1305043.out input1.txt
	fi
fi

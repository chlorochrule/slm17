all: pp slm
pp: pp2017.c
	gcc pp2017.c -o pp -lm
	# ./pp bigram.model -bi 28 < corpus/kokoro.num
	# ./pp trigram.model -tri 24 28 < corpus/kokoro.num

slm: slm17.cpp
	g++ -std=gnu++11 -o slm slm17.cpp
	# ./slm < corpus/neko.num > bigram.model
	# ./slm < corpus/neko.num > trigram.model

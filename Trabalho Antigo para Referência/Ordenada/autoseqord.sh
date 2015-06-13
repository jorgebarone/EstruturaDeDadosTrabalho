#!/bin/bash
for ((i = 100; i <=30000;i += 100))
	do 
		gcc gerador.c -o gerador -D N=$i
		./gerador > entrada.txt
		gcc trabalhoISEQUENCIALORDENADA.c -o trabalhoISEQUENCIALORDENADA -D NUM_MAX_ALUNOS=$i
		./trabalhoISEQUENCIALORDENADA < entrada.txt
		echo "$i"
	done

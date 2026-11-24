programme.exe:main.o sauvegarde.o competition.o match.o
	gcc -o programme.exe main.o sauvegarde.o competition.o match.o 

main.o:main.c sauvegarde.h competition.h match.h
	gcc -c main.c

sauvegarde.o:sauvegarde.c sauvegarde.h
	gcc -c sauvegarde.c

match.o:match.c match.h
	gcc -c match.c

competition.o: competition.c competition.h
	gcc -c competition.c 
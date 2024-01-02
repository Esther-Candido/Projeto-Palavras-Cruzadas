#
# Identificação do Formando
#
############################# Makefile ##########################
CC=gcc
CFLAGS=-Wall

######Alterar Dependências e Objetos #####
DEPS = ui.h pc.h#ficheiros .h - Colocar todos
OBJ = main.o ui.o pc.o#objetos (.o). Um por ficheiro .c da Aplicação
##########################################

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

#Mudar o nome de app para o nome da aplicação pretendido
palavras: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o
	rm -rf palavras

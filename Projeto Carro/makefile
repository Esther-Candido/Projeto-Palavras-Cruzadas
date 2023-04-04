#
# Make para uma aplicação de gestão de carros
#
############################# Makefile ##########################
CC=gcc
CFLAGS=-Wall

######Alterar Dependências e Objetos #####
DEPS = ui.h menu.h carros.h #ficheiros .h - Colocar todos
OBJ = main.o ui.o menu.o carros.o #objetos (.o). Um por ficheiro .c da Aplicação
##########################################

%.o: %.c $(DEPS)
	$(CC) $(CFLAGS) -c -o $@ $<

#Mudar o nome de app para o nome da aplicação pretendido
gestor_carros: $(OBJ)
	gcc $(CFLAGS) -o $@ $^

clean:
	rm -rf *.o 
	rm -rf gestor_carros


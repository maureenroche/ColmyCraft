CC       =  gcc
CFLAGS   = -Wall -O2 -g
LIB      = -lSDL -lSDL_image -lGLU -lGL -lGLUT -lm  
INCLUDES = 

OBJ      = obj/dessin.o obj/fonctionsGL.o obj/fonctionsInit.o obj/fonctionsJeu.o obj/lectureEcriture.o obj/hovercraft.o 
RM       = rm -f
BIN      = hovercraft
DIRNAME  = $(shell basename $$PWD)
BACKUP   = $(shell date +`basename $$PWD`-%m.%d.%H.%M.tgz)
STDNAME  = $(DIRNAME).tgz

all : $(BIN)

$(BIN) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIB) $(INCLUDES)  -o $(BIN)
	@echo "--------------------------------------------------------------"
	@echo "                 to execute type: ./$(BIN) &"
	@echo "--------------------------------------------------------------"

hovercraft.o : hovercraft.c
	@echo "compile hovercraft"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

dessin.o : dessin.c
	@echo "compile dessin"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

fonctionsGL.o : fonctionsGL.c
	@echo "compile fonctionsGL"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

fonctionsInit.o : fonctionsInit.c
	@echo "compile fonctionsInit"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

fonctionsJeu.o : fonctionsJeu.c
	@echo "compile fonctionsJeu"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

lectureEcriture.o : lectureEcriture.c
	@echo "compile lectureEcriture"
	$(CC) $(CFLAGS) -c $<  
	@echo "done..."

clean :	
	@echo "**************************"
	@echo "CLEAN"
	@echo "**************************"
	$(RM) *~ $(OBJ) $(BIN) 

tar : clean 
	@echo "**************************"
	@echo "TAR"
	@echo "**************************"
	cd .. && tar cvfz $(BACKUP) $(DIRNAME)




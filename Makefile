CC       =  gcc
CFLAGS   = -Wall -O2 -std=c99 -g
LIB      = -lSDL -lSDL_image -lGLU -lGL -lglut -lm
INCLUDES =

OBJ      = dessin.o fonctionsGL.o fonctionsInit.o fonctionsJeu.o lectureEcriture.o audio.o hovercraft.o
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

dessin.o : src/dessin.c
	@echo "compile dessin"
	$(CC) $(CFLAGS) -c $<
	@echo "done..."

fonctionsGL.o : src/fonctionsGL.c
	@echo "compile fonctionsGL"
	$(CC) $(CFLAGS) -c $<
	@echo "done..."

fonctionsInit.o : src/fonctionsInit.c
	@echo "compile fonctionsInit"
	$(CC) $(CFLAGS) -c $<
	@echo "done..."

fonctionsJeu.o : src/fonctionsJeu.c
	@echo "compile fonctionsJeu"
	$(CC) $(CFLAGS) -c $<
	@echo "done..."

lectureEcriture.o : src/lectureEcriture.c
	@echo "compile lectureEcriture"
	$(CC) $(CFLAGS) -c $<
	@echo "done..."

audio.o : src/audio.c
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

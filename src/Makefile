SHELL='bash'
#
# Bridges - PSC
#
# Intel Compilers are loaded by default
# You will need to specifically switch to GNU Modules
# With with `modules.sh`
#

CC = g++
CFLAGS = -O3
LIBS = -IBox2d -IParticle2D -ISimulation

COMMON=Simulation/common
SERIAL=Simulation/serial
BOX2D=Box2D/Box2D
PARTICLE2D=Particle2D/Particle2D
MAIN=main

TARGETS = main

all: $(TARGETS)

main: ${MAIN}.o ${COMMON}.o ${SERIAL}.o ${BOX2D}.o ${PARTICLE2D}.o
	$(CC) -o ${MAIN} $(LIBS) ${MAIN}.o ${COMMON}.o ${SERIAL}.o ${BOX2D}.o ${PARTICLE2D}.o

main.o: ${MAIN}.cpp 
	$(CC) -c $(CFLAGS) ${LIBS} ${MAIN}.cpp -o ${MAIN}.o
common.o: ${COMMON}.cpp ${COMMON}.h
	$(CC) -c $(CFLAGS) ${LIBS} ${COMMON}.cpp -o ${COMMON}.o
serial.o: ${SERIAL}.cpp ${SERIAL}.h
	$(CC) -c $(CFLAGS) ${LIBS} ${SERIAL}.cpp -o ${SERIAL}.o
Box2D.o: ${BOX2D}.cpp ${BOX2D}.h
	$(CC) -c $(CFLAGS) ${LIBS} ${BOX2D}.cpp -o ${BOX2D}.o
Particle2D.o: ${PARTICLE2D}.cpp ${PARTICLE2D}.h
	$(CC) -c $(CFLAGS) ${LIBS} ${PARTICLE2D}.cpp -o ${PARTICLE2D}.o


clean:
	rm -f $(TARGETS) ${MAIN}.o ${COMMON}.o ${SERIAL}.o ${BOX2D}.o ${PARTICLE2D}.o

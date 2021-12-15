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
OPENGLFLAGS= -lglut -lGLU -lGL -lstdc++ 
LIBS = -I. -ISimulation -IBox2d -IParticle2D -ICircle2D -IEllipse2D -IRegularPolygon2D -IGraphicObject2D

MAIN=mainGLUT
COMMON=Simulation/common
SERIAL=Simulation/serial
BOX2D=Box2D/Box2D
PARTICLE2D=Particle2D/Particle2D
CIRCLE2D=Circle2D/Circle2D
ELLIPSE2D=Ellipse2D/Ellipse2D
REGULARPOLYGON2D=RegularPolygon2D/RegularPolygon2D
GRAPHICOBJECT2D=GraphicObject2D/GraphicObject2D
EXEC=main

TARGETS = main

all: $(TARGETS)

main: mainGLUT.o common.o serial.o Box2D.o Particle2D.o Circle2D.o Ellipse2D.o RegularPolygon2D.o GraphicObject2D.o
	$(CC) -o ${EXEC} $(CFLAGS) ${OPENGLFLAGS} $(LIBS) ${MAIN}.o ${COMMON}.o ${SERIAL}.o ${BOX2D}.o ${PARTICLE2D}.o ${CIRCLE2D}.o ${ELLIPSE2D}.o ${REGULARPOLYGON2D}.o ${GRAPHICOBJECT2D}.o

mainGLUT.o: ${MAIN}.cpp 
	$(CC) -c $(CFLAGS) ${OPENGLFLAGS} ${LIBS} ${MAIN}.cpp -o ${MAIN}.o
common.o: ${COMMON}.cpp ${COMMON}.h
	$(CC) -c $(CFLAGS) ${LIBS} ${COMMON}.cpp -o ${COMMON}.o
serial.o: ${SERIAL}.cpp ${SERIAL}.h
	$(CC) -c $(CFLAGS) ${LIBS} ${SERIAL}.cpp -o ${SERIAL}.o
Box2D.o: ${BOX2D}.cpp ${BOX2D}.h
	$(CC) -c $(CFLAGS) ${OPENGLFLAGS} ${LIBS} ${BOX2D}.cpp -o ${BOX2D}.o
Particle2D.o: ${PARTICLE2D}.cpp ${PARTICLE2D}.h
	$(CC) -c $(CFLAGS) ${OPENGLFLAGS} ${LIBS} ${PARTICLE2D}.cpp -o ${PARTICLE2D}.o
Circle2D.o: ${CIRCLE2D}.cpp ${CIRCLE2D}.h
	$(CC) -c $(CFLAGS) ${OPENGLFLAGS} ${LIBS} ${CIRCLE2D}.cpp -o ${CIRCLE2D}.o
Ellipse2D.o: ${ELLIPSE2D}.cpp ${ELLIPSE2D}.h
	$(CC) -c $(CFLAGS) ${OPENGLFLAGS} ${LIBS} ${ELLIPSE2D}.cpp -o ${ELLIPSE2D}.o
RegularPolygon2D.o: ${REGULARPOLYGON2D}.cpp ${REGULARPOLYGON2D}.h
	$(CC) -c $(CFLAGS) ${OPENGLFLAGS} ${LIBS} ${REGULARPOLYGON2D}.cpp -o ${REGULARPOLYGON2D}.o
GraphicObject2D.o: ${GRAPHICOBJECT2D}.cpp ${GRAPHICOBJECT2D}.h
	$(CC) -c $(CFLAGS) ${OPENGLFLAGS} ${LIBS} ${GRAPHICOBJECT2D}.cpp -o ${GRAPHICOBJECT2D}.o

clean:
	rm -f $(TARGETS) ${MAIN}.o ${COMMON}.o ${SERIAL}.o ${BOX2D}.o ${PARTICLE2D}.o ${CIRCLE2D}.o ${ELLIPSE2D}.o ${REGULARPOLYGON2D}.o ${GRAPHICOBJECT2D}.o

SHELL='bash'
#
# Bridges - PSC
#
# Intel Compilers are loaded by default
# You will need to specifically switch to GNU Modules
# With with `modules.sh`
#

choose:
	@echo make linux or make mac

CC = g++
CFLAGS = -O3 
OPENGLFLAGS= -lglut -lGLU -lGL -lstdc++ 
LIBS = -I. -ISimulation -IBox2D -IParticle2D -ICircle2D -ISquare2D -IRegularPolygon2D -IPolygon2D -IGraphicObject2D
MACFLAGS = -framework OpenGL -framework GLUT -framework glut -lstdc++


MAIN=mainGLUT
COMMON=Simulation/common
SERIAL=Simulation/serial
BOX2D=Box2D/Box2D
PARTICLE2D=Particle2D/Particle2D
CIRCLE2D=Circle2D/Circle2D
SQUARE2D=Square2D/Square2D
REGULARPOLYGON2D=RegularPolygon2D/RegularPolygon2D
POLYGON2D=Polygon2D/Polygon2D
GRAPHICOBJECT2D=GraphicObject2D/GraphicObject2D
EXEC=main

LTARGETS=main
MTARGETS=mmain

linux: $(LTARGETS)

main: mainGLUT.o common.o serial.o Box2D.o Particle2D.o Circle2D.o Square2D.o RegularPolygon2D.o Polygon2D.o GraphicObject2D.o 
	$(CC) -o ${EXEC} $(CFLAGS) ${OPENGLFLAGS} $(LIBS) ${MAIN}.o ${COMMON}.o ${SERIAL}.o ${BOX2D}.o ${PARTICLE2D}.o ${CIRCLE2D}.o ${SQUARE2D}.o ${REGULARPOLYGON2D}.o ${POLYGON2D}.o ${GRAPHICOBJECT2D}.o

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
Square2D.o: ${SQUARE2D}.cpp ${SQUARE2D}.h
	$(CC) -c $(CFLAGS) ${OPENGLFLAGS} ${LIBS} ${SQUARE2D}.cpp -o ${SQUARE2D}.o
RegularPolygon2D.o: ${REGULARPOLYGON2D}.cpp ${REGULARPOLYGON2D}.h
	$(CC) -c $(CFLAGS) ${OPENGLFLAGS} ${LIBS} ${REGULARPOLYGON2D}.cpp -o ${REGULARPOLYGON2D}.o
Polygon2D.o: ${POLYGON2D}.cpp ${POLYGON2D}.h
	$(CC) -c $(CFLAGS) ${OPENGLFLAGS} ${LIBS} ${POLYGON2D}.cpp -o ${POLYGON2D}.o
GraphicObject2D.o: ${GRAPHICOBJECT2D}.cpp ${GRAPHICOBJECT2D}.h
	$(CC) -c $(CFLAGS) ${OPENGLFLAGS} ${LIBS} ${GRAPHICOBJECT2D}.cpp -o ${GRAPHICOBJECT2D}.o


# MAC OS targets
mac: $(MTARGETS)

mmain: mmainGLUT.o mcommon.o mserial.o mBox2D.o mParticle2D.o mCircle2D.o mSquare2D.o mRegularPolygon2D.o mPolygon2D.o mGraphicObject2D.o 
	$(CC) -o ${EXEC} $(CFLAGS) ${MACFLAGS} $(LIBS) ${MAIN}.o ${COMMON}.o ${SERIAL}.o ${BOX2D}.o ${PARTICLE2D}.o ${CIRCLE2D}.o ${SQUARE2D}.o ${REGULARPOLYGON2D}.o ${POLYGON2D}.o ${GRAPHICOBJECT2D}.o

mmainGLUT.o: ${MAIN}.cpp 
	$(CC) -c $(CFLAGS) ${MACFLAGS} ${LIBS} ${MAIN}.cpp -o ${MAIN}.o
mcommon.o: ${COMMON}.cpp ${COMMON}.h
	$(CC) -c $(CFLAGS) ${LIBS} ${COMMON}.cpp -o ${COMMON}.o
mserial.o: ${SERIAL}.cpp ${SERIAL}.h
	$(CC) -c $(CFLAGS) ${LIBS} ${SERIAL}.cpp -o ${SERIAL}.o
mBox2D.o: ${BOX2D}.cpp ${BOX2D}.h
	$(CC) -c $(CFLAGS) ${MACFLAGS} ${LIBS} ${BOX2D}.cpp -o ${BOX2D}.o
mParticle2D.o: ${PARTICLE2D}.cpp ${PARTICLE2D}.h
	$(CC) -c $(CFLAGS) ${MACFLAGS} ${LIBS} ${PARTICLE2D}.cpp -o ${PARTICLE2D}.o
mCircle2D.o: ${CIRCLE2D}.cpp ${CIRCLE2D}.h
	$(CC) -c $(CFLAGS) ${MACFLAGS} ${LIBS} ${CIRCLE2D}.cpp -o ${CIRCLE2D}.o
mSquare2D.o: ${SQUARE2D}.cpp ${SQUARE2D}.h
	$(CC) -c $(CFLAGS) ${MACFLAGS} ${LIBS} ${SQUARE2D}.cpp -o ${SQUARE2D}.o
mRegularPolygon2D.o: ${REGULARPOLYGON2D}.cpp ${REGULARPOLYGON2D}.h
	$(CC) -c $(CFLAGS) ${MACFLAGS} ${LIBS} ${REGULARPOLYGON2D}.cpp -o ${REGULARPOLYGON2D}.o
mPolygon2D.o: ${POLYGON2D}.cpp ${POLYGON2D}.h
	$(CC) -c $(CFLAGS) ${MACFLAGS} ${LIBS} ${POLYGON2D}.cpp -o ${POLYGON2D}.o
mGraphicObject2D.o: ${GRAPHICOBJECT2D}.cpp ${GRAPHICOBJECT2D}.h
	$(CC) -c $(CFLAGS) ${MACFLAGS} ${LIBS} ${GRAPHICOBJECT2D}.cpp -o ${GRAPHICOBJECT2D}.o

clean:
	rm -f $(MTARGETS) $(LTARGETS) ${MAIN}.o ${COMMON}.o ${SERIAL}.o ${BOX2D}.o ${PARTICLE2D}.o ${CIRCLE2D}.o ${REGULARPOLYGON2D}.o ${POLYGON2D}.o ${GRAPHICOBJECT2D}.o

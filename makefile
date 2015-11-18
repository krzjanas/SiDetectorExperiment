CXXLAGS=-g -Wall -std=c++11 `root-config --cflags`
LFLAGS=`root-config --glibs`

OBJExp=Obj/Experiment.o Obj/ParticleSource.o Obj/SensorRes.o Obj/SiDetector.o Obj/Reconstruction.o Obj/MakeTrees.o

all: Experiment

Experiment: $(OBJExp) 
	g++ -o Experiment $(OBJExp) $(LFLAGS)

Obj/Experiment.o: Main/Experiment.cpp 
	g++ -c -o Obj/Experiment.o Main/Experiment.cpp $(CXXLAGS)
	
Obj/ParticleSource.o: Source/ParticleSource.cpp Headers/ParticleSource.hpp
	g++ -c -o Obj/ParticleSource.o Source/ParticleSource.cpp $(CXXLAGS)
	
Obj/SensorRes.o: Source/SensorRes.cpp Headers/SensorRes.hpp
	g++ -c -o Obj/SensorRes.o Source/SensorRes.cpp $(CXXLAGS)
	
Obj/SiDetector.o: Source/SiDetector.cpp Headers/SiDetector.hpp
	g++ -c -o Obj/SiDetector.o Source/SiDetector.cpp $(CXXLAGS)
	
Obj/Reconstruction.o: Source/Reconstruction.cpp Headers/Reconstruction.hpp
	g++ -c -o Obj/Reconstruction.o Source/Reconstruction.cpp $(CXXLAGS)
	
Obj/MakeTrees.o: Source/MakeTrees.cpp Headers/MakeTrees.hpp
	g++ -c -o Obj/MakeTrees.o Source/MakeTrees.cpp $(CXXLAGS)
	
.PHONY: clean run

clean:
	rm -f Experiment Obj/*.o *.root VIS/*.png
	
run:
	./Experiment

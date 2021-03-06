CXXLAGS=-g -Wall -std=c++11 `root-config --cflags`
LFLAGS=`root-config --glibs`

OBJExp=Obj/Experiment.o Obj/ParticleSource.o Obj/SensorRes.o Obj/SiDetector.o Obj/Reconstruction.o Obj/MakeTrees.o 
OBJVis=Obj/Visualisation.o Obj/ReadTrees.o Obj/TreeTracks.o Obj/TreeReco.o Obj/TreeSensor.o Obj/VisEvent.o
OBJPlo=Obj/Plots.o Obj/ReadTrees.o Obj/TreeTracks.o Obj/TreeReco.o Obj/TreeSensor.o

all: Experiment Visualisation Plots

Experiment: $(OBJExp) 
	g++ -o Experiment $(OBJExp) $(LFLAGS)

Visualisation: $(OBJVis) 
	g++ -o Visualisation $(OBJVis) $(LFLAGS)

Plots: $(OBJPlo) 
	g++ -o Plots $(OBJPlo) $(LFLAGS)

Obj/Experiment.o: Main/Experiment.cpp ConfigureSiDet.hpp
	g++ -c -o Obj/Experiment.o Main/Experiment.cpp $(CXXLAGS)
	
Obj/Visualisation.o: Main/Visualisation.cpp ConfigureSiDet.hpp
	g++ -c -o Obj/Visualisation.o Main/Visualisation.cpp $(CXXLAGS)
	
Obj/Plots.o: Main/Plots.cpp ConfigureSiDet.hpp
	g++ -c -o Obj/Plots.o Main/Plots.cpp $(CXXLAGS)
	
Obj/ParticleSource.o: Source/ParticleSource.cpp Headers/ParticleSource.hpp
	g++ -c -o Obj/ParticleSource.o Source/ParticleSource.cpp $(CXXLAGS)
	
Obj/SensorRes.o: Source/SensorRes.cpp Headers/SensorRes.hpp
	g++ -c -o Obj/SensorRes.o Source/SensorRes.cpp $(CXXLAGS)
	
Obj/SiDetector.o: Source/SiDetector.cpp Headers/SiDetector.hpp
	g++ -c -o Obj/SiDetector.o Source/SiDetector.cpp $(CXXLAGS)
	
Obj/Reconstruction.o: Source/Reconstruction.cpp Headers/Reconstruction.hpp
	g++ -c -o Obj/Reconstruction.o Source/Reconstruction.cpp $(CXXLAGS)
	
Obj/VisEvent.o: Source/VisEvent.cpp Headers/VisEvent.hpp
	g++ -c -o Obj/VisEvent.o Source/VisEvent.cpp $(CXXLAGS)
	
Obj/MakeTrees.o: Tree/MakeTrees.cpp Tree/MakeTrees.hpp
	g++ -c -o Obj/MakeTrees.o Tree/MakeTrees.cpp $(CXXLAGS)
	
Obj/ReadTrees.o: Tree/ReadTrees.cpp Tree/ReadTrees.hpp
	g++ -c -o Obj/ReadTrees.o Tree/ReadTrees.cpp $(CXXLAGS)
	
Obj/TreeReco.o: Tree/Trees/TreeReco.cpp Tree/Trees/TreeReco.hpp
	g++ -c -o Obj/TreeReco.o Tree/Trees/TreeReco.cpp $(CXXLAGS)
	
Obj/TreeTracks.o: Tree/Trees/TreeTracks.cpp Tree/Trees/TreeTracks.hpp
	g++ -c -o Obj/TreeTracks.o Tree/Trees/TreeTracks.cpp $(CXXLAGS)
	
Obj/TreeSensor.o: Tree/Trees/TreeSensor.cpp Tree/Trees/TreeSensor.hpp
	g++ -c -o Obj/TreeSensor.o Tree/Trees/TreeSensor.cpp $(CXXLAGS)
	
.PHONY: clean experiment visualisation plots all

clean:
	rm -f Experiment Visualisation Plots Obj/*.o Tree/*.root Vis/*.png Vis/*.root
	
experiment:
	./Experiment
	
visualisation:
	./Visualisation
	
plots:
	./Plots

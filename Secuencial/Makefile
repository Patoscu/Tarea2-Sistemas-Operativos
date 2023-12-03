# Nombre del archivo fuente y del ejecutable
SOURCE = OpenMP.cpp
EXECUTABLE = OpenMP

# Compilador a utilizar
CXX = g++

# Flags para el compilador
# -std=c++11 para usar la versión C++11
# -Wall para mostrar todas las advertencias
# -O3 para optimización de nivel 3
# -fopenmp para habilitar OpenMP
CXXFLAGS = -std=c++11 -Wall -O3 -fopenmp

# Librerías a incluir
# pkg-config --cflags --libs opencv4 para obtener los flags de OpenCV
LIBS = `pkg-config --cflags --libs opencv4`

# Regla principal
all: $(EXECUTABLE)

# Cómo construir el ejecutable
$(EXECUTABLE): $(SOURCE)
	$(CXX) $(CXXFLAGS) $(SOURCE) -o $(EXECUTABLE) $(LIBS)

# Regla para limpiar archivos compilados
clean:
	rm -f $(EXECUTABLE)

.PHONY: all clean

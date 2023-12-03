# Nombre del archivo fuente y del ejecutable
SOURCE = CodigoHilos.cpp
EXECUTABLE = Hilos

# Compilador a utilizar
CXX = g++

# Flags para el compilador
CXXFLAGS = -std=c++11 -Wall -O3

# Librerías a incluir
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

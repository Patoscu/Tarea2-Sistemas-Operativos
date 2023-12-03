#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <thread>
#include <vector>

using namespace cv;
using namespace std;
using namespace std::chrono;

void convertToGrayscale(const Mat &input, Mat &output, int startRow, int endRow)
{
    for (int r = startRow; r < endRow; r++)
    {
        for (int c = 0; c < input.cols; c++)
        {
            Vec3b pixel = input.at<Vec3b>(r, c);
            uchar grayPixel = static_cast<uchar>(pixel[2] * 0.299 + pixel[1] * 0.587 + pixel[0] * 0.114);
            output.at<uchar>(r, c) = grayPixel;
        }
    }
}

int main(int argc, char **argv)
{
    // Verificamos los argumentos
    if (argc != 4)
    {
        cerr << "Uso: " << argv[0] << " <ImagenEntrada> <ImagenSalida> <NumeroDeHilos>" << endl;
        return -1;
    }

    // Cargamos la imagen
    Mat image = imread(argv[1], IMREAD_COLOR);

    // Se verifica si la imagen se ha cargado correctamente
    if (image.empty())
    {
        cerr << "Error al cargar la imagen!" << endl;
        return -1;
    }

    // Obtenemos el número de hilos de los argumentos
    int numThreads = stoi(argv[3]);
    vector<thread> threads(numThreads);

    // Creamos una imagen en escala de grises
    Mat grayImage(image.size(), CV_8UC1);

    // Iniciamos el cronómetro
    auto start = high_resolution_clock::now();

    // Dividimos el trabajo entre los hilos
    int rowsPerThread = image.rows / numThreads;
    for (int i = 0; i < numThreads; i++)
    {
        int startRow = i * rowsPerThread;
        int endRow = (i == numThreads - 1) ? image.rows : (i + 1) * rowsPerThread;
        threads[i] = thread(convertToGrayscale, ref(image), ref(grayImage), startRow, endRow);
    }

    // Se espera a que todos los hilos terminen su ejecución
    for (auto &t : threads)
    {
        t.join();
    }

    // Detenemos el cronómetro
    auto stop = high_resolution_clock::now();

    // Calculamos y muestramos el tiempo que se demora en ejecutar
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Tiempo de ejecución: " << duration.count() << " microsegundos" << endl;

    // Guardamos la imagen en escala de grises
    imwrite(argv[2], grayImage);

    return 0;
}

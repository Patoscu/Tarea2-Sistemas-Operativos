#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>
#include <omp.h>

using namespace cv;
using namespace std;
using namespace std::chrono;

void convertToGrayscale(const Mat &input, Mat &output)
{
#pragma omp parallel for
    for (int r = 0; r < input.rows; r++)
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

    // Se Verifica si la imagen se ha cargado correctamente
    if (image.empty())
    {
        cerr << "Error al cargar la imagen!" << endl;
        return -1;
    }

    // Configuramos el número de hilos de OpenMP
    int numThreads = stoi(argv[3]);
    omp_set_num_threads(numThreads);

    // Creamos una imagen en escala de grises
    Mat grayImage(image.size(), CV_8UC1);

    // Iniciamos el cronómetro
    auto start = high_resolution_clock::now();

    // Conviertimos la imagen a escala de grises usando OpenMP
    convertToGrayscale(image, grayImage);

    // Detenemos el cronómetro
    auto stop = high_resolution_clock::now();

    // Calculamos y muestramos el tiempo que se demora en ejecutar
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Tiempo de ejecución: " << duration.count() << " milisegundos" << endl;

    // Guardamos la imagen en escala de grises
    imwrite(argv[2], grayImage);

    return 0;
}

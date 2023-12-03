#include <iostream>
#include <opencv2/opencv.hpp>
#include <chrono>

using namespace cv;
using namespace std;
using namespace std::chrono;

int main(int argc, char **argv)
{
    // Se verifican los argumentos
    if (argc != 3)
    {
        cerr << "Uso: " << argv[0] << " <ImagenEntrada> <ImagenSalida>" << endl;
        return -1;
    }

    // Cargamos la imagen a transformar
    Mat image = imread(argv[1], IMREAD_COLOR);

    // Se verifica si la imagen se ha cargado correctamente
    if (image.empty())
    {
        cerr << "Error al cargar la imagen!" << endl;
        return -1;
    }

    // Iniciamos el cronómetro
    auto start = high_resolution_clock::now();

    // Creamos una imagen en escala de grises
    Mat grayImage(image.size(), CV_8UC1);

    // Método de luminosidad
    for (int r = 0; r < image.rows; r++)
    {
        for (int c = 0; c < image.cols; c++)
        {
            Vec3b pixel = image.at<Vec3b>(r, c);
            uchar grayPixel = static_cast<uchar>(pixel[2] * 0.299 + pixel[1] * 0.587 + pixel[0] * 0.114);
            grayImage.at<uchar>(r, c) = grayPixel;
        }
    }

    // Se detiene el cronómetro
    auto stop = high_resolution_clock::now();

    // Calculamos y muestramos el tiempo que se demoro en ejecutar
    auto duration = duration_cast<microseconds>(stop - start);
    cout << "Tiempo de ejecución: " << duration.count() << " milisegundos" << endl;

    // Guardamos la imagen en escala de grises
    imwrite(argv[2], grayImage);

    return 0;
}

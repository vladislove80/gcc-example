#include <iostream>
#include <iomanip>
#include <sys/times.h>
#include <cmath>
#include <omp.h>
#include <fstream>

int main(int argc, char** argv)
{

    const unsigned long numSteps=500000000;                     /* default # of rectangles */
    double step;
    double PI25DT = 3.141592653589793238462643;
    double pi=0;
    double sum=0.0;
    double x;
    
    ofstream myfile;
    myfile.open ("result.dat");

    #pragma omp parallel
    {
    #pragma omp master
        {
            int cntThreads=omp_get_num_threads();
            std::cout<<"OpenMP. number of threads = "<<cntThreads<<std::endl;
            myfile << "OpenMP. number of threads = " << cntThreads << endl;

        }
    }

    clock_t clockStart, clockStop;
    tms tmsStart, tmsStop;
    step = 1./static_cast<double>(numSteps);
    clockStart = times(&tmsStart);
    #pragma omp parallel for private (x), reduction (+:sum)
    for (int i=0; i<numSteps; i++)
    {
        x = (i + .5)*step;
        sum = sum + 4.0/(1.+ x*x);
    }
    pi = sum*step;
    clockStop = times(&tmsStop);
    std::cout << "The value of PI is " << pi << " Error is " << fabs(pi - PI25DT) << std::endl;
    myfile << "The value of PI is" << pi <<".  Error is "<< fabs(pi - PI25DT) << endl;
    std::cout << "The time to calculate PI was " ;
    double secs= (clockStop - clockStart)/static_cast<double>(sysconf(_SC_CLK_TCK));
    std::cout << secs << " seconds\n" << std::endl;
    myfile << "The time to calculate PI was" << secs <<"seconds " << endl;
    
    myfile.close();
    
    string buff;
    ifstream fin("datain.dat");
    if (fin==NULL) {
        cout << "Error loading file \n";
    }
    else {
        fin >> buff;
        cout << buff << endl;
    }
    
    return 0;
}

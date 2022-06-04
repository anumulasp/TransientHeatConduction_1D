// This program contains the solution code for solving the temperature variation due to transient
// conduction along the 1D bar using explicit time stepping. 


#include <iostream>
#include <math.h>
#include <fstream>

using namespace std;
const int n = 20; // No. of finite volumes in which the domain is divided (can be changed)

int main()
{
    double T[n] = {};
    double Tnew[n] = {};

    double k = 1.0;     // Thermal conductivity 
    double rho = 1.0;   // Density              
    double cp = 1.0;    // Specific heat        
    double b = k / (rho * cp);
    
    double err = 0;
    double length = 1.0; // Length of bar       
    double dx = length / n;  
    double dt = 0.001;   // Value should be taken by keeping in mind about CFL number 
    double T_left = 0;   // Left most temperature of the bar = 0 degrees   
    double T_right = 100;// Right most temperature of the bar = 100 degrees

    /* Solution algorithm using explicit time stepping*/
    do
    {
        for (int i = 0; i < n; i++)
        {
            T[i] = Tnew[i];
        }
        for (int i = 1; i < n - 1; i++)
        {
            Tnew[i] = T[i] + (b * dt / (dx * dx)) * (T[i + 1] - 2 * T[i] + T[i - 1]); // internal cells
        }
        Tnew[0] = (T[1] + 2 * T_left) / 3.0;            // Boundary condition
        Tnew[n - 1] = ((2 * T_right) + T[n - 2]) / 3.0; // Boundary condition

        err = 0;
        for (int i = 0; i < n; i++)
        {
            err = err + (Tnew[i] - T[i]);               // error calculation 
        }
        
        std::cout <<" "<<err << std::endl;
        
    } while (err > 1e-3);   // This is a threshold at which the solver should stop

    /* Writing the solution to a file */
    ofstream myfile;
    myfile.open("explicit.txt");
    myfile << T_left << " ";
    for (int i = 0; i < n; i++)
    {
        myfile << Tnew[i] << " ";
    }
    myfile << T_right;
    myfile.close();
} 
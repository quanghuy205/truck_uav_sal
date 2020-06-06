
#include "TSPalgorithm.h"
#include "NN.h"
#include "split.h"
#include "LKMatrix.h"
#include "LPT.h"
#include "algorithm1_cal.h"
#include <iostream>
#include <functional>
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <random>
#include <chrono>
#include <vector>  
#include<limits>
#include <cstdlib>

using namespace std;

TSPalgorithm::TSPalgorithm(void)
{
}


TSPalgorithm::~TSPalgorithm(void)
{
}


// Set up TSP problem to run
void TSPalgorithm::Initialize( //const int& iter,
							   CoordMatrix* mat )
{
	// Set the matrix pointer for Tour object
	tour.SetMatrix( mat );

	
	//iterations = iter;
}

void TSPalgorithm::SetupMatrix(CoordMatrix *mat )
{
	for (int i = 0; i < NumberOfParticles; i++)
	{
		for (int j = 0; j <NumberOfSalesman; j++) 
		{
			A.AllSolution.at(i).Solution.at(j).SetMatrix(mat);
		}
	}

}

default_random_engine dre (chrono::steady_clock::now().time_since_epoch().count());     // provide seed
int random (int lim)
{
    uniform_int_distribution<int> uid {1,lim};   // help dre to generate nos from 0 to lim (lim included);
    return uid(dre);    // pass dre as an argument to uid to generate the random no
}




// Get the tour node, given the index
int TSPalgorithm::GetTourCity( const int& index )
{
	int node = tour.GetCity( index );
	return node;
}


void TSPalgorithm::CreateTestSolution() {
    VehicleCost = { {0, 8, 8, 11, 6, 8, 0},
                              {8, 0, 10, 7, 10, 12, 8},
                              {8, 10, 0, 13, 8, 6, 8},
                              {11, 7, 13, 0, 11, 7, 11},
                              {6, 10, 8, 11, 0, 5, 6},
                              {8, 12, 6, 7, 5, 0, 8},
                              {0, 8, 8, 11, 6, 8, 0}}; 
    //vector <int> DroneCost = {0,0,0,0,0,0,0};
    DroneCost = {0,8,0,0,12,0,0};
    //DroneCost = {0,16,0,12,0,20,0};

}
void TSPalgorithm::CreateSolution()
{
	   
    // readTSP file
    matrix.Initialize("/home/quanghuy205/TruckUAV-master/tsp_data/att48.tsp");
    
   std::cout << "Problem name: "<<  matrix.GetFileTitle() << std::endl;
   // Initialize algorithm
   Initialize(&matrix);
    
	
	tour.CreateRandomTour();
	tour_size = tour.TourSize() ;
	cout << "Tour size: "<< tour_size << endl;
    
//	Create VehicleCost matrix
	// vector <vector<int> >VehicleCost(tour_size + 1,vector <int> (tour_size + 1, 0));
	// vector <int> DroneCost (tour_size + 1,0);
    VehicleCost.assign(tour_size + 1,vector<double> (tour_size + 1, 0) );
    DroneCost.assign(tour_size + 1, 0);
    
//Init DroneCost vector
	for (int i = 1; i < tour_size; i++) 
	{
		if (matrix.DroneTooHeavy.at(i) == 0) { 
			DroneCost.at(i) = tour.Distance(0,i);
		}
	}
   
	
//print DroneCost vector
    cout << endl << "DroneCost: " ;
	for ( int i = 0; i < DroneCost.size(); i++) 
	{
		cout << DroneCost.at(i) << " ";
	}

  
//init VehicleCost matrix


	for (int i = 0; i < tour_size + 1; i++) 
	{
		for (int j = 0; j < tour_size + 1; j++) 
		{	
			if ((i != tour_size ) && (j == tour_size  ))
			{
				VehicleCost.at(i).at(j) = tour.Distance(i,0);
			} else
			{
				if ((i == tour_size) && (j != tour_size ))
				{
					VehicleCost.at(i).at(j) = tour.Distance(0,j);
				} else
				{
					VehicleCost.at(i).at(j) = tour.Distance(i,j);
				}
			}	
				
		}
	}
//cout << tour.TourDistance() << " "<<calVehicleCost(tour.cities,VehicleCost);
//print VHcost matrix
	
cout << endl << "VehicleCost";
	for (int i = 0; i < tour_size + 1; i++) 
	{	
		cout << endl;
		for (int j = 0; j < tour_size + 1; j++) 	
		{	
			cout << VehicleCost.at(i).at(j) << " "	;
		}
	    }	

}

void TSPalgorithm::Optimize()
{	
	int n = 48;
    int M = 1;
    double UB1 = numeric_limits<double>::max(); // UB1 is the value of best solution so far, so UB1 is set to positive infinity for initialization.
    vector <int> T;    
    vector <int> T_vehicle;
    vector <int> T_drone;
    vector <int> T_opt_vehicle;
    vector <vector<int> >T_opt_drone(M);
    vector <vector <int> > Sol;
    vector <vector <int> > bestSol;

 

    bool bestSolIsImproved = true;
   solveTSP(T, VehicleCost,n);
    // T.push_back(0);
    // T.push_back(1);
    // T.push_back(2);
    // T.push_back(3);
    // T.push_back(4);
    // T.push_back(5);
    // T.push_back(0);
    //    for (int i = 0; i < n + 1; i++) 
    // {
    //     for (int j = 0; j < n +1; j++) 
    //     {
    //         if ( valid_arc(j,i,DroneCost,T))
    //         {
    //             cout << j << "," << i;
    //         } 
    //     }
    // }
    cout <<endl<< "Number of Customers: " << n << endl;
    cout << "Number of Drones: " << M << endl;
    cout << "----------------------------\n";
    cout << "Initialize tour: ";
    for (int i = 0; i < T.size(); i++) {
        cout << T.at(i) << " "; 
    }
    cout << endl << " T size : " <<  T.size() << endl;

   
    bestSol.push_back(T);

   //print
    for (int i = 0; i < bestSol.size(); i++) {
        cout << "bestSol " << i << ":" << endl;
        for (int j = 0; j < bestSol.at(i).size(); j++) {
            cout << bestSol.at(i).at(j) << " ";
        }
    }
    cout <<"Cost: " << calVehicleCost(T,VehicleCost) << endl;
    
    while (bestSolIsImproved) {
       
        cout << endl << "----------------" << endl;
      
        cout << "Split(T) " << endl;
        
        //Split----------------------------------------
        split(T,T_vehicle,T_drone,n,VehicleCost,DroneCost,UB1);
        //print T_vehicle and T_drone
        cout << "Split: " << endl << "T_vehicle: ";    
        for (int v = 0; v < T_vehicle.size(); v++) {
            cout <<  T_vehicle.at(v) << " ";
        }
        cout << endl << "T_drone: ";

        for (int v = 0; v < T_drone.size(); v++) {
            cout << T_drone.at(v) << " ";
        } 
        cout << endl;   
        //ReOptimize T_vehicle
        cout << "----------------------------\n";
        cout << "reoptimize(T_vehicle) " << endl;
        cout << "T_opt_vehicle: ";
       
        LKMatrix mat(VehicleCost,T_vehicle);
        mat.optimizeTour();
        mat.printTourIds(T_opt_vehicle);

        cout << endl;
        //ReOptimize T_drone
        cout << "----------------------------\n";
        cout << "ReoptimizePMS(T_drone) " << endl << "T_opt_drone: " << endl;   
       
        if (!T_drone.empty())
        {
            optimizePMS(T_opt_drone, T_drone, VehicleCost, DroneCost,M);
        }
        
        //Update Solution
        Sol.push_back(T_opt_vehicle);
        
        for(int i = 0; i < T_opt_drone.size(); i++) {
            Sol.push_back(T_opt_drone.at(i));
        }
       //Check solution is improved?
        cout << "----------------------------\n";
        if(isBetterSolution(Sol,bestSol,VehicleCost,DroneCost)) {
            cout << "bestSol is improved :" << endl;
            bestSol = Sol;
            bestSolIsImproved = true;
            bestInsertion(T,T_opt_vehicle,T_opt_drone,VehicleCost);
            
            cout << "Best Insertion: ";
            for (int i = 0; i < T.size(); i++) {
                cout << T.at(i) << " "; 
            }
        } else {
            cout << endl << "bestSol is not improved, stop" << endl;
            cout << "Final Best Sol: " << endl;
            for (int i = 0; i < bestSol.size(); i++) {
                cout << "bestSol " << i << ": " << endl;
                for (int j = 0; j < bestSol.at(i).size(); j++) {
                    cout << bestSol.at(i).at(j) << " ";
                }
                cout << endl;
            }
            bestSolIsImproved = false;
        }
        Sol.clear();
        T_drone.clear();
        T_vehicle.clear();
        T_opt_drone.clear();
        T_opt_vehicle.clear();
    
    } 

}
	
		

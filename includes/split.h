#ifndef SPLIT
#define SPLIT

#include <vector>
using namespace std;

struct Label {
    double vehicle_cost;
    double drone_cost;
};

int dominance (Label A, Label B);
bool valid_arc(int j, int i, vector<double> DroneCost, vector <int> T); 
double CalculateDroneCost(int j, int i, vector <double> DroneCost,vector <int> T);
double calculateUB2 (vector<vector<double> > VehicleCost, double DroneCost[], int NumberOfCustomer, vector <int> T);
double calculateUB3 (vector<vector<double> > VehicleCost, vector <double> DroneCost, int NumberOfCustomer, vector <int> T);
double *calculateLB_veh(vector<vector<double> > VehicleCost, vector <double> DroneCost, int NumberOfCustomer, vector <int> T);
double *calculateLB_tot(vector<vector<double> > VehicleCost, vector <double> DroneCost, int NumberOfCustomer, vector <int> T);
void split(vector <int> T, vector <int> &T_vehicle, vector <int> &T_drone, int n, vector <vector<double> > VehicleCost, vector <double>  DroneCost, double &UB1);

#endif
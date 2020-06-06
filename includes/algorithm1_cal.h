#ifndef ALGORITHM1_CAL
#define ALGORITHM1_CAL

#include <vector>
using namespace std;


double C1(vector <vector<int> > Solution, vector <vector<double> >VehicleCost);
double C2(vector <vector<int> > Solution, vector <double> DroneCost);
double calVehicleCost (vector <int> T, vector <vector<double> > VehicleCost);
bool isBetterSolution(vector<vector<int> > Solution1, vector<vector <int> > Solution2, vector <vector<double> > VehicleCost, vector<double> DroneCost);
void bestInsertion(vector <int> &T, vector<int>T_opt_vehicle, vector<vector<int> > T_opt_drone, vector <vector<double> > VehicleCost);

#endif
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include "algorithm1_cal.h"
using namespace std;

double C1(vector <vector<int> > Solution, vector <vector<double> >VehicleCost) {
    double C = VehicleCost[0][Solution[0].front()] + VehicleCost[Solution[0].back()][0];
    
    for (int i = 0; i < Solution[0].size() - 1; i++) {
        C += VehicleCost[Solution[0][i]][Solution[0][i+1]];
    }
    return C;
}

double C2(vector <vector<int> > Solution, vector <double> DroneCost) {
    double C = 0;
    if (Solution.size() > 1) {
        for (int i = 0; i < Solution[1].size(); i++) {
            C += DroneCost[Solution[1][i]];
        }
        for (int i = 1; i < Solution.size(); i++) {
            int tmp = 0;
            for (int j = 0; j < Solution[i].size(); j++) {
                tmp += DroneCost[Solution[i][j]];
            }
            if (C < tmp) {
                C = tmp;
            }
        }
        return C;
    } else {
        return 0;
    }
}
double calVehicleCost (vector <int> T, vector <vector<double> > VehicleCost) {
    double cost = VehicleCost[0][T.front()] + VehicleCost[T.back()][0];
    for (int i = 0; i < T.size() - 1; i++) {
        cost += VehicleCost[T[i]][T[i+1]];
    }
    return cost;
}

bool isBetterSolution(vector<vector<int> > Solution, vector<vector <int> > BestSolution, vector <vector<double> > VehicleCost, vector<double> DroneCost) {
    double CostS1 = max(C1(Solution,VehicleCost),C2(Solution,DroneCost));
    cout << " drone Cost" <<C2(Solution,DroneCost);
    double CostS2 = max(C1(BestSolution,VehicleCost),C2(BestSolution,DroneCost));
    cout << endl << CostS1 << " " << CostS2 << endl;
    double minCost1 = min(C1(Solution,VehicleCost),C2(Solution,DroneCost));
    double minCost2 =  min(C1(BestSolution,VehicleCost),C2(BestSolution,DroneCost));
    cout << minCost1 << " " << minCost2;
    if ((CostS1 < CostS2) || ((CostS1 == CostS2) && (minCost1 < minCost2))) {
        return true;
    } else {
        return false;
    }
}

void bestInsertion(vector <int> &T, vector<int>T_opt_vehicle, vector<vector<int> > T_opt_drone, vector <vector<double> > VehicleCost) {
    double minCost;
    int minIndex;
    T.clear();
    T = T_opt_vehicle;
    if (T_opt_drone.size() == 0) return;
    
    for (int i = 0; i < T_opt_drone.size(); i++) {
        for (int j = 0; j < T_opt_drone[i].size(); j++) {
            T.insert(T.begin(), T_opt_drone[i][j]);
            minCost = calVehicleCost(T,VehicleCost);
            minIndex = 0;
            T.erase(T.begin());

            for (int k = 1; k <= T.size(); k++) {
                T.insert(T.begin() + k, T_opt_drone[i][j]);
                if (minCost > calVehicleCost(T,VehicleCost)) {
                    minCost = calVehicleCost(T,VehicleCost);
                    minIndex = k;
                }
                T.erase(T.begin() + k);
            }
            
            T.insert(T.begin() + minIndex,T_opt_drone[i][j]);
            
        }   
    }
    T.push_back(0);
    T.insert(T.begin(),0);

}

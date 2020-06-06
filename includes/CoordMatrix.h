
#ifndef Coord
#define Coord 

#include <vector>
#include <map>
#include <fstream>
#include <tuple> 
#include <string>


class CoordMatrix
{
public:
	enum EDGE_WEIGHT_TYPE
	{
		ATT = 0,
		EUC_2D = 1
	};

	CoordMatrix(void);
	~CoordMatrix(void);

	void Initialize( std::string filepath );

	double CalcPseudoEuclidDistance( const double& x1,
		                             const double& x2,
								     const double& y1,
								     const double& y2 );
	double MDistance (const int &c1, const int &c2);

	double Distance( const int& c1, const int& c2 );	
	
	int size() const;
	int GetX( const int& index ) const;
	int GetY( const int& index ) const;
	int GetMinX() const;
	int GetMinY() const;
	int GetMaxX() const;
	int GetMaxY() const;

	
	std::string GetFileTitle() const;
	std::vector< std::pair<double, double> > coords;
	std::map< std::pair<int,int>, double > distMatrix;
	std::string title;
	std::vector <bool> DroneTooHeavy;
	int minx;
	int miny;
	int maxx;
	int maxy;
	int edge_weight_type;
private:
	
	void tokenize( std::vector<std::string>& tokens,  
				   const std::string& text,  
				   const std::string& delimiter );  

	void SetDistanceMatrix();
	void Reset();
};

#endif
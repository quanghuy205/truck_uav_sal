#ifndef TourH
#define TourH 
#include "CoordMatrix.h"
#include <vector>
#include <set>


class Tour
{
public:
	Tour();

	// Copy constructor
	Tour( const Tour& t );

	// Assignment operator
	Tour& operator=( const Tour& t );

	~Tour();


	double TourDistance() const;
	int TourSize() const;
	int GetCity( const int& index );
	int GetCity1( const int& index, Tour* tour1 );
	
	void SetCity( const int& index, const int& value );

	void SetMatrix( CoordMatrix* mat );
	void CreateRandomTour();
	void CreateTour();
	void CreateNearestNeighbourTour();
	void Reset();
	void Reset1(Tour* tour1);
	void SetCities( const std::vector<int>& v );
	void SetCity1( const int& index, const int& value, Tour* tour1 );
	std::vector< int > cities;
	
	double Distance( const int& c1, 
		             const int& c2 ) const;	
	double ManhattanDistance( const int& c1, 
		             const int& c2 ) const;	
private:	


	int GetNearestNeighbour( const int& c, std::set<int>& cset );

private:
//	std::vector< int > cities;
	CoordMatrix* matrix;
};

#endif
#include "CoordMatrix.h"

#include <iostream>
#include <fstream>  
#include <sstream>  
#include <cmath>
#include <cstdlib> 


using namespace std;  

const int infinity = 99999999;

#define round(n) ((int)((n)+0.5))


CoordMatrix::CoordMatrix(void)
{
	minx =  infinity;
	miny =  infinity;
	maxx = -infinity;
	maxy = -infinity;
	edge_weight_type = ATT;
	title = "";
}


CoordMatrix::~CoordMatrix(void)
{
}


// Initialise cost / distance matrix from input file
void CoordMatrix::Initialize( std::string filepath )
{
	Reset();

	minx =  infinity;
	miny =  infinity;
	maxx =  infinity * -1;
	maxy =  infinity * -1;

	// Reset existing coordinate data
	std::vector< std::pair<double, double> >().swap( coords );

	// Read in text/tsp file data
	ifstream file;
	
	file.open( filepath.c_str() );

	if ( !file )  
    {  
        std::cout << "Error in opening text/tsp file\n";  
        return;  
    }  	
    
	// Read each line of tsp file text, ignoring the first six lines of non-data stuff
	// Put the coordinate data into the matrix
	int line = 0;
	
	while( !file.eof() )
    {
		line++;
		
        char buf[ 255 ];  
        file.getline( buf, 128 );      

		std::vector<std::string> tokens;
		std::string text( buf );		
		tokenize( tokens, text, " " );
		


		// Read file title
		if ( tokens.at( 0 ) == "NAME" )
		{	
			title = tokens.at( 2 );
		}

		// Read edge weight type
		if ( tokens.at( 0 ) == "EDGE_WEIGHT_TYPE" )
		{
			if ( tokens.at( 2 ) == "ATT" )
			{
				edge_weight_type = ATT;
			} 
			if ( tokens.at( 2 ) == "EUC_2D" )
			{
				edge_weight_type = EUC_2D;
			} 
			
		}
  
		if ( line < 7 || 
			( tokens.size() == 1 && text != "EOF" )
			) 
		{			
			continue;	
		}		

		if ( text == "EOF" ) 
		{
			break;
		}
						

		// Fill in city data
		int node = atoi( tokens.at( 0 ).c_str() );
		double x    = atoi( tokens.at( 1 ).c_str() );
		double y    = atoi( tokens.at( 2 ).c_str() );
	    int tooHeavy = atoi( tokens.at( 3 ).c_str());
		
		std::pair<double,double> n( x, y );
		coords.push_back( n );
		DroneTooHeavy.push_back(tooHeavy);
		// Get node extremities
		if ( x > maxx ) maxx = x;
		if ( y > maxy ) maxy = y;
		if ( x < minx ) minx = x;
		if ( y < miny ) miny = y;	
    } 
  	
    file.close(); 

	SetDistanceMatrix();
}


// Get Euclidean distance between two cities
double CoordMatrix::Distance( const int& c1, const int& c2 )
{
	// Ensure node ids in ascending order
	if ( c1 < c2 ) 
	{
		std::pair<int,int> p( c1, c2 );		
		return distMatrix[ p ];
	}
	else
	{
		std::pair<int,int> p( c2, c1 );
		return distMatrix[ p ];
	}	
}


// Reset the distance matrix
void CoordMatrix::Reset()
{
	std::vector< std::pair<double, double> >().swap( coords );
	std::map< std::pair<int,int>, double >().swap( distMatrix );
}


// Tokenize the input string
void CoordMatrix::tokenize( std::vector<std::string>& tokens,  
						    const std::string& text,  
						    const std::string& delimiter )  
{  
    size_t next_pos = 0;  
    size_t init_pos = text.find_first_not_of( delimiter, next_pos );  
  
    while ( next_pos != string::npos &&  
            init_pos != string::npos )  
    {  
        // Get next delimiter position  
        next_pos = text.find( delimiter, init_pos );  
  
        string token = text.substr( init_pos, next_pos - init_pos );  
        tokens.push_back( token );     
  
        init_pos = text.find_first_not_of( delimiter, next_pos );  
    }  
}  



// Get number of items contained in matrix
int CoordMatrix::size() const
{
	return (int) coords.size();
}

// Get selected x coordinate
int CoordMatrix::GetX( const int& index ) const
{
	std::pair<double,double> n = coords.at( index );	
	return n.first;
}



// Get selected y coordinate
int CoordMatrix::GetY( const int& index ) const
{
	std::pair<double,double> n = coords.at( index );	
	return n.second;
}

// Get minimum x coordinate
int  CoordMatrix::GetMinX() const
{
	return minx;
}

// Get minimum y coordinate
int  CoordMatrix::GetMinY() const
{
	return miny;
}

// Get maximum x coordinate
int  CoordMatrix::GetMaxX() const
{
	return maxx;
}

// Get maximum y coordinate
int  CoordMatrix::GetMaxY() const
{
	return maxy;
}


// Get the file name
std::string CoordMatrix::GetFileTitle() const
{
	return title;
}

// Set up distance matrix between node pairs
void CoordMatrix::SetDistanceMatrix()
{
	for ( int i = 0; i < (int) coords.size() - 1; i++ )
	{
		// Get first node coordinate
		std::pair<double,double> p1 = coords.at( i );
		double x1 = p1.first;
		double y1 = p1.second;

		for ( int j = i + 1; j < (int) coords.size(); j++ )
		{
			// Get second node coordinate
			std::pair<double,double> p2 = coords.at( j );		
			double x2 = p2.first;
			double y2 = p2.second;

			// Get Euclidean distance between nodes
			double dist = 0.0;
		//	cout << edge_weight_type;
			if ( edge_weight_type == ATT )
			{
				dist = CalcPseudoEuclidDistance( x1, x2, y1, y2 );
				//cout << dist << " ";
			}
			else
			{
				dist =  sqrt( ( x1 - x2 ) * ( x1 - x2 ) +  
				                      ( y1 - y2 ) * ( y1 - y2 ) );
			//	cout << dist << " ";
			}

			// Map the distance to node pair
			std::pair< int, int > p( i, j );
			
			distMatrix[ p ] = dist;
		}
	}
}


// For edge weight type 'ATT'
// Pseudo Euclidean distance
double CoordMatrix::CalcPseudoEuclidDistance( const double& x1,
										   const double& x2,
										   const double& y1,
										   const double& y2 )
{
	int dij = 0;

	int xd = x1 - x2;
	int yd = y1 - y2;

	double rij = sqrt( (xd*xd + yd*yd) / 10.0 );  

	int tij = round( rij );
	
	if ( tij < rij ) 
	{
		dij = tij + 1;
	}
	else 
	{
			dij = tij;
	}

	return dij;
}


// Get Euclidean distance between two cities
double CoordMatrix::MDistance( const int& c1, const int& c2 )
{
	std::pair <double,double> p1 = coords.at(c1);
	std::pair <double,double> p2 = coords.at(c2);
	
	double x1 = p1.first;
	double y1 = p1.second;
	double x2= p2.first;
	double y2 = p2.second;
	
	return abs(x2-x1) + abs(y2-y1);

}
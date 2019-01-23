//============================================================================
// Name        : Final Project.cpp
// Author      : Sri Harsha Karumuri, Sindhura Chilukoti, Nikhil Kumar Vandanapu
// Description : K-Means Algorithm in C++
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <cmath>
#include <stdlib.h>
#include <iomanip>

using namespace std;

int numOfPoints()		//Number of Points in the Input File
{
	int count = 0;
	ifstream input("input.txt");
	string temp;
	while(!input.eof())		//Takes till end of the file
	{
		getline(input, temp);		//Scans each point from line
		count++;
	}
	return count;
}

struct Point		//Structure of the 4-dimensional point is declared here
{
	int x;
	int y;
	int z;
	int p;
	int cluster;
};


double distBetween(Point a, Point b)		//Function which calculates Euclidean distance between 2 points
{
	return sqrt((pow((a.x-b.x),2)) + (pow((a.y-b.y),2)) + (pow((a.z-b.z),2)) + (pow((a.p-b.p),2)));
}

int main()		//Program starts here
{

	int num = numOfPoints();		//No of Points is stored in num
	Point point[num];			//Point Structure Array is initialized
	for(int l=0; l<num; l++)	//Initializing points to Zero
	{
		point[l].x=0;
		point[l].y=0;
		point[l].z=0;
		point[l].p=0;
	}

	ifstream input("input.txt");
	string temp, t;
	int i = 0;
	int values[4], j = 0, tt;
	while(!input.eof())         //Reading points from the file
	{
		getline(input, temp);
		stringstream ss(temp);

		while(getline(ss, t, ',')) {		//Converts input string to int
			tt = atoi(t.c_str());
			values[j] = tt;
			j++;
		}

		j=0;
		point[i].x = values[0];		//Storing point values into point structure array
		point[i].y = values[1];
		point[i].z = values[2];
		point[i].p = values[3];
		i++;
	}

	Point BSSCentroid;		//Point for centroid for all points

	BSSCentroid.x =0;
	BSSCentroid.y =0;
	BSSCentroid.z =0;
	BSSCentroid.p =0;

	for(int l=0; l<num; l++)
	{
		BSSCentroid.x += point[l].x;
		BSSCentroid.y += point[l].y;
		BSSCentroid.z += point[l].z;
		BSSCentroid.p += point[l].p;
	}
	BSSCentroid.x = BSSCentroid.x / num;		//Calculating centroid for all points
	BSSCentroid.y = BSSCentroid.y / num;
	BSSCentroid.z = BSSCentroid.z / num;
	BSSCentroid.p = BSSCentroid.p / num;


	for(int k=3; k<6; k++)   //Main Loop starts here!! 		K-Means Clustering For k = 3 , 4 and 5
	{
		int count[k];
		for(int t=0 ; t<k; t++)
		{
			count[t] = 0;
		}
		cout<<"Number of Clusters : "<<k <<endl<<endl;
		int randNums[k];
		double dist[k];

		for(int j=0; j<k; j++)		//(Random Function)Initial centroids are chosen randomly
		{
			randNums[j] = rand()%num;
		}


		Point initCentroids[k];
		int b=0;

		for(int q=0; q<k; q++)		//Initial Centroids are created based on random values
		{
			initCentroids[q].x = point[randNums[b]].x;
			initCentroids[q].y = point[randNums[b]].y;
			initCentroids[q].z = point[randNums[b]].z;
			initCentroids[q].p = point[randNums[b]].p;
			b++;
		}
		cout<<"Initial Centroids are: "<<endl;
		for(int q=0; q<k; q++)			//Printing Initial Centroids
		{
			cout<<"( "<<initCentroids[q].x<<" , "<<initCentroids[q].y<<" , "<<initCentroids[q].z<<" , "<<initCentroids[q].p<<" ) "<<endl;
		}

		//Checks which points fall into which clusters

		Point prevCentroids[k];		//Saving all Previous Centroids to this point

		for(int q=0; q<k; q++)
		{
			prevCentroids[q].x = initCentroids[q].x;
			prevCentroids[q].y = initCentroids[q].y;
			prevCentroids[q].z = initCentroids[q].z;
			prevCentroids[q].p = initCentroids[q].p;
			prevCentroids[q].cluster = initCentroids[q].cluster;
		}

		double small = 0;
		int smallIndex = 0;
		for(int i=0; i<num; i++)		//Calculates which centroids fall into which cluster
		{								//based on Euclidian distance between point and all cluster centroids
			for(int j=0; j<k; j++)
			{
				dist[j] = distBetween(point[i], prevCentroids[j]);		//Reutrns the distance between point and each cluster
			}
			small = dist[0];
			smallIndex = 0;
			for(int a = 1; a < k; a++)		//Checks which cluster centroid is near to the point
			    {
			       if(small > dist[a])
			       {
			    	   smallIndex = a;
			    	   small = dist[a];
			       }
			    }
			point[i].cluster = smallIndex;		//Declare that corresponding point falls into that cluster
			count[smallIndex]++;		//Counts Cluster points
		}

		//calculate new centroids
		int h = 1, flag;
		do			//After the Points and Clusters are ready.. Find new centroids..
		{
			flag = 0;

			Point newCentroids[k];
			int f;
			int sumX, sumY, sumZ, sumP;

			cout<<"\nIteration "<< h <<" : "<<endl<<"Centroids are ->"<<endl;

			for(int s=0; s<k; s++)		 //To check which point is near to which cluster
			{

				sumX=0; sumY=0; sumZ=0; sumP=0; f=0;
				for(int r=0; r<num; r++)
				{
					if(point[r].cluster == s)
					{
						f++;
						sumX += point[r].x;
						sumY += point[r].y;
						sumZ += point[r].z;
						sumP += point[r].p;
					}

				}
				newCentroids[s].x = sumX / f;		//Calculates the new Centroids
				newCentroids[s].y = sumY / f;
				newCentroids[s].z = sumZ / f;
				newCentroids[s].p = sumP / f;

				cout<<"Cluster "<<s+1<<" :  ";

				cout<<"( "<<newCentroids[s].x<<" , "<<newCentroids[s].y<<" , "<<newCentroids[s].z<<" , "<<newCentroids[s].p<<" )  --> "<<count[s]<<" points"<<endl;
			}

			for(int t=0;t<k;t++)
				count[t]=0;

			small = 0;
			smallIndex = 0;
			for(int u=0; u<num; u++)		//Calculates the distance between all points and all clusters..
			{								//Each point goes to nearest new centroid
				for(int v=0; v<k; v++)
				{
					dist[v] = distBetween(point[u], newCentroids[v]);		//Distance between points is returned
				}

				small = dist[0];
				smallIndex = 0;
				for(int d = 1; d < k; d++)
				    {
				       if(small > dist[d])
				       {
				    	   smallIndex = d;
				    	   small = dist[d];
				       }
				    }
				point[u].cluster = smallIndex;		//Sets the cluster values to all points

				count[smallIndex]++;
			}

			//If both centroids are same stop looping
			for(int c=0; c<k; c++)			//Checks whether previous centroids and new centroids are same (Exit condition)
			{
					if(prevCentroids[c].x!=newCentroids[c].x || prevCentroids[c].y!=newCentroids[c].y || prevCentroids[c].z!=newCentroids[c].z || prevCentroids[c].p!=newCentroids[c].p)
					{
						flag = 1; 		//false condition.. if flag = 1 continue loop.. if flag = 0.. stop looping
					}
					prevCentroids[c].x = newCentroids[c].x;			//marking all new centroids as old centroids for next iteration
					prevCentroids[c].y = newCentroids[c].y;
					prevCentroids[c].z = newCentroids[c].z;
					prevCentroids[c].p = newCentroids[c].p;
					prevCentroids[c].cluster = newCentroids[c].cluster;
			}

		h++;

		} while(flag==1);		//Checks the Exit Condition

		//WSS

		double distSum = 0;
		int clus = 0;
		for(int n=0;n<num;n++)		//Calculating WSS-- Sum of Squares of distances between point and cluster centroid
		{
			clus = point[n].cluster;
			distSum += pow(distBetween(point[n], prevCentroids[clus]),2);
		}
		cout<<fixed<<setprecision(2)<<"\nWSS: "<<distSum<<endl;


		//BSS

		double distforBSS = 0;
		for(int n=0; n<k; n++)		//Calculating BSS-- Sum of the Product of Number of Points in Cluster and Squared Distance between Cluster Centroid and Centroid of all Potins
		{
			distforBSS += (count[n]) * (pow(distBetween(prevCentroids[n],BSSCentroid),2));
		}
		cout<<fixed<<setprecision(2)<<"BSS: "<<distforBSS<<endl;

		cout<<"\nSSE: WSS+BSS:  "<<distSum+distforBSS<<endl;			//Sum of WSS and BSS is said to be SSE
		distSum = 0;
		distforBSS = 0;
		cout<<endl<<endl<<endl;
	}


}

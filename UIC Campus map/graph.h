// graph.h <Starter Code>
// < Your name >
//
// Basic graph class using adjacency matrix representation.  Currently
// limited to a graph with at most 100 vertices.
//
//
// Adam T Koehler, PhD
// University of Illinois Chicago
// CS 251, Fall 2022
//
// Project Original Variartion By:
// Joe Hummel, PhD
// University of Illinois at Chicago
//

#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>
#include <algorithm>
#include <utility>


using namespace std;

template<typename VertexT, typename WeightT>
class graph {
 private:
  typedef pair<VertexT, WeightT> vwPair;
  map<VertexT, vector<vwPair>> adjList;

static bool sortbysec(const pair<VertexT,WeightT> &a,
              const pair<VertexT,WeightT> &b)
{
    return (a.first < b.first);
}

static bool sortVert(const VertexT  &a,
              const VertexT &b)
{
    return (a < b);
}

int binary_search_iterative(vector<vwPair> allEdges, VertexT edge, int len) const {
  int low = 0;
  int high = len - 1;

  while (low <= high) {
    int mid = low + ((high - low) / 2);
    if (allEdges.at(mid).first == edge) {
      return mid;
    } else if (edge < allEdges.at(mid).first) {
      high = mid - 1;
    } else {
      low = mid + 1;
    }
  }
  return -1;
}

 public:
  //
  // default constructor:
  //
  // Default constructs an empty graph where n is the max # of vertices
  // you expect the graph to contain.
  //
  graph()
   {
    this->adjList.clear();
   }

  //
  // Copy: copy all vertices and edges
  //
  graph& operator=(const graph &other)
    {
      other.adjList = this->adjList;
    }

  //
  // Clear: remove all vertices and edges
  //
void clear()
{
      this->adjList.clear();
}

  //
  // NumVertices
  //
  // Returns the # of vertices currently in the graph.
  //
  int NumVertices() const {
    return static_cast<int>(this->adjList.size());
  }

  //
  // NumEdges
  //
  // Returns the # of edges currently in the graph.
  //
  int NumEdges() const {
    int count = 0;

     
    for (auto const& x : this->adjList)
{
    count = + x.second.size() + count;
}

    return count;
  }

  //
  // addVertex
  //
  // Adds the vertex v to the graph if there's room, and if so
  // returns true.  If the graph is full, or the vertex already
  // exists in the graph, then false is returned.
  //
  bool addVertex(VertexT v) {
     
    //
    // is the vertex already in the graph?  If so, we do not
    // insert again otherwise Vertices may fill with duplicates:
    //
    if (this->adjList.find(v)!=this->adjList.end()) {
      return false;
    }

    //
    // if we get here, vertex does not exist so insert.  Where
    // we insert becomes the rows and col position for this
    // vertex in the adjacency matrix.
    //
    vector<vwPair> adjacents;
    this->adjList.emplace(v, adjacents);

    return true;
  }

  //
  // addEdge
  //
  // Adds the edge (from, to, weight) to the graph, and returns
  // true.  If the vertices do not exist or for some reason the
  // graph is full, false is returned.
  //
  // NOTE: if the edge already exists, the existing edge weight
  // is overwritten with the new edge weight.
  //
  bool addEdge(VertexT from, VertexT to, WeightT weight) {
    //
    // we need to search the Vertices and find the position
    // of each vertex; this will denote the row and col to
    // access in the adjacency matrix:
    //
    if (this->adjList.find(from)==this->adjList.end()) {
      return false;
    }

    //
    // the vertices exist and we have the row and col of the
    // adjacency matrix, so insert / update the edge:
    //
    vector<vwPair> copyVector = this->adjList.at(from);
   // cout << "making pair: " << to << " and " << weight << endl;
    copyVector.push_back(make_pair(to, weight));
    this->adjList.at(from) =  copyVector;
    return true;
  }

  //
  // getWeight
  //
  // Returns the weight associated with a given edge.  If
  // the edge exists, the weight is returned via the reference
  // parameter and true is returned.  If the edge does not
  // exist, the weight parameter is unchanged and false is
  // returned.
  //
  bool getWeight(VertexT from, VertexT to, WeightT& weight) const {
    //
    // we need to search the Vertices and find the position
    // of each vertex; this will denote the row and col to
    // access in the adjacency matrix:
    //
   
     if (this->adjList.find(from)==this->adjList.end()) {

      return false;
    }
    /*
       for (auto const& x : this->adjList)
    {
      cout << "key is " << x.first << endl;
        for(int i = 0; i < x.second.size(); i++)
        {
          cout << endl << x.second.at(i).first << " and " << x.second.at(i).second;
        }
        cout << endl;
    }
    */


      vector<vwPair> copyVecotr = this->adjList.at(from);

      sort(copyVecotr.begin(), copyVecotr.end(),  sortbysec );

    




    //
    // the vertices exist, but does the edge exist?
    //
   
    /*
    pair<VertexT, WeightT> item;
    item = make_pair(to,weight);
    int index = 0; 
    
    auto it = find(this->adjList.at(from).begin(),this->adjList.at(from).end(), item);
  
    if ( it != this->adjList.at(from).end()){
     index = it - this->adjList.at(from).begin();
     cout << endl << " something changed " ;
     } 
     else 
     {
      cout << endl << " something should have changed ";
     }
    */
    int index = binary_search_iterative(copyVecotr, to, copyVecotr.size());
    if(index == -1)
    {
      return false;
    }
    else
   

    //
    //cout << endl << " prior weight " << weight  << " now ";
    //cout << endl << " index is "<< index << endl;
    //cout << " vector size is " << copyVecotr.size() << endl;
    weight = copyVecotr.at(index).second;

    return true;
  }

  //
  // neighbors
  //
  // Returns a set containing the neighbors of v, i.e. all
  // vertices that can be reached from v along one edge.
  // Since a set is returned, the neighbors are returned in
  // sorted order; use foreach to iterate through the set.
  //
  set<VertexT> neighbors(VertexT v) const {
    set<VertexT>  S;

    //
    // we need to search the Vertices and find the position
    // of v, that will be the row we need in the adjacency
    // matrix:
    //
    
    

    //
    // we found the row, so loop along the row and for every
    // edge that exists, add the column vertex to V:
    //
    // NOTE: how many columns are there?  The # of vertices.
    //
    for(int i = 0; i < this->adjList.at(v).size(); i++)
    {
         S.insert(this->adjList.at(v).at(i).first);
    }
       
      
    return S;
  }

  //
  // getVertices
  //
  // Returns a vector containing all the vertices currently in
  // the graph.
  //
  vector<VertexT> getVertices() const {
    vector<VertexT> allVertexs;
    for (auto const& x : this->adjList)
    {
   allVertexs.push_back(x.first);
    }
    return allVertexs;  // returns a copy:
  }

  //
  // dump
  //
  // Dumps the internal state of the graph for debugging purposes.
  //
  // Example:
  //    graph<string,int>  G(26);
  //    ...
  //    G.dump(cout);  // dump to console
  //
  void dump(ostream& output) const {
    vector<VertexT> copyVecotr = getVertices();
    sort(copyVecotr.begin(), copyVecotr.end(),  sortVert );
    output << "***************************************************" << endl;
    output << "********************* GRAPH ***********************" << endl;

    output << "**Num vertices: " << this->NumVertices() << endl;
    output << "**Num edges: " << this->NumEdges() << endl;

    output << endl;
    output << "**Vertices:" << endl;
    for (int i = 0; i < copyVecotr.size(); ++i) {
      output << " " << i << ". " << copyVecotr.at(i) << endl;
    }

    output << endl;
    output << "**Edges:" << endl;
    for (int row = 0; row < this->NumVertices(); ++row) {
      output << " row " << copyVecotr.at(row) << ": ";

      for (int col = 0; col < this->NumVertices(); ++col) {
        int weight;
        if (this->getWeight(copyVecotr.at(row), copyVecotr.at(col), weight) == false) {
          output << "F ";
        } else {
          output << "(T,"
            << weight
            << ") ";
        }
      }
      output << endl;
    }
    output << "**************************************************" << endl;
  }
};



#include <ext/pb_ds/assoc_container.hpp> 
#include <ext/pb_ds/tree_policy.hpp> 
using namespace __gnu_pbds; 
  
#define ordered_set tree<int, null_type,less<int>, rb_tree_tag,tree_order_statistics_node_update> 

// in contest, this can also be replaced with segment / fenwick tree + walk on tree + number compression (if needed)
// set a tree saving number of elements

// USAGE
// find_by_order() : returns an iterator to the k-th largest element (counting from zero)
// order_of_key() : the number of items in a set that are strictly smaller than our item

// for multiset: replace less<int> with less_equal<int>
// REMEMBER THAT OSET IS SLOW AS F AND USE ALTERNATIVES IF CAN!!!!

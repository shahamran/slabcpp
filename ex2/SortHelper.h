#ifndef SORT_HELPER_H
#define SORT_HELPER_H

#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <list>
#include <vector>

/**
* ListItem contain value and original index
*/
typedef struct ListItem
{
ListItem(const int value, const int originalIndex) :
    _value(value), _originalIndex(originalIndex)
    {}
    
    int _value;
    int _originalIndex;
} ListItem;


/**
 * Class to help sort items according to some int value.
 *
 * The class has one add method to insert items (that have int value),
 * and several "getSortedOrder..." methods to get the sorted order of indices,
 * each method returns the sorted order in a different way. You can use
 * whatever is convenient to you.
 *
 */
class SortHelper
{
 public:
    SortHelper()
    {}

   /**
   * add an item, with  size() index
  	*   As in insertion sort, place the given value in the appropriate
  	* position, while maintaining a sorted list, with descending order of values.
  	*/
    void addItem(const int value);

	/**
	* return how many items are currently in the SortHelper
   */     
    inline int size() const
    {
        return (int)_list.size();
    }

	/**
	 *   Get the sorted order of indices (the indices of the insertion of items,
	 * sorted according to the values of the items).
	 *   The given array must be of length the same as the number of values inserted
	 * (the same as what SortHelper::size() will return),
	 * otherwise memory access errors (like segmentation fault) might occur.
	 *   The given array will be filled with the indices in the sorted order.
	 */
    void getSortedOrderInArray(int arrayToFill[]) const;

	/**
	 *   Get the sorted order of indices (the indices of the insertion of items,
	 *   sorted according to the values of the items).	
	 *   The returned list will contain the indices of the inserted items in an
 	 *   order such that the original items will be from large value to smaller value.
	*/
    std::list<int> getSortedOrderInList() const;

	/**
	 *   Get the sorted order of indices (the indices of the insertion of items,
	 * sorted according to the values of the items).
	 *   The returned vector will contain the indices of the inserted items in an
	 *   order such that the original items will be from large value to smaller value.
 	*/  
    std::vector<int> getSortedOrderInVector() const;
    
    /**
    */
    virtual ~SortHelper()
    {}
    
 private:
    std::list<ListItem> _list;
    
};

#endif

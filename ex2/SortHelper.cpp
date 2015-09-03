#include "SortHelper.h"
/**
   * add an item, with  size() index
  	*   As in insertion sort, place the given value in the appropriate
  	* position, while maintaining a sorted list, with descending order of values.
  	*/
void SortHelper::addItem(const int value)
{
    // The original index of the new item will be the index in the order of
    // insertion to the list:
    int originalIndex = _list.size();
    ListItem item(value, originalIndex);
    
    std::list<ListItem>::iterator it = _list.begin();

    // Look for the first position where the value is smaller than the
    // new item's value:
    while ((it != _list.end()) && (it->_value >= value))
    {
        it++;
    }
    // it is now in the position to insert the new item:
    _list.insert(it, item);

    #ifdef DEBUG
    std::cout << "list now has size: " << _list.size() << " and is now: ";
    for (std::list<ListItem>::iterator it = _list.begin(); it != _list.end(); it++) 
    {
        std::cout << "<" << it->_value << "," << it->_originalIndex << ">,";
    }
    std::cout << std::endl;
    #endif
    
}

/**
	 *   Get the sorted order of indices (the indices of the insertion of items,
	 * sorted according to the values of the items).
	 *   The given array must be of length the same as the number of values inserted
	 * (the same as what SortHelper::size() will return),
	 * otherwise memory access errors (like segmentation fault) might occur.
	 *   The given array will be filled with the indices in the sorted order.
	 */
void SortHelper::getSortedOrderInArray(int arrayToFill[]) const
{
    if (arrayToFill != NULL)
    {
        std::cerr << "The given array is NULL" << std::endl;
        return;
    }

    // Go over the list and fill each item's original index in the
    // appropriate index in the given array:
    std::list<ListItem>::const_iterator it = _list.begin();
    int i;
    for (i = 0; it != _list.end(); i++, it++)
    {
        arrayToFill[i] = it->_originalIndex;
    }
    
}

/**
 * Get the sorted order of indices (the indices of the insertion of items,
 * sorted according to the values of the items).
 *
 * The returned list will contain the indices of the inserted items in an
 * order such that the original items will be from large value to smaller value.
 */
std::list<int> SortHelper::getSortedOrderInList() const
{
    std::list<int> orderList(size(), 0);
    std::list<int>::iterator orderIter;
    std::list<ListItem>::const_iterator itemsIter;

    for (orderIter = orderList.begin(), itemsIter = _list.begin(); itemsIter != _list.end(); orderIter++, itemsIter++)
    {
        *orderIter = itemsIter->_originalIndex;
    }

    return orderList;
}

/**
 * Get the sorted order of indices (the indices of the insertion of items,
 * sorted according to the values of the items).
 *
 * The returned vector will contain the indices of the inserted items in an
 * order such that the original items will be from large value to smaller value.
 */
std::vector<int> SortHelper::getSortedOrderInVector() const
{
    std::vector<int> orderVector(size(), 0);
    int i;
    std::list<ListItem>::const_iterator itemsIter;

    for (i = 0, itemsIter = _list.begin(); i < size(); i++, itemsIter++)
    {
        orderVector[i] = itemsIter->_originalIndex;
    }

    return orderVector;
}

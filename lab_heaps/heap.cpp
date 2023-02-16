/**
 * @file heap.cpp
 * Implementation of a heap class.
 */
#include <cmath>

template <class T, class Compare>
size_t heap<T, Compare>::root() const
{
	return 0;
}

template <class T, class Compare>
size_t heap<T, Compare>::leftChild(size_t currentIdx) const
{
	/*if (_elems.size()<=currentIdx*2+1) {
		std::cout << "no left child" << std::endl;
		return -1;
	}*/
	return currentIdx * 2+1;
}

template <class T, class Compare>
size_t heap<T, Compare>::rightChild(size_t currentIdx) const
{
	/// @todo Update to return the index of the right child.
	/*if (_elems.size() <= currentIdx*2+2) {
		std::cout << "no right child" << std::endl;
		return -1;
	}*/
	return currentIdx * 2 + 2;
}

template <class T, class Compare>
size_t heap<T, Compare>::parent(size_t currentIdx) const
{
	int temp = (int)(currentIdx-1) / 2;
	return (size_t) temp;
}

template <class T, class Compare>
bool heap<T, Compare>::hasAChild(size_t currentIdx) const
{
	if (_elems.size() > currentIdx * 2+1) {
		return true;
	}
	return false;
}

template <class T, class Compare>
size_t heap<T, Compare>::maxPriorityChild(size_t currentIdx) const
{
	if (_elems.size()<=currentIdx*2+1) {
		std::cout << "no child" << std::endl;
		return -1;
	}
	else if (_elems.size() == currentIdx*2+2) {
		return currentIdx*2+1;
	}
    if (higherPriority(_elems[currentIdx*2+1], _elems[currentIdx*2+2]) == true) {
        return currentIdx*2+1;
    }
	return currentIdx*2+2;
}

template <class T, class Compare>
void heap<T, Compare>::heapifyDown(size_t currentIdx)
{
	if (currentIdx>=_elems.size() || hasAChild(currentIdx)==false) {
		return;
	}
	if (higherPriority(_elems[maxPriorityChild(currentIdx)], _elems[currentIdx]) == true) {
        T temp = _elems[currentIdx];
		int exchange = maxPriorityChild(currentIdx);
		_elems[currentIdx] = _elems[exchange];
		_elems[exchange] = temp;
		heapifyDown(exchange);
    }
}

template <class T, class Compare>
void heap<T, Compare>::heapifyUp(size_t currentIdx)
{
	if (currentIdx == root())
		return;
	size_t parentIdx = parent(currentIdx);
	if (higherPriority(_elems[currentIdx], _elems[parentIdx])) {
		std::swap(_elems[currentIdx], _elems[parentIdx]);
		heapifyUp(parentIdx);
	}
}

template <class T, class Compare>
heap<T, Compare>::heap()
{
	//_elems.push_back((T) 927);
}

template <class T, class Compare>
heap<T, Compare>::heap(const std::vector<T>& another)
{
	//_elems.resize(0);
	_elems = another;
	/*for (int i = 0; i < (int)_elems.size(); i++) {
		std::cout << another[i] << " ";
	}*/
	int height = ceil(log2(another.size())) - 1;
	int rightmost = pow(2, height) - 2;
	//std::cout << "rightmost " << rightmost << std::endl;
	for (int i = rightmost; i >= 0; i--) {
		//std::cout << another[i] << " ";
		heapifyDown(i);
	}
}

template <class T, class Compare>
T heap<T, Compare>::pop()
{
	T temp = _elems[0];
	_elems[0] = _elems[_elems.size()-1];
	_elems.pop_back();
	heapifyDown(0);
	return temp;
}

template <class T, class Compare>
T heap<T, Compare>::peek() const
{
	return _elems[0];
}

template <class T, class Compare>
void heap<T, Compare>::push(const T& elem)
{
	_elems.push_back(elem);
	heapifyUp(_elems.size()-1);
}

template <class T, class Compare>
bool heap<T, Compare>::empty() const
{
	if (_elems.size() == 0) {
		return true;
	}
	return false;
}

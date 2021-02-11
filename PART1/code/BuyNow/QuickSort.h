#pragma once

#include <vector>

using namespace std;

template<class T>

class QuickSort
{
public:
    /**
     * Array to be sorted
     */
    vector<T> *sortingArray;
    /**
     * starting index for the sort method
     */
    int left;
    /**
     * ending index for the sort method
     */
    int right;

    /**
     *  The main function that implements QuickSort
     * @tparam T
     * @param sortArray, array to be sorted
     * @param InicialIndex
     * @param FinalIndex
     * @param flag
     */
    QuickSort(vector<T> *sortArray, int InicialIndex, int FinalIndex, bool flag);
    /**
     *  Places the pivot element at its correct position in sorted array, and places all smaller (smaller than pivot) to left of pivot and all greater elements to right of pivot
     * @tparam T
     * @param sortArray
     * @param indexInicial
     * @param indexFinal
     * @param flag
     * @return
     */
    int Particion(vector<T> *sortArray, int InicialIndex, int FinalIndex, bool flag);
    /**
     *  A utility function to swap two elements
     * @tparam T
     * @param l
     * @param k
     */
    void Swap(int l, int k);
};



template<class T>
QuickSort<T>::QuickSort(vector<T> *sortArray, int InicialIndex, int FinalIndex, bool flag)
{
    if (InicialIndex >= FinalIndex)
    {
        return;
    }

    sortingArray = sortArray;

    left = InicialIndex;
    right = FinalIndex;

    if (left < right)
    {
        int pivot = Particion(sortingArray, left, right, flag);

        QuickSort(sortingArray, left, (pivot - 1), flag);

        QuickSort(sortingArray, (pivot + 1), right, flag);
    }
}


template<class T>
int QuickSort<T>::Particion(vector<T> *sortArray, int indexInicial, int indexFinal, bool flag)
{
    int l = indexInicial - 1;
    int k = indexFinal;

    if (flag)
    {
        for (int i = indexInicial; i <= k - 1; i++)
        {
            if ((*sortArray).at(i) < (*sortArray).at(k))
            {
                l++;
                Swap(l, i);
            }
        }
    }
    else
    {
        for (int i = indexInicial; i <= k - 1; i++)
        {
            if (!((*sortArray).at(i) > (*sortArray).at(k)))
            {
                l++;
                Swap(l, i);
            }
        }
    }

    Swap(l + 1, k);

    return l + 1;
}

template<class T>
void QuickSort<T>::Swap(int l, int k)
{
    swap((*sortingArray).at(l), (*sortingArray).at(k));
}
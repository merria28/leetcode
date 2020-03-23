#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <unordered_map>

using namespace std;

/// 第295题作为第480题的一个基础理解
/// 这一题涉及到了新的数据结构，需要提前理解一下：proirity_queue和multiset


/** 295. 数据流的中位数
 ** 题目描述：
	中位数是有序列表中间的数。如果列表长度是偶数，中位数则是中间两个数的平均值。

	例如，
	[2,3,4] 的中位数是 3
	[2,3] 的中位数是 (2 + 3) / 2 = 2.5

	设计一个支持以下两种操作的数据结构：

	void addNum(int num) - 从数据流中添加一个整数到数据结构中。
	double findMedian() - 返回目前所有元素的中位数。

	示例：
	addNum(1)
	addNum(2)
	findMedian() -> 1.5
	addNum(3)
	findMedian() -> 2

	进阶:
	如果数据流中所有整数都在 0 到 100 范围内，你将如何优化你的算法？
	如果数据流中 99% 的整数都在 0 到 100 范围内，你将如何优化你的算法？
*/

/**
 * Your MedianFinder object will be instantiated and called as such:
 * MedianFinder* obj = new MedianFinder();
 * obj->addNum(num);
 * double param_2 = obj->findMedian();
 */

/// 这个题看完之后一脸懵逼，本来简单粗暴的排序之后，直接找中位数的想法破灭了
/// 优化1： 排序变为二分查找
	// 方法一的缺点在于对数组进行了排序操作，导致时间复杂度较高，假如每次插入一个值前数组已经排好序了呢？
	// 这样我们只需考虑每次将值插在合适的位置即可，所以使用二分查找来找到这个合适的位置，
	// 会将时间复杂度降低到{ \mathcal{O} }(n)O(n)（查找: {\mathcal{ O }}(log n)O(logn)，插入 : {\mathcal{ O }}(n)O(n)）。
/// 优化2：二分查找变成优先队列 priority_queue 大顶堆小顶堆
/// 优化3：Multiset 和双指针


/// 优化1
class MedianFinder_insertsort {
public:
	/** initialize your data structure here. */

	vector<int> store;

	MedianFinder_insertsort() {
		store.clear();
	}

	void addNum(int num) {
		if(store.empty())
			store.push_back(num);
		else {			
			store.insert(lower_bound(store.begin(), store.end(), num), num);  // 插入O(n) + 查找O(logn)≈O(n).
		}
			
	}

	double findMedian() {
		int n = store.size();
		return n & 1 ? store[n / 2] : (store[n / 2 - 1] + store[n / 2]) * 0.5;
	}
};

/// 优化2
/// 基础数据准备 c++ priority_queue
/** 两个堆	
	以上两种方法对如何解决这个问题提供了一些有价值的见解。具体来说，我们可以推断出两件事：
		1.如果我们可以一直直接访问中值元素，那么找到中值将需要一个恒定的时间。
		2.如果我们能找到一种相当快速的方法来增加容器的数量，那么所产生的额外操作可能会减少。
	
	但也许最重要的洞察是我们只需要一种一致的方式来访问中值元素，这是不容易观察到的。不需要对整个输入进行排序。
	事实证明，有两种数据结构符合：
		1.堆（或优先级队列）
		2.自平衡二进制搜索树（我们将在方法4中详细讨论它们）
	堆是这道题的天然原料！向元素添加元素需要对数时间复杂度。它们还可以直接访问组中的最大/最小元素。

	如果我们可以用以下方式维护两个堆：
		1.用于存储输入数字中较小一半的最大堆
		2.用于存储输入数字的较大一半的最小堆
	这样就可以访问输入中的中值：它们组成堆的顶部！

	如果满足以下条件：
		1.两个堆都是平衡的（或接近平衡的）
		2.最大堆包含所有较小的数字，而最小堆包含所有较大的数字
		
	那么我们可以这样说：
		1.最大堆中的所有数字都小于或等于最大堆的top元素（我们称之为 x）
		2.最小堆中的所有数字都大于或等于最小堆的顶部元素（我们称之为 y）
	那么 x 和 y 几乎小于（或等于）元素的一半，大于（或等于）另一半。这就是中值元素的定义。
	这使我们在这种方法中遇到了一个巨大的难题：平衡这两个堆！


算法：
	1.两个优先级队列：
		用于存储较小一半数字的最大堆 lo
		用于存储较大一半数字的最小堆 hi
	
	2.最大堆 lo 允许存储的元素最多比最小堆 hi 多一个。因此，如果我们处理了 k 元素：
		如果 k=2∗n+1(∀,n∈z) 则允许 lo 持有 n+1 元素，而 hi 可以持有 n 元素。
		如果 k=2∗n(∀,n∈z)，那么两个堆都是平衡的，并且每个堆都包含 n 个元素。
	**这给了我们一个很好的特性，即当堆完全平衡时，中间值可以从两个堆的顶部派生。否则，最大堆 lo 的顶部保留合法的中间值。**

	3.添加一个数 num：
		将 num 添加到最大堆 lo。因为 lo 收到了一个新元素，所以我们必须为 hi 做一个平衡步骤。因此，从 lo 中移除最大的元素并将其提供给 hi。
		在上一个操作之后，最小堆 hi 可能会比最大堆 lo 保留更多的元素(条件满足，再执行后面描述)。我们通过从 hi 中去掉最小的元素并将其提供给 lo 来解决这个问题。


复杂度分析

时间复杂度： O(5⋅logn)+O(1)≈O(logn)。
	1.最坏情况下，从顶部有三个堆插入和两个堆删除。每一个都需要花费 O(\log n)O(logn) 时间。
	2.找到平均值需要持续的 O(1)O(1) 时间，因为可以直接访问堆的顶部。
空间复杂度：O(n) 用于在容器中保存输入的线性空间。

*/
// 执行用时：148 ms  内存消耗：43.2 MB
class MedianFinder_heap {
public:
	/** initialize your data structure here. */
	priority_queue<int> lo;                              // max heap
    priority_queue<int, vector<int>, greater<int>> hi;   // min heap


	//MedianFinder() {
	//}

	void addNum(int num) {
		lo.push(num);                                    // Add to max heap

        hi.push(lo.top());                               // balancing step
        lo.pop();

        if (lo.size() < hi.size()) {                     // maintain size property
            lo.push(hi.top());
            hi.pop();
        }

	}

	double findMedian() {
		return lo.size() > hi.size() ? (double) lo.top() : (lo.top() + hi.top()) * 0.5;
	}
};

/// 优化3：Multiset
/**
	自平衡二进制搜索树（如AVL树）具有一些非常有趣的特性。它们将树的高度保持在对数范围内。因此，插入新元素具有相当好的时间性能。
	中值总是缠绕在树根或它的一个子树上。使用与方法 3 相同的方法解决这个问题，但是使用自平衡二叉树似乎是一个不错的选择。
	但是，实现这样一个树并不是简单的，而且容易出错。

	大多数语言实现模拟这种行为的是 multiset 类。唯一的问题是跟踪中值元素。这很容易用指针解决！
	cpp语言中，multiset是<set>库中一个非常有用的类型，它可以看成一个序列，插入一个数，删除一个数都能够在O(logn)的时间内完成，
	而且它能时刻保证序列中的数是有序的，而且序列中可以存在重复的数。

	我们保持两个指针：
		一个用于中位数较低的元素，另一个用于中位数较高的元素。
		当元素总数为奇数时，两个指针都指向同一个中值元素（因为在本例中只有一个中值）。
		当元素数为偶数时，指针指向两个连续的元素，其平均值是输入的代表中位数。


算法：
	1.两个迭代器/指针 lo_median 和 hi_median，它们在 multiset上迭代 data。
	
	2.添加数字 num 时，会出现三种情况：
		a.容器当前为空。因此，我们只需插入 num 并设置两个指针指向这个元素。
		b.容器当前包含奇数个元素。这意味着两个指针当前都指向同一个元素。
			*如果 num 不等于当前的中位数元素，则 num 将位于元素的任一侧。
			无论哪一边，该部分的大小都会增加，因此相应的指针会更新。
			例如，如果 num 小于中位数元素，则在插入 num 时，输入的较小半部分的大小将增加 11。			
			*如果 num 等于当前的中位数元素，那么所采取的操作取决于 num 是如何插入数据的。
			
	3.容器当前包含偶数个元素。这意味着指针当前指向连续的元素。
		a.如果 num 是两个中值元素之间的数字，则 num 将成为新的中值。两个指针都必须指向它。
		b.否则，num 会增加较小或较高一半的大小。我们相应地更新指针。必须记住，两个指针现在必须指向同一个元素。
	
	4.找到中间值很容易！它只是两个指针 lo_median 和 hi_median 所指元素的平均值。
	
	
复杂度分析:
	时间复杂度：O(logn)+O(1)≈O(logn)。
		对于标准 multiset 方案，插入数字需要花费 O(logn) 时间。
		找到平均值需要固定的 O(1) 时间，因为中位数元素可以直接从两个指针访问。
	空间复杂度：O(n) 用于在容器中保存输入的线性空间。
*/

// 执行用时：156 ms  内存消耗：46 MB
class MedianFinder_multiset {
    multiset<int> data;
    multiset<int>::iterator lo_median, hi_median;

public:
    MedianFinder_multiset()
        : lo_median(data.end())
        , hi_median(data.end())
    {
    }

    void addNum(int num)
    {
        const size_t n = data.size();   // store previous size

        data.insert(num);               // insert into multiset

        if (!n) {
            // no elements before, one element now
            lo_median = hi_median = data.begin();
        }
        else if (n & 1) {
            // odd size before (i.e. lo == hi), even size now (i.e. hi = lo + 1)

            if (num < *lo_median)       // num < lo
                lo_median--;
            else                        // num >= hi
                hi_median++;            // insertion at end of equal range
        }
        else {
            // even size before (i.e. hi = lo + 1), odd size now (i.e. lo == hi)

            if (num > *lo_median && num < *hi_median) {
                lo_median++;                    // num in between lo and hi
                hi_median--;
            }
            else if (num >= *hi_median)         // num inserted after hi
                lo_median++;
            else                                // num <= lo < hi
                lo_median = --hi_median;        // insertion at end of equal range spoils lo
        }
    }

    double findMedian()
    {
        return (*lo_median + *hi_median) * 0.5;
    }
};


/// 优化3的单指针版本
// 执行用时：156 ms  内存消耗：45.8 MB
class MedianFinder_multiset_one {
    multiset<int> data;
    multiset<int>::iterator mid;

public:
    MedianFinder_multiset_one()
        : mid(data.end())
    {
    }

    void addNum(int num)
    {
        const int n = data.size();
        data.insert(num);

        if (!n)                                 // first element inserted
            mid = data.begin();
        else if (num < *mid)                    // median is decreased
            mid = (n & 1 ? mid : prev(mid));
        else                                    // median is increased
            mid = (n & 1 ? next(mid) : mid);
    }

    double findMedian()
    {
        const int n = data.size();
        return (*mid + *next(mid, n % 2 - 1)) * 0.5;
    }
};

#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <unordered_map>

using namespace std;

/// 为了更好的理解第480题使用的大顶堆小顶堆方法，可以先查看第295题的题解


/** 480. 滑动窗口中位数
 ** 题目描述：
	中位数是有序序列最中间的那个数。如果序列的大小是偶数，则没有最中间的数；此时中位数是最中间的两个数的平均数。

	例如：

	[2,3,4]，中位数是 3

	[2,3]，中位数是 (2 + 3) / 2 = 2.5

	给出一个数组 nums，有一个大小为 k 的窗口从最左端滑动到最右端。窗口中有 k 个数，每次窗口向右移动 1 位。你的任务是找出每次窗口移动后得到的新窗口中元素的中位数，并输出由它们组成的数组。

	 

	示例：

	给出 nums = [1,3,-1,-3,5,3,6,7]，以及 k = 3。

	窗口位置                      中位数
	---------------               -----
	[1  3  -1] -3  5  3  6  7       1
	 1 [3  -1  -3] 5  3  6  7       -1
	 1  3 [-1  -3  5] 3  6  7       -1
	 1  3  -1 [-3  5  3] 6  7       3
	 1  3  -1  -3 [5  3  6] 7       5
	 1  3  -1  -3  5 [3  6  7]      6
	 因此，返回该滑动窗口的中位数数组 [1,-1,-1,3,5,6]。

	 

	提示：

	你可以假设 k 始终有效，即：k 始终小于输入的非空数组的元素个数。
	与真实值误差在 10 ^ -5 以内的答案将被视作正确答案。
*/
/**
 **提示1：
 The simplest of solutions comes from the basic idea of finding the median given a set of numbers. 
 We know that by definition, a median is the center element (or an average of the two center elements). 
 Given an unsorted list of numbers, how do we find the median element? If you know the answer to this question, 
 can we extend this idea to every sliding window that we come across in the array?
 
 **提示2：
 Is there a better way to do what we are doing in the above hint? Don't you think there is duplication of calculation being done there? 
 Is there some sort of optimization that we can do to achieve the same result? 
 This approach is merely a modification of the basic approach except that it simply reduces duplication of calculations once done.
 
 **提示3：
 The third line of thought is also based on this same idea but achieving the result in a different way.
 We obviously need the window to be sorted for us to be able to find the median. 
 Is there a data-structure out there that we can use (in one or more quantities) to obtain the median element extremely fast, 
 say O(1) time while having the ability to perform the other operations fairly efficiently as well?

*/

class Solution {
public:

///维护一个长度为k的vector数组，每次滑动就从滑动窗口中删除离开的那个数（二分查找O(lgn)），然后插入新的进入窗口的数，
///采用插入排序（On）,从排序后的数组值那个找出中位数。 发现官方的lower_bound好像要比自己写的二分查找快些-
	vector<double> medianSlidingWindow_insertsort(vector<int>& nums, int k) {
		vector<long long>arr;
		vector<double>ans;
		int  i, j;
		for (int i = 0; i < k; i++)
		arr.push_back(nums[i]);
		sort(arr.begin(), arr.end());
		ans.push_back((arr[k / 2] + arr[(k - 1) / 2]) / 2.0);
		for ( i = k; i < nums.size(); i++)
		{
			arr.erase(lower_bound(arr.begin(), arr.end(), nums[i - k]));
			arr.push_back(nums[i]);
			for ( j = k - 2; j >= 0; j--)
			{
				if (arr[j] > arr[j + 1])
				swap(arr[j], arr[j + 1]);
				else break;
			}
			ans.push_back((arr[k / 2] + arr[(k - 1) / 2]) / 2.0);
		}
		return ans;
	}

/// 优化1： 
/** 使用两个堆（大顶堆和小顶堆）维护滑动窗口内的数据。当移动窗口时，有一个元素会被移除，也就是要删除堆中的元素。
	“延迟删除”：当两个堆平衡时，从堆顶获得中位数。
	我们可以使用哈希表来标记所有被移除的无效元素，如果某个堆的堆顶是一个无效元素，我们才会把它删除。下面给出了我们的算法：

	1. 我们维护两个堆：

		一个大根堆 lo，用来存放较小的那一半的元素；

		一个小根堆 hi，用来存放较大的那一半的元素。

	2. 使用哈希集合（HashSet）或者哈希映射（HashMap），记为 hash_table，标记所有被移除的无效元素，哈希表的大小等于在堆中无效元素的数量；

	3. 大根堆 lo 最多允许比小根堆 hi 存放多一个元素，当我们已经处理了 k 个元素时：

		如果 k = 2n + 1 为奇数，那么 lo 中存储 k + 1 个元素，hi 中存储 k 个元素；

		如果 k = 2n 为偶数，那么 lo 和 hi 中都存储 k 个元素；

		根据这样的性质，我们就可以从堆顶元素得到中位数。

	4. 注意：当我们考虑堆中的元素个数时，我们指的是堆中有效的元素个数，无效的元素并不会被计入，它们只是暂时地被存放在堆中；

	5. 使用变量 balance 表示两个堆是否平衡：

		如果 balance == 0，那么两个堆平衡；

		如果 balance < 0，那么 lo 中的元素较少，需要从 hi 中取出若干个元素放入 lo；

		如果 balance > 0，那么 hi 中的元素较少，需要从 lo 中取出若干个元素放入 hi。

	6. 此时我们需要插入一个新的元素 in_num：

		如果 in_num 小于等于 lo 的堆顶元素，那么它可以被放入 lo 中，此时需要增加 balance 的值；

		否则，in_num 可以被放入 hi 中，此时需要减少 balance 的值。

	7. 延迟删除被移出窗口的元素 out_num：

		如果 out_num 在 lo 中，那么需要减少 balance 的值；

		如果 out_num 在 hi 中，那么需要增加 balance 的值；

		我们将 out_num 放入哈希表中；

		每当无效的元素出现在堆顶，我们就将其从堆中删除，同时从哈希表中删除。

复杂度分析：
	时间复杂度：O(Nlogk)，其中 N 是数组的长度。
	空间复杂度：O(N)。
*/

	//执行用时：56 ms  内存消耗：17.1 MB
	vector<double> medianSlidingWindow_heap(vector<int>& nums, int k)
	{
		vector<double> medians;
		unordered_map<int, int> hash_table;
		priority_queue<int> lo;                                 // max heap
		priority_queue<int, vector<int>, greater<int> > hi;     // min heap

		int i = 0;      // index of current incoming element being processed

		// initialize the heaps
		while (i < k)
			lo.push(nums[i++]);
		for (int j = 0; j < k / 2; j++) {
			hi.push(lo.top());
			lo.pop();
		}

		while (true) {
			// get median of current window
			medians.push_back(k & 1 ? lo.top() : ((double)lo.top() + (double)hi.top()) * 0.5);

			if (i >= nums.size())
				break;                          // break if all elements processed

			int out_num = nums[i - k],          // outgoing element
				in_num = nums[i++],             // incoming element
				balance = 0;                    // balance factor

			// number `out_num` exits window
			balance += (out_num <= lo.top() ? -1 : 1);
			hash_table[out_num]++;

			// number `in_num` enters window
			if (!lo.empty() && in_num <= lo.top()) {
				balance++;
				lo.push(in_num);
			}
			else {
				balance--;
				hi.push(in_num);
			}

			// re-balance heaps
			if (balance < 0) {                  // `lo` needs more valid elements
				lo.push(hi.top());
				hi.pop();
				balance++;
			}
			if (balance > 0) {                  // `hi` needs more valid elements
				hi.push(lo.top());
				lo.pop();
				balance--;
			}

			// remove invalid numbers that should be discarded from heap tops
			while (hash_table[lo.top()]) {
				hash_table[lo.top()]--;
				lo.pop();
			}
			while (!hi.empty() && hash_table[hi.top()]) {
				hash_table[hi.top()]--;
				hi.pop();
			}
		}

		return medians;
	}

///优化2：
/** 多重集合 + 迭代器
	这种方法基于特定的语言，即 C++ 中的 multiset（多重集合）数据结构。

	我们使用一个多重集合和一个迭代器（iterator），其中迭代器指向集合中的中位数。当我们添加或删除元素时，我们修改迭代器的指向，保证其仍然指向中位数。下面给出了我们的算法：

		1. 我们维护多重集合 window 的迭代器 mid；

		2. 首先我们在 window 中加入前 k 个元素，并让 mid 指向 window 中的第 ⌊k/2⌋ 个元素（从 0 开始计数）；

		3. 当我们在 window 中加入数 num 时：

			如果 num < *mid，那么我们需要将 mid 往前移；

			如果 num >= mid，我们不需要对 mid 进行任何操作。

		4. 当我们在 windows 中删除数 num 时：

			如果 num < *mid，我们需要将 mid 先往后移，再删除 num；

			如果 num > *mid，我们不需要对 mid 进行任何操作；

			如果 num == *mid，我们需要找到 num 第一次出现的位置对应的迭代器（使用 lower_bound()）并删除，而不是删除 mid 对应的数。随后和 num < *mid 的处理方式相同。
			
	复杂度分析：
		时间复杂度：O(Nlogk)，其中 N 是数组的长度。
		空间复杂度：O(N)。
*/

	//执行用时：44 ms  内存消耗：18.5 MB
	vector<double> medianSlidingWindow(vector<int>& nums, int k)
	{
		vector<double> medians;
		multiset<int> window(nums.begin(), nums.begin() + k);

		auto mid = next(window.begin(), k / 2);

		for (int i = k;; i++) {

			// Push the current median
			medians.push_back(((double)(*mid) + *next(mid, k % 2 - 1)) * 0.5);

			// If all done, break
			if (i == nums.size())
				break;

			// Insert incoming element
			window.insert(nums[i]);
			if (nums[i] < *mid)
				mid--;                  // same as mid = prev(mid)

			// Remove outgoing element
			if (nums[i - k] <= *mid)
				mid++;                  // same as mid = next(mid)

			window.erase(window.lower_bound(nums[i - k]));
		}

		return medians;
	}

};

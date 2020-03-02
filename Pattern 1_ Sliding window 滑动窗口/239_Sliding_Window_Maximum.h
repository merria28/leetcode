#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <unordered_map>

using namespace std;

/** 239. 滑动窗口最大值
 ** 题目描述：
	给定一个数组 nums，有一个大小为 k 的滑动窗口从数组的最左侧移动到数组的最右侧。你只可以看到在滑动窗口内的 k 个数字。滑动窗口每次只向右移动一位。

	返回滑动窗口中的最大值。
 

	示例:
	输入: nums = [1,3,-1,-3,5,3,6,7], 和 k = 3
	输出: [3,3,5,5,6,7] 
	
	解释: 

	  滑动窗口的位置                最大值
	---------------               -----
	[1  3  -1] -3  5  3  6  7       3
	 1 [3  -1  -3] 5  3  6  7       3
	 1  3 [-1  -3  5] 3  6  7       5
	 1  3  -1 [-3  5  3] 6  7       5
	 1  3  -1  -3 [5  3  6] 7       6
	 1  3  -1  -3  5 [3  6  7]      7
	 

	提示：
	你可以假设 k 总是有效的，在输入数组不为空的情况下，1 ≤ k ≤ 输入数组的大小。

	 

	进阶：
	你能在线性时间复杂度内解决此题吗？
	
	提示1：
	How about using a data structure such as deque (double-ended queue)?
	
	提示2：
	The queue size need not be the same as the window’s size.
	
	提示3：
	Remove redundant elements and the queue should store only elements that need to be considered.
*/

class Solution {
public:
	//执行用时：92 ms  内存消耗：18.2 MB
	vector<int> maxSlidingWindow_1(vector<int>& nums, int k) {
		int n = nums.size();
		vector<int> res;

		// 1 ≤ k ≤ n
		if (k > n)
			res;

		int start(0), end(0), max_data_window(INT_MIN);

		while (end < n)
		{		
			while ((end - start + 1) == k)
			{
				max_data_window = INT_MIN;
				for (int i = start; i <= end; i++) {
					if (nums[i] > max_data_window)
						max_data_window = nums[i];
				}				
				res.push_back(move(max_data_window));

				start++;
			}
			end++;
		}

		return res;
    }
	
	//执行用时：20 ms  内存消耗：18 MB
	vector<int> maxSlidingWindow_2(vector<int>& nums, int k) {
		int n = nums.size();
		vector<int> res;

		// 1 ≤ k ≤ n
		if (k > n || k==0)
			return res;

		//deque<size_t>window; //双项队列存储数组的下标
		vector<size_t>window;
		// 操作方式：
		// 1. 当我们遇到新的数时，将新的数和双项队列的末尾（也就是window.back()）比较，如果末尾比新数小，则把末尾扔掉，直到该队列的末尾比新数大或者队列为空的时候才停止
		// 2. 双项队列中的所有值都要在窗口范围内
		// 结果:
		// 1. 变量的最前端（也就是 window.front()）是此次遍历的最大值的下标
		// 2. 保证队列里的元素是从头到尾降序的，由于队列里只有窗口内的数，所以他们其实就是窗口内第一大，第二大，第三大... 的数。

		/*Init K integers in the list*/
		for (size_t i = 0; i < k; i++) {
			while (!window.empty() && nums[i] > nums[window.back()]) { //比较双项队列中最后一个元素与当前元素的大小
				window.pop_back(); //删除最后一个
			}
			window.push_back(i);
		}
		res.push_back(nums[window.front()]);
		/*End of initialization*/

		for (size_t winEnd = k; winEnd < nums.size(); winEnd++) {
			// 判断队列中的第一个位置是否在窗口内
			// 不在则删除第一个元素
			// winEnd-winStart+1=k  ==>  winStart-1=winEnd-k 则index<=winEnd-k表示index不在窗口内
			if (!window.empty() && window.front() <= winEnd - k) {
				//window.pop_front();
				window.erase(window.begin());
			}
			while (!window.empty() && nums[winEnd] > nums[window.back()]) {
				window.pop_back();
			}
			window.push_back(winEnd);
			res.push_back(nums[window.front()]);
		}
		return res;

	}
	
	// deque 与 vector的不同之处在于：deque支持高效插入和删除容器的头部元素，因此也叫做双端队列。
	// deque容器为一个给定类型的元素进行线性处理，像向量一样，它能够快速地随机访问任一个元素，并且能够高效地插入和删除容器的尾部元素。
	// 这个题目中耗时上并未体现deque比vector的优越之处，但不影响我们开始接触它并感受它的使用方法。
	//执行用时：36 ms  内存消耗：18.7 MB
	vector<int> maxSlidingWindow(vector<int>& nums, int k) {
		int n = nums.size();
		vector<int> res;

		// 1 ≤ k ≤ n
		if (k > n || k==0)
			return res;

		deque<size_t>window; //双项队列存储数组的下标
		//vector<size_t>window;
		// 操作方式：
		// 1. 当我们遇到新的数时，将新的数和双项队列的末尾（也就是window.back()）比较，如果末尾比新数小，则把末尾扔掉，直到该队列的末尾比新数大或者队列为空的时候才停止
		// 2. 双项队列中的所有值都要在窗口范围内
		// 结果:
		// 1. 变量的最前端（也就是 window.front()）是此次遍历的最大值的下标
		// 2. 保证队列里的元素是从头到尾降序的，由于队列里只有窗口内的数，所以他们其实就是窗口内第一大，第二大，第三大... 的数。

		/*Init K integers in the list*/
		for (size_t i = 0; i < k; i++) {
			while (!window.empty() && nums[i] > nums[window.back()]) { //比较双项队列中最后一个元素与当前元素的大小
				window.pop_back(); //删除最后一个
			}
			window.push_back(i);
		}
		res.push_back(nums[window.front()]);
		/*End of initialization*/

		for (size_t winEnd = k; winEnd < nums.size(); winEnd++) {
			// 判断队列中的第一个位置是否在窗口内
			// 不在则删除第一个元素
			// winEnd-winStart+1=k  ==>  winStart-1=winEnd-k 则index<=winEnd-k表示index不在窗口内
			if (!window.empty() && window.front() <= winEnd - k) {
				window.pop_front();
				//window.erase(window.begin());
			}
			while (!window.empty() && nums[winEnd] > nums[window.back()]) {
				window.pop_back();
			}
			window.push_back(winEnd);
			res.push_back(nums[window.front()]);
		}
		return res;

	}
};

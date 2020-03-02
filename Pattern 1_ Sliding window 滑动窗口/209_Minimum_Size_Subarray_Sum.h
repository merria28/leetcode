#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <unordered_map>

using namespace std;

/** 209_Minimum_Size_Subarray_Sum
 ** 题目描述：
	给定一个含有 n 个正整数的数组和一个正整数 s ，找出该数组中满足其和 ≥ s 的长度最小的连续子数组。如果不存在符合条件的连续子数组，返回 0。

	示例:
	输入: s = 7, nums = [2,3,1,2,4,3]
	输出: 2
	
	解释: 子数组 [4,3] 是该条件下的长度最小的连续子数组。
	
	进阶:
	如果你已经完成了O(n) 时间复杂度的解法, 请尝试 O(n log n) 时间复杂度的解法。
*/

class Solution {
public:
	
	/*
	思路1：使用滑动窗口的技巧来完成，要看过一遍整个数组的元素，时间复杂度是 O(n)。要求满足区间和 >= s 的最小子区间的长度，因此，我们从左向右进行扫描。

	情况1：当区间和小于 s 的时候，右区间的端点向右扩展，这一点依赖外层循环的遍历就可以完成；

	情况2：一旦区间和大于等于 s，尝试一步一步缩小左区间端点，看看是否能得到一个更短的区间，满足区间和 >=s，这一步通过一个内层循环实现。
	*/
	
	// 执行用时：12 ms  内存消耗：10 MB
	// 时间复杂度 O(n)
    int minSubArrayLen_1(int s, vector<int>& nums) {
        int window = nums.size() + 1;
        int winStart = 0;
        int sum = 0;

        for (int winEnd = 0; winEnd < nums.size(); winEnd++)
        {
            sum += nums[winEnd];
            while (sum >= s)
            {
                window = min(window, winEnd - winStart + 1);
                sum -= nums[winStart++];
            }
        }
        // 题目中的特殊情况处理
        if (window == nums.size() + 1)
            return 0;

        return window;
    }
	
	// 执行用时：8 ms  内存消耗：10.2 MB
	// 时间复杂度 O(n)
	int minSubArrayLen_2(int s, vector<int>& nums) {
        int window = nums.size() + 1;
        int winStart = 0;
        int sum = 0;

        for (int winEnd = 0; winEnd < nums.size(); winEnd++)
        {
            sum += nums[winEnd];
            while (sum >= s)
            {
                window = min(window, winEnd - winStart + 1);
                sum -= nums[winStart];
                winStart++;
            }
        }
        // 题目中的特殊情况处理
        if (window == nums.size() + 1)
            return 0;

        return window;
    }
	
	/*
	思路 2：外层循环是全部遍历作为所求连续区间的左边界，内层是一个二分法，用来求连续区间的右边界
			sums[right] >= s+sums[left]-nums[left] = s+sums[left-1]
			右边界从最大值开始，若满足上述条件，则将区间变为[left,mid]
			否则，在区间[mid+1,n-1]中更新中值mid
	*/
	
	// 执行用时：8 ms  内存消耗：12.7 MB
	// 时间复杂度  O(n log n)： 外层循环是全部遍历，内层是一个二分法
	int minSubArrayLen_1(int s, vector<int>& nums) {
		int n = nums.size();
		if (n == 0)
			return 0;

		// 计算前i个数的和
		//vector<int> sums(n,0);
		//sums[0] = nums[0];
		//for (int i = 1; i < n; i++)
		//	sums[i] = sums[i - 1] + nums[i];

		// 子区间[i,j]的和为 sij=sums[j]-sums[i]+nums[i]
		// sij≥s，则 sums[j]≥s+sums[i]-nums[i]
		// 即sums[j]≥s+sums[i-1]
		// 我们可以使用二分搜索的方法找到sums中不小于s+sums[i-1] 的第一个sums[j]
		// 即设定左边界为i,寻找符合条件的第一个右边界j


		// 为了方便计算，设置sums有n+1项
		// sums[i]表示前i-1个数的和
		// sums[0]=0
		vector<int> sums(n + 1, 0);
		for (int i = 1; i <= n; i++)
			sums[i] = sums[i - 1] + nums[i - 1];
	 

		int ans = INT_MAX; //因为要求最小区间，将区间范围设置为最大

		for (int i = 1; i <= n; i++)
		{		
			int to_find = s + sums[i - 1];
			// 利用lower_bound函数实现二分法
			/*auto bound = lower_bound(sums.begin(), sums.end(), to_find);
			int range = static_cast<int>(bound - sums.begin()) - i + 1;
			if (bound != sums.end())
				ans = min(ans, range);*/

			// 寻找区间[l,n-1]中满足其和 ≥ s 的长度最小的连续子数组的右边界
			int l = i-1, r = n-1;
			if (sums[r + 1] - sums[l + 1] + nums[l] < s) break;
			while (l < r)
			{
				int mid = l + (r - l)/2;
				if (sums[mid + 1] >= to_find) //区间[l,mid]的和大于等于s
					r = mid;
				else
					l = mid + 1;
			}
			ans = min(ans, r - i + 2);  // r-(i-1)+1;
		}

		return (ans != INT_MAX) ? ans : 0;
	}
};

#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <unordered_map>

using namespace std;


/** 978. 最长湍流子数组
 ** 题目描述：
	当 A 的子数组 A[i], A[i+1], ..., A[j] 满足下列条件时，我们称其为湍流子数组：

	若 i <= k < j，当 k 为奇数时， A[k] > A[k+1]，且当 k 为偶数时，A[k] < A[k+1]；
	或 若 i <= k < j，当 k 为偶数时，A[k] > A[k+1] ，且当 k 为奇数时， A[k] < A[k+1]。
	也就是说，如果比较符号在子数组中的每个相邻元素对之间翻转，则该子数组是湍流子数组。

	返回 A 的最大湍流子数组的长度。

	 
	示例 1：
	输入：[9,4,2,10,7,8,8,1,9]
	输出：5
	解释：(A[1] > A[2] < A[3] > A[4] < A[5])
	
	示例 2：
	输入：[4,8,12,16]
	输出：2
	
	示例 3：
	输入：[100]
	输出：1
	 

	提示：
	1 <= A.length <= 40000
	0 <= A[i] <= 10^9
*/

/// 关于运行时间的题外话
/// leetcode的编译器很是奇怪，对于这道题的动态规划方法，优化后的代码，明显比优化前的运行时间要少，且我经过vs测试后得到同样的结论
/// 虽然不同编译器的优化效果是不同的，但是同一台设备（只性能相同的设备）上的优化后代码应该更快速才对
/// 看到leetcode编译器如此气人，不死心的我对于函数maxTurbulenceSize_3，我经过vs测试（1000次后的平均值，加inline最保险，其他不想吐槽了
/*
    // 执行用时：108 ms  -->  0.143050   未用static，inline， &
	// 执行用时：96  ms  -->  0.136315   static 未用&
	// 执行用时：152 ms  -->  0.133107   inline 未用&
	// 执行用时：144 ms  -->  0.14305    static + &
	// 执行用时：84  ms  -->  0.136956   inline + &
*/

class Solution {
public:

	// 执行用时：80 ms  内存消耗：39.3 MB 
	int maxTurbulenceSize_1(vector<int>& A) {	
		// 处理特殊情况
		if (A.size() < 1) return A.size();
		if (A.size() <= 2) return 1;


		// 数组有三个数及以上才需要判断是否是湍流数组

		//INT_MAX 2147483647
		int maxlen = 0;

		int a, b;

		int start = 0, end = 0;

		int i = start;
		while (i + 2 < A.size())
		{			
			// 以start+1为中心点
			a = A[i + 1] - A[i];
			b = A[i + 1] - A[i + 2];

			//(a > 0 && b > 0) || (a < 0 && b < 0) 
			// a*b>0 满足湍流数组的条件, 则a*b<=0 不满足条件
			// 0 <= A[i] <= 10^9 a*b>INT_MAX
			if (a > 0) a = 1;
			else if (a < 0) a = -1;
			if (b > 0) b = 1;
			else if (b < 0) b = -1;		

			// 更新起始点
			if (a * b <= 0) {
				if (a * b == 0)
				{
					if (a == 0)
						maxlen = max(maxlen, i - start + 1); // 终止位置为i
					else
						maxlen = max(maxlen, i - start + 2); // 终止位置为i+1

				}
				else
				{
					// 当数组数量等于3时，只有一个元素对满足比较符号
					if(i==0)
						maxlen = max(maxlen, i - start + 2); // i+1-start+1
					else
					{
						a = A[i] - A[i - 1];
						b = A[i] - A[i + 1];
						if (a > 0) a = 1;
						else if (a < 0) a = -1;
						if (b > 0) b = 1;
						else if (b < 0) b = -1;
						if (a * b > 0)
							maxlen = max(maxlen, i - start + 2); // i+1-start+1
						else
							maxlen = max(maxlen, i - start + 1); //i-start+1
					}					
				}
					
				start = i + 1;
			}				
			else
				maxlen = max(maxlen, i - start + 3); 	 // i+2-start+1

			i++;
		}

		return maxlen;
	}


	// 执行用时：72 ms  内存消耗：39.5 MB 
	int maxTurbulenceSize_2(vector<int>& A) {
		// 处理特殊情况
		if (A.empty()) return 0;


		// 数组有三个数及以上才需要判断是否是湍流数组

		//INT_MAX 2147483647
		int maxlen = 1;

		int a, b;

		int start = 0, end = 1;

		while (end < A.size())
		{
			// 以end为中心点
			a = A[end] - A[end - 1];
			if (end + 1 < A.size())
				b = A[end] - A[end + 1];
			else
				b = 0;

			if (a > 0) a = 1;
			else if (a < 0) a = -1;
			if (b > 0) b = 1;
			else if (b < 0) b = -1;

			// 更新起始点
			if (a * b <= 0) {
				if (a != 0)
					maxlen = max(maxlen, end - start + 1);
				start = end;
			}

			end++;
		}

		return maxlen;
	}

	/*
	题目重点语句：如果比较符号在子数组中的每个相邻元素对之间翻转，则该子数组是湍流子数组。
	通俗点解释就是<、>、<、>要交替出现，不能出现连续的>、>或<、<或>、=或<、=。
	对于本题例子9 4 2 10 7 8 8 1 9，我们用-1，0，1来b表示两个数字之间的符号（小于，等于，大于），
	也就是说n个数字将产生n-1个符号，将例子转换后的结果为9 1>4 1> 2 -1< 10 1> 7 -1< 8 0= 8 1> 1 -1< 9 。
	窗口内的符号为1,1,-1,1,-1,0,1,-1，然后当我们遇到连续两个符号相等或符号为0时，
	也就是当我们发现湍流不成立时，我们需要划分窗口，所以可划分为四个窗口,1, 1,-1,1,-1, 0, 1,-1。
	*/
	// 执行用时：108 ms  内存消耗：39.6 MB  未用static，inline， &
	// 执行用时：96 ms   内存消耗：39.5 MB  static 未用&
	// 执行用时：152 ms  内存消耗：39.4 MB  inline 未用&
	// 执行用时：144 ms  内存消耗：39.3 MB  static + &
	// 执行用时：84 ms   内存消耗：39.6 MB  inline + &
	inline int compare(int& a, int& b) {
		return (a > b) ? 1 : (a == b) ? 0 : -1;
	}
	int maxTurbulenceSize_3(vector<int>& A) {
		if (A.empty())return 0;

		//初始化窗口边界，result以及数组边界
		int left = 0, right = 1, result = 1, N = A.size();

		while (right < N)
		{
			int flag = compare(A[right - 1], A[right]);

			//到达数组末尾或者湍流不成立时，开始划分窗口
			if (right == N - 1 || flag * compare(A[right], A[right + 1]) != -1)
			{
				if (flag != 0)result = max(result, right - left + 1);//划分窗口，更新result值
				left = right;//窗口左边界右移
			}
			++right;
		}
		return result;
	}
	
	// 动态规划
	// 动态数组记录连续异号：<、>、<、>交替出现的数字次数
	// 执行用时：42 ms  内存消耗：41.1 MB 
	int maxTurbulenceSize_4(vector<int>& A) {
		int N = A.size();
		if (N < 2) return N;
		vector<int> dp(N, 1);
		dp[0] = 1;
		for (int i = 1; i < N; i++) {
			if (A[i - 1] == A[i]) {
				dp[i] = 1;
			}
			else {
				if (i - 1 == 0 || (A[i - 2] < A[i - 1] == A[i - 1] > A[i])) dp[i] = dp[i - 1] + 1;
				else dp[i] = 2;
			}
		}
		int max_counter = 1;
		for (int i = 0; i < N; i++) {
			max_counter = max(max_counter, dp[i]);
		}
		return max_counter;
	}
	
	// 动态规划优化
	// 执行用时：120 ms  内存消耗：39.3 MB 
	int maxTurbulenceSize(vector<int>& A) {
		int N = A.size();
		if (N < 2) return N;
		int max_counter = 1;
		int dp_pre = 1;
		for (int i = 1; i < N; i++) {
			if (A[i - 1] == A[i]) {
				dp_pre = 1;
			}
			else {
				if (i - 1 == 0 || (A[i - 2] < A[i - 1] == A[i - 1] > A[i])) dp_pre = dp_pre + 1;
				else dp_pre = 2;
			}
			max_counter = max(max_counter, dp_pre);
		}
		return max_counter;
	}
    
};

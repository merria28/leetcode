#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <unordered_map>

using namespace std;


/** 567. 字符串的排序
 ** 题目描述：
	给定两个字符串 s1 和 s2，写一个函数来判断 s2 是否包含 s1 的排列。

	换句话说，第一个字符串的排列之一是第二个字符串的子串。

	示例1:

	输入: s1 = "ab" s2 = "eidbaooo"
	输出: True
	解释: s2 包含 s1 的排列之一 ("ba").
	 

	示例2:

	输入: s1= "ab" s2 = "eidboaoo"
	输出: False
	 
	示例3:
	"hello","ooolleoooleh" false

	注意：

	输入的字符串只包含小写字母
	两个字符串的长度都在 [1, 10,000] 之间
*/
/**
 **提示1：
 Obviously, brute force will result in TLE. Think of something else.
 
 **提示2：
 How will you check whether one string is a permutation of another string?
 
 **提示3：
 One way is to sort the string and then compare. But, Is there a better way?

 **提示4：
 If one string is a permutation of another string then they must one common metric. What is that?
 
 **提示5：
 Both strings must have same character frequencies, if one is permutation of another. Which data structure should be used to store frequencies?
 
 **提示6：
 What about hash table? An array of size 26?
 
*/

class Solution {
public:

    // 执行用时：16 ms  内存消耗：8.9 MB  动态数组
	// 执行用时：12 ms  内存消耗：8.7 MB  定长数组
	bool checkInclusion(string s1, string s2) {
		//s1不是s2的子串，直接排除
		if (s1.size() > s2.size())return false;

		int left = 0, right = 0;
		//vector<int> needs(26, 0), window(26, 0);//needs表示s1的字符表，window表示窗口，用来匹配s1的字符表needs
		int needs[26] = { 0 };
		int window[26] = { 0 };

		for (char c : s1)
		{
			needs[c - 'a']++;
			window[s2[right++] - 'a']++;
		}

		//if (window == needs)return true;//s2的前s1.size()个字符刚好与s1为异位词
		int i = 0;
		while (i < 26)
		{
			if (window[i] != needs[i])
				break;
			i++;
		}
		if (i == 26) return true;

		while (right < s2.size())//开始滑动窗口
		{
			window[s2[right++] - 'a']++;
			window[s2[left++] - 'a']--;
			//if (window == needs)return true;
			i = 0;
			while (i < 26)
			{
				if (window[i] != needs[i])
					break;
				i++;
			}
			if (i == 26) return true;
		}
		return false;
	}
};

#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <unordered_map>

using namespace std;

/** 3. 无重复字符的最长子串
 ** 题目描述：
	给定一个字符串，请你找出其中不含有重复字符的 最长子串 的长度。

	示例 1:
	输入: "abcabcbb"
	输出: 3
	解释: 因为无重复字符的最长子串是 "abc"，所以其长度为 3。
	
	示例 2:
	输入: "bbbbb"
	输出: 1
	解释: 因为无重复字符的最长子串是 "b"，所以其长度为 1。

	示例 3:
	输入: "pwwkew"
	输出: 3
	解释: 因为无重复字符的最长子串是 "wke"，所以其长度为 3。
 				请注意，你的答案必须是 子串 的长度，"pwke" 是一个子序列，不是子串。
*/ 

class Solution {
public:
	// 执行用时24ms， 内存消耗11.1MB
	int lengthOfLongestSubstring_1(string s)
	{
		int start(0), end(0), result(0);
		int sSize = int(s.size());
		unordered_map<char, int> hash;
		while (end < sSize)
		{
			hash[s[end]]++;

			while (hash[s[end]] > 1) {
				hash[s[start]]--;
				start++;
			}

			end++;
			result = max(result, end-start);
		}
		return result;
	}

	// 滑动窗口  
	// execute:better than 数组（桶）
	// 执行用时4ms， 内存消耗9MB
	int lengthOfLongestSubstring(string s)
	{
		//s[start,end) 前面包含 后面不包含
		int start(0), end(0), length(0), result(0);
		int sSize = int(s.size());
		while (end < sSize)
		{
			char tmpChar = s[end];
			for (int index = start; index < end; index++)
			{
				if (tmpChar == s[index])
				{
					start = index + 1;
					length = end - start;
					break;
				}
			}

			end++;
			length++;
			result = max(result, length);
		}
		return result;
	}
};
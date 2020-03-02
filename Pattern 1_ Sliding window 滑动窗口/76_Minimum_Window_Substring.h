#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <unordered_map>

using namespace std;

/** 76. 最小覆盖子串
 ** 题目描述：
	给你一个字符串 S、一个字符串 T，请在字符串 S 里面找出：包含 T 所有字母的最小子串。

	示例：
	输入: S = "ADOBECODEBANC", T = "ABC"
	输出: "BANC"
	
	说明：
	如果 S 中不存这样的子串，则返回空字符串 ""。
	如果 S 中存在这样的子串，我们保证它是唯一的答案。
	
	提示1：
	Use two pointers to create a window of letters in S, which would have all the characters from T.
	
	提示2：
	Since you have to find the minimum window in S which has all the characters from T, you need to expand and contract the window using the two pointers and keep checking the window for all the characters. This approach is also called Sliding Window Approach.

	L ------------------------ R , Suppose this is the window that contains all characters of T 
							  
			L----------------- R , this is the contracted window. We found a smaller window that still contains all the characters in T

	When the window is no longer valid, start expanding again
*/

/// 题目含义：
/// 题目不难理解，就是说要在 S(source) 中找到包含 T(target) 中全部字母的一个子串，顺序无所谓，但这个子串一定是所有可能子串中最短的。
/// 最容易忽略的一点：字符相同，字符数量也相同
// 参考： https://leetcode-cn.com/problems/find-all-anagrams-in-a-string/solution/hua-dong-chuang-kou-tong-yong-si-xiang-jie-jue-zi-/
// 可以用两个哈希表当作计数器解决。用一个哈希表 needs 记录字符串 t 中包含的字符及出现次数，用另一个哈希表 window 记录当前「窗口」中包含的字符及出现的次数，
// 如果 window 包含所有 needs 中的键，且这些键对应的值都大于等于 needs 中的值，那么就可以知道当前「窗口」符合要求了，可以开始移动 left 指针了。


class Solution {
public:

	//执行用时：36 ms  内存消耗：10.4 MB
	string minWindow_1(string s, string t) {
		// 记录最小子串的起始位置和长度
		int start = 0, minLen = INT_MAX;
		int left = 0,  right = 0; // 窗口边界

		// 用来包含 T 所有字母的最小子串。
		unordered_map<char, int> needs;
		unordered_map<char, int> window;

		// 记录目标字符串中所有字符出现的次数
		for (char c : t)
			needs[c]++;

		int match = 0;

		while (right < s.size())
		{
			// 记录窗口内的字符出现的次数
			char c1 = s[right];
			if (needs.count(c1)) // 判断key=s1是否存在
			{
				window[c1]++;
				if (window[c1] == needs[c1]) // 判断键值（即字符出现的次数）是否相等
					match++;
			}
			right++;

			
			while (match == needs.size()) {
				// 更新最小窗口
				if (right - left < minLen)
				{
					start = left;
					minLen = right - left;
				}

				// 满足条件，开始缩小窗口
				char c2 = s[left];
				if (needs.count(c2))
				{
					window[c2]--; // 移出 window
					if (window[c2] < needs[c2]) // 字符 c2 出现次数不再符合要求
						match--;						
				}
				left++;
			}
		}

		return minLen == INT_MAX ? "" : s.substr(start, minLen);
	}
	
	//执行用时：20 ms  内存消耗：10.4 MB
	string minWindow(string s, string t) {
		unordered_map<char, int> map;
		for (auto c : t) map[c]++; 

		// map的所有字符数量都大于等于1
		// map中不存在等于s[i]的字符时，对应的初始数量为0

		int left = 0, cnt = 0, minlen = s.size() + 1, start = left;

		for (int i = 0; i < s.size(); ++i) {
			// 左边界不动，扩大右边界
			// 如果当前字符在map中，对应的数量-1之后必将大于等于0，匹配数量加一次
			// 将-1之后的数量赋予map，表示需要被匹配的字符找到一次；当某个字母的所有出现次数都找到时，map中对应的数量变为0
			if (--map[s[i]] >= 0)
				++cnt;


			while (cnt == t.size()) {
				if (minlen > i - left + 1) {
					minlen = i - left + 1;
					start = left;
				}

				// 右边界不动，缩小左边界
				// 此时所有t中的字符在map中显示的数量都大于等于0， +1之后都大于0
				// 所有不在t中的字符在map中显示的数量都为-1,+1之后都等于0
				// 左边界不在t中，匹配数量减一次
				if (++map[s[left]] > 0) 
					cnt--;

				left++;
			}
		}
		return minlen == s.size() + 1 ? "" : s.substr(start, minlen);

	}
};

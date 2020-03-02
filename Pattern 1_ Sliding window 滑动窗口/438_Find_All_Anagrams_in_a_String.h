#pragma once

#include <string>
#include <vector>
#include <iostream>

#include <unordered_map>

using namespace std;

/** 438. 找到字符串中所有字母异位词
 ** 题目描述：
	给定一个字符串 s 和一个非空字符串 p，找到 s 中所有是 p 的字母异位词的子串，返回这些子串的起始索引。

	字符串只包含小写英文字母，并且字符串 s 和 p 的长度都不超过 20100。

	说明：
	字母异位词指字母相同，但排列不同的字符串。
	不考虑答案输出的顺序。

	示例 1:
	输入:
	s: "cbaebabacd" p: "abc"
	输出:
	[0, 6]
	解释:
	起始索引等于 0 的子串是 "cba", 它是 "abc" 的字母异位词。
	起始索引等于 6 的子串是 "bac", 它是 "abc" 的字母异位词。

 		示例 2:
	输入:
	s: "abab" p: "ab"
	输出:
	[0, 1, 2]
	解释:
	起始索引等于 0 的子串是 "ab", 它是 "ab" 的字母异位词。
	起始索引等于 1 的子串是 "ba", 它是 "ab" 的字母异位词。
	起始索引等于 2 的子串是 "ab", 它是 "ab" 的字母异位词。	
*/

class Solution {
public:
	//执行用时：56 ms  内存消耗：11 MB
	vector<int> findAnagrams(string s, string p) {
		int n = s.size();
		int m = p.size();

		vector<int> res;
		if (n == 0)
			return res;

		unordered_map<char, int> window;
		unordered_map<char, int> map;
		for (char c : p) map[c]++;
		int size_of_map = map.size();

		int winStart = 0, cnt = 0; // 这里的cnt表示p中的不同字符（不重复的字符）数量在s的窗口中出现的数量和

		for (int winEnd = 0; winEnd <n; winEnd++)
		{
			// 判断s[winEnd]是否存在于map中，不存在时，数值默认为0
			if (map[s[winEnd]] > 0) {
				window[s[winEnd]]++;
				if (window[s[winEnd]] == map[s[winEnd]])
					cnt++;					
			}				
				

			while (cnt == size_of_map)
			{
				if ((winEnd - winStart + 1) == m)
					res.push_back(winStart);

				if (map[s[winStart]] > 0){
					window[s[winStart]]--;
					if (window[s[winStart]] < map[s[winStart]]) 
						cnt--;					
				}
				winStart++;
			}
		}


		return res;
	}
	
	//执行用时：16 ms  内存消耗：11.2 MB
	vector<int> findAnagrams(string s, string p) {
		int n = s.size();
		int m = p.size();

		vector<int> res;
		if (n == 0)
			return res;

		unordered_map<char, int> map;
		for (char c : p) map[c]++;
		
		// map的所有字符数量都大于等于1
		// map中不存在等于s[i]的字符时，对应的初始数量为0

		int winStart = 0, cnt = 0; // 这里的cnt表示p中的所有字符在s的窗口中出现的数量和
		// 因此while中的判断条件会有不同

		for (int winEnd = 0; winEnd < n; winEnd++)
		{
			// 先-1，然后赋值给map[s[winEnd]]
			if (--map[s[winEnd]] >= 0) {
				cnt++;
			}

			while (cnt == m)
			{
				if ((winEnd - winStart + 1) == m)
					res.push_back(winStart);
				if (++map[s[winStart]] > 0) {
					cnt--;
				}
				winStart++;
			}
		}


		return res;
	}
};

//
//  main.cpp
//  KMP
//
//  Created by 李佳 on 15/11/4.
//  Copyright © 2015年 LiJia. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
using namespace  std;

#define IN
#define OUT

//返回subStr在str匹配上了的起始位置。
size_t KMP(IN const string& str, IN const string& subStr)
{
    size_t pos = std::string::npos;
    
    size_t startPos = 0;
    size_t curMatchPos = 0;
    size_t subMatchPos = 0;
    
    vector<int> matchResult(subStr.size(), -1);
    
    while (startPos < str.size() - subStr.size())
    {
        if (str[startPos + curMatchPos] == subStr[curMatchPos])
        {
            if (curMatchPos == subStr.size() - 1) //得到匹配结果
                return startPos;
            if (curMatchPos != 0) //需要检查好后缀
            {
                int subLastPos = matchResult[curMatchPos - 1];
                if (subLastPos >= 0 && str[startPos + curMatchPos] == subStr[subMatchPos])
                {
                    matchResult[curMatchPos] += subLastPos + 1;
                    subMatchPos++;
                }
            }
            matchResult[curMatchPos] += 1;
            curMatchPos++;
        }
        else
        {
            if (curMatchPos != 0) //进行好后缀检查
            {
                int subLastPos = matchResult[curMatchPos - 1];
                if (str[startPos + curMatchPos] == subStr[subMatchPos])
                {
                    matchResult[curMatchPos] += subLastPos + 2;
                }
                
                if (matchResult[curMatchPos] > 0)
                {
                    startPos += curMatchPos - matchResult[curMatchPos];
                    curMatchPos = matchResult[curMatchPos];
                }
                else
                {
                    startPos += curMatchPos;
                    curMatchPos = 0;
                }
                
                matchResult.assign(matchResult.size(), -1);
            }
            else
            {
                startPos++;
                curMatchPos = 0;
            }
            subMatchPos = 0;
        }
    }
    return pos;
}


int main(int argc, const char * argv[])
{
    string str = "BBC ABCDAB ABCDABCDABDE";
    string subStr = "BCDAB";
    size_t pos = KMP(str, subStr);
    
    printf("pos = %zu", pos);
    return 0;
}

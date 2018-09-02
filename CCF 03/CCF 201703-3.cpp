/*
 本题要求由你来编写一个 Markdown 的转换工具，完成 Markdown 文本到 HTML 代码的转换工作。简化起见，本题定义的 Markdown 语法规则和转换规则描述如下：
 　　●区块：区块是文档的顶级结构。本题的 Markdown 语法有 3 种区块格式。在输入中，相邻两个区块之间用一个或多个空行分隔。输出时删除所有分隔区块的空行。
 　　○段落：一般情况下，连续多行输入构成一个段落。段落的转换规则是在段落的第一行行首插入 `<p>`，在最后一行行末插入 `</p>`。
 　　○标题：每个标题区块只有一行，由若干个 `#` 开头，接着一个或多个空格，然后是标题内容，直到行末。`#` 的个数决定了标题的等级。转换时，`# Heading` 转换为 `<h1>Heading</h1>`，`## Heading` 转换为 `<h2>Heading</h2>`，以此类推。标题等级最深为 6。
 　　○无序列表：无序列表由若干行组成，每行由 `*` 开头，接着一个或多个空格，然后是列表项目的文字，直到行末。转换时，在最开始插入一行 `<ul>`，最后插入一行 `</ul>`；对于每行，`* Item` 转换为 `<li>Item</li>`。本题中的无序列表只有一层，不会出现缩进的情况。
 　　●行内：对于区块中的内容，有以下两种行内结构。
 　　○强调：`_Text_` 转换为 `<em>Text</em>`。强调不会出现嵌套，每行中 `_` 的个数一定是偶数，且不会连续相邻。注意 `_Text_` 的前后不一定是空格字符。
 　　○超级链接：`[Text](Link)` 转换为 `<a href="Link">Text</a>`。超级链接和强调可以相互嵌套，但每种格式不会超过一层。
 */
#include <bits/stdc++.h>
#define PAR 1 //段落
#define TIT 2 //标题
#define SEQ 3 //无序列表
#define SPA 4 //空

using namespace std;

string int_to_string(int i) {
    stringstream ss;
    ss << i;
    string re;
    ss >> re;
    return re;
}

bool startWith(string &s1, string &s2) {
    if (s1.size() < s2.size()) {
        return false;
    }
    else {
        string sub = s1.substr(0, s2.size());
        if (s2 == sub) {
            return true;
        }
    }
    return false;
}

bool endWith(string &s1, string &s2) {
    if (s1.size() < s2.size()) {
        return false;
    }
    else {
        string sub = s1.substr(s1.size() - s2.size(), s2.size());
        if (s2 == sub) {
            return true;
        }
    }
    return false;
}

void _Text_handle(string &str) {
    string begin = "<em>", end = "</em>";
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '_') {
            for (int j = i + 1; j < str.size(); j++) {
                if (str[j] == ' ') {
                    break;
                }
                else if (str[j] == '_') {
                    str.replace(j, 1, end);
                    str.replace(i, 1, begin);
                    break;
                }
            }
        }
    }
}

void Link_handle(string &str) {
    string left = "<a href=\"", mid = "\">", right = "</a>";
    int l2 = -1, l1 = -1, r1 = -1, r2 = -1;
    for (int i = 0; i < str.size(); i++) {
        if (str[i] == '[') {
            l2 = i;
        }
        else if (str[i] == ']') {
            l1 = i;
        }
        else if (str[i] == '(') {
            r1 = i;
        }
        else if (str[i] == ')') {
            r2 = i;
            if (l2 != -1 && l1 != -1 && r1 != -1 && r2 != -1) {
                string s1, s2;
                s1 = str.substr(l2 + 1, l1 - l2 - 1);
                s2 = str.substr(r1 + 1, r2 - r1 - 1);
                string re = left + s2 + mid + s1 + right;
                str.replace(l2, r2 - l2 + 1, re);
                l2 = -1; l1 = -1; r1 = -1; r2 = -1;
            }
        }
        else if (str[i] == ' ') {
            l2 = -1; l1 = -1; r1 = -1; r2 = -1;
        }
    }
}

void Handle_line(string &str) {
    _Text_handle(str);
    Link_handle(str);
}

void PAR_handle(string &str) {
    str = "<p>" + str + "</p>";
}

void TIT_handle(string &str) {
    int i = 0, num = 0;
    do {
        char c = str[i];
        if (c == '#' || c == ' ') {
            if (num < 6 && c == '#') {
                num++;
            }
        }
        else {
            break;
        }
        i++;
    } while(i < str.size());
    str = str.substr(i, str.size() - i);
    str = "<h" + int_to_string(num) + ">" + str + "</h" + int_to_string(num) + ">";
}

void SEQ_handle(string &str) {
    int i = 0;
    do {
        char c = str[i];
        if (!(c == '*' || c == ' ')) {
            break;
        }
        i++;
    } while(i < str.size());
    str = str.substr(i, str.size() - i);
    string beg = "<ul>\n", end = "\n</ul>";
    string left = "<li>", right = "</li>";
    str = beg + left + str + right + end;
}

void handle_block(string &line, int FLAG) {
    switch (FLAG) {
        case PAR: //段落处理
            PAR_handle(line);
            break;
            
        case TIT: //标题处理
            TIT_handle(line);
            break;
            
        case SEQ: //无序列表处理
            SEQ_handle(line);
            break;
            
        case SPA:
            break;
    }
}

void handle_vec(vector<string> &v) {
    vector<string>::iterator it1, it2;
    it1 = v.begin();
    it2 = it1 + 1;
    string beg = "<ul>\n", end = "\n</ul>";
    string BEG = "<p>", END = "</p>";
    for (; it2 != v.end(); it1++, it2++) {
        string &s1 = *it1;
        string &s2 = *it2;
        bool f1 = endWith(s1, end);
        bool f2 = startWith(s2, beg);
        bool f3 = endWith(s1, END);
        bool f4 = startWith(s2, BEG);
        if (f1 && f2) {
            s1.replace(s1.size() - end.size(), end.size(), "");
            s2.replace(0, beg.size(), "");
        }
        if (f3 && f4) {
            s1.replace(s1.size() - END.size(), END.size(), "");
            s2.replace(0, BEG.size(), "");
        }
    }
}

vector<string> run() {
    string line;
    vector<string> output;
    while (getline(cin, line)) {
        if (line == "00")   break;
        char c = line[0];
        int FLAG;
        switch (c) {
            case '*':
                FLAG = SEQ;
                break;
                
            case '#':
                FLAG = TIT;
                break;
                
            case '\0':
                FLAG = SPA;
                break;
                
            default:
                FLAG = PAR;
                break;
        }
        handle_block(line, FLAG);
        Handle_line(line);
        output.push_back(line);
    }
    handle_vec(output);
    return output;
}

int main() {
    vector<string>::iterator it;
    vector<string> v = run();
    for (it = v.begin(); it != v.end(); it++) {
        if (*it == "")
            continue;
        cout << *it << endl;
    }
    return 0;
}

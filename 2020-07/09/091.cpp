//#include<iostream>
//#include<string>
//#include<string_view>
//using namespace std;
//
//string replace_post(string_view src, string_view new_post)
//{
//// �ҵ����λ��
//	auto pos = src.find(".") + 1;
//// ȡ���㼰��֮ǰ��ȫ���ַ���string_view��substr�᷵��һ��    
//// string_view��������Ҫȡdata()��ֵ��string����
//	string_view sv1 = src.substr(0, pos);
//	string s1 = sv1.data();
//	cout << "sv1 = " << sv1 << ", s1=" << s1 << endl;
//	return s1 + new_post.data();
//}
//
//int main()
//{
//	string_view sv = "abcdefg.xxx";
//	string s = replace_post(sv, "yyy");
//
//	cout << sv << " replaced post by yyy result is:" << s << endl;
//	return 0;
//}
//
//int main()
//{
//	string s = "abc";
//	cout << s << endl;
//	string_view sv(s);
//	cout << sv << endl;
//	s = 'A'+s ;
//	cout << s << endl;
//	cout << sv << endl;
//	return 0;
//}
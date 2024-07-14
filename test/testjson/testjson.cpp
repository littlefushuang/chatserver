#include<iostream>
#include<vector>
#include<map>
#include<string>
#include "json.hpp"
using json = nlohmann::json; 
using namespace std;


//json 序列化 
void func1() {
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello world!!!";
    string sendBuf = js.dump();
    cout << sendBuf.c_str() << endl;
}
void func2() {
    json js;
    js["id"] = {1,2,3,4,5};
    // 添加key-value
    js["name"] = "zhang san";
    // 添加对象
    js["msg"]["zhang san"] = "hello world";
    js["msg"]["liu shuo"] = "hello china";
    // 上面等同于下面这句一次性添加数组对象
    js["msg"] = {{"zhang san", "hello world"}, {"liu shuo", "hello china"}};
    cout << js << endl;
}
string func3() {
    json js;
    // 直接序列化一个vector容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);
    js["list"] = vec;
    // 直接序列化一个map容器
    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "泰山"});
    js["path"] = m;
    string sendBuf = js.dump();
    //cout<<sendBuf.c_str()<<endl;
    return sendBuf;

}




int main() {


    func1();
    func2();
    string recvBuf = func3();
    json jsbuf = json::parse(recvBuf);
    cout << jsbuf << endl;
    return 0;
}

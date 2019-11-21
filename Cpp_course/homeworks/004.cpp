/*
课程：C++面向对象程序设计
题目：STL实践练习
要求：用 multimap 实现实现好友列表
开发环境：Linux
编译器：g++
时间：2019.11.21
*/

# include <iostream>
# include <map>
# include <string>

using namespace std;

class FriendList {
public:
    FriendList() {};
    // ~FriendList() {delete this;};

    bool isFriend(string name, string partner);
    void add(string name, string partner);
    void remove(string name, string partner);
    void printList(string name);
    void update(string name, string partner, string newFriend);
private:
    multimap<string, string> myFriends;
};

// 判断是否是好友
bool FriendList::isFriend(string name, string partner) {
    auto start = myFriends.lower_bound(name);
    auto end = myFriends.upper_bound(name);
    for (;start != end; ++start)
        if (start->second == partner) return true;

    return false;
}

// 新增好友
void FriendList::add(string name, string partner) {
    if (isFriend(name, partner))
        return ;

    myFriends.insert(make_pair(name, partner));
}

// 删除好友
void FriendList::remove(string name, string partner) {
    if (!isFriend(name, partner))
        return ;

    auto op = myFriends.equal_range(name);
    for (; op.first != op.second; op.first++) {
        if (op.first->second == partner) {
            myFriends.erase(op.first);
            break;
        }
    }
    cout << "Remove a note of " << name << " and " << partner << endl;
}

// 获取好友列表
void FriendList::printList(string name) {
    cout << name << "'s friends:" << endl;
    auto op = myFriends.equal_range(name);
    for (; op.first != op.second; op.first++)
        cout << op.first->second << ", ";
    cout << endl;
}

// 更新好友
void FriendList::update(string name, string partner, string newFriend) {
    if (!isFriend(name, partner) && !isFriend(name, newFriend))
        return ;

    auto op = myFriends.equal_range(name);
    for (; op.first != op.second; op.first++) {
        if (op.first->second == partner) {
            op.first->second = newFriend;
            break;
        }
    }
}

int main() {
    FriendList friends;

    friends.add("Nick", "Bowser");
    friends.add("Nick", "Shadow");
    friends.add("Nick", "Lily");
    friends.add("Nick", "l1");
    friends.add("Nick", "l2");
    friends.add("Nick", "l3");
    friends.add("Nick", "l4");
    friends.add("Nick", "l5");
    friends.add("Nick", "l6");
    friends.add("Nick", "l7");
    friends.add("Nick", "l8");
    friends.add("Nick", "l9");
    friends.add("Nick", "l10");
    friends.add("Nick", "l11");
    friends.add("Nick", "l12");
    friends.add("Nick", "l13");
    friends.add("Nick", "l14");
    friends.add("Nick", "l15");
    friends.add("Nick", "l16");

    friends.printList("Nick");

    if (friends.isFriend("Nick", "Shadow"))
        cout << "Nick and Shadow are friends" << endl;
    else cout << "Nick and Shadow are not friends" << endl;

    friends.remove("Nick", "Bowser");
    friends.printList("Nick");

    friends.update("Nick", "Shadow", "Mick");
    friends.printList("Nick");

    return 0;
}

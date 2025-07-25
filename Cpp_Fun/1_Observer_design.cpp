//Task:-
//1.A channel can upload video
//2.All the subsciber get notify



#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Subscriber{
    public:
        virtual void notify(const string& videoTitle) = 0;
};

class Channel{
    vector<Subscriber*> subscribers;
    public:
        void subscribe(Subscriber* sub){
            subscribers.push_back(sub);
        }

        void uploadVideo(const string& title){
            cout<<"Channel uploaded: "<<title<<endl;
            for(auto* sub : subscribers){
                sub->notify(title);
            }
        }
};

class User:public Subscriber{
    string username;
    public:
        User(const string& name):username(name){}

        void notify(const string& videoTitle) override{
            cout<<username<<" got notified: New Video - "<<videoTitle<<endl;
        }
};

int main(){
    Channel cppNuts;

    User user1("Mritunjey");
    User user2("Ram");
    User user3("Rohit");

    cppNuts.subscribe(&user1);
    cppNuts.subscribe(&user2);
    cppNuts.subscribe(&user3);

    cppNuts.uploadVideo("Observer pattern in c++");
}
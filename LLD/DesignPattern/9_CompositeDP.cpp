//1.Treat individual objects and groups of objects in the same way
//File System Example:- file and folder




//      <<abstract>>
//FileSystemItem(ls, openAll, getSize, getName)----------------|
//     |                                                       |is-a + has-a
//     |                                                       |
//File(name, size, ls, openAll, getSize, getName)        Folder(name, vector<FileSystem>, ls, openAll, getSize, getName)



#include<iostream>
#include<vector>
#include<string>
#include<stdexcept>
using namespace std;

class FileSystemItem{
    public:
        virtual ~FileSystemItem() {};
        virtual void ls(int indent = 0) = 0;
        virtual void openAll(int indent = 0) = 0;
        virtual int getSize() = 0;
        virtual FileSystemItem* cd(cosnt string& name) = 0;
        virtual string getName() = 0;
        virtual bool isFolder()  = 0;
};

class File : public FileSystemItem{
    string name;
    int size;
    public:
        File(const string& n, int s){
            name = n;
            size = s;
        }

        void ls(int indent = 0) override{
            cout<< string(indent, ' ') << name << "\n";
        }

        void openAll(int indent = 0) override{
            cout<< string(indent, ' ') << name << "\n";
        }

        int getSize() override{
            return size;
        }

        FileSystemItem* cd(const string& name) override{
            throw runtime_error("Cannot cd into a file");
        }

        bool isFolder() override{
            return false;
        }
};

class Folder : public FileSystemItem{
    string name;
    vector<FileSystemItem*> child;
    public:
        Folder(const string& n){
            name = n;
        }
        ~Folder(){
            for(auto &c: child){
                delete c;
            }
        }

        void add(FileSystemItem* item){
            child.push_back(item);
        }

        void ls(int indent = 0) override{
            for(auto &c : child){
                if(c->isFolder()){
                    cout<< string(indent, ' ') << "+ " << c->getName() << "\n";
                }else{
                    cout<< string(indent, ' ') <<c->getName() << "\n";
                }
            }
        }

        
}







#include "Map.h"

using namespace std;

Map::Map(string filename){
    string n;
    int x, y;
    ifstream myfile(filename.c_str());
    if(!myfile.is_open()) cerr<<"Failed to open file/n";
    else{
        while(!myfile.eof()){
            myfile>>n;
            myfile>>x;
            myfile>>y;
            myfile.ignore(1000, '\n');
            array.push_back(new City(n, x, y));
        }
        myfile.close();

        //#build adjacency#
        for(int i = 0; i < array.size(); i++){
            vector<City*> xline, yline, up, down, left, right;
            for(int j = 0; j < array.size(); j++){
                if(array[i]->getXCoor() == array[j]->getXCoor()) xline.push_back(array[j]);
            }
            while(!xline.empty()){
                if(array[i]->getYCoor() < xline.back()->getYCoor()){
                    if(up.empty()){
                    up.push_back(xline.back());
                    xline.pop_back();
                    }
                    else if(up.back()->getYCoor() > xline.back()->getYCoor()){
                        up.pop_back();
                        up.push_back(xline.back());
                        xline.pop_back();
                    }
                    else xline.pop_back();
                } 
                else if(array[i]->getYCoor() > xline.back()->getYCoor()){
                    if(down.empty()){
                    down.push_back(xline.back());
                    xline.pop_back();
                    }
                    else if(down.back()->getYCoor() < xline.back()->getYCoor()){
                        down.pop_back();
                        down.push_back(xline.back());
                        xline.pop_back();
                    }
                    else xline.pop_back();
                }
                else xline.pop_back();
            }
            
            for(int j = 0; j < array.size(); j++){
                if(array[i]->getYCoor() == array[j]->getYCoor()) yline.push_back(array[j]);
            }
            while(!yline.empty()){
                if(array[i]->getXCoor() > yline.back()->getXCoor()){
                    if(left.empty()){
                        left.push_back(yline.back());
                        yline.pop_back();
                    }
                    else if(left.back()->getXCoor() < yline.back()->getXCoor()){
                        left.pop_back();
                        left.push_back(yline.back());
                        yline.pop_back();
                    }
                    else yline.pop_back();
                } 
                else if(array[i]->getXCoor() < yline.back()->getXCoor()){
                    if(right.empty()){
                    right.push_back(yline.back());
                    yline.pop_back();
                    }
                    else if(right.back()->getXCoor() > yline.back()->getXCoor()){
                        right.pop_back();
                        right.push_back(yline.back());
                        yline.pop_back();
                    }
                    else yline.pop_back();
                }
                else yline.pop_back();
            }
            if(!up.empty()){ 
                array[i]->addEdge(up.back());
                //cout<<array[i].getName()<<" up "<<up.back().getName()<<endl;
            }
            if(!down.empty()){ 
                array[i]->addEdge(down.back());
                //cout<<array[i].getName()<<" down "<<down.back().getName()<<endl;
            }
            if(!left.empty()) {
               // cout<<array[i].getName()<<" left "<<left.back().getName()<<endl;
                array[i]->addEdge(left.back());
            }
            if(!right.empty()){
               // cout<<array[i].getName()<<" right "<<right.back().getName()<<endl;
                array[i]->addEdge(right.back());
            }    
        }
        // std::list<City*> q;
        // q=array[0].getAdjacent();
        // for(auto i:q)
        // cout<<"name "<<i->getName()<<endl;
        
    }
}

City* Map::findByName(string cityName){
        for(int i = 0;i < array.size();i++){
            if(array[i]->getName() == cityName) 
                return array[i];
        }
    }

int Map::distance(City *a, City *b){
     if(a->getXCoor() == b->getXCoor()){
         return abs(a->getYCoor() - b->getYCoor());
     }
     else if(a->getYCoor() == b->getYCoor()){
         return abs(a->getXCoor() - b->getXCoor());
     }
     else{
         cout<<"wrong"<<endl;
         return -1;
     }
}

City* Map::closestCity(City * a){
    int min = 9999;
    City * temp = 0;
    for(auto i:a->ajacency){
        if(i->tag == false){
            if(a->getXCoor() == i->getXCoor()){
                 int t = abs(a->getYCoor() - i->getYCoor());
                 if(t < min){ 
                    min = t;
                    temp = i;
                 }
            }
            else if(a->getYCoor() == i->getYCoor()){
                int t = abs(a->getXCoor() - i->getXCoor());
                if(t < min){
                    min = t;
                    temp = i;
                } 
            }
        }
    }
    return temp;
}

unsigned int Map::pathDistance(City * start, City * dest){
    if(start == dest) return 0;
    else{
        shortestPath(start, dest);
        return dest->dis;
    } 
}

vector<City *> Map::shortestPath(City * start, City * dest){
    vector<City*> a,spt;
    int min;
    City* m;
    for(auto i:array){
        i->tag = false;
        i->dis = 9999;
        i->pre = 0;
    }
    start->dis = 0;
    start->pre = start;
    City * current = start;
    a.push_back(start);
    City* next = closestCity(current);
    
    for(int j=0; j < array.size(); j++){
        current->tag = true;
        for(auto i:current->ajacency){
            if(i->tag == false){
                i->dis = current->dis + distance(current, i);
                i->pre = current;
                a.push_back(i);
            }
        }
        if(next != 0){
            if(next->dis > (current->dis + distance(current, next)) && next->tag == false){
                next->dis = current->dis + distance(current, next);
                next->pre = current;
            }
        }
        min = 9999;
        m = start;
        for(auto i:a){
            if(i !=0 && i->dis < min && i->tag ==false){
                min = i->dis;
                m = i;
            }
        }
        //cout<<"next min city "<<m->getName()<<endl;
        current = m;
        next = closestCity(current);
    }
    
    if(dest->dis == 9999){
        //cout<<"no connection"<<endl;
        path.clear();
        return path;
    }
    else{
        City* temp = dest;
        while(temp != start){
            spt.push_back(temp);
            temp = temp->pre;
        }
        path.clear();
        path.push_back(start);
        while(!spt.empty()){
            path.push_back(spt.back());
            spt.pop_back();
        }
        
    }
    return path;
}



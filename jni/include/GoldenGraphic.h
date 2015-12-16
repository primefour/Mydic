#ifndef __GOLDEN_GRAPHIC_H__
#define __GOLDEN_GRAPHIC_H__
#include<map>
#include<vector>
#include<algorithm>
#include<string>
#include<stack>

using namespace std;


template<class VectexType,class EdgeType>
class Graphic{
    public:
    Graphic(bool isDirected){
        mIsDirected = isDirected;
    }

    typedef std::map<int,EdgeType> Successor;
    typedef std::pair<VectexType,Successor> GraphicType;
    int InsertVectex(VectexType &vectex){
        typename vector<GraphicType>::iterator begin = mAjsList.begin();
        typename vector<GraphicType>::iterator end = mAjsList.end();
        int i = 0;
        while(begin != end){
            if(begin->first == vectex){
                return i;
            }
            i++;
            begin ++;
        }
        if(begin == end){
            mAjsList.push_back(GraphicType(vectex,Successor()));
        }
        return mAjsList.size() -1;
    }

    void InsertEdge(VectexType &vectex1,VectexType &vectex2,EdgeType &value){
        int i1 = InsertVectex(vectex1);
        int i2 = InsertVectex(vectex2);
        pair<int,EdgeType> tmp(i2,value);

        //mAjsList[i1].second[i2] = value;
        mAjsList[i1].second.insert(tmp);
        if(!mIsDirected){
          //  map<int,EdgeType> tmpi(i1,value);
            mAjsList[i2].second[i1] = value;
        }
    }
    int GetVectexCount(){
        return mAjsList.size();
    }

    int GetEdgesCount(){
        typename vector<GraphicType>::iterator begin = mAjsList.begin();
        typename vector<GraphicType>::iterator end = mAjsList.end();
        int count = 0 ;
        while(begin != end){
            count += begin.second.size();
            begin ++;
        }
        if(mIsDirected){
            return count>>1;
        }else{
            return count;
        }
    }

    vector< Graphic<VectexType,EdgeType>* >& GetCircleAndConnectivity( vector< Graphic<VectexType,EdgeType>* > &cc){
        enum {
            NO_VISITED,
            VISITED,
            PROCESSED,
        }VisitType;
        vector<int> visit_status(mAjsList.size(),NO_VISITED);
        stack<int,vector<int> > visit_stack;

        int vectex_idx = 0;
        int count = mAjsList.size();
        while(vectex_idx < count){
            visit_stack.push(vectex_idx);
            Graphic<VectexType,EdgeType> *child_graph = NULL;
            if(visit_status[vectex_idx] == NO_VISITED){
                //new componount
                child_graph = new Graphic<VectexType,EdgeType>(mIsDirected);
                cc.push_back(child_graph);
            }
            int pre_idx = -1;
            while(!visit_stack.empty()){
                int vec_idx = visit_stack.top();
                visit_stack.pop();
                if(visit_status[vec_idx] == NO_VISITED){
                    typename map<int,EdgeType>::iterator s_begin = mAjsList[vec_idx].second.begin();
                    typename map<int,EdgeType>::iterator s_end = mAjsList[vec_idx].second.end();
                    while(s_begin != s_end){
                        if(visit_status[s_begin->first] == NO_VISITED){
                            visit_stack.push(s_begin->first);
                        }
                        s_begin ++;
                    }
                    visit_status[vec_idx] = VISITED;
                    visit_stack.push(vec_idx);
                }else if(visit_status[vec_idx] == VISITED){
                    if(pre_idx == -1 && child_graph->mAjsList.size() == 0){
                        child_graph->InsertVectex(mAjsList[vec_idx].first);
                        pre_idx =  vec_idx;
                    }else{
                        child_graph->InsertEdge(child_graph->mAjsList.back().first,mAjsList[vec_idx].first,mAjsList[pre_idx].second[vec_idx]);
                        pre_idx =  vec_idx;
                    }
                    visit_status[vec_idx] = PROCESSED;
                }

            }
        }
    }

    private:
        int GetIndex(VectexType vectex){
            typename  vector<GraphicType>::iterator begin = mAjsList.begin();
            typename  vector<GraphicType>::iterator end = mAjsList.end();
            int i = 0;
            while(begin != end){
                if(begin->first == vectex){
                    return i;
                }
                i++;
                begin ++;
            }
            return -1;
        }
        vector<GraphicType> mAjsList;
        bool mIsDirected;
};

#endif

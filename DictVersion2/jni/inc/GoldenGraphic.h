#ifndef __GOLDEN_GRAPHIC_H__
#define __GOLDEN_GRAPHIC_H__
#include<map>
#include<vector>
#include<algorithm>
#include<string>
#include<stack>
#include<stdio.h>

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
            printf("insert a vectex  %ld \n",mAjsList.size());
            mAjsList.push_back(GraphicType(vectex,Successor()));
        }
        return mAjsList.size() -1;
    }

    void InsertEdge(VectexType &vectex1,VectexType &vectex2,EdgeType &value){
        int i1 = InsertVectex(vectex1);
        int i2 = InsertVectex(vectex2);
        printf("i1 = %d i2 = %d  \n",i1 ,i2);
        //pair<int,EdgeType> tmp(i2,value);
        mAjsList[i1].second[i2] = value;
        //mAjsList[i1].second.insert(tmp);
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
            count += begin->second.size();
            begin ++;
        }
        if(!mIsDirected){
            return count>>1;
        }else{
            return count;
        }
    }

    vector< Graphic<VectexType,EdgeType>* >& GetConnectComponount( vector< Graphic<VectexType,EdgeType>* > &cc){
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
            vectex_idx ++;
        }
    }

    void debug_short_path(vector<int> &data){
        vector<int>::iterator begin = data.begin();
        vector<int>::iterator end = data.end(); 
        while(begin != end){
            printf("%d  \n",*begin);
            begin ++;
        }
        printf("xxxx size = %ld \n",data.size());
    }

    Graphic<VectexType,EdgeType>* GetShortPath(Graphic<VectexType,EdgeType> *cc,VectexType vectex1,VectexType vectex2,EdgeType undef){
        if(cc == NULL ) return NULL;

        int i1 = GetIndex(vectex1);
        int i2 = GetIndex(vectex2);
        printf("#########i1 = %d i2 = %d \n",i1,i2);
        if(i1 == -1 || i2 == -1){
            return NULL;
        }

        vector<int> des_vector;
        vector<int> pre_vector;
        vector<EdgeType> distance;

        stack<int,vector<int> > stack_route;
        stack_route.push(i1);

        printf("#########i1 = %d \n",__LINE__);
        des_vector.push_back(i1);
        pre_vector.push_back(i1);
        distance.push_back(undef);
        printf("#########i1 = %d \n",__LINE__);

        while(!stack_route.empty()){
            int idx = stack_route.top();
            printf("############idx = %d \n ",idx);
            stack_route.pop();
            typename map<int,EdgeType>::iterator begin = mAjsList[idx].second.begin();
            typename map<int,EdgeType>::iterator end = mAjsList[idx].second.end();
           
            //update distance
            while(begin != end){
                vector<int>::iterator des_begin  = des_vector.begin();
                vector<int>::iterator des_end = des_vector.end();
                vector<int>::iterator des_curr = find(des_begin,des_end,begin->first);
                vector<int>::iterator offset_t = find(des_begin,des_end,idx);
                if(des_curr == des_end){
                    //update pre and add new des in des vector
                    des_vector.push_back(begin->first);
                    pre_vector.push_back(idx);
                    distance.push_back(distance[offset_t - des_begin]+begin->second);
                    stack_route.push(begin->first);
                    printf("###################des##########\n");
                    debug_short_path(des_vector);
                    printf("###################pre##########\n");
                    debug_short_path(pre_vector);
                    printf("###################dis##########\n");
                    debug_short_path(distance);
                    printf("###################end##########\n");
                }else{
                    int offset = des_curr - des_begin;
                    //get distance  and update if it is less than curr
                    int c_dis = distance[offset_t - des_begin] + begin->second ;
                    //get index 0 ==> curr_dis
                    int d_dis = distance[offset] ;
                    printf("c_dis = %d d_dis = %d \n",c_dis,d_dis);
                    if(c_dis < d_dis){
                        pre_vector[offset] = idx ;
                        distance[offset] = c_dis;
                    }

                    printf("###################des##########\n");
                    debug_short_path(des_vector);
                    printf("###################pre##########\n");
                    debug_short_path(pre_vector);
                    printf("###################dis##########\n");
                    debug_short_path(distance);
                    printf("###################end##########\n");
                }
                begin ++;
            }
        }

        vector<int>::iterator xbegin  = des_vector.begin();
        vector<int>::iterator xend = des_vector.end();
        vector<int>::iterator xcurr = find(xbegin,xend,i2);
        int xoffset = xcurr - xbegin;
        printf("shortest distance is %d \n",distance[xoffset]);
        return cc;
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

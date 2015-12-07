package com.Dict.DictApp2;

import android.app.Activity;
import android.content.Context;
import android.graphics.drawable.AnimationDrawable;
import android.os.Bundle;
import android.os.Handler;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.Menu;
import android.view.MenuItem;
import android.view.View;
import android.view.ViewGroup;
import android.widget.AbsListView;
import android.widget.ArrayAdapter;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;

import java.util.ArrayList;


public class ListTestActivity extends Activity implements ListView.OnScrollListener {
    private TestListView mListView;
    private TestAdapter  mAdapter;
    private ArrayList<String> mDataList;
    private static int mIdx = 0;
    private final static String TAG="ListTestActivity ";
    private LayoutInflater mInf = null;


    private void UpdateDataList(ArrayList<String> dataList) {
        StringBuilder sb = new StringBuilder();
        sb.append("Hello");
        int i = 20;
        while(i-- > 0 ){
           dataList.add(sb.toString() + (mIdx ++) );
        }
    }


    View mfootView = null;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_list_test);
        mListView = (TestListView )findViewById(R.id.test_list_view);
        mDataList = new ArrayList<String>();
        UpdateDataList(mDataList );
        mAdapter = new TestAdapter(this,R.id.test_text);
        mListView.setAdapter(mAdapter);
        mListView.setOnScrollListener(this);
        mInf = getLayoutInflater();
        mfootView = mInf.inflate(R.layout.list_behind_item, null);
        mListView.addFooterView(mfootView);
    }

    int mScrollStatus = 0;
    Handler myHandler = new Handler();


    void TaskCompletedNotify() {
        myHandler.postDelayed(new Runnable(){
            @Override
            public void run() {
                Log.e(TAG,"#########Completed Task ");
                UpdateDataList(mDataList);
                mListView.removeFooterView(mfootView);
                mTaskIsRunning = false;

            }
        },2000);
    }


    boolean mTaskIsRunning  = false;

    void StartTask() {
        myHandler.postDelayed(new Runnable(){
            @Override
            public void run() {
                TaskCompletedNotify();
                Log.e(TAG,"#########start Task ");
            }
        },100);
    }



    @Override
    public void onScrollStateChanged(AbsListView absListView, int i) {
        Log.e(TAG,"onScrollStateChanged##### i = " + i);
        mScrollStatus = i;
        if(mListView != null && mfootView != null) {

            if (i == 0 && mTaskIsRunning == false ){
                mListView.removeFooterView(mfootView);
            }

            if(i == 1 && mListView.getFooterViewsCount() == 0){
                mListView.addFooterView(mfootView);
                if(mfootView.getVisibility() == View.VISIBLE){
                    TextView tv = (TextView) mfootView.findViewById(R.id.foot_loading_text);
                    //ImageView iv = (ImageView)mfootView.findViewById(R.id.foot_imageView);
                    //iv.setVisibility(View.INVISIBLE);
                    tv.setVisibility(View.VISIBLE);
                }
            }
        }
    }

    @Override
    public void onScroll(AbsListView absListView, int i, int i2, int i3) {
        Log.e(TAG,"onScroll##### i = " + i + "i2 = " + i2 + "  i3 = " + i3);
        if(mfootView != null && i + i2 == i3) {
            if(mTaskIsRunning == false) {
                mTaskIsRunning = true;
                StartTask();
            }
            if(mfootView.getVisibility() == View.INVISIBLE) {
                mfootView.setVisibility(View.VISIBLE);
            }
        }
    }

    class TestAdapter extends ArrayAdapter<String> {
        int mResourceId;
        LayoutInflater mInflater;

        public TestAdapter(Context context, int resource) {
            super(context, resource);
            mInflater = (LayoutInflater) context
                    .getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        }

        @Override
        public int getCount() {
            return mDataList.size();
        }

        @Override
        public String getItem(int pos) {
            return mDataList.get(pos);
        }

        @Override
        public long getItemId(int pos) {
            return pos;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            TextView v = null;
            if(convertView == null){
               convertView  = mInflater.inflate(R.layout.list_test_item,null);
                v = (TextView) convertView.findViewById(R.id.test_text);
            }else {
                v = (TextView) convertView.findViewById(R.id.test_text);
            }
            v.setText(mDataList.get(position));
            return v;
        }
    }


}

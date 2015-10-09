package com.Dict.DictApp2;

import android.app.Activity;
import android.content.Context;
import android.content.res.Resources;
import android.database.DataSetObserver;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.RemoteException;
import android.support.v4.app.Fragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.view.animation.AnimationUtils;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.TextView;


import com.Dict.DictApp2.dummy.DummyContent;

import java.util.ArrayList;
import java.util.Collection;
import java.util.Iterator;
import java.util.List;
import java.util.ListIterator;

/**
 * A list fragment representing a list of Slot1_Items. This fragment
 * also supports tablet devices by allowing list items to be given an
 * 'activated' state upon selection. This helps indicate which item is
 * currently being viewed in a {@link SlotDetailFragment}.
 * <p>
 */
public class SlotListFragment extends android.support.v4.app.Fragment {

    /**
     * The serialization (saved instance state) Bundle key representing the
     * activated item position. Only used on tablets.
     */
    private static final String STATE_ACTIVATED_POSITION = "activated_position";
    /**
     * The current activated item position. Only used on tablets.
     */
    private int mActivatedPosition = ListView.INVALID_POSITION;

    /**
     * A callback interface that all activities containing this fragment must
     * implement. This mechanism allows activities to be notified of item
     * selections.
     */

    private static final String TAG = "SlotListFragment";
    private Resources mResources;
    private List<String> mDictList ;
    private List<String> mAboutList;
    View mProgressContainer;
    View mListContainer;
    View mEmptyText;
    DictAdapter mDictAdapter;
    AboutAdapter mAboutAdapter;
    ListView mDictListView;
    ListView mAboutListView;
    boolean mListShown = false;
    public static final int DISK_SCAN_CHECKER =  0;

    void makeListShown() {
        getDictList();
        if (!mListShown) {
            mListShown = true;
            mDictAdapter= new DictAdapter(getActivity(),R.layout.fragment_list_item);
            mDictListView.setAdapter(mDictAdapter);
            if(getDictList().size() == 0){
                mEmptyText.setVisibility(View.VISIBLE);
            }else{
                mEmptyText.setVisibility(View.INVISIBLE);
            }
            mProgressContainer.startAnimation(AnimationUtils.loadAnimation(getActivity(), android.R.anim.fade_out));
            mProgressContainer.setVisibility(View.GONE);
            mListContainer.startAnimation(AnimationUtils.loadAnimation(getActivity(), android.R.anim.fade_in));
            mListContainer.setVisibility(View.VISIBLE);
        }
    }

    private Handler SlotListHandler = new Handler(){
        @Override
        public void handleMessage(Message msg) {

            switch (msg.what) {
                case DISK_SCAN_CHECKER :
                    Log.e(TAG,"############DISK_SCAN_CHECKER##########");
                    if(DictUtils.getService() != null){
                        Log.e(TAG, "############setActivateOnItemClick");
                        try {
                            Log.e(TAG,"DictUtils.getService().checkDiskScanComplete() " + DictUtils.getService().checkDiskScanComplete());
                            if(DictUtils.getService().checkDiskScanComplete()){
                                makeListShown();
                            }else{
                                Message msg1 = SlotListHandler.obtainMessage(DISK_SCAN_CHECKER) ;
                                SlotListHandler.sendMessageDelayed(msg1,1000);
                            }
                        } catch (RemoteException e) {
                            e.printStackTrace();
                        }
                    }
                    break;
                default:
                    break;
            }
        }
    };

    private List<String> getDictList(){
        try {
            if(DictUtils.getService() == null || !DictUtils.getService().checkDiskScanComplete()){
                return null;
            }
            mDictList = DictUtils.getService().getDictList();
        } catch (RemoteException e) {
            e.printStackTrace();
        }
        return mDictList;
    }

    private List<String> getAboutList() {
        if(mAboutList != null){
           return mAboutList ;
        }
        mAboutList = new ArrayList<String>();
        String[] about = mResources.getStringArray(R.array.dict_about);
        int i =0 ;
        for(String tmp:about){
            mAboutList.add(tmp);
        }
        return mAboutList;
    }
    /**
     * Mandatory empty constructor for the fragment manager to instantiate the
     * fragment (e.g. upon screen orientation changes).
     */
    public SlotListFragment() {

    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        Log.e(TAG,"############onCreate");
        super.onCreate(savedInstanceState);
        mResources = getActivity().getResources();
    }


     @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,Bundle savedInstanceState){
         Log.e(TAG,"############onCreateViev");
         View view = inflater.inflate(R.layout.fragment_list_frame, container, false);
         mProgressContainer = view.findViewById(R.id.progressContainer);
         mListContainer = view.findViewById(R.id.listContainer);
         mAboutListView = (ListView) view.findViewById(R.id.about_list);
         mDictListView = (ListView)view.findViewById(R.id.dict_list);
         mEmptyText = view.findViewById(R.id.empty);
         mAboutAdapter = new AboutAdapter(getActivity(),R.layout.fragment_list_item);
         mAboutListView.setAdapter(mAboutAdapter );


         Message msg1 = SlotListHandler.obtainMessage(DISK_SCAN_CHECKER) ;
         SlotListHandler.sendMessageDelayed(msg1,1000);

         return view;
     }

    @Override
    public void onAttach(Activity activity) {
        Log.e(TAG,"############onAttach");
        super.onAttach(activity);
    }

    @Override
    public void onDetach() {
        Log.e(TAG,"############onDetach");
        super.onDetach();
    }

    public void onListItemClick(ListView listView, View view, int position, long id) {
        // Notify the active callbacks interface (the activity, if the
        // fragment is attached to one) that an item has been selected.
    }

    @Override
    public void onSaveInstanceState(Bundle outState) {
        Log.e(TAG,"############onSaveInstanceState");
        super.onSaveInstanceState(outState);
        if (mActivatedPosition != ListView.INVALID_POSITION) {
            // Serialize and persist the activated item position.
            outState.putInt(STATE_ACTIVATED_POSITION, mActivatedPosition);
        }
    }

    /**
     * Turns on activate-on-click mode. When this mode is on, list items will be
     * given the 'activated' state when touched.
     */
    public void setActivateOnItemClick(boolean activateOnItemClick) {
        Log.e(TAG,"############setActivateOnItemClick");
        // When setting CHOICE_MODE_SINGLE, ListView will automatically
        // give items the 'activated' state when touched.
        mDictListView.setChoiceMode(activateOnItemClick
                ? ListView.CHOICE_MODE_SINGLE
                : ListView.CHOICE_MODE_NONE);
        mAboutListView.setChoiceMode(activateOnItemClick
                ? ListView.CHOICE_MODE_SINGLE
                : ListView.CHOICE_MODE_NONE);

    }

    private void setActivatedPosition(int position) {
        Log.e(TAG,"############setActivatedPositio");
        if (position == ListView.INVALID_POSITION) {
            mDictListView.setItemChecked(mActivatedPosition, false);
            mAboutListView.setItemChecked(mActivatedPosition, false);
        } else {
            mDictListView.setItemChecked(position, true);
            mAboutListView.setItemChecked(position, true);
        }
        mActivatedPosition = position;
    }

    class AboutAdapter extends ArrayAdapter<String> {
        int mResourceId;
        LayoutInflater mInflater;

        public AboutAdapter(Context context, int resource) {
            super(context, resource);
            mInflater = (LayoutInflater) context
                    .getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        }

        @Override
        public int getCount() {
            Log.e("AboutAdapter ","getAboutList().size() = " + getAboutList().size());
            return getAboutList().size();
        }

        @Override
        public String getItem(int pos) {
            return getAboutList().get(pos);
        }

        @Override
        public long getItemId(int pos) {
            return pos;
        }

        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            ViewHolder holder = null;
            if (convertView == null) {
                holder = new ViewHolder();
                convertView = mInflater.inflate(R.layout.fragment_list_item, null);
                holder.mAbout= (TextView) convertView.findViewById(R.id.dict_name);
                holder.mButton= (Button) convertView.findViewById(R.id.enable_button);
                convertView.setTag(holder);
            } else {
                holder = (ViewHolder) convertView.getTag();
            }
            holder.mAbout.setText(getAboutList().get(position));
            if (position == 0) {
                holder.mButton.setText(getActivity().getString(R.string.scanner));
                holder.mButton.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View view) {
                        try {
                            DictUtils.getService().scanPath(null);
                        } catch (RemoteException e) {
                            e.printStackTrace();
                        }
                    }
                });
            }
            return convertView;
        }

        private class ViewHolder {
            public TextView mAbout;
            public Button mButton;
        }
    }

    class DictAdapter extends ArrayAdapter<String>{
        int mResourceId ;
        LayoutInflater mInflater;
        public DictAdapter(Context context, int resource) {
            super(context,resource);
            mInflater = (LayoutInflater) context
                    .getSystemService(Context.LAYOUT_INFLATER_SERVICE);
        }
        @Override
        public int getCount(){
            try {
                if(DictUtils.getService() == null || !DictUtils.getService().checkDiskScanComplete()){
                    return 0;
                }
            } catch (RemoteException e) {
                e.printStackTrace();
            }
            return getDictList().size();
        }
        @Override
        public String getItem(int pos){
            try {
                if(DictUtils.getService() == null || !DictUtils.getService().checkDiskScanComplete()){
                    return null;
                }
            } catch (RemoteException e) {
                e.printStackTrace();
            }
            return getDictList().get(pos);
        }
        @Override
        public long getItemId(int pos){
            try {
                if(DictUtils.getService() == null || !DictUtils.getService().checkDiskScanComplete()){
                    return 0;
                }
            } catch (RemoteException e) {
                e.printStackTrace();
            }
            return pos;
        }
        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            try {
                if(DictUtils.getService() == null || !DictUtils.getService().checkDiskScanComplete()){
                    return convertView;
                }
            } catch (RemoteException e) {
                e.printStackTrace();
            }
            ViewHolder holder = null;
            if(convertView == null){
                holder = new ViewHolder();
                convertView = mInflater.inflate(R.layout.fragment_list_item, null);
                holder.dictName = (TextView) convertView.findViewById(R.id.dict_name);
                holder.enableButton = (Button) convertView.findViewById(R.id.enable_button);
                convertView.setTag(holder);
            }else {
                holder = (ViewHolder) convertView.getTag();
            }

            holder.dictName.setText(getDictList().get(position));
            try {
                if (DictUtils.getService().getDictStatus(getDictList().get(position))) {
                    holder.enableButton.setText(mResources.getString(R.string.remove));
                } else {
                    holder.enableButton.setText(mResources.getString(R.string.add));
                }
                holder.enableButton.setTag(getDictList().get(position));
            } catch (RemoteException e) {
                e.printStackTrace();
            }

            holder.enableButton.setOnClickListener(new View.OnClickListener() {
                @Override
                public void onClick(View view) {
                    Button aa = (Button) view;
                    try {
                        if (aa.getText().equals(mResources.getString(R.string.add))) {
                            DictUtils.getService().addDictionary((String) aa.getTag());
                            aa.setText(mResources.getString(R.string.remove));
                            DictUtils.getService().setDictStatus((String) aa.getTag(),true);
                        } else {
                            DictUtils.getService().removeDictionary((String) aa.getTag());
                            aa.setText(mResources.getString(R.string.add));
                            DictUtils.getService().setDictStatus((String) aa.getTag(),false);
                        }
                    } catch (RemoteException e) {
                        e.printStackTrace();
                    }
                }
            });
            return convertView;
        }

        private class ViewHolder {
            public TextView dictName;
            public Button   enableButton;
        }
    }
}

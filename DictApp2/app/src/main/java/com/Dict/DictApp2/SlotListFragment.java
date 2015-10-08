package com.Dict.DictApp2;

import android.app.Activity;
import android.content.Context;
import android.content.res.Resources;
import android.os.Bundle;
import android.os.RemoteException;
import android.support.v4.app.ListFragment;
import android.util.Log;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;
import android.widget.ArrayAdapter;
import android.widget.Button;
import android.widget.ImageView;
import android.widget.ListView;
import android.widget.TextView;


import com.Dict.DictApp2.dummy.DummyContent;

import java.util.ArrayList;
import java.util.List;

/**
 * A list fragment representing a list of Slot1_Items. This fragment
 * also supports tablet devices by allowing list items to be given an
 * 'activated' state upon selection. This helps indicate which item is
 * currently being viewed in a {@link SlotDetailFragment}.
 * <p>
 * Activities containing this fragment MUST implement the {@link Callbacks}
 * interface.
 */
public class SlotListFragment extends ListFragment {

    /**
     * The serialization (saved instance state) Bundle key representing the
     * activated item position. Only used on tablets.
     */
    private static final String STATE_ACTIVATED_POSITION = "activated_position";

    /**
     * The fragment's current callback object, which is notified of list item
     * clicks.
     */
    private Callbacks mCallbacks = sDummyCallbacks;

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
    private List<String> mDictList = new ArrayList<String>();

    public interface Callbacks {
        /**
         * Callback for when an item has been selected.
         */
        public void onItemSelected(String id);
    }

    private List<String> getList() {
        if(DictUtils.getService() == null || mResources == null){
            return null;
        }

        try {
            mDictList = DictUtils.getService().getDictList();
            if(mDictList == null){
                mDictList = new ArrayList<String>();
            }
            mDictList.add(0, mResources.getString(R.string.full_scanner));
        } catch (RemoteException e) {
            e.printStackTrace();
        }
        return mDictList;
    }
    /**
     * A dummy implementation of the {@link Callbacks} interface that does
     * nothing. Used only when this fragment is not attached to an activity.
     */
    private static Callbacks sDummyCallbacks = new Callbacks() {
        @Override
        public void onItemSelected(String id) {
        }
    };

    /**
     * Mandatory empty constructor for the fragment manager to instantiate the
     * fragment (e.g. upon screen orientation changes).
     */
    public SlotListFragment() {
    }

    @Override
    public void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        // TODO: replace with a real list adapter.
        setListAdapter(new DictAdapter(getActivity(),R.layout.fragment_list_item));
        if(DictUtils.getService() == null){
            return ;
        }
        getList();
    }

    @Override
    public void onViewCreated(View view, Bundle savedInstanceState) {
        super.onViewCreated(view, savedInstanceState);

        // Restore the previously serialized activated item position.
        if (savedInstanceState != null
                && savedInstanceState.containsKey(STATE_ACTIVATED_POSITION)) {
            setActivatedPosition(savedInstanceState.getInt(STATE_ACTIVATED_POSITION));
        }
    }

    @Override
    public void onAttach(Activity activity) {
        super.onAttach(activity);
        mResources = activity.getResources();
        // Activities containing this fragment must implement its callbacks.
        if (!(activity instanceof Callbacks)) {
            throw new IllegalStateException("Activity must implement fragment's callbacks.");
        }
        mCallbacks = (Callbacks) activity;
    }

    @Override
    public void onDetach() {
        super.onDetach();

        // Reset the active callbacks interface to the dummy implementation.
        mCallbacks = sDummyCallbacks;
    }

    @Override
    public void onListItemClick(ListView listView, View view, int position, long id) {
        super.onListItemClick(listView, view, position, id);

        // Notify the active callbacks interface (the activity, if the
        // fragment is attached to one) that an item has been selected.
        mCallbacks.onItemSelected(DummyContent.ITEMS.get(position).id);
    }

    @Override
    public void onSaveInstanceState(Bundle outState) {
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
        // When setting CHOICE_MODE_SINGLE, ListView will automatically
        // give items the 'activated' state when touched.
        getListView().setChoiceMode(activateOnItemClick
                ? ListView.CHOICE_MODE_SINGLE
                : ListView.CHOICE_MODE_NONE);
    }

    private void setActivatedPosition(int position) {
        if (position == ListView.INVALID_POSITION) {
            getListView().setItemChecked(mActivatedPosition, false);
        } else {
            getListView().setItemChecked(position, true);
        }

        mActivatedPosition = position;
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
            if(DictUtils.getService() == null){
                return 0;
            }
            return getList().size();
        }
        @Override
        public String getItem(int pos){
            if(DictUtils.getService() == null){
                return null;
            }
            return getList().get(pos);
        }
        @Override
        public long getItemId(int pos){
            if(DictUtils.getService() == null){
                return 0;
            }
            return pos;
        }
        @Override
        public View getView(int position, View convertView, ViewGroup parent) {
            if(DictUtils.getService() == null){
                return convertView;
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
            holder.dictName.setText(getList().get(position));
            if(position == 0){
                holder.enableButton.setText(mResources.getString(R.string.scanner));
                holder.enableButton.setOnClickListener(new View.OnClickListener() {
                    @Override
                    public void onClick(View view) {
                        try {
                            DictUtils.getService().scanPath(null);
                        } catch (RemoteException e) {
                            e.printStackTrace();
                        }
                    }
                });
            }else {
                try {
                    if (DictUtils.getService().getDictStatus(getList().get(position))) {
                        holder.enableButton.setText(mResources.getString(R.string.remove));
                    } else {
                        holder.enableButton.setText(mResources.getString(R.string.add));
                    }
                    holder.enableButton.setTag(getList().get(position));
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
            }

            return convertView;
        }

        private class ViewHolder {
            public TextView dictName;
            public Button   enableButton;
        }
    }
}

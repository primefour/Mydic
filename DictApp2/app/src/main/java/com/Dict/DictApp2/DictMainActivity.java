package com.Dict.DictApp2;

import android.app.Fragment;
import android.content.ComponentName;
import android.content.Intent;
import android.content.ServiceConnection;
import android.os.Bundle;
import android.os.RemoteException;
import android.support.v4.app.FragmentActivity;
import android.support.v4.view.ViewPager;
import android.util.Log;
import android.view.Window;
import android.widget.Button;


/**
 * Created by crazyhorse on 15-4-5.
 */
public class DictMainActivity extends FragmentActivity implements SlotListFragment.Callbacks,MainFragment.Callbacks {
    MainPagerAdapter mPagerAdapter;
    ViewPager mViewPager;
    ServiceBinder  mSBinder = new ServiceBinder(null);
    static final String TAG = "DictMainActivity ";

    public final static int SETTING_PAGE_IDX = 0;
    public final static int MAIN_PAGE_IDX = 1;
    public final static int NEWS_PAGE_IDX = 2;

    public IDictQueryService sService = null;


    private class ServiceBinder implements ServiceConnection{
        ServiceConnection mCallback;

        ServiceBinder(ServiceConnection callback){
            mCallback = callback ;
        }
        public void onServiceConnected(ComponentName className, android.os.IBinder binder){
            Log.e(TAG,"onServiceConnected");
            sService = IDictQueryService.Stub.asInterface(binder);
            if(mCallback != null){
                mCallback.onServiceConnected(className,binder);
            }
        }

        public void onServiceDisconnected(ComponentName className){
            Log.e(TAG,"onServiceDisconnected");
            if(mCallback != null){
                mCallback.onServiceDisconnected(className);
            }
            sService = null;
        }
    }


    public void bindToService(){
        Intent ii = new Intent(this,DictQueryService.class);
        startService(new Intent(this,DictQueryService.class));
        bindService(ii,mSBinder,0);
    }

    public void unBindFromService(){
        unbindService(mSBinder);
        sService = null;
    }

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        getWindow().requestFeature(Window.FEATURE_PROGRESS);
        setContentView(R.layout.dict_main_activity);
        mPagerAdapter = new MainPagerAdapter( getSupportFragmentManager());
        mViewPager = (ViewPager) findViewById(R.id.pager);
        mViewPager.setAdapter(mPagerAdapter);
        mViewPager.setCurrentItem(MAIN_PAGE_IDX);
        bindToService();
    }


    @Override
    public void onDestroy() {
        unBindFromService();
        super.onDestroy();
    }

    public void onItemSelected(String id) {
            // In single-pane mode, simply start the detail activity
            // for the selected item ID.
            Intent detailIntent = new Intent(this, SlotDetailActivity.class);
            detailIntent.putExtra(SlotDetailFragment.ARG_ITEM_ID, id);
            startActivity(detailIntent);
    }

    public String onSearchButtonClick(String searchWord) {
        if(sService != null){
            try {
                return sService.queryWord(searchWord);
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }
        return "Service doesn't work !!";
    }

}

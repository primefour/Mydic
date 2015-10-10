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

import java.util.HashMap;


/**
 * Created by crazyhorse on 15-4-5.
 */
public class DictMainActivity extends FragmentActivity implements MainFragment.Callbacks {
    MainPagerAdapter mPagerAdapter;
    ViewPager mViewPager;
    static final String TAG = "DictMainActivity ";

    public final static int SETTING_PAGE_IDX = 0;
    public final static int MAIN_PAGE_IDX = 1;
    public final static int NEWS_PAGE_IDX = 2;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        //getWindow().requestFeature(Window.FEATURE_PROGRESS);
        setContentView(R.layout.dict_main_activity);
        mPagerAdapter = new MainPagerAdapter( getSupportFragmentManager());
        mViewPager = (ViewPager) findViewById(R.id.pager);
        mViewPager.setAdapter(mPagerAdapter);
        mViewPager.setCurrentItem(MAIN_PAGE_IDX);
        DictUtils.bindToService(this);
    }


    @Override
    public void onDestroy() {
        DictUtils.unBindFromService(this);
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
        if(DictUtils.getService() != null){
            try {
                return DictUtils.getService().queryWord(searchWord);
            } catch (RemoteException e) {
                e.printStackTrace();
            }
        }
        return "Service doesn't work !!";
    }

}

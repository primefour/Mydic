package com.Dict.DictApp2;

import android.app.Fragment;
import android.content.Intent;
import android.os.Bundle;
import android.support.v4.app.FragmentActivity;
import android.support.v4.view.ViewPager;
import android.util.Log;
import android.widget.Button;


/**
 * Created by crazyhorse on 15-4-5.
 */
public class DictMainActivity extends FragmentActivity implements SlotListFragment.Callbacks,MainFragment.Callbacks,DictSearchEngine.Callbacks {
    MainPagerAdapter mPagerAdapter;
    ViewPager mViewPager;
    DictSearchEngine mSE;
    Thread mInit = null;

    public final static int SETTING_PAGE_IDX = 0;
    public final static int MAIN_PAGE_IDX = 1;
    public final static int NEWS_PAGE_IDX = 2;



    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.dict_main_activity);
        mPagerAdapter = new MainPagerAdapter(
                getSupportFragmentManager());
        mViewPager = (ViewPager) findViewById(R.id.pager);
        mViewPager.setAdapter(mPagerAdapter);
        mViewPager.setCurrentItem(MAIN_PAGE_IDX);
        mSE = new DictSearchEngine();
        mInit = new Thread() {
            public void run() {
                Log.d("%s","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxDict");
                mSE.initEng();
                mSE.addDictionary("/sdcard/langdao-ec-gb.ifo");
                Log.d("%s","xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxDictxxx");
            }
        };
        mInit.start();
    }


    @Override
    protected void onDestroy() {
        if(mInit.isAlive()) {
            try {
                mInit.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }
        mSE.destroyEng();
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
        if(mInit.isAlive()) {
            try {
                mInit.join();
            } catch (InterruptedException e) {
                e.printStackTrace();
            }
        }

        TextMetaData tmp = mSE.queryWord(searchWord);
        return tmp != null ? tmp.mTextMeaning:null;

    }

    public void onWordMeaningArriving(String searchResult) {
        //for async query
        MainFragment mainFlagment = (MainFragment)mPagerAdapter.getItem(MAIN_PAGE_IDX);
        mainFlagment.setWordMeaningString(searchResult);
    }

    public void onWordMetaArriving(TextMetaData mt){

    }

}

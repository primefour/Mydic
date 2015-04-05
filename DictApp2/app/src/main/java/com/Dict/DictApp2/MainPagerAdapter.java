package com.Dict.DictApp2;

import android.app.Fragment;
import android.os.Bundle;
import android.support.v4.app.FragmentManager;
import android.support.v4.app.FragmentPagerAdapter;

/**
 * Created by crazyhorse on 15-4-4.
 */
public class MainPagerAdapter extends FragmentPagerAdapter {


    public MainPagerAdapter(FragmentManager fm) {
        super(fm);
    }

    public android.support.v4.app.Fragment getItem(int idx){
        Bundle arguments = new Bundle();
        switch(idx) {
            case DictMainActivity.SETTING_PAGE_IDX: {
                SlotListFragment mainPager = new SlotListFragment();
                mainPager.setArguments(arguments);
                return mainPager;
            }
            case DictMainActivity.MAIN_PAGE_IDX: {
                MainFragment mainPager = new MainFragment();
                mainPager.setArguments(arguments);
                return mainPager;
            }
            case DictMainActivity.NEWS_PAGE_IDX:

                break;
            default:
                //show MAIN_PAGE_IDX
                break;
        }

        MainFragment mainPager = new MainFragment();
        mainPager.setArguments(arguments);
        return mainPager;
    }

    @Override
    public int getCount() {
        return 2;
    }
}

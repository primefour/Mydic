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
        arguments.putString(MainFragment.PAGE_TITLE,"HELLO");
        return null;
    }

    @Override
    public int getCount() {
        return 0;
    }
}

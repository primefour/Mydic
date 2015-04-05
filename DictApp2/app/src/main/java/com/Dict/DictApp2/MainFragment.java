package com.Dict.DictApp2;

import android.os.Bundle;
import android.support.v4.app.Fragment;
import android.view.LayoutInflater;
import android.view.View;
import android.view.ViewGroup;


/**
 * Created by crazyhorse on 15-4-4.
 */
public class MainFragment extends Fragment {

    @Override
    public View onCreateView(LayoutInflater inflater, ViewGroup container,
                             Bundle savedInstanceState) {
        View viewMainFragment;
        viewMainFragment = inflater.inflate(R.layout.fragment_main_page,container,false);
        return viewMainFragment;
    }

}


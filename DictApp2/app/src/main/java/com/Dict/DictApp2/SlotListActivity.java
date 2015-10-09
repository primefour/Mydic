package com.Dict.DictApp2;

import android.content.Intent;
import android.os.Bundle;
import android.os.Handler;
import android.os.Message;
import android.os.RemoteException;
import android.support.v4.app.FragmentActivity;
import android.view.View;
import android.view.animation.AnimationUtils;


/**
 * An activity representing a list of Slot1_Items. This activity
 * has different presentations for handset and tablet-size devices. On
 * handsets, the activity presents a list of items, which when touched,
 * lead to a {@link SlotDetailActivity} representing
 * item details. On tablets, the activity presents the list of items and
 * item details side-by-side using two vertical panes.
 * <p>
 * The activity makes heavy use of fragments. The list of items is a
 * {@link SlotListFragment} and the item details
 * (if present) is a {@link SlotDetailFragment}.
 * <p>
 * This activity also implements the required
 * to listen for item selections.
 */
public class SlotListActivity extends FragmentActivity{
    private static final int DISK_SCAN_CHECKER = 0;
    /**
     * Whether or not the activity is in two-pane mode, i.e. running on a tablet
     * device.
     */
    private boolean mTwoPane;

    @Override
    protected void onCreate(Bundle savedInstanceState) {
        super.onCreate(savedInstanceState);
        setContentView(R.layout.activity_slot_list);

        if (findViewById(R.id.slot_detail_container) != null) {
            // The detail container view will be present only in the
            // large-screen layouts (res/values-large and
            // res/values-sw600dp). If this view is present, then the
            // activity should be in two-pane mode.
            mTwoPane = true;

            // In two-pane mode, list items should be given the
            // 'activated' state when touched.
            /*
            ((SlotListFragment) getSupportFragmentManager()
                    .findFragmentById(R.id.slot_list))
                    .setActivateOnItemClick(true);
                    */
        }
        DictUtils.bindToService(this);
        // TODO: If exposing deep links into your app, handle intents here.
    }



    @Override
    public void onDestroy(){
        DictUtils.unBindFromService(this);
        super.onDestroy();
    }
}

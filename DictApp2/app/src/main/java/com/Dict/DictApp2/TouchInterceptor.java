package com.Dict.DictApp2;

import android.content.Context;
import android.content.SharedPreferences;
import android.content.res.Resources;
import android.graphics.Bitmap;
import android.graphics.PixelFormat;
import android.graphics.Rect;
import android.graphics.drawable.Drawable;
import android.graphics.drawable.LevelListDrawable;
import android.util.AttributeSet;
import android.util.Log;
import android.view.GestureDetector;
import android.view.Gravity;
import android.view.MotionEvent;
import android.view.View;
import android.view.ViewConfiguration;
import android.view.ViewGroup;
import android.view.WindowManager;
import android.view.GestureDetector.SimpleOnGestureListener;
import android.widget.AdapterView;
import android.widget.ImageView;
import android.widget.ListAdapter;
import android.widget.ListView;
import android.widget.RelativeLayout;
import android.widget.Switch;

public class TouchInterceptor extends ListView {
    private static final String TAG="TouchInterceptor ";

    private WindowManager mWindowManager;
    private WindowManager.LayoutParams mWindowParams;
    private ImageView mDragView;
    private Bitmap mDragBitmap;

    /**
     * At which position is the item currently being dragged. Note that this
     * takes in to account header items.
     */
    private int mDragPos;
    /**
     * At which position was the item being dragged originally
     */
    private int mSrcDragPos;
    private int mDragPointX;    // at what x offset inside the item did the user grab it
    private int mDragPointY;    // at what y offset inside the item did the user grab it
    private int mXOffset;  // the difference between screen coordinates and coordinates in this view
    private int mYOffset;  // the difference between screen coordinates and coordinates in this view
    private DragListener mDragListener;
    private int mUpperBound;
    private int mLowerBound;
    private int mHeight;
    private int mWidth;
    private GestureDetector mGestureDetector;
    private static final int SLIDE = 1;
    private Rect mTempRect = new Rect();
    private final int mTouchSlop;
    private int mItemHeightNormal;
    private int mItemWidthNormal;
    private int mItemHeightExpanded;
    private int mItemHeightHalf;
    private int mSwitchHeight;
    private int mSwitchWidth;
    private int mSwitchXOffset;
    private int mSwitchYOffset;
    private boolean mDragBegin = false;

    public TouchInterceptor(Context context, AttributeSet attrs) {
        super(context, attrs);
        mTouchSlop = ViewConfiguration.get(context).getScaledTouchSlop();
        if(mGestureDetector == null){
            mGestureDetector = new GestureDetector(getContext(), new SimpleOnGestureListener() {
                @Override
                public boolean onFling(MotionEvent e1, MotionEvent e2, float velocityX, float velocityY) {
                    Log.e(TAG,"###################e1 = " + e1 + "   e2" + e2 + "velocityX = " + velocityX + "velocityY = " + velocityY);
                    if (mDragView != null) {
                        if (velocityX > 1000) {
                            Rect r = mTempRect;
                            mDragView.getDrawingRect(r);
                            if ( e2.getX() > r.right * 2 / 3) {
                                // fast fling right with release near the right edge of the screen
                                stopDragging();
                                unExpandViews(true);
                            }
                        }
                        // flinging while dragging should have no effect
                        return true;
                    }
                    return false;
                }
            });
        }
    }


    private void getItemDimension(){
        if(mSwitchYOffset != 0){
            return ;
        }
        mHeight = getHeight();
        mWidth = getWidth();
        ListAdapter listAdapter = getAdapter();

        if(listAdapter != null) {
            View listItem = listAdapter.getView(0, null, this);
            if (listItem != null && listItem.getVisibility() == View.VISIBLE) {
                Switch sh = (Switch) listItem.findViewById(R.id.switch1);
                listItem.measure(0, 0);
                mItemHeightNormal = listItem.getMeasuredHeight();
                mItemWidthNormal = listItem.getMeasuredWidth();
                mItemHeightHalf = mItemHeightNormal / 2;
                mItemHeightExpanded = mItemHeightNormal + 30;
                sh.measure(0, 0);
                mSwitchHeight = sh.getMeasuredHeight();
                mSwitchWidth = sh.getMeasuredWidth();
                mSwitchXOffset = mWidth - mSwitchWidth;
                //please fix me mSwitchXOffset always return 0
                //mSwitchXOffset = sh.getTop();
                //mSwitchYOffset = sh.getLeft();
                Log.e(TAG, "mItemWidthNormal =" + mItemWidthNormal + "mSwitch === " + mSwitchHeight + "x" + mSwitchWidth + "  offset  " + mSwitchXOffset + "," + mSwitchYOffset);
            }
        }
    }

    @Override
    public boolean onInterceptTouchEvent(MotionEvent ev) {
        int ex = (int) ev.getX();
        int ey = (int) ev.getY();

        Log.e(TAG,"onInterceptTouchEvent = " + ex + "," + ey);

       /*
        int itemNo = AdapterView.INVALID_POSITION;
        ListAdapter listAdapter = getAdapter();
                pointToPosition(ex, ey);
        if (itemNo == AdapterView.INVALID_POSITION) {
            Log.e(TAG,"onInterceptTouchEvent listItem == null xxxxxxxxxxxxx");
            return super.onInterceptTouchEvent(ev);
        }else{

        }
        */
        getItemDimension();

        switch (ev.getAction()) {
            case MotionEvent.ACTION_UP: {
                if (mDragBegin) {
                    int itemNo = 0;
                    mDragBegin = false;
                    int x = (int) ev.getX();
                    int y = (int) ev.getY();
                    itemNo = getItemForPosition(y);
                    if (mDragListener != null) {
                        mDragListener.drag(mDragPos, itemNo);
                    }
                    mDragPos = itemNo;
                    doExpansion();
                    stopDragging();
                    unExpandViews(true);
                    return false;
                } else {
                    break;
                }
            }
            case MotionEvent.ACTION_MOVE: {
                if(mDragBegin) {
                    if(ey < 0){
                        int itemNo = 0;
                        itemNo= getItemForPosition(0);
                        Log.e(TAG,"itemnum ==================" + itemNo);
                        if (mDragListener != null) {
                            mDragListener.drag(mDragPos, itemNo);
                        }
                        mDragPos = itemNo;
                        doExpansion();
                        stopDragging();
                        unExpandViews(true);
                    }else if(ey > mHeight){
                        int itemNo = 0;
                        itemNo = getItemForPosition(mHeight);
                        Log.e(TAG,"itemnum ==================" + itemNo);
                        if (mDragListener != null) {
                            mDragListener.drag(mDragPos,itemNo);
                        }
                        mDragPos = itemNo;
                        doExpansion();
                        stopDragging();
                        unExpandViews(true);
                    }else {
                        dragView(ex, ey);
                        doExpansion();
                    }
                    return false;
                }else{
                   break;
                }
            }
            case MotionEvent.ACTION_CANCEL:
                if(mDragBegin){
                    mDragBegin = false;
                    Rect r = mTempRect;
                    mDragView.getDrawingRect(r);
                    stopDragging();
                    unExpandViews(false);
                    return false;
                }
                break;
            case MotionEvent.ACTION_DOWN: {
                int itemNo = 0;
                itemNo = pointToPosition(ex,ey);
                if (itemNo == AdapterView.INVALID_POSITION) {
                    return super.onInterceptTouchEvent(ev);
                }else {
                    if (ex < mSwitchXOffset) {
                        Log.e(TAG, "#######getFirstVisiblePosition = " + getFirstVisiblePosition());
                        mDragBegin = true;
                        ViewGroup item = (ViewGroup) getChildAt(itemNo - getFirstVisiblePosition());
                        mDragPointX = ex - item.getLeft();
                        mDragPointY = ey - item.getTop();
                        Log.e(TAG, "x = " + ex + " y = " + ey + "ev.getRawX() = " + ev.getRawX() + "ev.getRawY() = "
                                + ev.getRawY() + "item.getLeft() = " + item.getLeft() + "item.getTop() = " + item.getTop());

                        mXOffset = ((int) ev.getRawX()) - ex;
                        mYOffset = ((int) ev.getRawY()) - ey;
                        Log.e(TAG, "mDragPointX = " + mDragPointX + "mDragPointY  = " + mDragPointY + "mXOffset =  " + mXOffset + "mYOffset = " + mYOffset);

                        // The left side of the item is the grabber for dragging the item
                        item.setDrawingCacheEnabled(true);
                        // Create a copy of the drawing cache so that it does not get recycled
                        // by the framework when the list tries to clean up memory
                        Bitmap bitmap = Bitmap.createBitmap(item.getDrawingCache());
                        startDragging(bitmap, ex, ey);
                        mDragPos = itemNo;
                        mSrcDragPos = mDragPos;
                        int touchSlop = mTouchSlop;
                        mUpperBound = Math.min(ey - touchSlop, mHeight / 3);
                        mLowerBound = Math.max(ey + touchSlop, mHeight * 2 / 3);
                        return false;
                    } else {
                        break;
                    }
                }
            }
            default:
                break;
        };
        return super.onInterceptTouchEvent(ev);
    }


    /*
     * pointToPosition() doesn't consider invisible views, but we
     * need to, so implement a slightly different version.
     */
    private int myPointToPosition(int x, int y) {

        if (y < 0) {
            // when dragging off the top of the screen, calculate position
            // by going back from a visible item
            int pos = myPointToPosition(x, y + mItemHeightNormal);
            if (pos > 0) {
                return pos - 1;
            }
        }

        Rect frame = mTempRect;
        final int count = getChildCount();
        for (int i = count - 1; i >= 0; i--) {
            final View child = getChildAt(i);
            child.getHitRect(frame);
            if (frame.contains(x, y)) {
                return getFirstVisiblePosition() + i;
            }
        }
        return INVALID_POSITION;
    }

    private int getItemForPosition(int y) {
        int adjustedy = y - mDragPointY - mItemHeightHalf;
        int pos = myPointToPosition(0, adjustedy);
        if (pos >= 0) {
            if (pos <= mSrcDragPos) {
                pos += 1;
            }
        } else if (adjustedy < 0) {
            // this shouldn't happen anymore now that myPointToPosition deals
            // with this situation
            pos = 0;
        }
        return pos;
    }

    private void adjustScrollBounds(int y) {
        if (y >= mHeight / 3) {
            mUpperBound = mHeight / 3;
        }
        if (y <= mHeight * 2 / 3) {
            mLowerBound = mHeight * 2 / 3;
        }
        Log.e(TAG,"adjustScrollBounds " + "mUpperBound = " + mUpperBound + "mLowerBound =" + mLowerBound  );
    }

    /*
     * Restore size and visibility for all listitems
     */
    private void unExpandViews(boolean deletion) {
        for (int i = 0;; i++) {
            View v = getChildAt(i);
            if (v == null) {
                if (deletion) {
                    // HACK force update of mItemCount
                    int position = getFirstVisiblePosition();
                    int y = getChildAt(0).getTop();
                    setAdapter(getAdapter());
                    setSelectionFromTop(position, y);
                    // end hack
                }
                try {
                    layoutChildren(); // force children to be recreated where needed
                    v = getChildAt(i);
                } catch (IllegalStateException ex) {
                    // layoutChildren throws this sometimes, presumably because we're
                    // in the process of being torn down but are still getting touch
                    // events
                }
                if (v == null) {
                    return;
                }
            }
            ViewGroup.LayoutParams params = v.getLayoutParams();
            params.height = mItemHeightNormal;
            v.setLayoutParams(params);
            v.setVisibility(View.VISIBLE);
        }
    }

    /* Adjust visibility and size to make it appear as though
     * an item is being dragged around and other items are making
     * room for it:
     * If dropping the item would result in it still being in the
     * same place, then make the dragged listitem's size normal,
     * but make the item invisible.
     * Otherwise, if the dragged listitem is still on screen, make
     * it as small as possible and expand the item below the insert
     * point.
     * If the dragged item is not on screen, only expand the item
     * below the current insertpoint.
     */
    private void doExpansion() {
        int childnum = mDragPos - getFirstVisiblePosition();

        if (mDragPos > mSrcDragPos) {
            childnum++;
        }
        int numheaders = getHeaderViewsCount();

        Log.e(TAG,"doExpansion mDragPos = " + mDragPos  + "mSrcDragPos =" +  mSrcDragPos + "numheaders = " + numheaders + "childnum = " + childnum);

        View first = getChildAt(mSrcDragPos - getFirstVisiblePosition());
        for (int i = 0;; i++) {
            View vv = getChildAt(i);
            if (vv == null) {
                break;
            }

            int height = mItemHeightNormal;
            int visibility = View.VISIBLE;
            if (mDragPos < numheaders && i == numheaders) {
                // dragging on top of the header item, so adjust the item below
                // instead
                if (vv.equals(first)) {
                    visibility = View.INVISIBLE;
                } else {
                    height = mItemHeightExpanded;
                }
            } else if (vv.equals(first)) {
                // processing the item that is being dragged
                if (mDragPos == mSrcDragPos || getPositionForView(vv) == getCount() - 1) {
                    // hovering over the original location
                    visibility = View.INVISIBLE;
                } else {
                    // not hovering over it
                    // Ideally the item would be completely gone, but neither
                    // setting its size to 0 nor settings visibility to GONE
                    // has the desired effect.
                    height = 1;
                }
            } else if (i == childnum) {
                if (mDragPos >= numheaders && mDragPos < getCount() - 1) {
                    height = mItemHeightExpanded;
                }
            }
            ViewGroup.LayoutParams params = vv.getLayoutParams();
            params.height = height;
            vv.setLayoutParams(params);
            vv.setVisibility(visibility);
        }
    }

    private void startDragging(Bitmap bm, int x, int y) {
        stopDragging();

        mWindowParams = new WindowManager.LayoutParams();
        mWindowParams.gravity = Gravity.TOP | Gravity.LEFT;
        mWindowParams.x = x - mDragPointX + mXOffset;
        mWindowParams.y = y - mDragPointY + mYOffset;

        mWindowParams.height = WindowManager.LayoutParams.WRAP_CONTENT;
        mWindowParams.width = WindowManager.LayoutParams.WRAP_CONTENT;
        mWindowParams.flags = WindowManager.LayoutParams.FLAG_NOT_FOCUSABLE
                | WindowManager.LayoutParams.FLAG_NOT_TOUCHABLE
                | WindowManager.LayoutParams.FLAG_KEEP_SCREEN_ON
                | WindowManager.LayoutParams.FLAG_LAYOUT_IN_SCREEN
                | WindowManager.LayoutParams.FLAG_LAYOUT_NO_LIMITS;
        mWindowParams.format = PixelFormat.TRANSLUCENT;
        mWindowParams.windowAnimations = 0;

        Context context = getContext();
        ImageView v = new ImageView(context);
        int backGroundColor = context.getResources().getColor(R.color.dragndrop_background);
        v.setBackgroundColor(backGroundColor);
        v.setBackgroundResource(R.drawable.playlist_tile_drag);
        v.setPadding(0, 0, 0, 0);
        v.setImageBitmap(bm);
        mDragBitmap = bm;
        mWindowManager = (WindowManager)context.getSystemService(Context.WINDOW_SERVICE);
        mWindowManager.addView(v, mWindowParams);
        mDragView = v;
    }

    private void dragView(int x, int y) {
        if(mDragView != null) {
            float alpha = 1.0f;
            int width = mDragView.getWidth();
            if (x > width / 2) {
                alpha = ((float) (width - x)) / (width / 2);
            }
            mWindowParams.alpha = alpha;
            mWindowParams.x = 0;

            mWindowParams.y = y - mDragPointY + mYOffset;
            mWindowManager.updateViewLayout(mDragView, mWindowParams);
        }
    }

    private void stopDragging() {
        if (mDragView != null) {
            mDragView.setVisibility(GONE);
            WindowManager wm = (WindowManager)getContext().getSystemService(Context.WINDOW_SERVICE);
            wm.removeView(mDragView);
            mDragView.setImageDrawable(null);
            mDragView = null;
        }
        if (mDragBitmap != null) {
            mDragBitmap.recycle();
            mDragBitmap = null;
        }
    }

    public void setDragListener(DragListener l) {
        mDragListener = l;
    }

    public interface DragListener {
        void drag(int from, int to);
    }
}


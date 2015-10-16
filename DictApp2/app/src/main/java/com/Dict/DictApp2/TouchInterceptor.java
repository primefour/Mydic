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
    private GestureDetector mGestureDetector;
    private static final int SLIDE = 1;
    private Rect mTempRect = new Rect();
    private final int mTouchSlop;
    private int mItemHeightNormal;
    private int mItemHeightExpanded;
    private int mItemHeightHalf;

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
/*
        Resources res = getResources();
        int w = View.MeasureSpec.makeMeasureSpec(0,
                View.MeasureSpec.UNSPECIFIED);
        int h = View.MeasureSpec.makeMeasureSpec(0,
                View.MeasureSpec.UNSPECIFIED);
        imageView.measure(w, h);
        int height = imageView.getMeasuredHeight();
        int width = imageView.getMeasuredWidth();
        */
    }

    @Override
    public boolean onInterceptTouchEvent(MotionEvent ev) {
        Log.e(TAG,"onInterceptTouchEvent" );

        switch (ev.getAction()) {
            case MotionEvent.ACTION_UP: {
                int x = (int) ev.getX();
                int y = (int) ev.getY();
                int itemnum = getItemForPosition(y);
                if (mDragListener != null) {
                    mDragListener.drag(mDragPos, itemnum);
                }
                mDragPos = itemnum;
                doExpansion();
                stopDragging();
                unExpandViews(true);
            }
            return false;
            case MotionEvent.ACTION_MOVE: {
                int x = (int) ev.getX();
                int y = (int) ev.getY();

                if(y < 0 ){
                    int itemnum = getItemForPosition(0);
                    Log.e(TAG,"itemnum ==================" + itemnum );
                    if (mDragListener != null) {
                        mDragListener.drag(mDragPos, itemnum);
                    }
                    mDragPos = itemnum;
                    doExpansion();
                    stopDragging();
                    unExpandViews(true);
                    return true;
                }else if(y > mHeight){
                    int itemnum = getItemForPosition(mHeight);
                    Log.e(TAG,"itemnum ==================" + itemnum );
                    if (mDragListener != null) {
                        mDragListener.drag(mDragPos, itemnum);
                    }
                    mDragPos = itemnum;
                    doExpansion();
                    stopDragging();
                    unExpandViews(true);
                    return true;
                }else {
                    dragView(x, y);
                    int itemnum = getItemForPosition(y);
                    doExpansion();
                    Log.e(TAG, "x = " + x + "y = " + y);
                    /*
                    if (itemnum >= 0) {
                        int speed = 0;
                        adjustScrollBounds(y);
                        if (y > mLowerBound) {
                            // scroll the list up a bit
                            if (getLastVisiblePosition() < getCount() - 1) {
                                speed = y > (mHeight + mLowerBound) / 2 ? 16 : 4;
                            } else {
                                speed = 1;
                            }
                        } else if (y < mUpperBound) {
                            // scroll the list down a bit
                            speed = y < mUpperBound / 2 ? -16 : -4;
                            if (getFirstVisiblePosition() == 0
                                    && getChildAt(0).getTop() >= getPaddingTop()) {
                                // if we're already at the top, don't try to scroll, because
                                // it causes the framework to do some extra drawing that messes
                                // up our animation
                                speed = 0;
                            }
                        }
                        if (speed != 0) {
                            smoothScrollBy(speed, 30);
                        }
                    }
                    */
                }
            }
            return false;
            case MotionEvent.ACTION_CANCEL:
                Rect r = mTempRect;
                mDragView.getDrawingRect(r);
                stopDragging();
                unExpandViews(false);
                break;
            case MotionEvent.ACTION_DOWN: {
                ListAdapter listAdapter = getAdapter();
                if(listAdapter == null){
                    mItemHeightNormal = 260;
                    mItemHeightHalf = mItemHeightNormal / 2;
                    mItemHeightExpanded = 370;
                }else {
                    View listItem = listAdapter.getView(0, null,this);
                    listItem.measure(0, 0);
                    mItemHeightNormal = listItem.getMeasuredHeight();
                    mItemHeightHalf = mItemHeightNormal / 2;
                    mItemHeightExpanded = mItemHeightNormal + 30;
                }
                Log.e(TAG,"mItemHeightNormal = " + mItemHeightNormal );

                int x = (int) ev.getX();
                int y = (int) ev.getY();
                int itemnum = pointToPosition(x, y);
                Log.e(TAG, "itemnum  = " + itemnum);
                if (itemnum == AdapterView.INVALID_POSITION) {
                    break;
                }
                Log.e(TAG, "#######getFirstVisiblePosition = " + getFirstVisiblePosition());

                ViewGroup item = (ViewGroup) getChildAt(itemnum - getFirstVisiblePosition());

                mDragPointX = x - item.getLeft();
                mDragPointY = y - item.getTop();
                Log.e(TAG, "x = " + x + " y = " + y + "ev.getRawX() = " + ev.getRawX() + "ev.getRawY() = " + ev.getRawY());

                mXOffset = ((int) ev.getRawX()) - x;
                mYOffset = ((int) ev.getRawY()) - y;

                Log.e(TAG, "mDragPointX = " + mDragPointX + "mDragPointY  = " + mDragPointY + "mXOffset =  " + mXOffset + "mYOffset = " + mYOffset);

                // The left side of the item is the grabber for dragging the item
                item.setDrawingCacheEnabled(true);
                // Create a copy of the drawing cache so that it does not get recycled
                // by the framework when the list tries to clean up memory
                Bitmap bitmap = Bitmap.createBitmap(item.getDrawingCache());
                startDragging(bitmap, x, y);
                mDragPos = itemnum;
                mSrcDragPos = mDragPos;
                mHeight = getHeight();
                int touchSlop = mTouchSlop;
                mUpperBound = Math.min(y - touchSlop, mHeight / 3);
                mLowerBound = Math.max(y + touchSlop, mHeight * 2 / 3);
                Log.e(TAG, "mHeight =  " + mHeight + "mTouchSlop = " + mTouchSlop + "mUpperBound = " + mUpperBound + "mLowerBound = " + mLowerBound);
            }
            return false;
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


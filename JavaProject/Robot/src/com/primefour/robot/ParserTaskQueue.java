package com.primefour.robot;
import java.io.IOException;
import java.io.InputStream;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Set;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class ParserTaskQueue {
	private static final int THREAD_COUNT = 10;
	private static ArrayList<QueueItem>mISList = new ArrayList<QueueItem>();
	private static ReadWriteLock mlock = new ReentrantReadWriteLock(false);
	private static Condition mCond = mlock.writeLock().newCondition();
	private static ThreadPool mPool = new ThreadPool("ParserTaskQueue",THREAD_COUNT);
	
	
	ParserTaskQueue(){
		int count = THREAD_COUNT;
		while(count-- > 0){
			mPool.commitTask(new ParserTask());
		}
	}
	
	class ParserTask implements Runnable{

		@Override
		public void run() {
			// TODO Auto-generated method stub
			QueueItem qi = null;
			do {
				mlock.writeLock().lock(); 
				while(mISList.isEmpty()){
					try {
						mCond.await();
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} 
				}
				qi = mISList.remove(0);
				mlock.writeLock().unlock(); 
				HtmlPage ihp = new HtmlPage(qi.mIs,qi.mUrl);
				//insert link to crawler task
				HashMap<String,HtmlHRef> tmpRef = ihp.getHRef();
				Set<String> it = tmpRef.keySet();
				for(String em :it){
					HtmlHRef item = tmpRef.get(em);
					CrawlerTaskQueue.enqTask(item.getBaseUrl(),item.getContent());
				}
				//insert hp to write queue
				WriteTaskQueue.enqTask(ihp);
			}while(true);
		}
	};
	
	public static void enqTask(InputStream is,String Url){
		mlock.writeLock().lock();
		mISList.add(new QueueItem(is,Url));
		mCond.signalAll(); 
		mlock.writeLock().unlock();
	}

};

class QueueItem{
	public InputStream mIs;
	public String mUrl;
	public QueueItem(InputStream is,String url){
		mIs = is;
		mUrl = url;
	}
};

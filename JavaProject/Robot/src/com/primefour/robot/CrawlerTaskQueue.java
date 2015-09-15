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

class ReqInfo{
	String mTitle;
	CookieUtility mCookie;
	String mSession;
};

public class CrawlerTaskQueue {
	private static final int THREAD_COUNT = 10;
	private static ArrayList<String> mUrlList = new ArrayList<String>();
	private static HashMap<String,ReqInfo>mUrlSet = new HashMap<String,ReqInfo>();
	private static ReadWriteLock mlock = new ReentrantReadWriteLock(false);  
	private static Condition mCond = mlock.writeLock().newCondition();
	private static ThreadPool mPool = new ThreadPool("WriteTaskQueue",THREAD_COUNT);
	private static CookieUtility mCookieSet = new CookieUtility();
	private String mBaseUrl; 
	
	CrawlerTaskQueue(String baseUrl){
		mBaseUrl = baseUrl;
		int count = THREAD_COUNT;
		while(count-- > 0){
			mPool.commitTask(new CrawlerTask());
		}
	}
	
	class CrawlerTask implements Runnable{

		@Override
		public void run() {
			// TODO Auto-generated method stub
			String url = null;
			do {
				mlock.writeLock().lock(); 
				while(mUrlList.isEmpty()){
					try {
						//System.out.println("Enter wait state");
						mCond.await();
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} 
				}
				url = mUrlList.remove(0);
				mlock.writeLock().unlock(); 
				
				//System.out.println("crawler do with " + url);
				try {
					URL request = new URL(url);
					HttpURLConnection conn = (HttpURLConnection) request.openConnection();
					mCookieSet.loadCookies(conn); 
					mCookieSet.loadCookies(conn); 
					conn.setConnectTimeout(1000);
					conn.setReadTimeout(1000);
					InputStream is = conn.getInputStream();
					//deliver this input stream to  Parser Task
					ParserTaskQueue.enqTask(is, url);
					
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}while(true);
		}
	};
	
	public static String getFileTitle(String url){
		return mUrlSet.get(url).mTitle;
	}
	
	public static void enqTask(String url,String title){
		mlock.readLock().lock(); 
		if(mUrlSet.containsKey(url)){
			mlock.readLock().unlock(); 
			return ;
		}
		mlock.readLock().unlock(); 
		
		mlock.writeLock().lock();
		ReqInfo obj = new ReqInfo();
		obj.mTitle = title;
		mUrlSet.put(url,obj);
		mUrlList.add(url);
		mCond.signalAll(); 
		mlock.writeLock().unlock();
	}
}

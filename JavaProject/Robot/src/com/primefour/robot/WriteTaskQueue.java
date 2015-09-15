package com.primefour.robot;

import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.Set;
import java.util.concurrent.atomic.AtomicLong;
import java.util.concurrent.locks.Condition;
import java.util.concurrent.locks.ReadWriteLock;
import java.util.concurrent.locks.ReentrantReadWriteLock;

public class WriteTaskQueue {
	private static final int THREAD_COUNT = 10;
	private static ArrayList<HtmlPage> mHPList = new ArrayList<HtmlPage>();
	private static ReadWriteLock mlock = new ReentrantReadWriteLock(false);
	private static Condition mCond = mlock.writeLock().newCondition();
	private static ThreadPool mPool = new ThreadPool("ParserTaskQueue",THREAD_COUNT);
	private static long mIdx = 0;
	
	WriteTaskQueue(){
		int count = THREAD_COUNT;
		while(count-- > 0){
			mPool.commitTask(new WriteTask());
		}
	}
	
	class WriteTask implements Runnable{

		@Override
		public void run() {
			// TODO Auto-generated method stub
			HtmlPage hp = null;
			do {
				mlock.writeLock().lock(); 
				while(mHPList.isEmpty()){
					try {
						mCond.await();
					} catch (InterruptedException e) {
						// TODO Auto-generated catch block
						e.printStackTrace();
					} 
				}
				hp = mHPList.remove(0);
				mIdx ++;
				mlock.writeLock().unlock(); 
				String fileName = null;
				FileOutputStream aa;
				try {
					if(hp.getBaseUrl() != null){
						fileName = CrawlerTaskQueue.getFileTitle(hp.getBaseUrl());
					}
					
					if(fileName != null){
						fileName = fileName + ".txt";
					}else{
						fileName = "crawlerFile"  + mIdx + ".txt";
					}
					
					System.out.println("Write queue" + hp.getBaseUrl() + "===>" + fileName + mIdx);
					aa = new FileOutputStream(fileName);
					aa.write(hp.toString().getBytes());
				} catch (FileNotFoundException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				} catch (IOException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			}while(true);
		}
	};
	
	
	public static void enqTask(HtmlPage hp){
		mlock.writeLock().lock();
		mHPList.add(hp);
		mCond.signalAll();
		mlock.writeLock().unlock();
	}
	
}

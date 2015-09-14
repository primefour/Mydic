package com.primefour.robot;

import java.util.concurrent.ExecutorService;
import java.util.concurrent.Executors;

public class ThreadPool {
	private String mName ;
	private int mThreadCount;
	ExecutorService mPool;
	public ThreadPool(String name,int count){
		 mPool = Executors.newFixedThreadPool(count);
	}
	
	public void commitTask(Runnable task){
		mPool.submit(task);
	}
}

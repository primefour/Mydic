package com.primefour.robot;

public class SimpleWebServer {
	
	public static void main(String argv[]) {
		System.out.println("Hello world!");
		/*DigestThread dt = new DigestThread("Hello.txt");
		dt.start();
		*/
		/*
		CrawlerTaskQueue crawler = new CrawlerTaskQueue("http://news.sina.com.cn/");
		
		System.out.println("World start 1");
		ParserTaskQueue parser = new ParserTaskQueue();
		
		System.out.println("World start 2");
		WriteTaskQueue writer = new WriteTaskQueue();
		
		System.out.println("World start 3");
		crawler.enqTask("http://news.sina.com.cn/","news.sina");
		System.out.println("World start 4");
		
		try {
			Thread.sleep(100000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		System.out.println("World start 5");
		*/
		// auto commit order at amazon website
		AmazonJPOrder order = new AmazonJPOrder();
		//order.searchProduct("pen");
		order.connectHttp("http://www.amazon.com");
		order.searchProduct(null);
	}

}

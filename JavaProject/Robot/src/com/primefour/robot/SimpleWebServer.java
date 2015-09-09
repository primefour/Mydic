package com.primefour.robot;

public class SimpleWebServer {
	
	public static void main(String argv[]){
		System.out.println("Hello world!");
		DigestThread dt = new DigestThread("Hello.txt");
		dt.start();
	}

}
